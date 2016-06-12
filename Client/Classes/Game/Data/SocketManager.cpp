#include "SocketManager.h"
#include "Game/Object/NetPlayer.h"

using namespace network;
USING_NS_CC;
static SocketManager* gSockManager = nullptr;
SocketManager::SocketManager()
{

}

SocketManager::~SocketManager()
{

}

SocketManager* SocketManager::getInstance()
{
	if (gSockManager == nullptr)
	{
		gSockManager = new SocketManager();
		if (gSockManager && gSockManager->init())
		{
			gSockManager->autorelease();
			gSockManager->retain();
		}
	}
	return gSockManager;
}

bool SocketManager::init()
{

	return true;
}

bool SocketManager::connectServer(std::string url)
{
	socket_ = SocketIO::connect(url, *this);
	socket_->on("chat message", CC_CALLBACK_2(SocketManager::onChat, this));
	socket_->on("connect", CC_CALLBACK_2(SocketManager::connect, this));
	socket_->on("num Connect", CC_CALLBACK_2(SocketManager::onNum, this));
	socket_->on("upload name", CC_CALLBACK_2(SocketManager::onUploadName, this));
	socket_->on("all users", CC_CALLBACK_2(SocketManager::onAllUsers, this));
	socket_->on("start", CC_CALLBACK_2(SocketManager::onStart, this));
	return true;
}

void SocketManager::disConnect()
{

}

void SocketManager::sendMessage(std::string eventName, std::string data)
{
	socket_->emit(eventName, data);
}

void SocketManager::onConnect(SIOClient* client)
{

}

void SocketManager::onClose(SIOClient* client)
{

	CCLOG("on Close~~~~~");
	Director::getInstance()->end();
}

void SocketManager::onError(SIOClient* client, const std::string& data)
{

}

void SocketManager::onStart(SIOClient* client, const std::string data)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("start");
}

void SocketManager::onAllUsers(SIOClient* client, const std::string& data)
{
	std::string newData = SocketManager::parseJson(data);
	auto player = NetPlayer::create(newData);
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("NotifyNewUserIn", player);	

}

std::string SocketManager::parseJson(std::string data)
{
	std::string newData;
	for (int i = 1; i < data.size() - 1; ++i)
	{
		
		if (data.at(i) == (char)'\\')
			continue;
		if ((data.at(i) == (char)'[' )|| (data.at(i) == (char)']'))
			continue;

		newData.push_back(data.at(i));
		
	}

	for (int i = 0; i < newData.size(); i++)
	{
		if (newData.at(i) == (char)'\"')
			newData.at(i) = (char)'"';
	}
	return newData;
}

void SocketManager::onUploadName(SIOClient* client, const std::string& data)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("showUserList");
	this->sendMessage("login", "");
}

void SocketManager::onChat(SIOClient* client, const std::string& data)
{
	std::string newData;
	for (int i = 1; i < data.size() - 1; ++i)
	{
		newData.push_back(data.at(i));
	}
}

void SocketManager::connect(SIOClient* client, const std::string& data)
{
	CCLOG("on connect");

	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("showInputName");
}

void SocketManager::onNum(SIOClient* client, const std::string& data)
{
	std::string newData;
	for (int i = 1; i < data.size() - 1; ++i)
	{
		newData.push_back(data.at(i));
	}
}
