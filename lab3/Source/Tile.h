#pragma once
#include "Actor.h"
#include "MeshComponent.h"
#include "Tower.h"

class Tile : public Actor
{
	DECL_ACTOR(Tile, Actor);
public:
	enum State
	{
		Default,
		Selected,
		Green,
		Red
	};
	
	Tile(Game& game);
	
    // Use this to change the "state" of the tile
    // (You shouldn't have to manually call this)
	void SetState(State state);
	State GetState() const { return mState; }

    // Use this to set/get the grid postiion of the tile
    // (You shouldn't have to call the set function yourself)
	void SetGridPos(const Vector2& pos) { mGridPos = pos; }
	const Vector2& GetGridPos() const { return mGridPos; }

    // Call this function to set/unset a tile on a path
	void SetOnPath(bool value);
	void AddRedSphereCol();
	TowerPtr GetTower() { return mTower; };
	void SetTower(TowerPtr builtTower) { mTower = builtTower; };
private:
    // This is used to track the (x, y) location in the array
    // of tiles that's in GameMode
	Vector2 mGridPos;
    // Mesh component to draw this tile
	MeshComponentPtr mMesh;
    // Used to track the state of the tile, which determines texture
	State mState;
    // Track whether or not this tile is on a path
	bool mIsOnPath;
	TowerPtr mTower;
};

DECL_PTR(Tile);
