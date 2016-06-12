#include "StoreScene.h"
#include "Game/Data/ItemManager.h"
#include "Game/Data/GameData.h"
#include "Game/Object/Item.h"
#include "../Sea.h"

USING_NS_CC;
using namespace cocos2d::ui;

bool StoreScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	noticePanel_ = nullptr;
	auto size = Director::getInstance()->getVisibleSize();
	layer_ = Sea::createStoreLayer();
	addChild(layer_);

	auto listView = static_cast<ListView*>(layer_->getChildByName("ItemList"));
	auto storeNode = Sea::createStoreNode();
	itemSeed_ = static_cast<Layout*>(storeNode->getChildByName("Panel"));
	itemSeed_->retain();
	char priceDes[25];
	auto items = ItemManager::getInstance()->getItems();
	for (int i = 0; i < items->size(); i++)
	{
		auto itemInfo = items->at(i);
		auto itemView = itemSeed_->clone();
		auto itemName = static_cast<Text*>(itemView->getChildByName("ItemName"));
		itemName->setString(itemInfo->getName());

		auto itemText = static_cast<Text*>(itemView->getChildByName("ItemDes"));
		itemText->setString(itemInfo->getDes());

		auto itemImg = static_cast<ImageView*>(itemView->getChildByName("ItemImage"));
		itemImg->loadTexture(itemInfo->getTextureName(), TextureResType::PLIST);

		auto itemPriceText = static_cast<Text*>(itemView->getChildByName("ItemPrice"));
		sprintf(priceDes, "%dCoins/%.2f yuan", itemInfo->getNorPrice(), itemInfo->getSpecPrice());
		if (itemInfo->getType() == Item::SHOP)
		{
			sprintf(priceDes, "%.2f yuan", itemInfo->getSpecPrice());
		}
		itemPriceText->setString(priceDes);

		listView->pushBackCustomItem(itemView);
		auto btn = static_cast<Button*>(itemView->getChildByName("Button_Buy"));
		btn->setSize(Size(  150, 80));
		if (ItemManager::getInstance()->isGetItem(itemInfo))
		{
			btn->addClickEventListener([itemInfo](Ref* ref){
				ItemManager::getInstance()->useItem(itemInfo);
			});
			btn->setTitleText("Use");
		}
		else
		{
			btn->addClickEventListener([itemInfo, this](Ref* ref){
				ItemManager::getInstance()->buyItem(itemInfo);
				this->updateUI();
			});
			btn->setTitleText("Buy");
		}
		//CCLOG("Textis :%s", itemText->getString());;
	}

	//back Button
	auto btn = static_cast<Button*>(layer_->getChildByName("Back"));
	btn->addClickEventListener([](Ref* ref){
		Director::getInstance()->popScene();
	});

	this->updateUI();

	this->addEvent();


	return true;
}

void StoreScene::addEvent()
{
	auto showNoticeEvent = EventListenerCustom::create("showNotice", [this](EventCustom* event){
		Item* item = static_cast<Item*>(event->getUserData());
		this->showNoticePanel();
	});

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(showNoticeEvent, this);
}

void StoreScene::showNoticePanel()
{
	if (noticePanel_) 
		return;
		
	noticePanel_ = Sea::createNoticePanel();
	addChild(noticePanel_);

	auto backBtn = static_cast<Button*>(noticePanel_->getChildByName("NoBtn"));
	backBtn->addClickEventListener([this](Ref* ref){
		noticePanel_->removeFromParent();
		noticePanel_ = nullptr;
	});

	auto okBtn = static_cast<Button*>(noticePanel_->getChildByName("YesBtn"));
	okBtn->addClickEventListener([this](Ref* ref)
	{
		noticePanel_->removeFromParent();
		noticePanel_ = nullptr;
	});
}

void StoreScene::updateUI()
{
	auto starLb = static_cast<Text*>(layer_->getChildByName("StarLb"));
	char starStr[10];
	sprintf(starStr, "Star:%d", GameData::getInstance()->getStarNum());
	starLb->setString(starStr);

}