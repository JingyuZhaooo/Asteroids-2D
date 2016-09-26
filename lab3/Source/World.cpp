#include "World.h"

World::World()
{

}

World::~World()
{

}

void World::AddActor(ActorPtr actor)
{
	mActors.emplace_back(actor);
}

void World::Tick(float deltaTime)
{
	// Tick a copy of the actor pointers, in case any actor adds more actors
	auto actors = mActors;
	for (auto& actor : actors)
	{
		actor->TickInternal(deltaTime);
	}

	// Remove any actors that are dead
	auto iter = mActors.begin();
	while (iter != mActors.end())
	{
		if (!(*iter)->IsAlive())
		{
			(*iter)->EndPlay();
			iter = mActors.erase(iter);
		}
		else
		{
			++iter;
		}
	}
}

void World::RemoveAllActors()
{
	for (auto& actor : mActors)
	{
		actor->EndPlay();
	}
	mActors.clear();
}

void World::RemoveEnemy(Enemy* enemy)
{
	mEnemies.erase(enemy);
}

void World::AddEnemy(Enemy* enemy)
{
	mEnemies.insert(enemy);
}

std::vector<Enemy*> World::GetEnemiesInRange(Vector3 position, float radius)
{
	std::vector<Enemy*> enemiesInRange;
	for (auto enemy : mEnemies)
	{
		float length = (position - enemy->GetWorldTransform().GetTranslation()).Length(); // Get the distance vector3 and then calculate the norm of the vector3
		if (length <= radius)									// if the norm is less than atteack range, then add it to vector
		{
			enemiesInRange.push_back(enemy);
		}
	}
	return enemiesInRange;
}

Enemy* World::GetClosestEnemy(Vector3 position, float radius)
{
	Enemy* closesetEnemy = nullptr;
	float shortestRange = 1000; // initialize it to 1000 so we can narrow down later
	for (auto enemy : mEnemies)
	{
		float length = (position - enemy->GetWorldTransform().GetTranslation()).Length();
		if (length < shortestRange && length <= radius)
		{
			closesetEnemy = enemy;
			shortestRange = length;
		}
	}
	return closesetEnemy;
}
