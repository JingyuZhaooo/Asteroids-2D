#pragma once
#include "Asset.h"

class Sound : public Asset
{
	DECL_ASSET(Sound, Asset);
public:
	Sound();
	~Sound();
	bool Load(const char* fileName, class AssetCache* cache) override;
private:
	struct Mix_Chunk* mData;
};
DECL_PTR(Sound);