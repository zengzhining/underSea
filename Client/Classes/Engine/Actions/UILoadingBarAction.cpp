#include "UILoadingBarAction.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"
#include "editor-support/cocostudio/CocoStudio.h"

USING_NS_CC;
using namespace cocos2d::ui;

UIProgressTo* UIProgressTo::create(float duration, float percent)
{
	UIProgressTo *progressTo = new (std::nothrow) UIProgressTo();
	progressTo->initWithDuration(duration, percent);
	progressTo->autorelease();

	return progressTo;
}

bool UIProgressTo::initWithDuration(float duration, float percent)
{
	if (ActionInterval::initWithDuration(duration))
	{
		_to = percent;

		return true;
	}

	return false;
}

UIProgressTo* UIProgressTo::clone() const
{
	// no copy constructor    
	auto a = new (std::nothrow) UIProgressTo();
	a->initWithDuration(_duration, _to);
	a->autorelease();
	return a;
}

UIProgressTo* UIProgressTo::reverse() const
{
	CCASSERT(false, "reverse() not supported in UIProgressTo");
	return nullptr;
}

void UIProgressTo::startWithTarget(Node *target)
{
	ActionInterval::startWithTarget(target);
	_from = ((LoadingBar*)(target))->getPercent();
}

void UIProgressTo::update(float time)
{
	((LoadingBar*)(_target))->setPercent(_from + (_to - _from) * time);
}


UILoadingBarProgressFromTo* UILoadingBarProgressFromTo::create(float duration, float fromPercentage, float toPercentage)
{
	UILoadingBarProgressFromTo *progressFromTo = new (std::nothrow) UILoadingBarProgressFromTo();
	progressFromTo->initWithDuration(duration, fromPercentage, toPercentage);
	progressFromTo->autorelease();

	return progressFromTo;
}

bool UILoadingBarProgressFromTo::initWithDuration(float duration, float fromPercentage, float toPercentage)
{
	if (ActionInterval::initWithDuration(duration))
	{
		_to = toPercentage;
		_from = fromPercentage;

		return true;
	}

	return false;
}

UILoadingBarProgressFromTo* UILoadingBarProgressFromTo::clone() const
{
	// no copy constructor    
	auto a = new (std::nothrow) UILoadingBarProgressFromTo();
	a->initWithDuration(_duration, _from, _to);
	a->autorelease();
	return a;
}


UILoadingBarProgressFromTo* UILoadingBarProgressFromTo::reverse() const
{
	return UILoadingBarProgressFromTo::create(_duration, _to, _from);
}

void UILoadingBarProgressFromTo::startWithTarget(Node *target)
{
	ActionInterval::startWithTarget(target);
}

void UILoadingBarProgressFromTo::update(float time)
{
	((LoadingBar*)(_target))->setPercent(_from + (_to - _from) * time);
}