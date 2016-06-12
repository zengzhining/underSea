#include "GameData.h"
USING_NS_CC;
static GameData* gGameData = nullptr;
GameData::GameData()
{

}

GameData::~GameData()
{

}

GameData* GameData::getInstance()
{
	if (gGameData == nullptr)
	{
		gGameData = new GameData();
		if (gGameData && gGameData->init())
		{
			return gGameData;
		}
	}
	return gGameData;
}

bool GameData::init()
{
	this->setScore(0);
	this->setSameIdNum(0);
	this->setLastTypeId(-1);
	//设置关卡为第一关第一波
	this->setLevel(1);
	this->setRound(1);
	this->setMaxLevel(1);
	this->setMaxRound(1);
	this->setScoreAddFactor(1);
	this->setComboAddFactor(10);
	this->setComboNum(0);
	this->setLeftItem(nullptr);
	this->setRightItem(nullptr);

	this->setArmySpeedFactor(1.0f);

	//测试数据
	this->loadStarNum();
	return true;
}

void GameData::loadStarNum()
{
	int starNum = UserDefault::getInstance()->getIntegerForKey("StarNum", 0);
	this->setStarNum( starNum );
}

void GameData::saveStarNum()
{
	int starNum = this->getStarNum();
	UserDefault::getInstance()->setIntegerForKey("StarNum", starNum);
}

void GameData::restart()
{
	this->setRound(1);
	this->setScore(0);
	this->setSameIdNum(0);
	this->setLastTypeId(-1);
	this->setScoreAddFactor(1);
	this->setComboAddFactor(10);
	this->setComboNum(0);
}

void GameData::nextLevel()
{
	this->addLevel(1);
	restart();
}