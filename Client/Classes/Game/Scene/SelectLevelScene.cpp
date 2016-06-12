#include "SelectLevelScene.h"
#include "SceneManager.h"
#include "../Sea.h"
#include "Game/Data/LevelManager.h"
#include "Game/Data/GameData.h"
#include "Game/Object/Level.h"

#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"
#include "editor-support/cocostudio/CocoStudio.h"


USING_NS_CC;
using namespace cocos2d::ui;

bool SelectLevelScene::init()
{
	if (!Scene::init())
		return false;

	LevelManager::getInstance()->loadLevelInfo();


	auto size = Director::getInstance()->getVisibleSize();
	bgLayer_ = Layer::create();
	addChild(bgLayer_);

	auto bg = Sea::createLevelSelectLayer();
	// bg->setPosition(size.width * 0.50f, size.height * 0.50f);
	bgLayer_->addChild(bg);

	this->initBg(bg);

	return true;
}

void SelectLevelScene::initBg(Node* node)
{
	auto pageView = static_cast<PageView*>(node->getChildByName("PageView"));

	auto pages = pageView->getPages();
	char name[10];
	char levelStr[3];
	int id = 0;
	for (int i = 0; i < pages.size(); i++)
	{
		auto layout = pages.at(i);
		for (int j = 1; j <= 6; j++)
		{
			sprintf(name, "Level%02d", j);
			auto levelNode = layout->getChildByName(name);
			sprintf(levelStr, "%d", j);
			Sea::setLevelNodeName(levelNode, levelStr);

			id = 6 * i + j;
			auto levelInfo = LevelManager::getInstance()->getLevelById(id);
			auto btn =static_cast<Button*>(levelNode->getChildByName("ButtonLevel"));
			btn->addClickEventListener([this, levelInfo,id](Ref* ref){
				if (levelInfo->getState() == Level::LOCK)
				{

				}
				else
				{
					GameData::getInstance()->setLevel(id);
					auto scene = SceneManager::createBattleScene();
					Director::getInstance()->replaceScene(scene);
				}
			});


			Level::State state = levelInfo->getState();
			switch (state)
			{
			case Level::LOCK:
				hideStars(btn);
				btn->getChildByName("Level")->setVisible(false);
				break;
			case Level::ONESTAR:
			case Level::TWOSTAR:
			case Level::ALLSTAR:
				showStars(btn, (int)state);
				btn->getChildByName("Lock")->setVisible(false);
				break;
			case Level::UNLOCK:
				hideStars(btn);
				btn->getChildByName("Lock")->setVisible(false);
				break;

			default:
				break;
			}

		}
	}

	//back btn
	auto backBtn = static_cast<Button*>(node->getChildByName("Back"));
	backBtn->addClickEventListener([](Ref* ref){
		auto scene = SceneManager::createMenuScene();
		Director::getInstance()->replaceScene(scene);
	});

	//store btn
	auto storeBtn = static_cast<Button*>(node->getChildByName("Store"));
	storeBtn->addClickEventListener([](Ref* ref){
		auto scene = SceneManager::createStoreScene();
		Director::getInstance()->pushScene(scene);
	});

}

void SelectLevelScene::showStars(Node* node, int starNum)
{
	char name[12];
	bool list[3][3] = {
		{ false, true, false },
		{ true, false, true },
		{ true, true, true }
	};

	for (int i = 1; i <= 3; i++)
	{
		sprintf(name, "Star%02d", i);
		auto img = node->getChildByName(name);
		img->setVisible(list[starNum-1][i-1]);
	}
}

void SelectLevelScene::hideStars(Node* node)
{
	char name[12];
	for (int i = 1; i <= 3; i++)
	{
		sprintf(name, "Star%02d", i);
		auto img = node->getChildByName(name);
		img->setVisible(false);
	}
}
void SelectLevelScene::updateUI()
{

}