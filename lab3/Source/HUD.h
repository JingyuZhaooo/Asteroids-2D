#pragma once
#include "Actor.h"
#include "FontComponent.h"

class HUD :public Actor
{
	DECL_ACTOR(HUD, Actor);
public:
	HUD(Game &mGame);
	~HUD();
	void ShowMessage();
	void HideMessage();
	FontComponentPtr GetHitPoint() { return mHitPoint; };
	FontComponentPtr GetMoney() { return mMoney; };
	FontComponentPtr GetStatusMsg() { return mStatusMsg; };
private:
	FontComponentPtr mHitPoint;
	FontComponentPtr mMoney;
	FontComponentPtr mStatusMsg;
};
DECL_PTR(HUD);
