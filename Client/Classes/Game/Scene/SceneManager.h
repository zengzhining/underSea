#ifndef __SCENE_MANAGER__
#define __SCENE_MANAGER__
#include "cocos2d.h"
USING_NS_CC;
class SceneManager
{
public:
	static Scene* createSelectScene();

	static Scene* createMenuScene();

	static Scene* createBattleScene();

	static Scene* createStoreScene();

	static Scene* createOnlineScene();

};
#endif