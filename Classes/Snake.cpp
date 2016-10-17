#include "Snake.h"

USING_NS_CC;

const Vec2 Snake::s_Left = Vec2(-1.0, 0.0);
const Vec2 Snake::s_Right = Vec2(1.0, 0.0);
const Vec2 Snake::s_Up = Vec2(0.0, 1.0);
const Vec2 Snake::s_Down = Vec2(0.0, -1.0);

const Vec2 Snake::LEFT_BOTTOM = Vec2(0.05f, 0.05f);
const Vec2 Snake::RIGHT_TOP = Vec2(0.95f, 0.95f);

Snake::Snake()
	:_isTurned(false)
{
}


Snake::~Snake()
{
}

void Snake::setOrientation(Orientation orientation)
{
	//1.同一方向忽略
	//2.如果之前方向改变且未移动的也忽略本次改动（有可能导致反方向移动）
	if (_orientation == orientation || _orientation == -orientation || _isTurned)
		return;

	_orientation = orientation;
	_isTurned = true;
}

void Snake::initSnake(cocos2d::Vec2 origin, cocos2d::Vec2 head, const std::list<cocos2d::Vec2> bodyList, int bodyNodeLength)
{
	_origin = origin;
	_head = head;
	_bodyList = bodyList;
	_bodyNodeLength = bodyNodeLength;

}

void Snake::draw(cocos2d::DrawNode* drawNode)
{
	int half = _bodyNodeLength / 2;
	Vec2 center(half, half);

	for (const Vec2 node : _bodyList)
	{
		drawNode->drawSolidRect(_origin + (node+LEFT_BOTTOM)*_bodyNodeLength, _origin + (node+RIGHT_TOP)*_bodyNodeLength, Color4F::BLUE);
	}

	drawNode->drawDot(_origin + center + _head*_bodyNodeLength, half, Color4F::BLACK);
}

void Snake::draw(cocos2d::SpriteBatchNode* drawNode)
{
	int half = _bodyNodeLength / 2;
	Vec2 center(half, half);

	for (const Vec2 node : _bodyList)
	{
		auto body = Sprite::create();
		if (node != _bodyList.back())
		{
			body->initWithTexture(drawNode->getTexture(), Rect(64, 0, 64, 64));
		}
		else
		{
			body->initWithTexture(drawNode->getTexture(), Rect(128, 0, 64, 64));
		}
		
		body->setScale(_bodyNodeLength / 64.f);
		Vec2 position = _origin + center + node*_bodyNodeLength;
		body->setPosition(position);
		drawNode->addChild(body);
	}

	auto head = Sprite::createWithTexture(drawNode->getTexture(), Rect(0, 0, 64, 64));
	head->setScale(_bodyNodeLength / 64.f);
	Vec2 position(_origin + center + _head*_bodyNodeLength);
	head->setPosition(position);
	currectSprite(head);
	drawNode->addChild(head);
}

void Snake::currectSprite(Sprite* node)
{
	switch (_orientation)
	{
	case Snake::RIGHT:
		node->setFlippedX(true);
		break;
	case Snake::UP:
		node->setRotation(90.0f);
		break;
	case Snake::DOWN:
		node->setRotation(-90.0f);
		break;
	default:
		return;
	}
}

void Snake::stepMove(bool catchApple)
{
	Vec2 moveDistance;
	switch (_orientation)
	{
	case Snake::RIGHT:
		moveDistance = Snake::s_Right;
		break;
	case Snake::LEFT:
		moveDistance = Snake::s_Left;
		break;
	case Snake::UP:
		moveDistance = Snake::s_Up;
		break;
	case Snake::DOWN:
		moveDistance = Snake::s_Down;
		break;
	default:
		return;
	}

	if (!catchApple)_bodyList.pop_back();
	_bodyList.push_front(_head);

	_head += moveDistance;

	_isTurned = false;
}

void Snake::eatApple()
{

}

bool Snake::isSuicide()
{
	for (const Vec2 node : _bodyList)
	{
		if (node == _head)
			return true;
	}

	return false;
}

bool Snake::isInSnake(const cocos2d::Vec2& position)
{
	for (const Vec2 node : _bodyList)
	{
		if (node == position)
			return true;
	}

	if (_head == position)
		return true;

	return false;
}
