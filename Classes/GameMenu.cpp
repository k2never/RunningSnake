#include "ui/CocosGUI.h"
#include "RunningSnake.h"
#include "GameMenu.h"

USING_NS_CC;


GameMenu::GameMenu()
{
}


GameMenu::~GameMenu()
{
}

Scene* GameMenu::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = GameMenu::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}


bool GameMenu::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Director::getInstance()->setDisplayStats(false);

	int winWidth = visibleSize.width;
	int winHeight = visibleSize.height;

	auto background = Sprite::create("background.jpg");
	background->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	Rect rect = background->getTextureRect();
	background->setScale(MAX(winWidth / rect.size.width, winHeight / rect.size.height));
	this->addChild(background, -1);

	auto gameName = Label::createWithTTF("Running Snake", "fonts/Marker Felt.ttf", 40);
	gameName->setPosition(Vec2(winWidth / 2, winHeight - gameName->getContentSize().height*2));
	this->addChild(gameName, 0);

	auto startButton = ui::Button::create("button.jpg");
	startButton->setTitleText("Play");
	startButton->setTitleFontSize(28);
	startButton->setPosition(Vec2(winWidth / 2, winHeight*0.7));
	startButton->addTouchEventListener([](Ref* pSender, ui::Widget::TouchEventType type){
		if (type == ui::Widget::TouchEventType::ENDED){
			auto transition = TransitionSlideInL::create(0.5, RunningSnake::createScene());
			Director::getInstance()->replaceScene(transition);
		}
	});
	this->addChild(startButton, 1);

	auto settingButton = ui::Button::create("button.jpg");
	settingButton->setTitleText("Options");
	settingButton->setTitleFontSize(28);
	settingButton->setPosition(Vec2(winWidth / 2, winHeight*0.5));
	this->addChild(settingButton, 1);

	auto quitButton = ui::Button::create("button.jpg");
	quitButton->setTitleText("Quit");
	quitButton->setTitleFontSize(28);
	quitButton->setPosition(Vec2(winWidth / 2, winHeight*0.3));
	quitButton->addTouchEventListener([](Ref* pSender, ui::Widget::TouchEventType type){
		Director::getInstance()->end();
		#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
				exit(0);
		#endif
	});
	this->addChild(quitButton, 1);

	auto ellaName = Label::createWithTTF("Ella Book: http://www.ella.cn", "fonts/Marker Felt.ttf", 18);
	ellaName->setPosition(Vec2(winWidth / 2, ellaName->getContentSize().height));
	this->addChild(ellaName, 2);

	auto ella = Sprite::create("ella.png");
	ella->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
	ella->setScale(0.5);
	ella->setPosition(Vec2(winWidth / 2, ellaName->getContentSize().height*2));
	this->addChild(ella, 2);

	return true;
}