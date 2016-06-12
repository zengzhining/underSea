#ifndef __SEA___
#define __SEA___
#include "cocos2d.h"
#include "Object/GameSprite.h"

USING_NS_CC;
class Sea
{
public:
	enum OBJType
	{
		PANGXIE,
		FISH,
		FISHGIRL,
		STAR,
		WUZEI,
	};

	static GameSprite* createObject(OBJType typeId);

	static Label* createLabel();

	static Node* createMenuBg();
	static Node* createMainBg();
	static Node* createLevelSelectLayer();
	static Node* createLogo();
	static Node* createResultLayer();
	static Node* createStoreLayer();
	static Node* createStoreNode();
	static Node* createBattleBg();

	static Node* createNoticePanel();
	static Node* createInputNamePanel();
	static Node* createOnlineRoomLayer();
	static Node* createUserNode();

	static void setMenuItemName(Node* node, std::string name);
	static void setLevelNodeName(Node* node, std::string name);

	static MenuItemSprite* createLevelNode(int level);

	static GameSprite* createBubbleExplore();
	static GameSprite* createClickEffect();
};
#endif