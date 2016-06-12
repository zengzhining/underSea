#ifndef _ITEM_MANAGER__
#define _ITEM_MANAGER__
#include "cocos2d.h"
#include "Game/Object/Item.h"
USING_NS_CC;

class ItemManager
{
public:
	enum ITEMID
	{
		GOLD_COIN = 1,
		SILVER_COIN = 2,
		COPPER_COIN = 3,
		APPLE  = 4,
		CHICKEN_LEG = 5,
		CARROT  = 6,
		WATERMELON = 7
	};
public:
	ItemManager();
	~ItemManager();
	static ItemManager* getInstance();
	bool init();
	void initItemDef();

	bool isGetItem(int id);
	bool isGetItem(Item* item);

	void useItem(int id);
	void useItem(Item* item);

	void buyItem(int id);
	void buyItem(Item* item);

	void getGameItem(Item* item); //获得物品时候
	void getShopItem(Item* item);

	Item* getItemById(int id);
	std::vector<Item*>* getItems() { return allItem_; };
private:
	ValueMap itemDef_;
	std::vector<Item*>* allItem_;
};
#endif