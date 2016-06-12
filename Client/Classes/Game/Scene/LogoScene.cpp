#include "LogoScene.h"
#include "SceneManager.h"
#include  "Game/Data/LevelManager.h"

USING_NS_CC;
Scene* LogoScene::createScene()
{
	auto scene = Scene::create();
	auto layer = LogoScene::create();
	scene->addChild(layer);
	return scene;
}

bool LogoScene::init()
{
	if (!LayerColor::initWithColor(Color4B::WHITE))
		return false;

	auto size = Director::getInstance()->getVisibleSize();
	auto title = Label::createWithTTF("Pure Studio", "fonts/Pixel.ttf", 80);
	title->setPosition(size.width / 2, size.height * 2 / 4);
	title->setTextColor(Color4B::BLACK);
	addChild(title);

	return true;
}

void LogoScene::onEnter()
{
	LayerColor::onEnter();

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("GameObject/gameItems.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("GameObject/gameUI.plist");

	//¶ÁÈ¡ÎÄµµ
	LevelManager::getInstance()->loadLevelInfo();

	auto act = Sequence::create(DelayTime::create(3), CallFunc::create([](){
		Director::getInstance()->replaceScene(TransitionFade::create(1, SceneManager::createMenuScene()));
	}), NULL);
	this->runAction(act);
}

void LogoScene::onExit()
{
	LayerColor::onExit();
}