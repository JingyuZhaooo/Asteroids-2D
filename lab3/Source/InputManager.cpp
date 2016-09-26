#include "InputManager.h"
#include <SDL/SDL.h>

void InputManager::HandleKeyPressed(int key)
{
	auto iter = mKeyToActionMap.find(key);
	if (iter != mKeyToActionMap.end())
	{
		if (iter->second->mPressedDelegate != nullptr)
		{
			iter->second->mPressedDelegate->Execute();
		}
		
	}

	auto iter2 = mKeyToAxisMap.find(key);
	if (iter2 != mKeyToAxisMap.end())
	{
		if (iter2->second->mDelegate != nullptr)
		{
			if (iter2->second->mPositiveKey == key)
			{
				iter2->second->mValue += 1.0f;
				iter2->second->mDelegate->Execute(iter2->second->mValue);
			}
			else
			{
				iter2->second->mValue -= 1.0f;
				iter2->second->mDelegate->Execute(iter2->second->mValue);
			}
		}
	}

}

void InputManager::HandleKeyReleased(int key)
{
	auto iter = mKeyToActionMap.find(key);
	if (iter != mKeyToActionMap.end())
	{
		if (iter->second->mReleasedDelegate != nullptr)
		{
			iter->second->mReleasedDelegate->Execute();
		}
	}

	auto iter2 = mKeyToAxisMap.find(key);
	if (iter2 != mKeyToAxisMap.end())
	{
		if (iter2->second->mDelegate != nullptr)
		{
			if (iter2->second->mPositiveKey == key)
			{
				iter2->second->mValue -= 1.0f;
				iter2->second->mDelegate->Execute(iter2->second->mValue);
			}
			else
			{
				iter2->second->mValue += 1.0f;
				iter2->second->mDelegate->Execute(iter2->second->mValue);
			}
		}
	}
}

void InputManager::AddActionMapping(const std::string& name, int key)
{
	ActionMappingPtr ptr = std::make_shared<ActionMapping>();
	ptr->mName = name;
	ptr->mKey = key;
	mNameToActionMap.emplace(name, ptr);
	mKeyToActionMap.emplace(key, ptr);
}

void InputManager::AddAxisMapping(const std::string& name, int positiveKey, int negativeKey)
{
	AxisMappingPtr ptr = std::make_shared<AxisMapping>();
	ptr->mName = name;
	ptr->mPositiveKey = positiveKey;
	ptr->mNegativeKey = negativeKey;
	ptr->mValue = 0;
	mNameToAxisMap.emplace(name, ptr);
	mKeyToAxisMap.emplace(positiveKey, ptr);
	mKeyToAxisMap.emplace(negativeKey, ptr);
}

void InputManager::BindActionInternal(const std::string& name, InputEvent event, ActionDelegatePtr delegate)
{
	auto iter = mNameToActionMap.find(name);
	if (iter != mNameToActionMap.end())
	{
		if (event == IE_Pressed)
		{
			iter->second->mPressedDelegate = delegate;
		}
		else
		{
			iter->second->mReleasedDelegate = delegate;
		}
	}
}

void InputManager::BindAxisInternal(const std::string& name, AxisDelegatePtr delegate)
{
	auto iter = mNameToAxisMap.find(name);
	if (iter != mNameToAxisMap.end())
	{
		iter->second->mDelegate = delegate;
	}
}

Vector2 InputManager::GetMousePos()
{
	int x;
	int y;
	SDL_GetMouseState(&x, &y);
	return Vector2(static_cast<float>(x), static_cast<float>(y));
}