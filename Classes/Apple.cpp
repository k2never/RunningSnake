#include "Apple.h"
USING_NS_CC;

Apple::Apple()
{
}


Apple::~Apple()
{
}

void Apple::init(cocos2d::Vec2 origin, int width)
{
	_origin = origin;
	_width = width;
}

void Apple::draw(cocos2d::DrawNode* drawNode)
{
	int half = _width / 2;
	Vec2 center(half, half);
	drawNode->drawDot(_origin + center + _position*_width, half, Color4F::RED);
}

void Apple::draw(cocos2d::Sprite* sprite)
{
	sprite->initWithFile("apple.png");
	sprite->setPosition(_origin + _position*_width);
	Rect rect = sprite->getTextureRect();
	sprite->setScale(_width / rect.size.width);
	sprite->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
}

