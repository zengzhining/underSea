#ifndef _SCORE__NODE__
#define _SCORE__NODE__
#include "cocos2d.h"
USING_NS_CC;
class ScoreNode : public Node
{
public:
	CREATE_FUNC(ScoreNode);
	bool init();

	void initData();
	void initUI();

	void addBg();
	void addDesUI();
	void addScoreUI();
	void addButton();

	void restart();
	void goBack();
	void goNext();

private:
	Sprite* bg_;
	Sprite* desSp_;
	MenuItemSprite* restartItem_;
	MenuItemSprite* backItem_;
	MenuItemSprite* nextItem_;
};
#endif