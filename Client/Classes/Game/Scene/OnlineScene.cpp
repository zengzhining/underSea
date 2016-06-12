#include "OnlineScene.h"
#include "Game/Data/SocketManager.h"
#include "Game/Object/NetPlayer.h"
#include "Game/Layer/BattleLayer.h"
#include "../Sea.h"
USING_NS_CC;

bool OnlineScene::init()
{
	if (!Scene::init())
		return false;

	bg_ = Sea::createOnlineRoomLayer();
	bg_->setVisible(false);
	addChild(bg_);

	initWidget();
	addEvent();
	return true;
}

void OnlineScene::initWidget()
{
	seedNameItem_ = Sea::createUserNode();
	seedNameItem_->retain();
	
	userList_ = static_cast<ListView*>(bg_->getChildByName("UserList"));

	auto btn = static_cast<Button*>(bg_->getChildByName("Next"));
	btn->addClickEventListener([this](Ref* ref){
		if ((userList_->getItems().size()) >= 2 )
		{
			SocketManager::getInstance()->sendMessage("start", "");
		}
	});

}

void OnlineScene::addEvent()
{
	auto dispatcher = Director::getInstance()->getEventDispatcher();

	auto userInfoListener = EventListenerCustom::create("NotifyUserInfo", [this](EventCustom* eventCus)
	{
		
	});
	dispatcher->addEventListenerWithSceneGraphPriority(userInfoListener, this);

	auto userInListener = EventListenerCustom::create("NotifyNewUserIn", [this](EventCustom* eventCus)
	{
		NetPlayer* data = static_cast<NetPlayer*>(eventCus->getUserData());
		this->addNewUser(data->getName());
	});

	dispatcher->addEventListenerWithSceneGraphPriority(userInListener, this);

	auto userListListener = EventListenerCustom::create("showUserList", [this](EventCustom* eventCus)
	{
		inputPanel_->removeFromParent();
		bg_->setVisible(true);
	});

	dispatcher->addEventListenerWithSceneGraphPriority(userListListener, this);

	auto userInputListener = EventListenerCustom::create("showInputName", [this](EventCustom* eventCus)
	{
		this->addInputNamePanel();
	});

	dispatcher->addEventListenerWithSceneGraphPriority(userInputListener, this);

	auto startListener = EventListenerCustom::create("start", [this](EventCustom* eventCus)
	{
		this->startGame();
	});

	dispatcher->addEventListenerWithSceneGraphPriority(startListener, this);
	
}

void OnlineScene::addInputNamePanel()
{
	inputPanel_ = Sea::createInputNamePanel();
	auto inputText = static_cast<TextField*>(inputPanel_->getChildByName("Bg")->getChildByName("Input"));
	auto btn = static_cast<Button*>(inputPanel_->getChildByName("Bg")->getChildByName("Next"));
	btn->addClickEventListener([inputText](Ref* ref){
		SocketManager::getInstance()->sendMessage("upload name", inputText->getString());
	});
	addChild(inputPanel_);
}

void OnlineScene::startGame()
{
	bg_->removeFromParent();
	auto battleLayer = BattleLayer::create();
	addChild(battleLayer);
}

void OnlineScene::addNewUser(std::string name)
{
	auto nameTitle = static_cast<Layout*>(seedNameItem_->getChildByName("Panel"));
	auto cloneTitle = nameTitle->clone();
	auto nameLb = static_cast<Text*>(cloneTitle->getChildByName("NameLb"));
	nameLb->setString(name);
	userList_->pushBackCustomItem(cloneTitle);
}

void OnlineScene::onEnter()
{
	Scene::onEnter();
	SocketManager::getInstance()->connectServer("ws://localhost:3211");
}

void OnlineScene::onExit()
{
	Scene::onExit();
	seedNameItem_->release();
}