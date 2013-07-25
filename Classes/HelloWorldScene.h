#ifndef __GameLayer_SCENE_H__
#define __GameLayer_SCENE_H__

#include "cocos2d.h"

class GameLayer: public cocos2d::CCLayer {
private:
	int _rows; 	// rows needed for rows in the window for block placement
	int _columns; // same with columns
	int score;

	float _paddleWidth; // height of paddle
	float _paddleHeight; // width of paddle use with window

	float ball_pos;
	float ball_posy;
	float paddle_pos;

	cocos2d::CCLabelTTF * label;
	cocos2d::CCLabelTTF * touchLabel;
	cocos2d::CCLabelTTF * menuLabel;

	cocos2d::CCSprite * ball;
	cocos2d::CCSprite * _paddle;
	cocos2d::CCSprite * leftButton;
	cocos2d::CCSprite * rightButton;

	cocos2d::CCArray* _blocks; // array to hold each of the block to be displayed on by loop

	void backAction(cocos2d::CCObject* pSender);
	void checkAccel(cocos2d::CCAcceleration* pAccelerationValue);
	void logSetup(float dt);

	void backClicked();

	//default methods
	void ccTouchesMoved(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
	void ccTouchesBegan(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
	void ccTouchesEnded(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
	cocos2d::CCPoint touchToPoint(cocos2d::CCTouch* touch);

	void update(float dt);

	// a selector callback
	void menuButtonCallback(CCObject* pSender);

public:

	bool inputMode;
	bool sound;

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// there's no 'id' in cpp, so we recommand to return the exactly class pointer
	static cocos2d::CCScene* scene();

	GameLayer();
	~GameLayer();

	// implement the "static node()" method manually
	CREATE_FUNC (GameLayer);
};

class BackgroundLayer: public cocos2d::CCLayer {
private:
	void update(cocos2d::CCTime dt);

public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	BackgroundLayer();
	~BackgroundLayer();

	// implement the "static node()" method manually
	CREATE_FUNC (BackgroundLayer);
};

#endif // __GameLayer_SCENE_H__
