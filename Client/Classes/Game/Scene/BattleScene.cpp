#include "BattleScene.h"
#include "Game/Layer/BattleLayer.h"
USING_NS_CC;
bool BattleScene::init()
{
	if (!GameScene::init())
	{
		return false;
	}

	addChild(BattleLayer::create());

	return true;
}