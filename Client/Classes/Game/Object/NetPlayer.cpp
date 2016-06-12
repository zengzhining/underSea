#include "NetPlayer.h"
#include "json/rapidjson.h"
#include "json/document.h"

USING_NS_CC;

NetPlayer* NetPlayer::create(std::string jsonStr)
{
	auto player = new NetPlayer();
	if (player && player->init(jsonStr))
	{
		player->autorelease();
		return player;
	}
	return nullptr;
}

bool NetPlayer::init(std::string jsonStr)
{
	rapidjson::Document d;
	d.Parse<0>(jsonStr.c_str());
	if (d.HasParseError())  //
	{
		CCLOG("GetParseError %s\n", d.GetParseError());
	}

	if (d.IsObject()) {
		
		std::string name = d["name_"].GetString();//
		this->setName(name);
	}

	return true;
}

bool NetPlayer::init()
{
	this->setName("");
	return true;
}

AllNetPlayer* AllNetPlayer::create(std::string jsonData)
{
	auto player = new AllNetPlayer();
	if (player && player->init(jsonData))
	{
		player->autorelease();
		return player;
	}
	return nullptr;
}

bool AllNetPlayer::init(std::string jsonData)
{
	allPLayers_ = new Vector<NetPlayer*>();
	rapidjson::Document d;
	d.Parse<0>(jsonData.c_str());
	if (d.HasParseError())  //
	{
		CCLOG("GetParseError %s\n", d.GetParseError());
	}

	if (d.IsObject()) {
		for (auto itr = d.MemberBegin(); itr != d.MemberEnd(); ++itr)
		{

		}
		CCLOG("%s\n", d["name_"].GetString());//
	}
	return true;
}