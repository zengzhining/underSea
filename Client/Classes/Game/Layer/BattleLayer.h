#ifndef _BATTLE__LAYER___
#define _BATTLE__LAYER___
#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"
#include "editor-support/cocostudio/CocoStudio.h"


USING_NS_CC;
using namespace cocos2d::ui;

class BattleLayer : public Layer
{
public:
	enum OBJOrder
	{
		BG,
		ROLE,
		UI

	};
	CREATE_FUNC(BattleLayer);
	bool init();
	void initResult(Node* node);

	void addRes();
	void createBg();
	void createUI();
	void updateUI();
	void createLevelObject();
	void addEvent();

	void initLifeBar();
	void initComboUI();
	void initItemBtn();

	bool dealTouchBegan(Touch* touch, Event* event);

	Vec2 getSpeed();
	Vec2 getAcc();
	Vec2 getPos( Size size );

	void updateTime(float dt);

	void update(float delta);
	
	bool isEffectPlay() const { return isEffectPlay_; }
	void setEffectPlay(bool flag) { isEffectPlay_ = flag; }

	//显示游戏结果
	void showResult();

	void hideUI(); //显示游戏结果时候隐藏游戏的UI
	void showUI();

	void onEnter() override ;
	void onExit() override;
private:
	Node* bg_;
	TextBMFont* scoreLb_;
	TextBMFont* comboLb_;
	LoadingBar* lifeBar_;
	ImageView* leftBtn_;
	ImageView* rightBtn_;
	bool isEffectPlay_;
};
#endif