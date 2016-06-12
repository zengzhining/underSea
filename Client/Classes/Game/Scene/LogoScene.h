#ifndef __LOGO_SCENE__
#define __LOGO_SCENE__
#include "cocos2d.h"
USING_NS_CC;
class LogoScene : public LayerColor
{
public:
	CREATE_FUNC(LogoScene);
	bool init();

	static Scene* createScene();

	void onEnter() override;
	void onExit() override;

};
#endif