#include "HUD.h"
#include "Game.h"

IMPL_ACTOR(HUD, Actor);

HUD::HUD(Game &mGame) :Actor(mGame)
{

	ScoreDel = Actor::Spawn(mGame);
	mScore = FontComponent::Create(*ScoreDel);
	AssetCache& mAssetCache = mGame.GetAssetCache();
	FontPtr mFont = mAssetCache.Load<Font>("Fonts/Carlito-Regular.ttf");
	mScore->SetFont(mFont);
	mScore->SetText("Score: 000", Color::Yellow);
	ScoreDel->SetPosition(Vector3(-50, 325, 0));

	TimeDel = Actor::Spawn(mGame);
	mTime = FontComponent::Create(*TimeDel);
	mTime->SetFont(mFont);
	mTime->SetText("Time: 30", Color::LightGreen);
	TimeDel->SetPosition(Vector3(-41, 300, 0));

	GameOverDel = Actor::Spawn(mGame);
	mGameOverMsg = FontComponent::Create(*GameOverDel);
	mGameOverMsg->SetFont(mFont);
	mGameOverMsg->SetText("Game Over!", Color::LightPink);
	GameOverDel->SetPosition(Vector3(-60, 0, 0));
	mGameOverMsg->SetIsVisible(false);
}

HUD::~HUD()
{
	ScoreDel = nullptr;
	TimeDel = nullptr;
	GameOverDel = nullptr;
	mScore = nullptr;
	mTime = nullptr;
	mGameOverMsg = nullptr;
}

void HUD::ShowMessage()
{
	mGameOverMsg->SetIsVisible(true);
	TimerHandle tempTimeHandle;

}