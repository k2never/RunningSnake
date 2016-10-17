#ifndef __APPLE_H__
#define __APPLE_H__

#include "cocos2d.h"

class Apple
{
public:
	Apple();
	~Apple();
	void init(cocos2d::Vec2 origin, int width);
	void setPosition(const cocos2d::Vec2& position){ _position = position; }
	const cocos2d::Vec2& getPosition(){ return _position; }
	void draw(cocos2d::DrawNode* drawNode);
	void draw(cocos2d::Sprite* sprite);

private:
	cocos2d::Vec2	_position;
	cocos2d::Vec2	_origin;
	int				_width;
};

#endif
