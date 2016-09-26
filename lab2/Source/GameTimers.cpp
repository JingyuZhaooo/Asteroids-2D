#include "GameTimers.h"

GameTimerManager::GameTimerManager()
	:mNextTimerId(0)
	,mAreTimersTicking(false)
{

}

void GameTimerManager::Tick(float deltaTime)
{
	mAreTimersTicking = true;
	for (auto &i : mActiveTimers)
	{
		if (i.second.mStatus == Active)
		{
			i.second.mRemainingTime -= deltaTime;
		}
		if (i.second.mRemainingTime <= 0.0f)
		{
			i.second.mDelegate->Execute();
			if (i.second.mIsLooping == true)
			{
				i.second.mRemainingTime = i.second.mDuration;
			}
			else
			{
				i.second.mStatus = Cleared;
				mClearedTimers.push_back(i.second.mHandle);
			}
		}
	}
	for (auto &i : mClearedTimers)
	{
		auto iter = mActiveTimers.find(i);
		if (iter != mActiveTimers.end())
		{
			RemoveFromObjMap(iter->second.mObj, iter->second.mHandle);
			mActiveTimers.erase(iter);
		}
	}
	mClearedTimers.clear();
	for (auto &i : mPendingTimers)
	{
		i.second.mStatus = Active;
		mActiveTimers.emplace(i.first, i.second);
	}
	mPendingTimers.clear();
	mAreTimersTicking = false;
}

void GameTimerManager::ClearTimer(const TimerHandle& handle)
{
	// Is this pending?
	auto iter = mPendingTimers.find(handle);
	if (iter != mPendingTimers.end())
	{
		// We can just remove this from pending timers
		RemoveFromObjMap(iter->second.mObj, handle);
		mPendingTimers.erase(iter);
	}
	else
	{
		iter = mActiveTimers.find(handle);
		if (iter != mActiveTimers.end())
		{
			iter->second.mStatus = Cleared;
			mClearedTimers.push_back(handle);
		}
	}
}

void GameTimerManager::PauseTimer(const TimerHandle& handle)
{
	// Is this pending?
	auto iter = mPendingTimers.find(handle);
	if (iter != mPendingTimers.end())
	{
		iter->second.mStatus = Paused;
	}
	else
	{
		iter = mActiveTimers.find(handle);
		if (iter != mActiveTimers.end())
		{
			iter->second.mStatus = Paused;
		}
	}
}

void GameTimerManager::UnpauseTimer(const TimerHandle& handle)
{
	// Is this pending?
	auto iter = mPendingTimers.find(handle);
	if (iter != mPendingTimers.end())
	{
		iter->second.mStatus = Pending;
	}
	else
	{
		iter = mActiveTimers.find(handle);
		if (iter != mActiveTimers.end())
		{
			iter->second.mStatus = Active;
		}
	}
}

float GameTimerManager::GetRemainingTime(const TimerHandle& handle)
{
	// Is this pending?
	auto iter = mPendingTimers.find(handle);
	if (iter != mPendingTimers.end())
	{
		return iter->second.mRemainingTime;
	}
	else
	{
		iter = mActiveTimers.find(handle);
		if (iter != mActiveTimers.end())
		{
			return iter->second.mRemainingTime;
		}
	}

	// Unknown timer
	return -1.0f;
}

void GameTimerManager::AddTime(const TimerHandle& handle, float time)
{
	// Is this pending?
	auto iter = mPendingTimers.find(handle);
	if (iter != mPendingTimers.end())
	{
		iter->second.mRemainingTime += time;
	}
	else
	{
		iter = mActiveTimers.find(handle);
		if (iter != mActiveTimers.end())
		{
			iter->second.mRemainingTime += time;
		}
	}
}

void GameTimerManager::ClearAllTimers(Object* obj)
{
	auto iter = mObjToHandlesMap.find(obj);
	if (iter != mObjToHandlesMap.end())
	{
		for (auto& t : iter->second)
		{
			ClearTimer(t);
		}

		mObjToHandlesMap.erase(iter);
	}
}

void GameTimerManager::SetTimerInternal(TimerHandle& outHandle, Object* obj, TimerDelegatePtr delegate, float duration, bool looping)
{
	outHandle.mValue = mNextTimerId;
	TimerInfo timeInfo;
	timeInfo.mObj = obj;
	timeInfo.mDelegate = delegate;
	timeInfo.mDuration = duration;
	timeInfo.mRemainingTime = duration;
	timeInfo.mIsLooping = looping;
	timeInfo.mHandle = outHandle;
	mNextTimerId++;
	if (mAreTimersTicking == false)
	{
		timeInfo.mStatus = Active;
		mActiveTimers.emplace(outHandle, timeInfo);
	}
	else
	{
		timeInfo.mStatus = Pending;
		mPendingTimers.emplace(outHandle, timeInfo);
	}
	AddToObjMap(obj, outHandle);
}

void GameTimerManager::AddToObjMap(Object* obj, const TimerHandle& handle)
{
	auto iter = mObjToHandlesMap.find(obj);
	// Do we already know of this object?
	if (iter != mObjToHandlesMap.end())
	{
		iter->second.emplace(handle);
	}
	else
	{
		std::unordered_set<TimerHandle> temp;
		temp.emplace(handle);
		mObjToHandlesMap.emplace(obj, temp);
	}
}

void GameTimerManager::RemoveFromObjMap(Object* obj, const TimerHandle& handle)
{
	auto iter = mObjToHandlesMap.find(obj);
	if (iter != mObjToHandlesMap.end())
	{
		auto handleIter = iter->second.find(handle);
		if (handleIter != iter->second.end())
		{
			iter->second.erase(handleIter);
		}
	}
}
