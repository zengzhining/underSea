#ifndef _ARMY_MANAGER__
#define _ARMY_MANAGER__
#include "cocos2d.h"
USING_NS_CC;
class ArmyManager
{
public:
	ArmyManager();
	~ArmyManager();
	static ArmyManager* getInstance();
	bool init();

	ValueMap getArmyInfo(int level);
	ValueMap getRoundInfo(int round);

private:
	ValueMap armyInfo_;
};
#endif