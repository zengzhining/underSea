#ifndef _STORE_SCENE__
#define _STORE_SCENE__
#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"
#include "editor-support/cocostudio/CocoStudio.h"

USING_NS_CC;
using namespace cocos2d::ui;

class StoreScene : public Scene
{
public:
	CREATE_FUNC(StoreScene);
	bool init();

	void addEvent();

	void showNoticePanel();
	void updateUI();

private:
	Node* layer_;
	Layout* itemSeed_;
	Node* noticePanel_;

};
#endif