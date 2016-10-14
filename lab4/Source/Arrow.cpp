#include "Arrow.h"
#include "Game.h"

IMPL_ACTOR(Arrow, Actor);

Arrow::Arrow(Game & mGame) : Actor(mGame)
{
	//Set up the mesh
	texture = MeshComponent::Create(*this);
	AssetCache& mAssetCache = mGame.GetAssetCache();
	mMesh = mAssetCache.Load<Mesh>("Meshes/Arrow.itpmesh2");
	texture->SetMesh(mMesh);
}

void Arrow::UpdateWorldPosition()
{
	Vector3 unprojection = mGame.GetRenderer().Unproject(Vector3(0, 150, 0.6));
	SetPosition(unprojection);
}

void Arrow::Tick(float deltaTime)
{
	mCheckpointLocation = mGame.GetGameMode()->GetCheckpoint()->GetPosition(); // update the checkpoint position
	UpdateWorldPosition();
	Vector3 direction = mCheckpointLocation - mPlayer->GetPosition(); //direction vector FROM the ship TO the checkpoint
	direction.Normalize();

	float angle = acos(Dot(Vector3::UnitX, direction));
	Vector3 cross = Cross(Vector3::UnitX, direction);
	cross.Normalize();
	Vector3 rot = Cross(cross, Vector3::UnitX);
	if (rot.x == 0.0f && rot.y == 0.0f && rot.z == 0.0f)
	{
		SetRotation(Quaternion::Identity);
	}
	else
	{
		SetRotation(Quaternion(cross, angle));
	}
}

void Arrow::BeginPlay()
{
	UpdateWorldPosition();
}
