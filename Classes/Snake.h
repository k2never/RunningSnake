#ifndef __SNAKE_H__
#define __SNAKE_H__

#include "cocos2d.h"

class Snake
{
public:
	static const cocos2d::Vec2 s_Left;
	static const cocos2d::Vec2 s_Right;
	static const cocos2d::Vec2 s_Up;
	static const cocos2d::Vec2 s_Down;

	static const cocos2d::Vec2 LEFT_BOTTOM;
	static const cocos2d::Vec2 RIGHT_TOP;

	enum Orientation
	{
		UNKNOWN = 0,
		LEFT	= 1,
		RIGHT	= -1,
		UP		= 2,
		DOWN	= -2
	};

	const cocos2d::Vec2& getHead(){ return _head; }
	const std::list<cocos2d::Vec2>& getBody(){ return _bodyList; }

	void setOrientation(Orientation orientation);
	Orientation getOrientation() { return _orientation; }

	void initSnake(cocos2d::Vec2 origin, cocos2d::Vec2 head, const std::list<cocos2d::Vec2> bodyList, int bodyNodeLength);

	void draw(cocos2d::DrawNode* drawNode);
	void draw(cocos2d::SpriteBatchNode* drawNode);

	void stepMove(bool catchApple);

	void currectSprite(cocos2d::Sprite* node);

	bool isSuicide();

	bool isInSnake(const cocos2d::Vec2& position);

	void eatApple();

	Snake();
	~Snake();
private:
	cocos2d::Vec2				_origin;//左下角原点坐标
	cocos2d::Vec2				_head;//蛇头
	int							_bodyNodeLength;//蛇身每节长度
	std::list<cocos2d::Vec2>	_bodyList;//蛇身
	Orientation					_orientation;//蛇当前运行方向
	bool						_isTurned;//标记一次方向的改变
};

#endif
