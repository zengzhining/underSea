#ifndef __LEVEL_H_
#define __LEVEL_H_

class Level
{
public:
	enum State
	{
		LOCK,
		ONESTAR,
		TWOSTAR,
		ALLSTAR,
		UNLOCK
	};

	Level(){};
	~Level(){};
	static Level* create(int maxScore, int id ,State state = LOCK);

	bool init(int maxScore, int id, State state);

	void setId(int id){ id_ = id; }
	int getId() const{ return id_; }

	void setMaxScore(int num){ maxScore_ = num; }
	int getMaxScore() const { return maxScore_; }

	void setState(State state){ state_ = state; }
	void setState(int state){ state_ = (State)state; }
	State getState() const { return state_; }

private:
	int maxScore_;
	int id_;
	State state_;
};
#endif