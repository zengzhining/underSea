#include "BattleLayer.h"
#include "ScoreNode.h"
#include "Game/Data/GameData.h"
#include "Game/Data/ArmyManager.h"
#include "Game/Data/ItemManager.h"
#include "Game/Data/LevelManager.h"
#include "Game/Object/Level.h"
#include "Game/Scene/SceneManager.h"
#include "../Sea.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"
#include "editor-support/cocostudio/CocoStudio.h"
#include "Engine/Pure.h"


USING_NS_CC;
using namespace cocos2d::ui;

bool BattleLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	int nowLevel = GameData::getInstance()->getLevel();
	auto info = ArmyManager::getInstance()->getArmyInfo(nowLevel);
	GameData::getInstance()->setMaxRound(info.size());

	auto level = LevelManager::getInstance()->getLevelById(nowLevel);
	GameData::getInstance()->setMaxScoreInLevel(level->getMaxScore());
	this->setEffectPlay(false);
	this->addRes();

	this->createBg();

	this->createUI();
	this->addEvent();

	//设置当前关卡的敌人总数

	this->createLevelObject();
	//this->showResult();
	srand(time(NULL));
	scheduleUpdate();
	return true;
}

void BattleLayer::addRes()
{
	
}

void BattleLayer::updateTime( float dt )
{
	this->createLevelObject();
}

void BattleLayer::createBg()
{
	bg_ = Sea::createBattleBg();
	addChild(bg_, OBJOrder::BG);
}   

void BattleLayer::addEvent()
{
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	EventListenerCustom *scorelistener = EventListenerCustom::create("updateScore", [this](EventCustom* event){
		this->updateUI();
	});
	dispatcher->addEventListenerWithSceneGraphPriority(scorelistener, this );
	
	EventListenerCustom *levellistener = EventListenerCustom::create("NextLevel", [this](EventCustom* event){
		int maxRound = GameData::getInstance()->getMaxRound();
		int round = GameData::getInstance()->getRound();
		if (round >= maxRound)
		{
			this->hideUI();
			this->showResult();
		}
		else
		{
			GameData::getInstance()->addRound(1);
			this->createLevelObject();

		}
	});
	dispatcher->addEventListenerWithSceneGraphPriority(levellistener, this );

	//游戏失败
	EventListenerCustom *fiallistener = EventListenerCustom::create("GameFail", [this](EventCustom* event){

	});
	dispatcher->addEventListenerWithSceneGraphPriority(fiallistener, this );

	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(BattleLayer::dealTouchBegan, this);

	dispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	//按钮事件
	leftBtn_->addClickEventListener([this](Ref* ref){
		auto item = GameData::getInstance()->getLeftItem();
		if (item == nullptr)
			return;
		ItemManager::getInstance()->useItem(item);
		GameData::getInstance()->setLeftItem(nullptr);

		leftBtn_->setVisible(false);
		leftBtn_->setTouchEnabled(false);


	});

	rightBtn_->addClickEventListener([this](Ref* ref){
		auto item = GameData::getInstance()->getRightItem();
		if (item == nullptr)
			return;
		ItemManager::getInstance()->useItem(item);
		GameData::getInstance()->setRightItem(nullptr);

		rightBtn_->setVisible(false);
		rightBtn_->setTouchEnabled(false);
	});
}

void BattleLayer::createLevelObject()
{
	auto size = Director::getInstance()->getVisibleSize();
	auto armyInfo = ArmyManager::getInstance()->getRoundInfo(GameData::getInstance()->getRound());
	int maxNum = armyInfo.size();
	GameData::getInstance()->setMaxArmyInRound(maxNum);
	GameData::getInstance()->setArmyInRound(0);
	char name[10];
	float nextPosY = 0.0f;
	for (int i = 1; i <= maxNum; i++)
	{
		sprintf(name, "Army%03d", i);
		auto army = armyInfo[name].asValueMap();
		auto sp = Sea::createObject((Sea::OBJType)(army["ArmyType"].asInt()));
		sp->addEvent();
		sp->setVisible(false);
		addChild(sp, OBJOrder::ROLE);
		auto conSize = sp->getContentSize();
		float scaleX = size.width * 0.25f / conSize.width;
		sp->setScale(scaleX, scaleX);
		sp->setSpeed(Vec2(-0.0f, -4.0f));
		sp->setAcc(Vec2(0.0f, -0.00f));
		float posX = (army["PosX"].asFloat() + 0.50f)* sp->getBoundingBox().size.width;
		float posY = (army["PosY"].asFloat() + 0.50f) * sp->getBoundingBox().size.height + size.height;
		if (posX < sp->getBoundingBox().size.width * 0.50f)
		{
			posX = sp->getBoundingBox().size.width * 0.50f;
		}

		if (posX > size.width - sp->getBoundingBox().size.width * 0.50f)
		{
			posX = size.width - sp->getBoundingBox().size.width * 0.50f;
		}
		sp->setPosition(posX, posY);
		sp->setVisible(true);

	}
}

void BattleLayer::showResult()
{
	auto size = Director::getInstance()->getVisibleSize();
	auto resultNode = Sea::createResultLayer();
	this->initResult(resultNode);
	addChild( resultNode );
}

void BattleLayer::initResult(Node* node)
{
	auto backBtn = static_cast<Button*>(node->getChildByName("Back"));
	backBtn->addClickEventListener([](Ref* ref){
		GameData::getInstance()->restart();
		auto scene = SceneManager::createSelectScene();
		Director::getInstance()->replaceScene(scene);
	});

	auto restartBtn = static_cast<Button*>(node->getChildByName("Reatart"));
	restartBtn->addClickEventListener([](Ref* ref){
		GameData::getInstance()->restart();
		auto scene = SceneManager::createBattleScene();
		Director::getInstance()->replaceScene(scene);
	});

	auto nextBtn = static_cast<Button*>(node->getChildByName("Next"));
	nextBtn->addClickEventListener([](Ref* ref){
		GameData::getInstance()->nextLevel();
		auto scene = SceneManager::createBattleScene();
		Director::getInstance()->replaceScene(scene);
	});

	auto storeBtn = static_cast<Button*>(node->getChildByName("Store"));
	storeBtn->addClickEventListener([](Ref* ref){
		auto scene = SceneManager::createStoreScene();
		Director::getInstance()->pushScene(scene);
	});

	auto star1 = static_cast<ImageView*>(node->getChildByName("Star01"));
	auto star2 = static_cast<ImageView*>(node->getChildByName("Star02"));
	auto star3 = static_cast<ImageView*>(node->getChildByName("Star03"));
	auto levelImage = static_cast<ImageView*>(node->getChildByName("LevelDes"));
	int gameScore = GameData::getInstance()->getScore();
	int maxScore = GameData::getInstance()->getMaxScoreInLevel();

	auto levelInfo = LevelManager::getInstance()->getLevelById(GameData::getInstance()->getLevel());
	auto levelState = levelInfo->getState();
	if (gameScore >= 0.8 * maxScore)
	{
		star1->setVisible(true);
		star2->setVisible(true);
		star3->setVisible(true);
		levelInfo->setState(Level::ALLSTAR);

		if (levelState == Level::UNLOCK)
		{
			GameData::getInstance()->addStarNum(3);
		}
		else
		{
			GameData::getInstance()->addStarNum((int)Level::ALLSTAR - (int)levelState  );
		}
	}
	else if (gameScore >= 0.6 * maxScore)
	{
		star1->setVisible(true);
		star2->setVisible(false);
		star3->setVisible(true);
		if (levelState != Level::ALLSTAR )
		{
			levelInfo->setState(Level::TWOSTAR);
		}

		if (levelState == Level::UNLOCK)
		{
			GameData::getInstance()->addStarNum(2);
		}
		else
		{
			GameData::getInstance()->addStarNum((int)Level::TWOSTAR - (int)levelState  );
		}
	}
	else if (gameScore >= 0.5 * maxScore)
	{
		star1->setVisible(false);
		star2->setVisible(true);
		star3->setVisible(false);
		if (levelState != Level::TWOSTAR && levelState != Level::ALLSTAR )
		{
			levelInfo->setState(Level::ONESTAR);
		}

		if (levelState == Level::UNLOCK)
		{
			GameData::getInstance()->addStarNum(1);
		}
		else
		{
			GameData::getInstance()->addStarNum((int)Level::ONESTAR - (int)levelState  );
		}

	}
	else
	{
		star1->setVisible(false);
		star2->setVisible(false);
		star3->setVisible(false);
		levelImage->loadTexture("failed.png", TextureResType::PLIST);
	}

	if (gameScore >= 0.50f * maxScore )
	{
		//解锁下一关
		Level* nextLevel = LevelManager::getInstance()->getLevelById( GameData::getInstance()->getLevel() + 1 );
		auto nextLevelState = nextLevel->getState();
		if (nextLevelState == Level::LOCK)
		{	
			nextLevel->setState(Level::UNLOCK);
		}
		//如果分数比之前高就保存
		LevelManager::getInstance()->saveLevelInfo();
		GameData::getInstance()->saveStarNum();
	}
}

void BattleLayer::hideUI()
{
	scoreLb_->setVisible(false);
	comboLb_->setVisible(false);
	lifeBar_->setVisible(false);
	leftBtn_->setVisible(false);
	rightBtn_->setVisible(false);

	auto itemLeftBg = bg_->getChildByName("ItemLeftBg");
	itemLeftBg->setVisible(false);
	auto itemRightBg = bg_->getChildByName("ItemRightBg");
	itemRightBg->setVisible(false);

	auto barBg = bg_->getChildByName("TimeBarBg");
	barBg->setVisible(false);
}

void BattleLayer::showUI()
{

}

void BattleLayer::update(float delta)
{
}

Vec2 BattleLayer::getSpeed()
{
	Vec2 speed = Vec2(-0.0f, -4.0f);
	return speed;
}

Vec2 BattleLayer::getAcc()
{
	Vec2 acc = Vec2(0.0f, -0.12f);
	return acc;
}

Vec2 BattleLayer::getPos( Size contSize )
{
	auto size = Director::getInstance()->getVisibleSize();
	Vec2 pos(size.width * 0.25f * random(1, 3), size.height + contSize.height * 0.50f);
	return pos;
}

bool BattleLayer::dealTouchBegan(Touch* touch, Event* event)
{
	if (this->isEffectPlay())
		return false;

	auto effect = Sea::createClickEffect();
	effect->setPosition(touch->getLocation());
	addChild(effect, OBJOrder::UI);
	effect->playAnimation();
	auto act = Sequence::create(CallFunc::create([this](){
		this->setEffectPlay(true);
	}), FadeOut::create(0.4f), CallFunc::create([this](){
		this->setEffectPlay(false);
	}), RemoveSelf::create(true), NULL);
	effect->runAction(act);
	return false;

}

void BattleLayer::createUI()
{
	auto size = Director::getInstance()->getVisibleSize();
	scoreLb_ = static_cast<TextBMFont*>(bg_->getChildByName("ScoreLb"));
	this->initLifeBar();
	this->initComboUI();
	this->initItemBtn();
	this->updateUI();
}

void BattleLayer::initLifeBar()
{
	lifeBar_ = static_cast<LoadingBar*>(bg_->getChildByName("TimeBar"));
	lifeBar_->setPercent(0.0f);
}

void BattleLayer::initComboUI()
{
	comboLb_ = static_cast<TextBMFont*>(bg_->getChildByName("ComboLb"));
	char name[15];
	sprintf(name, "COMBOX%d", GameData::getInstance()->getComboNum());
	comboLb_->setString(name);
}

void BattleLayer::initItemBtn()
{
	leftBtn_ = static_cast<ImageView*>(bg_->getChildByName("ItemLeft"));
	rightBtn_ = static_cast<ImageView*>(bg_->getChildByName("ItemRight"));
	auto leftItem = GameData::getInstance()->getLeftItem();
	auto rightItem = GameData::getInstance()->getRightItem();
	if (leftItem)
	{
		leftBtn_->loadTexture(leftItem->getTextureName(), TextureResType::PLIST);
		leftBtn_->setVisible(true);
		leftBtn_->setTouchEnabled(true);
	}
	else
	{
		leftBtn_->setVisible(false);
		leftBtn_->setTouchEnabled(false);
	}

	if (rightItem)
	{
		rightBtn_->loadTexture(rightItem->getTextureName(), TextureResType::PLIST);
		rightBtn_->setVisible(true);
		rightBtn_->setTouchEnabled(true);
	}
	else
	{
		rightBtn_->setVisible(false);
		rightBtn_->setTouchEnabled(false);
	}
}

void BattleLayer::updateUI()
{
	char score[5];
	sprintf(  score ,"%02d", GameData::getInstance()->getScore());
	scoreLb_->setString( score );
	float percent = 100 * (float)GameData::getInstance()->getScore() / (float)GameData::getInstance()->getMaxScoreInLevel();
	auto act = UIProgressTo::create(0.20f, percent);
	lifeBar_->runAction(act);
	//lifeBar_->setPercent( percent );
	char name[15];
	sprintf(name, "COMBOX%d", GameData::getInstance()->getComboNum());
	comboLb_->setString(name);

	auto leftItem = GameData::getInstance()->getLeftItem();
	if (leftItem != nullptr)
	{
		leftBtn_->loadTexture(leftItem->getTextureName(), TextureResType::PLIST);
		leftBtn_->setVisible(true);
		leftBtn_->setTouchEnabled(true);
	}

	auto rightItem = GameData::getInstance()->getRightItem();
	if (rightItem != nullptr)
	{
		rightBtn_->loadTexture(rightItem->getTextureName(), TextureResType::PLIST);
		rightBtn_->setVisible(true);
		rightBtn_->setTouchEnabled(true);
	}
	
}

void BattleLayer::onEnter()
{
	Layer::onEnter();
}

void BattleLayer::onExit()
{
	Layer::onExit();
	Director::getInstance()->getEventDispatcher()->removeEventListenersForTarget(this);
}