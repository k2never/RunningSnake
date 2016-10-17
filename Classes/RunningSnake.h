#ifndef __RunningSnake_SCENE_H__
#define __RunningSnake_SCENE_H__

#include "cocos2d.h"
#include "Snake.h"
#include "Apple.h"

class RunningSnake : public cocos2d::Layer
{
public:

    static cocos2d::Scene* createScene();

    virtual bool init();
	void initGame();
	void randomApple();
	void drawSnakeAndApple();

	bool isSnakeKnockWall();

	void update(float delta);

	void updateOrientation(const cocos2d::Vec2& oriPoint, const cocos2d::Vec2& targetPoint);

	bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *pEvent);

	void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *pEvent);

	void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *pEvent);

	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
private:
	void stepMove();
    
    // implement the "static create()" method manually
    CREATE_FUNC(RunningSnake);
private:
	int _step;
	int _gridNumOfWidth;
	int _gridNumOfHeight;
	cocos2d::Rect _snakeTail;
	cocos2d::DrawNode* _snakeDraw;
	cocos2d::SpriteBatchNode* _snakeBatchDraw;
	cocos2d::Sprite* _appleDraw;
	cocos2d::Label* _scoreLable;
	cocos2d::Label* _levelLable;
	int _score;
	int _level;

	cocos2d::SEL_SCHEDULE _selectUpate;
	float _speed;

	cocos2d::Vec2 _orignLeftBottom;

	Snake _snake;
	Apple _apple;
};

#endif // __RunningSnake_SCENE_H__
