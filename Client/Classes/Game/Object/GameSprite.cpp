#include "GameSprite.h"
#include "Game/Data/GameData.h"
#include "Game/Data/ItemManager.h"
#include "Game/Sea.h"
USING_NS_CC;

GameSprite* GameSprite::create(const std::string& filename)
{
	auto sp = new GameSprite();
	if (sp && sp->initWithFile(filename))
	{
		sp->autorelease();
		return sp;
	}
	return nullptr;
}

bool GameSprite::initWithFile(const std::string& filename)
{
	this->setAniPartent(filename);
	char fileName[30];
	sprintf(fileName, filename.c_str(), 1);
	if (!Sprite::initWithSpriteFrameName(fileName))
	{
		return false;
	}

	this->setAcc( Vec2( 0.0f, 0.0f ) );
	this->setSpeed( Vec2( 0.0f, 0.0f ) );
	time_ = 0.0f;
	this->setId(0);
	this->setScore( 2 );
	this->setLength(6);
	isDie_ = false;
	return true;
}

void GameSprite::addEvent()
{
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [this](Touch* touch, Event* event){
		auto location = touch->getLocation();
		if (this->getBoundingBox().containsPoint(location))
		{
			Director::getInstance()->getEventDispatcher()->removeEventListenersForTarget(this);
			this->playAnimation();
			auto act = Sequence::create(FadeOut::create(0.6f), RemoveSelf::create(true), NULL);
			this->runAction(act);
			this->addScore();
			auto effect = Sea::createBubbleExplore();
			effect->setPosition(this->getContentSize().width * 0.5f, this->getContentSize().height * 0.5f);
			this->addChild(effect);
			effect->playAnimation();
			GameData::getInstance()->addArmyInRound(1);
			this->dispatchIfNumIsUp();
		}
		return false;
	};

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

}

void GameSprite::dispatchIfNumIsUp()
{
	int maxNum = GameData::getInstance()->getMaxArmyInRound();
	int num = GameData::getInstance()->getArmyInRound();
	if (num >= maxNum )
	{
		Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("NextLevel");
	}
}

void GameSprite::addScore()
{	
	GameData::getInstance()->addScore( GameData::getInstance()->getScoreAddFactor() * this->getScore() );
	//根据上次点击的到id跟这次做比较
	//不等于就置一
	if (this->getId() != GameData::getInstance()->getLastTypeId() && GameData::getInstance()->getSameIdNum() > 0 )
	{
		GameData::getInstance()->setLastTypeId( this->getId() );
		GameData::getInstance()->setSameIdNum(1);
		GameData::getInstance()->setComboNum(0);
	}
	//相等就加一
	else
	{
		GameData::getInstance()->setLastTypeId( this->getId() );
		GameData::getInstance()->addSameIdNum(1);
		//超过三就置零
		if (GameData::getInstance()->getSameIdNum() >= 3)
		{
			GameData::getInstance()->setSameIdNum(0);
			GameData::getInstance()->addComboNum(1);
			GameData::getInstance()->addScore(   GameData::getInstance()->getComboAddFactor() *GameData::getInstance()->getScoreAddFactor() * this->getScore());

		}

	}

	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("updateScore");

}

void GameSprite::playAnimation()
{
	Animation* animation = AnimationCache::getInstance()->getAnimation(this->getAniName());
	if (animation == nullptr)
	{
		auto partent = this->getAniPartent();
		char fileName[30];
		Vector<SpriteFrame*> aniArray;
		for (int i = 1; i <= this->getLength(); ++i)
		{
			sprintf( fileName, partent.c_str(), i );
			aniArray.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(fileName));
		}
		animation = Animation::createWithSpriteFrames(aniArray, 0.1f);
		AnimationCache::getInstance()->addAnimation(animation, this->getAniName());
	}
	this->runAction(Animate::create(animation));
	isDie_ = true;
}

void GameSprite::update(float dt)
{
	time_ += dt;
	updateLogic();
	updatePosition();
}

void GameSprite::updateLogic()
{
	if (time_ >= 0.20f)
	{
		time_ = 0.0f;
		this->addSpeed( this->getAcc() );
	}
}

void GameSprite::updatePosition()
{
	auto size = Director::getInstance()->getVisibleSize();
	auto pos = this->getPosition();
	auto finalPos = pos + ( GameData::getInstance()->getArmySpeedFactor() * this->getSpeed() * size.height /960.0f);
	this->setPosition( finalPos );

	if (finalPos.y < 0.0f && !this->isDie())
	{
		this->removeFromParent();
		GameData::getInstance()->addArmyInRound(1);
		this->dispatchIfNumIsUp();
	}
}

void GameSprite::onEnter()
{
	Sprite::onEnter();
	scheduleUpdate();
}

void GameSprite::onExit()
{
	Sprite::onExit();
	unscheduleUpdate();
}