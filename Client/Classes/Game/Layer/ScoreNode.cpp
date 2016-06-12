#include "ScoreNode.h"
USING_NS_CC;

bool ScoreNode::init()
{
	if (!Node::init())
		return false;
	initData();
	initUI();

	return true;
}

void ScoreNode::initData()
{

}

void ScoreNode::initUI()
{
	addBg();
	addScoreUI();
	addButton();
	addDesUI();

}

void ScoreNode::addScoreUI()
{
	auto size = Director::getInstance()->getVisibleSize();
	for (int i = -1; i <= 1; i++)
	{
		auto sp = Sprite::createWithSpriteFrameName("star_full.png");
		auto bgSize = bg_->getContentSize();
		float scaleX = size.width * (63 / 64.0f) / bgSize.width;
		float scaleY = size.height * (562 / 960.0f) / bgSize.height;
		sp->setScale(scaleX, scaleY);
		sp->setPosition(i * size.width * 0.25f, size.height * 0.00f);
		addChild(sp);
	}
}

void ScoreNode::addButton()
{
	auto size = Director::getInstance()->getVisibleSize();
	auto restartSp = Sprite::createWithSpriteFrameName("icon_back.png");
	auto restartSpPress = Sprite::createWithSpriteFrameName("icon_back_press.png");
	auto bgSize = bg_->getContentSize();
	float scaleX = size.width * (63 / 64.0f) / bgSize.width;
	float scaleY = size.height * (562 / 960.0f) / bgSize.height;
	restartSp->setScale(scaleX, scaleY);
	auto contentSize = restartSp->getContentSize();
	restartSpPress->setScale(scaleX, scaleY);
	restartSp->setContentSize( Size( contentSize.width * scaleX, contentSize.height * scaleY ) );
	restartSpPress->setContentSize( Size( contentSize.width * scaleX, contentSize.height * scaleY ) );
	restartItem_ = MenuItemSprite::create(restartSp , restartSpPress, nullptr, [this](Ref* ref){
		this->restart();
	});

	auto backSp = Sprite::createWithSpriteFrameName("icon_flash.png");
	auto backSpPress = Sprite::createWithSpriteFrameName("icon_flash_press.png");
	backSp->setScale(scaleX, scaleY);
	backSpPress->setScale(scaleX, scaleY);
	backSp->setContentSize( Size( contentSize.width * scaleX, contentSize.height * scaleY ) );
	backSpPress->setContentSize( Size( contentSize.width * scaleX, contentSize.height * scaleY ) );
	backItem_ = MenuItemSprite::create(backSp , backSpPress, nullptr, [this](Ref* ref){
		this->goBack();
	});

	auto nextSp = Sprite::createWithSpriteFrameName("icon_start.png");
	auto nextSpPress = Sprite::createWithSpriteFrameName("icon_start_press.png");
	nextSp->setScale(scaleX, scaleY);
	nextSpPress->setScale(scaleX, scaleY);
	nextSp->setContentSize( Size( contentSize.width * scaleX, contentSize.height * scaleY ) );
	nextSpPress->setContentSize( Size( contentSize.width * scaleX, contentSize.height * scaleY ) );
	nextItem_ = MenuItemSprite::create( nextSp , nextSpPress, nullptr, [this](Ref* ref){
		this->goNext();
	});

	restartItem_->setPosition(0.0f, size.width * -0.25f);
	nextItem_->setPosition(0.0f, size.width * 0.25f);

	Vector<MenuItem*> menuArray;
	menuArray.pushBack(restartItem_);
	menuArray.pushBack(backItem_);
	menuArray.pushBack(nextItem_);

	auto menu = Menu::createWithArray(menuArray);
	menu->alignItemsHorizontally();
	menu->setPosition(0.0f, -size.height * 0.20f);
	addChild(menu);

}

void ScoreNode::addBg()
{
	// auto size = Director::getInstance()->getVisibleSize();
	// bg_ = Sprite::create("BackGround/LevelBg.png");
	// auto bgSize = bg_->getContentSize();
	// float scaleX = size.width * (63/64.0f) / bgSize.width;
	// float scaleY = size.height * (562/960.0f)/ bgSize.height;
	// bg_->setScale(scaleX, scaleY);
	// bg_->setPosition(0, -size.height * 0.10f);
	// addChild(bg_);
}

void ScoreNode::addDesUI()
{
	auto size = Director::getInstance()->getVisibleSize();
	desSp_ = Sprite::createWithSpriteFrameName("cleared.png");
	auto bgSize = bg_->getContentSize();
	float scaleX = size.width * (63 / 64.0f) / bgSize.width;
	float scaleY = size.height * (562 / 960.0f) / bgSize.height;
	desSp_->setScale(scaleX, scaleY);
	desSp_->setPosition(0.0f, size.height * 0.30f);
	addChild(desSp_);
}

void ScoreNode::restart()
{

}

void ScoreNode::goBack()
{

}

void ScoreNode::goNext()
{

}