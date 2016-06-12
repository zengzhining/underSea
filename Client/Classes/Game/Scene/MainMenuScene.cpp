#include "MainMenuScene.h"
#include "SceneManager.h"
#include "../Sea.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"
#include "editor-support/cocostudio/CocoStudio.h"


using namespace cocos2d::ui;

USING_NS_CC;

bool MainMenuScene::init()
{
	if (!Scene::init())
		return false;


	auto size = Director::getInstance()->getVisibleSize();
	mainMenuLayer_ = Layer::create();
	addChild(mainMenuLayer_);

	//添加背景
	auto bg = Sea::createMenuBg();
	mainMenuLayer_->addChild(bg);

	auto singleNode = bg->getChildByName("Single");
	auto twoPlayerNode = bg->getChildByName("TwoPlayers");
	auto storeNode = bg->getChildByName("Store");

	Sea::setMenuItemName(twoPlayerNode, "ONLINE");
	Sea::setMenuItemName(storeNode, "STORE");

	auto singleBtn = static_cast<Button*>(singleNode->getChildByName("Button"));
	singleBtn->addClickEventListener([this](Ref* ref){
		auto scene = SceneManager::createSelectScene();
		Director::getInstance()->replaceScene(scene);
	});
	auto twoPlayerBtn = static_cast<Button*>(twoPlayerNode->getChildByName("Button"));
	twoPlayerBtn->addClickEventListener([this](Ref* ref){
		auto scene = SceneManager::createOnlineScene();
		Director::getInstance()->replaceScene(scene);
	});
	auto storeBtn = static_cast<Button*>(storeNode->getChildByName("Button"));
	storeBtn->addClickEventListener([this](Ref* ref){
		auto scene = SceneManager::createStoreScene();
		Director::getInstance()->pushScene(scene);
	});
	
	// mainMenuLayer_->addChild(menu);
	return true;
}