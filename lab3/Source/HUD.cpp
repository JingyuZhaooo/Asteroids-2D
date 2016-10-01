#include "HUD.h"
#include "Game.h"

IMPL_ACTOR(HUD, Actor);

HUD::HUD(Game &mGame) :Actor(mGame)
{

	ActorPtr HitPointDel = Actor::Spawn(mGame);
	mHitPoint = FontComponent::Create(*HitPointDel);
	AssetCache& mAssetCache = mGame.GetAssetCache();
	FontPtr mFont = mAssetCache.Load<Font>("Fonts/Carlito-Regular.ttf");
	mHitPoint->SetFont(mFont);
	mHitPoint->SetText("Base Health: 10", Color::LightGreen);
	HitPointDel->SetPosition(Vector3(-450, -300, 0));

	ActorPtr MoneyDel = Actor::Spawn(mGame);
	mMoney = FontComponent::Create(*MoneyDel);
	mMoney->SetFont(mFont);
	mMoney->SetText("Money: $50", Color::Yellow);
	MoneyDel->SetPosition(Vector3(-450, 300, 0));

	ActorPtr StatusDel = Actor::Spawn(mGame);
	mStatusMsg = FontComponent::Create(*StatusDel);
	mStatusMsg->SetFont(mFont);
	mStatusMsg->SetText("", Color::LightPink);
	StatusDel->SetPosition(Vector3(-100, 0, 0));
	mStatusMsg->SetIsVisible(false);
}

HUD::~HUD()
{
}

void HUD::ShowMessage()
{
	mStatusMsg->SetIsVisible(true);
	TimerHandle tempTimeHandle;
	mGame.GetGameTimers().SetTimer(tempTimeHandle, this, &HUD::HideMessage, 2.0f);

}

void HUD::HideMessage()
{
	mStatusMsg->SetIsVisible(false);
}