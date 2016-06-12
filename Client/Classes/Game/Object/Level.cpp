#include "Level.h"

Level* Level::create(int maxScore,int id, State state)
{
	auto level = new Level();
	if (level && level->init(maxScore, id, state))
	{
		return level;
	}
	return nullptr;
}

bool Level::init(int maxScore,int id, State state)
{
	setMaxScore(maxScore);
	setId(id);
	setState(state);
	return true;
}