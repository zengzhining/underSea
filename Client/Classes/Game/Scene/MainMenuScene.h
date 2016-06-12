#ifndef _MAIN_MENU_SCENE__
#define _MAIN_MENU_SCENE__
#include "cocos2d.h"
USING_NS_CC;

class MainMenuScene : public Scene
{
public:
	CREATE_FUNC(MainMenuScene);
	bool init();

private:
	Layer* mainMenuLayer_;
	MenuItemLabel* singleItem_;
	MenuItemLabel* twoPlayersItem_;
};
#endif