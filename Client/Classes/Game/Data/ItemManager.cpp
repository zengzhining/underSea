#include "ItemManager.h"
#include "GameData.h"
USING_NS_CC;
static ItemManager* gItemManager = nullptr;
ItemManager::ItemManager()
{

}

ItemManager::~ItemManager()
{

}

ItemManager* ItemManager::getInstance()
{
	if (gItemManager == nullptr)
	{
		gItemManager = new ItemManager();
		if (gItemManager && gItemManager->init())
		{
			return gItemManager;
		}
	}
	return gItemManager;
}

bool ItemManager::init()
{
	allItem_ = new std::vector<Item*>();
	initItemDef();

	return true;
}

void ItemManager::initItemDef()
{
	std::string fileName = "Config/item.plist";
	bool isExit = FileUtils::getInstance()->isFileExist(fileName);
	if (isExit)
	{
		itemDef_ = FileUtils::getInstance()->getValueMapFromFile(fileName);
		char name[10];
		for (int i = 1; i <= itemDef_.size(); i++)
		{
			sprintf(name, "Item%02d", i);
			auto info = itemDef_[name].asValueMap();
			Item* item = Item::create(info);
			allItem_->push_back(item);
		}
	}
}

bool ItemManager::isGetItem(int id)
{
	return false;
}

bool ItemManager::isGetItem(Item* item)
{
	int id = item->getId();
	return this->isGetItem(id);
}

void ItemManager::useItem(int id)
{
	auto item = getItemById(id);
	this->useItem(item);
}

void ItemManager::useItem(Item* item)
{
	CCLOG("USE Item %d", item->getId());
	ITEMID id = (ITEMID)item->getId();
	switch (id)
	{
	case GOLD_COIN:
		break;
	case SILVER_COIN:

		break;
	case COPPER_COIN:

		break;
	case APPLE:
		GameData::getInstance()->setComboAddFactor(2);
		break;
	case CHICKEN_LEG:
		GameData::getInstance()->addScore(GameData::getInstance()->getMaxScoreInLevel() * 2 /5);
		Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("updateScore");
		break;
	case CARROT:
		GameData::getInstance()->setScoreAddFactor(2);
		break;
	case WATERMELON:
		GameData::getInstance()->setArmySpeedFactor(2.0f / 3.0f);
		break;
	default:
		break;
	}
}

void ItemManager::buyItem(int id)
{
	auto item = getItemById(id);
	buyItem(item);
}

void ItemManager::buyItem(Item* item)
{
	if (item->getType() == Item::SHOP)
	{
		getShopItem(item);
	}
	else if (item->getType() == Item::GAME)
	{
		getGameItem(item);

	}
}

void ItemManager::getGameItem(Item* item)
{

	if (GameData::getInstance()->getStarNum() < item->getNorPrice())
	{
		Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("showNotice", item);
		return;
	}

	GameData::getInstance()->minitesStarNum(item->getNorPrice());
	GameData::getInstance()->saveStarNum();
	if (GameData::getInstance()->getLeftItem() == nullptr)
	{
		GameData::getInstance()->setLeftItem(item);
		Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("updateScore");
		return;
	}

	GameData::getInstance()->setRightItem(item);
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("updateScore");

}

void ItemManager::getShopItem(Item* item)
{

}

Item* ItemManager::getItemById(int id)
{
	for (auto itr = allItem_->begin(); itr != allItem_->end(); itr++)
	{
		auto item = (*itr);
		if (item->getId() == id)
		{
			return item;
		}
	}

	return nullptr;
}