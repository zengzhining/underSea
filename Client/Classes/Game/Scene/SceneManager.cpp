#include "SceneManager.h"
#include "BattleScene.h"
#include "SelectLevelScene.h"
#include "MainMenuScene.h"
#include "StoreScene.h"
#include "OnlineScene.h"
USING_NS_CC;

Scene* SceneManager::createSelectScene()
{
	return SelectLevelScene::create();
}

Scene* SceneManager::createMenuScene()
{
	return MainMenuScene::create();
}

Scene* SceneManager::createBattleScene()
{
	return BattleScene::create();
}

Scene* SceneManager::createStoreScene()
{
	return StoreScene::create();
}

Scene* SceneManager::createOnlineScene()
{
	return OnlineScene::create();
}