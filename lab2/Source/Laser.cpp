#include "Laser.h"
#include "Game.h"
#include "SpriteComponent.h"
#include "SphereCollision.h"
#include "Asteroid.h"
#include "Random.h"

IMPL_ACTOR(Laser, Actor);

Laser::Laser(Game& mGame) : Actor(mGame) // Initializer list
{
	LaserTexture = SpriteComponent::Create(*this);
	AssetCache& mAssetCache = mGame.GetAssetCache();
	TexturePtr tex = mAssetCache.Load<Texture>("Textures/Laser.png");
	LaserTexture->SetTexture(mAssetCache.Load<Texture>("Textures/Laser.png"));
	asteroidDie = mAssetCache.Load<Sound>("Sounds/AsteroidDie.wav");

	moveLaser = MoveComponent::Create(*this, Component::PreTick);
	moveLaser->SetLinearSpeed(600.0f);
	moveLaser->SetLinearAxis(1.0f);
	

	auto coll = SphereCollision::Create(*this); 
	coll->RadiusFromTexture(tex);
	coll->SetScale(0.9f);
}
MoveComponentPtr Laser::getLaser()
{
	return moveLaser;

}
void Laser::Tick(float deltaTime)
{

}

void Laser::OnDieTimer()
{
	SetIsAlive(false);
}

void Laser::BeginTouch(Actor& other)
{
	Super::BeginTouch(other);
	if (IsAlive() == true && IsA<Asteroid>(other))
	{
		SetIsAlive(false);
		other.SetIsAlive(false);
		Vector3 deadAsteroid= other.GetPosition();
		
		collisionSound->PlaySound(asteroidDie);
		if (other.GetScale() == 0.75)
		{
			for (int i = 0; i < 4; i++)
			{
				auto ast = Asteroid::Spawn(mGame);
				ast->SetPosition(deadAsteroid);
				ast->SetScale(0.25f);
		}
		}
	}
}
void Laser::BeginPlay()
{
	TimerHandle handle;
	mGame.GetGameTimers().SetTimer(handle, this, &Laser::OnDieTimer, 1.0f);
}