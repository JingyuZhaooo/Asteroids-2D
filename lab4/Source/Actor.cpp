#include "Actor.h"
#include "Game.h"
#include "GameTimers.h"

IMPL_ACTOR(Actor, Object);

Actor::Actor(Game& game)
	:mGame(game)
	, mParent(nullptr)
	, mScale(1.0f)
	, mRotation(Vector3(0.0f, 0.0f, 0.0f), 0)
	, mIsAlive(true)
	, mIsPaused(false)
{

}

Actor::~Actor()
{
	RemoveAllChildren();
	RemoveAllComponents();
	//mGame.GetGameTimers().ClearAllTimers(this);
}

void Actor::BeginPlay()
{

}

void Actor::Tick(float deltaTime)
{

}

void Actor::EndPlay()
{

}

void Actor::BeginTouch(Actor& other)
{

}

void Actor::AddComponent(ComponentPtr component, Component::UpdateType update)
{
	component->Register();
	if (update == Component::PostTick)
	{
		mPostTickComponents.emplace(component);
	}
	else
	{
		mPreTickComponents.emplace(component);
	}
}

void Actor::RemoveComponent(ComponentPtr component)
{
	component->Unregister();

	// This may be pre-tick or post-tick
	auto iter = mPreTickComponents.find(component);
	if (iter != mPreTickComponents.end())
	{
		mPreTickComponents.erase(component);
	}

	iter = mPostTickComponents.find(component);
	if (iter != mPreTickComponents.end())
	{
		mPostTickComponents.erase(component);
	}
}

void Actor::AddChild(ActorPtr child)
{
	mChildren.emplace(child);
	child->mParent = this;
	// Force the child to compute their transform matrix
	child->ComputeWorldTransform();
}

void Actor::RemoveChild(ActorPtr child)
{
	auto iter = mChildren.find(child);
	if (iter != mChildren.end())
	{
		(*iter)->EndPlay();
		mChildren.erase(iter);
	}
	child->mParent = nullptr;
}

Vector3 Actor::GetForward() const
{
	// Following Unreal coordinate system so X is forward
	return mWorldTransform.GetXAxis();
}

void Actor::ComputeWorldTransform()
{
	Matrix4 mMatrix = GetWorldTransform();
	Matrix4 scaleMat = mMatrix.CreateScale(mScale);
	Matrix4 RotationMat = mMatrix.CreateFromQuaternion(mRotation);
	Matrix4 TranslationMat = mMatrix.CreateTranslation(mPosition);
	mWorldTransform = scaleMat * RotationMat * TranslationMat;
	// No parent is the base case
	if (mParent)
	{
		// My transform * Parent's transform
		mWorldTransform *= mParent->GetWorldTransform();
	}
	// Tell my children to recompute their transforms
	for (auto& child : mChildren)
	{
		child->ComputeWorldTransform();
	}
}

void Actor::TickInternal(float deltaTime)
{
	if (mIsPaused == true)
	{
		return;
	}
	for (auto &i : mPreTickComponents)
	{
		i->Tick(deltaTime);
	}
	Tick(deltaTime);
	for (auto &i : mPostTickComponents)
	{
		i->Tick(deltaTime);
	}
	for (auto &i : mChildren)
	{
		i->TickInternal(deltaTime);
	}
}

void Actor::RemoveAllComponents()
{
	// Unregister everything first
	for (auto& comp : mPreTickComponents)
	{
		comp->Unregister();
	}

	for (auto& comp : mPostTickComponents)
	{
		comp->Unregister();
	}

	mPreTickComponents.clear();
	mPostTickComponents.clear();
}

void Actor::RemoveAllChildren()
{
	for (auto& child : mChildren)
	{
		child->EndPlay();
		child->mParent = nullptr;
	}

	mChildren.clear();
}
