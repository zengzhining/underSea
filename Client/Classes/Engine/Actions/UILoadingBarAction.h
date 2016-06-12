#ifndef __UI_LOADING_BAR_ACTIONS__
#define __UI_LOADING_BAR_ACTIONS__
#include "cocos2d.h"
USING_NS_CC;

class  UIProgressTo : public ActionInterval
{
public:
	/**
	* @brief Create and initializes with a duration and a destination percentage.
	* @param duration Specify the duration of the ProgressTo action. It's a value in seconds.
	* @param percent Specify the destination percentage.
	* @return If the creation success, return a pointer of ProgressTo action; otherwise, return nil.
	*/
	static UIProgressTo* create(float duration, float percent);

	//
	// Overrides
	//
	virtual UIProgressTo* clone() const override;
	virtual UIProgressTo* reverse() const override;
	virtual void startWithTarget(Node *target) override;
	virtual void update(float time) override;

CC_CONSTRUCTOR_ACCESS:
	UIProgressTo() {}
	virtual ~UIProgressTo() {}

	/**
	* @brief Initializes with a duration and destination percentage.
	* @param duration Specify the duration of the ProgressTo action. It's a value in seconds.
	* @param percent Specify the destination percentage.
	* @return If the creation success, return true; otherwise, return false.
	*/
	bool initWithDuration(float duration, float percent);

protected:
	float _to;
	float _from;

private:
	CC_DISALLOW_COPY_AND_ASSIGN(UIProgressTo);
};


class UILoadingBarProgressFromTo : public ActionInterval
{
public:
	/**
	* @brief Create and initializes the action with a duration, a "from" percentage and a "to" percentage.
	* @param duration Specify the duration of the ProgressFromTo action. It's a value in seconds.
	* @param fromPercentage Specify the source percentage.
	* @param toPercentage Specify the destination percentage.
	* @return If the creation success, return a pointer of ProgressFromTo action; otherwise, return nil.
	*/
	static UILoadingBarProgressFromTo* create(float duration, float fromPercentage, float toPercentage);

	//
	// Overrides
	//
	virtual UILoadingBarProgressFromTo* clone() const override;
	virtual UILoadingBarProgressFromTo* reverse() const override;
	virtual void startWithTarget(Node *target) override;
	virtual void update(float time) override;

CC_CONSTRUCTOR_ACCESS:
	UILoadingBarProgressFromTo() {}
	virtual ~UILoadingBarProgressFromTo() {}

	/**
	* @brief Initializes the action with a duration, a "from" percentage and a "to" percentage.
	* @param duration Specify the duration of the ProgressFromTo action. It's a value in seconds.
	* @param fromPercentage Specify the source percentage.
	* @param toPercentage Specify the destination percentage.
	* @return If the creation success, return true; otherwise, return false.
	*/
	bool initWithDuration(float duration, float fromPercentage, float toPercentage);

protected:
	float _to;
	float _from;

private:
	CC_DISALLOW_COPY_AND_ASSIGN(UILoadingBarProgressFromTo);
};

#endif