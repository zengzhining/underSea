#ifndef __NET_PLAYER__
#define __NET_PLAYER__

#include "cocos2d.h"
USING_NS_CC;
class NetPlayer : public Ref
{
public:
	CREATE_FUNC(NetPlayer);
	bool init();

	static NetPlayer* create(std::string jsonStr);
	bool init(std::string jsonStr);

	
	void setName(std::string name){ name_ = name; }
	std::string getName() const { return name_; }
private:
	std::string name_;
};

class AllNetPlayer : public Ref
{
public:
	static AllNetPlayer* create(std::string jsonData);
	bool init(std::string jsonData);

private:
	Vector<NetPlayer*>* allPLayers_;

};
#endif