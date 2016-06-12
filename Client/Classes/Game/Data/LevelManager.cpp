#include "LevelManager.h"

static LevelManager* gLevelManager = nullptr;
LevelManager::LevelManager()
{

}

LevelManager::~LevelManager()
{

}

LevelManager* LevelManager::getInstance()
{
	if (gLevelManager == nullptr)
	{
		gLevelManager = new LevelManager();
		if (gLevelManager && gLevelManager->init())
		{
			return gLevelManager;
		}
	}
	return gLevelManager;
}

bool LevelManager::init()
{
	initDef();
	return true;
}

void LevelManager::initDef()
{
	allLevel_ = new std::vector<Level*>();
	auto allLevelDef = FileUtils::getInstance()->getValueMapFromFile("Config/LevelDef.plist");
	char name[12];
	for (int i = 1; i <= allLevelDef.size(); i++)
	{
		sprintf(name, "Level%02d", i);
		auto def = allLevelDef[name].asValueMap();
		Level* level = Level::create(def["MaxScore"].asInt(), def["ID"].asInt());
		if (i ==1)
		{
			level->setState(4);
		}
		allLevel_->push_back(level);
	}
}

Level* LevelManager::getLevelById(int id)
{
	for (int i = 0; i< allLevel_->size(); i++)
	{
		auto level = allLevel_->at(i);
		if (level->getId() == id)
		{
			return level;
		}
	}
	return nullptr;
}

void LevelManager::setLevelState(int id, Level::State state)
{
	auto level = this->getLevelById(id);
	level->setState(state);
}

void LevelManager::saveLevelInfo()
{
	auto dict = Dictionary::create();
	char name[12];
	for (int i = 0; i < allLevel_->size(); i++)
	{
		auto level = allLevel_->at(i);

		auto levelInfo = Dictionary::create();
		int state = (int)(level->getState());
		levelInfo->setObject(Integer::create(state), "State");
		sprintf(name, "Level%02d", level->getId());
		dict->setObject(levelInfo, name);
	}
	dict->writeToFile( (FileUtils::getInstance()->getWritablePath() +  "Game.plist").c_str());
}

void LevelManager::loadLevelInfo()
{
	std::string fileName = FileUtils::getInstance()->getWritablePath() + "Game.plist";
	bool isExit = FileUtils::getInstance()->isFileExist(fileName);
	if (!isExit)
		return;

	auto alllevelInfo = FileUtils::getInstance()->getValueMapFromFile(fileName);
	char name[12];
	for (int i = 0; i < allLevel_->size(); i++)
	{
		auto level = allLevel_->at(i);
		sprintf(name, "Level%02d", level->getId());
		auto dict = alllevelInfo[name].asValueMap();
		level->setState(dict["State"].asInt());
	}
}
