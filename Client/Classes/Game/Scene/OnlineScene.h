#ifndef __ONLINE_SCENE__
#define __ONLINE_SCENE__
#include "cocos2d.h"

#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"
#include "editor-support/cocostudio/CocoStudio.h"


USING_NS_CC;
using namespace cocos2d::ui;

class OnlineScene : public Scene
{
public:
	CREATE_FUNC(OnlineScene);

	bool init();

	void initWidget();
	void addEvent();

	void startGame();

	void addInputNamePanel();
	void addNewUser(std::string name);

	void onEnter() override;
	void onExit() override;
private:
	Node* bg_;
	Node* inputPanel_;
	Node* seedNameItem_;
	ListView* userList_;
};
#endif