#ifndef _GAME_DATA__
#define _GAME_DATA__
#include "cocos2d.h"
#include "Game/Object/Item.h"

class GameData
{
public:
	GameData();
	~GameData();
	static GameData* getInstance();

	bool init();

	void setScore(int score){ score_ = score; }
	void addScore( int score ) { score_ += score; }
	int getScore() const { return score_; }

	//设置关卡的最高分数以便判定等级
	void setMaxScoreInLevel(int socre) { maxScoreInLevel_ = socre; }
	int getMaxScoreInLevel()const { return maxScoreInLevel_; };

	void setLastTypeId( int id ){ lastTypeId_ = id; }
	int getLastTypeId()const {return lastTypeId_;}

	//点击到相同敌人个数
	void setSameIdNum( int num ){ sumOfSameId_ = num; }
	int getSameIdNum() const { return sumOfSameId_; }
	void addSameIdNum( int num ){ sumOfSameId_ += num; }

	//连击个数
	void setComboNum(int num) { comboTimes_ = num; }
	void addComboNum(int num){ comboTimes_ += num; }
	int getComboNum() const { return comboTimes_; }

	void setLevel(int level){ level_ = level; }
	void addLevel(int level){ level_ += level; }
	int getLevel() const { return level_; }

	void setMaxLevel(int level){ maxLevel_ = level; }
	int getMaxLevel() const { return maxLevel_; }

	void setRound(int round){ round_ = round; }
	void addRound(int round){ round_ += round; }
	int getRound() const { return round_; }
	void setMaxRound(int round){ maxRound_ = round; }
	int getMaxRound() const { return maxRound_; }

	//当前的轮中的敌人数
	void setMaxArmyInRound(int num){ maxArmyInRound_ = num; }
	int getMaxArmyInRound() const { return maxArmyInRound_; }

	//当前关卡的人数
	void setMaxArmyInLevel(int num){ maxArmyInLevel_ = num; }
	int getMaxArmyInLevel() const { return maxArmyInLevel_; }

	//当前关卡打败的敌人数目
	void setArmyInLevel(int num) { armyInLevel_ = num; }
	void addArmyInLevel(int num){ armyInLevel_ += num; }
	int getArmyInLevel() const { return armyInLevel_; }

	//打败的敌人个数
	void setArmyInRound(int num){ armyInRound_ = num; }
	void addArmyInRound(int num){ armyInRound_ += num; }
	int getArmyInRound() const { return armyInRound_; }

	//分数增加的倍率
	void setScoreAddFactor(int factor){ scoreAddFactor_ = factor; }
	int getScoreAddFactor()const { return scoreAddFactor_; }

	//连击增加的倍率
	void setComboAddFactor(int factor) { comboAddFactor_ = factor; }
	int getComboAddFactor() const { return comboAddFactor_; }

	//设置左右两边的物品
	void setLeftItem(Item* item){ leftItem_ = item; }
	void setRightItem(Item* item){ rightItem_ = item; }
	Item* getLeftItem() { return leftItem_; }
	Item* getRightItem() { return rightItem_; }

	void loadStarNum();
	void saveStarNum();
	void setStarNum(int num) { starNum_ = num; }
	void addStarNum(int num) { starNum_ += num; }
	void minitesStarNum(int num){ starNum_ -= num; }
	int getStarNum() const { return starNum_; }

	void setArmySpeedFactor(float factor){ golbleArmySpeedFactor_ = factor; }
	float getArmySpeedFactor() const { return golbleArmySpeedFactor_; }

	void restart();
	void nextLevel();

private:
	int score_;
	int scoreAddFactor_; //分数增加倍率，有些道具需要改变分数倍率
	int comboAddFactor_; //连击增加倍率
	int maxScoreInLevel_; //关卡中的最大分数

	int starNum_; //获得的星星个数

	int lastTypeId_; //上次点击到的动物
	int sumOfSameId_; //点击到相同动物的个数
	int comboTimes_;
	int level_;
	int maxLevel_;
	int round_;
	int maxRound_;
	int maxArmyInRound_;  //当前波最多的敌人数
	int maxArmyInLevel_;  //当前关卡敌人总数
	int armyInRound_;  // 当前敌人数
	int armyInLevel_; //当前关卡打败的敌人数目
	float golbleArmySpeedFactor_; //全局敌人速度因子

	Item* leftItem_;
	Item* rightItem_;
};
#endif