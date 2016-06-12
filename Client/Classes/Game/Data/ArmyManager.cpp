#include "ArmyManager.h"
#include "GameData.h"
USING_NS_CC;
static ArmyManager* gArmyManager = nullptr;
ArmyManager::ArmyManager()
{

}

ArmyManager::~ArmyManager()
{

}

ArmyManager* ArmyManager::getInstance()
{
	if (gArmyManager == nullptr)
	{
		gArmyManager = new ArmyManager();
		if (gArmyManager && gArmyManager->init())
		{
			return gArmyManager;
		}
	}
	return gArmyManager;
}

bool ArmyManager::init()
{

	return true;
}

ValueMap ArmyManager::getArmyInfo(int level)
{
	char fileName[30];
	sprintf(fileName, "Config/Level%02d.plist", level);
	armyInfo_ = FileUtils::getInstance()->getValueMapFromFile(fileName);
	return armyInfo_;
}

ValueMap ArmyManager::getRoundInfo(int round)
{
	char name[10];
	sprintf(name, "Round%02d", round);
	return armyInfo_[name].asValueMap();

}

