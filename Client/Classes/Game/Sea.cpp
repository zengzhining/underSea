#include "Sea.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"
#include "editor-support/cocostudio/CocoStudio.h"

USING_NS_CC;
using namespace cocos2d::ui;

GameSprite* Sea::createObject(OBJType typeId)
{
	GameSprite* sp = nullptr;
	switch (typeId)
	{
	case Sea::PANGXIE:
		sp = GameSprite::create("pangxie%02d.png");
		sp->setAniName("PangXie");
		break;
	case Sea::FISH:
		sp = GameSprite::create("animFish%02d.png");
		sp->setAniName("Fish");
		break;
	case Sea::FISHGIRL:
		sp = GameSprite::create("animFishNu%02d.png");
		sp->setAniName("FishGirl");
		break;
	case Sea::STAR:
		sp = GameSprite::create("aniStar%02d.png");
		sp->setAniName("Star");
		break;
	case Sea::WUZEI:
		sp = GameSprite::create("animWuzei%02d.png");
		sp->setAniName("Wuzei");
		break;
	default:
		break;
	}
	sp->setId((int)(typeId));
	return sp;
}

void Sea::setMenuItemName(Node* node, std::string name)
{
	auto nameLb = static_cast<TextBMFont*>(node->getChildByName("Button")->getChildByName("Name"));
	nameLb->setString(name);
}

Node* Sea::createStoreLayer()
{
	auto bg = CSLoader::createNodeWithVisibleSize("GameObject/StoreLayer.csb");
	return bg;
}

Node* Sea::createStoreNode()
{
	auto item = CSLoader::createNodeWithVisibleSize("GameObject/StoreNode.csb");
	return item;
}

Node* Sea::createNoticePanel()
{
	auto item = CSLoader::createNodeWithVisibleSize("GameObject/NoticePanel.csb");
	return item;
}

Node* Sea::createOnlineRoomLayer()
{
	auto item = CSLoader::createNodeWithVisibleSize("GameObject/OnlineRoom.csb");
	return item;
}

Node* Sea::createInputNamePanel()
{
	auto item = CSLoader::createNodeWithVisibleSize("GameObject/InputName.csb");
	return item;
}

Node* Sea::createUserNode()
{
	auto item = CSLoader::createNodeWithVisibleSize("GameObject/UserNode.csb");
	return item;
}

void Sea::setLevelNodeName(Node* node, std::string name)
{
	auto nameLb = static_cast<TextBMFont*>(node->getChildByName("ButtonLevel")->getChildByName("Level"));
	nameLb->setText(name);
}

Label* Sea::createLabel()
{
	Label* lb = Label::createWithBMFont("fonts/GameFont.fnt", "SCORE");
	lb->setAnchorPoint(Vec2(0.50f, 0.50f));
	lb->setScale(0.50f, 0.50f);
	auto contentSize = lb->getContentSize();
	lb->setContentSize(Size(contentSize.width * 0.50f, contentSize.height * 0.50f));
	return lb;
}

Node* Sea::createResultLayer()
{
	auto bg = CSLoader::createNodeWithVisibleSize("GameObject/ScoreLayer.csb");
	return bg;
}

Node* Sea::createMenuBg()
{
	auto size = Director::getInstance()->getVisibleSize();
	auto bg = CSLoader::createNodeWithVisibleSize("GameObject/MenuBg.csb");
	return bg;
}

Node* Sea::createBattleBg()
{
	auto bg = CSLoader::createNodeWithVisibleSize("GameObject/BattleBg.csb");
	return bg;
}

Node* Sea::createMainBg()
{
	auto bg = CSLoader::createNodeWithVisibleSize("GameObject/MainBg.csb");
	return bg;
}

Node* Sea::createLevelSelectLayer()
{
	auto bg = CSLoader::createNodeWithVisibleSize("GameObject/SelectLevel.csb");
	return bg;
}

Node* Sea::createLogo()
{
	auto size = Director::getInstance()->getVisibleSize();
	auto logo = CSLoader::createNode("GameObject/LevelNode.csb");
	return logo;
}

MenuItemSprite* Sea::createLevelNode(int level)
{
	auto size = Director::getInstance()->getVisibleSize();
	Sprite* normalSp = Sprite::createWithSpriteFrameName("levelBlock.png");
	Sprite* selectSp = Sprite::createWithSpriteFrameName("levelBlockPress.png");
	auto contentSize = normalSp->getContentSize();
	float scaleX = size.width / contentSize.width * 200.0f / 640.0f;
	float scaleY = size.height / contentSize.height * 200.0f / 960.0f;
	normalSp->setScale(scaleX, scaleY);
	selectSp->setScale(scaleX, scaleY);
	normalSp->setContentSize(Size(contentSize.width * scaleX, contentSize.height * scaleY));
	selectSp->setContentSize(Size(contentSize.width * scaleX, contentSize.height * scaleY));
	MenuItemSprite* item = MenuItemSprite::create(normalSp, selectSp);
	auto title = Sea::createLabel();
	char name[3];
	sprintf(name, "%d", level);
	title->setString(name);
	title->setPosition(normalSp->getContentSize().width * 0.50f, normalSp->getContentSize().height * 0.50f);
	item->addChild(title);
	return item;
}

GameSprite* Sea::createBubbleExplore()
{
	GameSprite* bubble = GameSprite::create("bubbles1_%d.png");
	bubble->setLength( 4 );
	bubble->setAniName("BubbleExplore");
	return bubble;
}

GameSprite* Sea::createClickEffect()
{
	GameSprite* bubble = GameSprite::create("bubles2_%d.png");
	bubble->setLength( 4 );
	bubble->setAniName("ClickEffect");
	return bubble;	
}