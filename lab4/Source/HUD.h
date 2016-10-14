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
	FontComponentPtr GetScore() { return mScore; };
	FontComponentPtr GetTime() { return mTime; };
	FontComponentPtr GetStatusMsg() { return mGameOverMsg; };
private:
	ActorPtr ScoreDel;
	ActorPtr TimeDel;
	ActorPtr GameOverDel;

	FontComponentPtr mScore;
	FontComponentPtr mTime;
	FontComponentPtr mGameOverMsg;
};
DECL_PTR(HUD);
