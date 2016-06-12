#ifndef __LEVEL_MANAGER__
#define __LEVEL_MANAGER__
#include "Game/Object/Level.h"
#include "cocos2d.h"
USING_NS_CC;

class LevelManager
{
public:
	
public:
	LevelManager();
	~LevelManager();
	static LevelManager* getInstance();
	bool init();

	void initDef();

	Level* getLevelById(int id);
	void setLevelState(int id, Level::State state);

	std::vector<Level*>* getAllLevel() {
		return allLevel_;
	}

	void saveLevelInfo();
	void loadLevelInfo();

private:
	std::vector<Level*>* allLevel_;
};

#endif