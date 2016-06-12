#ifndef __GAME_SPRITE__
#define __GAME_SPRITE__
#include "cocos2d.h"
USING_NS_CC;
class GameSprite : public Sprite
{
public:
	static GameSprite* create(const std::string& filename)  ;

	bool initWithFile(const std::string& filename);

	void setSpeed(Vec2 speed) { speed_ = speed; } ;
	void addSpeed( Vec2 speed ) { speed_ += speed; };
	Vec2 getSpeed() const { return speed_; };

	void setAcc(Vec2 acc){ acc_ = acc;  };
	Vec2 getAcc() const { return acc_; };

	void setScore( int score){ score_ = score; } 
	int getScore() const {return score_;}
	void addScore();

	void setAniName( std::string name ){ name_ = name; }
	std::string getAniName() const { return name_; }

	void setAniPartent( std::string partent ){ aniPartent_ = partent; }
	std::string getAniPartent() const  {  return aniPartent_; }

	void setLength(int length) { length_ = length; }
	int getLength() const {  return length_; }

	void dispatchIfNumIsUp();

	void addEvent();

	void setId(int id){ id_ = id; }
	int getId() const { return id_; }

	void playAnimation();
	//逻辑更新
	void update(float dt) ;
	void updateLogic();
	void updatePosition();

	bool isDie() { return isDie_; }

	void onEnter() override;
	void onExit() override;

private:
	Vec2 speed_;
	Vec2 acc_;  //加速度
	int score_;
	int length_;
	int id_;
	std::string aniPartent_;
	std::string name_;
	float time_;

	bool isDie_;
};
#endif