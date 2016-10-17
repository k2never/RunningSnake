#include "RunningSnake.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;


const float SPPED_PLUS = 0.02f;
const float SPPED_INIT = 0.4f;
const float SPPED_LOWEST = 0.05f;

int SCORE_STEP = 1;

Scene* RunningSnake::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = RunningSnake::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool RunningSnake::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	int winWidth = visibleSize.width;
	int winHeight = visibleSize.height;

	auto background = Sprite::create("background.jpg");
	background->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	Rect rect = background->getTextureRect();
	background->setScale(MAX(winWidth / rect.size.width, winHeight / rect.size.height));
	this->addChild(background, -1);

	_gridNumOfHeight = 20;
	_step = winHeight / _gridNumOfHeight;
	int borderWidth = (winWidth % _step) / 2;
	int borderHeight = (winHeight % _step) / 2;

	_orignLeftBottom = Vec2(borderWidth, borderHeight);
	_gridNumOfWidth = winWidth / _step;

	auto label = Label::createWithTTF("Running Snake", "fonts/Marker Felt.ttf", 40);
	label->setPosition(Vec2(origin.x + winWidth / 2,
		origin.y + winHeight - label->getContentSize().height));
	this->addChild(label, 2);

	_scoreLable = Label::createWithTTF("Score: %d", "fonts/Marker Felt.ttf", 30);
	_scoreLable->setPosition(Vec2(origin.x + winWidth - _scoreLable->getContentSize().width,
		origin.y + winHeight - label->getContentSize().height));
	this->addChild(_scoreLable, 2);

	_levelLable = Label::createWithTTF("Level: %d", "fonts/Marker Felt.ttf", 30);
	_levelLable->setPosition(Vec2(origin.x + _levelLable->getContentSize().width,
		origin.y + winHeight - label->getContentSize().height));
	this->addChild(_levelLable, 2);

	initGame();

	auto eventListener = EventListenerTouchOneByOne::create();
	eventListener->setSwallowTouches(true);
	eventListener->onTouchBegan = CC_CALLBACK_2(RunningSnake::onTouchBegan, this);
	eventListener->onTouchMoved = CC_CALLBACK_2(RunningSnake::onTouchMoved, this);
	eventListener->onTouchEnded = CC_CALLBACK_2(RunningSnake::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, _snakeDraw);
	

	auto mouseListener = EventListenerKeyboard::create();
	mouseListener->onKeyPressed = CC_CALLBACK_2(RunningSnake::onKeyPressed, this);
	mouseListener->onKeyReleased = CC_CALLBACK_2(RunningSnake::onKeyReleased, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, _snakeDraw);

	_speed = SPPED_INIT;
	_selectUpate = schedule_selector(RunningSnake::update);
	schedule(_selectUpate, _speed);
    
    return true;
}

void RunningSnake::update(float delta)
{
	stepMove();
}

void RunningSnake::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	Snake::Orientation orientation;
	switch (keyCode)
	{
	case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		orientation = Snake::LEFT;
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		orientation = Snake::RIGHT;
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW:
		orientation = Snake::UP;
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		orientation = Snake::DOWN;
		break;
	default:
		break;
	}
	_snake.setOrientation(orientation);
}

void RunningSnake::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	
}

bool RunningSnake::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *pEvent)
{
	return true;
}

void RunningSnake::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *pEvent)
{
	Vec2 current = touch->getLocation();
	Vec2 pre = touch->getPreviousLocation();

	updateOrientation(pre, current);
}

void RunningSnake::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *pEvent)
{
}

void RunningSnake::updateOrientation(const Vec2& oriPoint, const Vec2& targetPoint)
{
	Vec2 dis = targetPoint - oriPoint;

	if (MAX(abs(dis.x), abs(dis.y)) < 10)
		return;

	Snake::Orientation orientation;
	if (abs(dis.x) > abs(dis.y))
	{
		orientation = dis.x > 0 ? Snake::RIGHT : Snake::LEFT;
	}
	else 
	{
		orientation = dis.y > 0 ? Snake::UP : Snake::DOWN;
	}
	_snake.setOrientation(orientation);
}

void RunningSnake::initGame()
{
	_score = 0;
	_level = 1;

	_appleDraw = Sprite::create();
	this->addChild(_appleDraw, 1);

	_snakeDraw = DrawNode::create();
	this->addChild(_snakeDraw, 1);

	_snakeBatchDraw = SpriteBatchNode::create("snake.png");
	this->addChild(_snakeBatchDraw, 2);
	_snakeBatchDraw->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);

	Vec2 head = Vec2(_gridNumOfWidth / 2, _gridNumOfHeight / 2);
	std::list<Vec2> body;
	body.push_back(head - Vec2(1, 0));
	body.push_back(body.back() - Vec2(1, 0));

	_snake.initSnake(_orignLeftBottom, head, body, _step);
	_snake.setOrientation(Snake::RIGHT);

	_apple.init(_orignLeftBottom, _step);

	randomApple();

	drawSnakeAndApple();
}

void RunningSnake::randomApple()
{
	bool getApple = false;
	Vec2 applePosition;
	while (!getApple)
	{
		applePosition = Vec2(random(0, _gridNumOfWidth - 1), random(0, _gridNumOfHeight - 1));
		getApple = !_snake.isInSnake(applePosition);
	}

	_apple.setPosition(applePosition);
}

void RunningSnake::drawSnakeAndApple()
{
	_snakeDraw->clear();
	_snakeBatchDraw->removeAllChildrenWithCleanup(true);
	_apple.draw(_appleDraw);
	//_snake.draw(_snakeDraw);
	_snake.draw(_snakeBatchDraw);
	_scoreLable->setString(StringUtils::format("Score: %d", _score));
	_levelLable->setString(StringUtils::format("Level: %d", _level));
}

bool RunningSnake::isSnakeKnockWall()
{
	Vec2 snakeHead = _snake.getHead();

	if (snakeHead.x < 0 || snakeHead.y < 0 || snakeHead.x >= _gridNumOfWidth || snakeHead.y >= _gridNumOfHeight)
		return true;

	return false;
}


void RunningSnake::stepMove()
{
	if (_snake.isSuicide() || isSnakeKnockWall())
	{
		unschedule(_selectUpate);
		return;
	}
	bool catchApple = _snake.isInSnake(_apple.getPosition());
	_snake.stepMove(catchApple);
	if (catchApple)
	{
		if (_speed > SPPED_LOWEST && _snake.getBody().size() % 5 == 0)
		{
			unschedule(_selectUpate);
			schedule(_selectUpate, _speed);
			_speed -= SPPED_PLUS;
			SCORE_STEP += _snake.getBody().size() / 5;

			_level++;
		}
		_score += SCORE_STEP;
		
		randomApple();
	}
	
	drawSnakeAndApple();
}


