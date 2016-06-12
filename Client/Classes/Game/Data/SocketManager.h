#ifndef _SOCKET_MANAGER__
#define _SOCKET_MANAGER__
#include "cocos2d.h"
#include "network/SocketIO.h"

USING_NS_CC;
using namespace network;
class SocketManager : public Ref, public network::SocketIO::SIODelegate
{
public:
	static SocketManager* getInstance();
	SocketManager();
	~SocketManager();

	bool init();

	bool connectServer(std::string url);
	void disConnect();
	void sendMessage(std::string eventName, std::string data);

	void onConnect(SIOClient* client) override;
	void onClose(SIOClient* client) override;
	void onError(SIOClient* client, const std::string& data) override;

	void onChat(SIOClient* client, const std::string& data);
	void connect(SIOClient* client, const std::string& data);
	void onNum(SIOClient* client, const std::string& data);
	void onUploadName(SIOClient* client, const std::string& data);
	void onAllUsers(SIOClient* client, const std::string& data);
	void onStart(SIOClient* client, const std::string data);

	static std::string parseJson(std::string data);

private:
	SIOClient* socket_;

};
#endif