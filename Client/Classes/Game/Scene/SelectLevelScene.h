#ifndef _SELECT_LEVEL_SCENE__
#define _SELECT_LEVEL_SCENE__
#include "cocos2d.h"
USING_NS_CC;

class SelectLevelScene : public Scene
{
public:
	CREATE_FUNC(SelectLevelScene);
	bool init();
	void initBg(Node* node);

	void updateUI();

	void hideStars(Node* node);
	void showStars(Node* node, int starNum);

private:
	Layer* bgLayer_;
};

#endif