#include "GameMode.h"
#include "Game.h"
#include "SphereCollision.h"
#include "Enemy.h"
#include "CannonTower.h"
#include "FrostTower.h"


IMPL_ACTOR(GameMode, Actor);

const int NUM_COLS = 18;
const int NUM_ROWS = 9;
const float XOFFSET = -425.0f;
const float YOFFSET = 200.0f;

GameMode::GameMode(Game& game)
	:Super(game)
{
	mEnemyCount = 0;
	mWaveCount = 1;
}

void GameMode::BeginPlay()
{
	Super::BeginPlay();

	CreateTiles();

	mGame.GetInput().BindAction("Select", IE_Pressed, this, &GameMode::HandleSelect);
	mGame.GetInput().BindAction("Build CannonTower", IE_Pressed, this, &GameMode::SpawnCanon);
	mGame.GetInput().BindAction("Build FrostTower", IE_Pressed, this, &GameMode::SpawnFrost);
}

void GameMode::EndPlay()
{
	Super::EndPlay();
}

const Vector3& GameMode::GetSpawnPos() const
{
	return mTiles[NUM_ROWS / 2][0]->GetPosition();
}

void GameMode::HandleSelect()
{
	Vector2 mousePos = mGame.GetInput().GetMousePos();
	int x = static_cast<int>(mousePos.x);
	int y = static_cast<int>(mousePos.y);
	
	// Unselect any previous selected tile
	if (mSelectedTile)
	{
		mSelectedTile->SetState(Tile::Default);
	}

	// Convert the mouse position into coordinates of a tile
	// on the grid (using some hacky magic numbers, yeah!!)
	x -= 62;
	y -= 159;

	x /= 50;
	y /= 50;

	if (x >= 0 && y >= 0 &&
		x < NUM_COLS &&
		y < NUM_ROWS)
	{
		mSelectedTile = mTiles[y][x];
		if (mSelectedTile->GetState() == Tile::Default)
		{
			mSelectedTile->SetState(Tile::Selected);
		}
		else
		{
			mSelectedTile.reset();
		}
	}
}

TilePtr GameMode::GetTile(const Vector2& gridPos)
{
	unsigned int x = static_cast<unsigned int>(gridPos.x);
	unsigned int y = static_cast<unsigned int>(gridPos.y);
	return mTiles[x][y];
}

void GameMode::CreateTiles()
{
	// Create tiles!
	
	// Since this is a vector of vectors, we have to first make the row
	// then the inner column vector
	mTiles.resize(NUM_ROWS);
	for (int i = 0; i < NUM_ROWS; i++)
	{
		mTiles[i].resize(NUM_COLS);
	}

	// Now that we have a 2D vector of TilePtrs, we need to actually
	// Spawn the tiles
	for (int i = 0; i < NUM_ROWS; i++)
	{
		for (int j = 0; j < NUM_COLS; j++)
		{
			// Set it's position both in the world space,
			// and then our easy grid position that's used to just index into
			// the array, basically.
			mTiles[i][j] = Tile::Spawn(mGame);
			mTiles[i][j]->SetPosition(Vector3(XOFFSET + j * 50.0f,
				YOFFSET - i * 50.0f, 0.0f));
			mTiles[i][j]->SetGridPos(Vector2(static_cast<float>(i),
				static_cast<float>(j)));
		}
	}

	// Setup which tiles should be red and green
	mTiles[NUM_ROWS / 2 - 1][0]->SetState(Tile::Green);
	mTiles[NUM_ROWS / 2][0]->SetState(Tile::Green);
	mTiles[NUM_ROWS / 2 + 1][0]->SetState(Tile::Green);
	mTiles[NUM_ROWS / 2][1]->SetState(Tile::Green);

	mTiles[NUM_ROWS / 2][NUM_COLS - 1]->SetState(Tile::Red);
	//Add a SphereCollision to the red tile
	mTiles[NUM_ROWS / 2][NUM_COLS - 1]->AddRedSphereCol();
}

void GameMode::SpawnEnemy()
{
	EnemyPtr enemy = Enemy::Spawn(mGame);
	enemy->SetPosition(GetSpawnPos()); // position of the middle tile of the leftmost column
	enemy->SetRotation(0.0);
	enemy->SetScale(1.0f);
	mEnemyCount += 1;
	SpawnNextEnemy();
}

void GameMode::SpawnNextEnemy()
{
	if (mEnemyCount == (mWaveCount * 5)) // summon the first enemy of a new wave
	{
		TimerHandle enemyTimeHandle;
		mWaveCount += 1;
		mEnemyCount = 0;
		mGame.GetGameTimers().SetTimer(enemyTimeHandle, this, &GameMode::SpawnEnemy, 5.0f);
	}
	else								// sommon the next enemy in the current wave
	{
		TimerHandle enemyTimeHandle;
		mGame.GetGameTimers().SetTimer(enemyTimeHandle, this, &GameMode::SpawnEnemy, 1.0f);
	}
}

void GameMode::SpawnCanon()
{
	if (mSelectedTile != nullptr && mSelectedTile->GetTower() == nullptr) // selected tile does not have a tower built
	{
		auto Tower = Tower::SpawnAttached(*mSelectedTile); // create a cannonTower, inherit from the selected Tile
		Tower->SetRotation(0.0f);
		Tower->SetScale(1.0f);
		
		CannonTowerPtr cannonChild = CannonTower::SpawnAttached(*Tower);	// make an actor that encapsulates the cannon mesh
		//cannonChild->SetRotation(Math::PiOver2);
		mSelectedTile->SetTower(cannonChild);
		
		
		cannonChild->FireCannon();
	}
	else	// if the tower is not successfully built, play the error sound
	{
		AssetCache& mAssetCache = mGame.GetAssetCache();
		SoundPtr mErrorSound = mAssetCache.Load<Sound>("Sounds/ErrorSound.wav");
		mAudioComp->PlaySound(mErrorSound);
	}
}

void GameMode::SpawnFrost()
{
	if (mSelectedTile != nullptr && mSelectedTile->GetTower() == nullptr) // selected tile does not have a tower built
	{
		auto Tower = Tower::SpawnAttached(*mSelectedTile); // create a cannonTower, inherit from the selected Tile
		Tower->SetRotation(0.0f);
		Tower->SetScale(1.0f);

		FrostTowerPtr frostChild = FrostTower::SpawnAttached(*Tower);	// make an actor that encapsulates the cannon mesh
		//frostChild->SetRotation(Math::PiOver2);
		mSelectedTile->SetTower(frostChild);
		frostChild->Freeze();
	}
	else	// if the tower is not successfully built, play the error sound
	{
		AssetCache& mAssetCache = mGame.GetAssetCache();
		SoundPtr mErrorSound = mAssetCache.Load<Sound>("Sounds/ErrorSound.wav");
		mAudioComp->PlaySound(mErrorSound);
	}
}