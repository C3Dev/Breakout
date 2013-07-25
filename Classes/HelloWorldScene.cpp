//
//  HelloWorldScene.cpp
//  Breakout
//
//  Created by Corey Crooks on 3/5/13.
//
//


#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "GameOverScene.h"
#include "MenuLayerScene.h"
#include "WinGameLayer.h"
#include <math.h>



using namespace cocos2d;
using namespace CocosDenshion;


CCScene* GameLayer::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    BackgroundLayer *bglayer = BackgroundLayer::create();

    // add layer as a child to scene
    scene->addChild(bglayer);

    // 'layer' is an autorelease object
    GameLayer *layer = GameLayer::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

BackgroundLayer::BackgroundLayer(){}
BackgroundLayer::~BackgroundLayer(){}

bool BackgroundLayer::init()
{
    if(! CCLayer::init()){
        return false;
    }


    this->setTouchEnabled(false);

    return true;
}

GameLayer::~GameLayer()
{
    if (_blocks)
    {
        _blocks->release();
        _blocks = NULL;
    }
}

GameLayer::GameLayer()
// setup constructor
:_blocks(NULL),
ball_pos(250),
ball_posy(250),
score(0),
paddle_pos(0),
inputMode(false)

{
}


bool GameLayer::init()
{
float height = 32;
int windowHeight = 100;
int buttonWidth = 100;
int buttonHeight = 60;
int ballWidth = 28;
int ballHeight = 28;
_rows = 4;  // set how many rows in the window space
_columns = 5; // set columns for window space
    _blocks = new CCArray;
//    _blocks->autorelease();

    bool bRet = false;
    //////////////////////////////////////////////////////////////////////////
    // super init first
    //////////////////////////////////////////////////////////////////////////

    if(! CCLayer::init()){
        return false;
    }

    //////////////////////////////////////////////////////////////////////////
    // add your codes below...
    //////////////////////////////////////////////////////////////////////////

    /////////////////////////////
    // 2. add your codes below...
    this->setTouchEnabled(true);
	

    CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	CCUserDefault *def = CCUserDefault::sharedUserDefault ();
	inputMode = def->getBoolForKey("inputMode", false);

	sound = def->getBoolForKey("sound", true);

		if(sound)
		{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("computer_truck.mp3", true);
		}
//-------------------set up ball sprite------------------------------
    ball = CCSprite::create("ball_icon.png",CCRectMake(0, 0, ballWidth, ballHeight) );
    ball->setPosition( CCPoint(80,.5));
	ball->setAnchorPoint(ccp(.5,.5));
	ball->setTag(1);
    this->addChild(ball);

//-------------set up paddle------------------------------------------
    _paddleWidth = 100;
    _paddleHeight = 25;
    _paddle = CCSprite::create("Paddle.png");
    _paddle->setScaleX(_paddleWidth / _paddle->getContentSize().width);
    _paddle->setScaleY(_paddleHeight / _paddle->getContentSize().height);
    _paddle->setPosition( ccp(winSize.width / 2, _paddleHeight));
	_paddle->setAnchorPoint(ccp(0.5,0.5));
	_paddle->setTag(2);
    this->addChild(_paddle);
	
	

		leftButton = CCSprite::create("left_arrow.png", CCRectMake(0, 0, buttonWidth, buttonHeight) );
		leftButton->setScaleX(buttonWidth / leftButton->getContentSize().width);
		leftButton->setScaleY(buttonHeight / leftButton->getContentSize().height);
		leftButton->setPosition( CCPoint(0, 0));
		leftButton->setAnchorPoint(ccp(0,0));
		leftButton->setTag(3);
		this->addChild(leftButton);


		rightButton = CCSprite::create("right_arrow.png",CCRectMake(0, 0, buttonWidth, buttonHeight) );
		rightButton->setScaleX(buttonWidth / rightButton->getContentSize().width);
		rightButton->setScaleY(buttonHeight / rightButton->getContentSize().height);
		rightButton->setPosition( CCPoint(winSize.width, 0));
		rightButton->setAnchorPoint(ccp(1,0));
		rightButton->setTag(4);
		this->addChild(rightButton);

		touchLabel = CCLabelTTF::create(" ","Courier", 32);
	
	
	touchLabel->setPosition(ccp(winSize.width,winSize.height));
	touchLabel->setAnchorPoint(ccp(1,1));
	touchLabel->setColor( ccc3(255,255,255) );
	touchLabel->setTag(5);
	addChild(touchLabel);
	
	menuLabel = CCLabelTTF::create("Main Menu","Courier", 32);
	menuLabel->setPosition(ccp(0,winSize.height));
	menuLabel->setAnchorPoint(ccp(0,1));
	menuLabel->setColor( ccc3(255,255,255) );
	menuLabel->setTag(6);
	addChild(menuLabel);
	


	label = CCLabelTTF::create("Score: 0","Courier", 32);
	label->setPosition(ccp(winSize.width/2,winSize.height));
	label->setAnchorPoint(ccp(0.5,1));
	label->setColor( ccc3(255,255,255) );
	addChild(label);



    float width = winSize.width / _columns;
    // double for loop for matrics
    for (int i=0; i < _rows; i++){
        for (int j=0; j < _columns; j++){
            CCSprite *block = CCSprite::create("bar.jpeg");
            // width and height of the blocks
            block->setScaleX(width / block->getContentSize().width);
            block->setScaleY(height / block->getContentSize().height);

            block->setPosition( ccp((j*width), winSize.height - windowHeight - (i*height + block->getContentSize().height/2)) );
			block->setAnchorPoint(ccp(0,0));
			_blocks->addObject(block);
            this->addChild(block);
        }
    }















    // Create a "close" menu item with close icon, it's an auto release object.
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
        "CloseNormal.png",
        "CloseSelected.png",
        this,
        menu_selector(GameLayer::menuButtonCallback));
    pCloseItem->setPosition(ccp(winSize.width / 2, winSize.height - 40));


    bRet = true;

    this->schedule( schedule_selector(GameLayer::logSetup), 1.0 );
    this->schedule( schedule_selector(GameLayer::update) );
    return bRet;
}

void GameLayer::menuButtonCallback(CCObject* pSender)
{

    CCDirector::sharedDirector()->end();
}



void GameLayer::update(float dt)
{
    CCObject* it = NULL;
    ball->setPosition(ccp(ball->getPosition().x + ball_pos * dt, ball->getPosition().y + ball_posy * dt));
	_paddle->setPosition( ccp(_paddle->getPosition().x + paddle_pos * dt, _paddle->getPosition().y));

    CCRect ballRect = ball->boundingBox();

    // Check collisions with blocks
    CCARRAY_FOREACH(_blocks, it)
    {
        CCSprite *block = dynamic_cast<CCSprite*>(it);

        CCRect blockRect = block->boundingBox();
        if (blockRect.intersectsRect(ballRect))
        {
            _blocks->removeObject(block); //intersect and remove the block from the top
            this->removeChild(block, true); // need to remove the child
            ball_posy = -ball_posy;
			score += 1000; // update
			char text[256];
			sprintf(text,"Score: %d", score);
			label->setString(text);
			if(sound)
			{
				CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("bell.wav");
			}
        }
    }

    if (_blocks->count() == 0)
    {
        WinGameLayer *winGameLayer = WinGameLayer::create();
        CCDirector::sharedDirector()->replaceScene(winGameLayer);
		CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();

    }

    //check collision with paddle
    CCRect paddleRect = _paddle->boundingBox();
    if (paddleRect.intersectsRect(ballRect) && ball_posy < 0){
		if(ball->getPosition().x > _paddle->getPosition().x + 50 / _paddle->getContentSize().width)
		{
			ball_pos = 200*cos(3.1415/3);
			ball_posy = 200*sin(3.1415/3);
		}
		else if(ball->getPosition().x < _paddle->getPosition().x - 50 / _paddle->getContentSize().width)
		{
			ball_pos = -200*cos(3.1415/3);
			ball_posy = 200*sin(3.1415/3);
		}
		else
		{
			ball_posy = -ball_posy;
		}
		if(sound)
		{
			CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("blip.wav");
		}
    }

    if ((ball->getPosition().x > CCDirector::sharedDirector()->getWinSize().width && ball_pos > 0) || (ball->getPosition().x < 0 && ball_pos < 0)){
        ball_pos = -ball_pos;
    }

	if(ball->getPosition().y < 0 && ball_posy < 0)
	{
		GameOverScene *gameOverScene = GameOverScene::create();
        CCDirector::sharedDirector()->replaceScene(gameOverScene);
		CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
	}

    if (ball->getPosition().y > CCDirector::sharedDirector()->getWinSize().height && ball_posy > 0){
        ball_posy = -ball_posy;
    }
	if ((_paddle->getPosition().x > CCDirector::sharedDirector()->getWinSize().width && paddle_pos > 0) || (_paddle->getPosition().x < 0 && paddle_pos < 0)){
        paddle_pos = 0;
    }
}

// cpp with cocos2d-x
void GameLayer::logSetup(float dt)
{
}

// cpp with cocos2d-x
void GameLayer::ccTouchesMoved(CCSet* touches, CCEvent* event)
{
	CCSetIterator it = touches->begin();
	CCTouch* touch = (CCTouch*)(*it);

	CCPoint location = touch->getLocation();

		CCNode* s = getChildByTag(2);
		s->stopAllActions();

		if(location.x > s->getPosition().x)
		{
			paddle_pos = 250;
		}
		else
		{
			paddle_pos = -250;
		}

		CCNode* left = getChildByTag(3);
		float distance = ccpDistance(left->getPosition(),
			this->touchToPoint(touch));
		if(distance < 100.0f )
		{
			paddle_pos = -250;
		}

		CCNode* right = getChildByTag(4);
		distance = ccpDistance(right->getPosition(),
			this->touchToPoint(touch));
		if(distance < 100.0f )
		{
			paddle_pos = 250;
		}
	}



// cpp with cocos2d-x
void GameLayer::ccTouchesEnded(CCSet* touches, CCEvent* event)
{
	if(inputMode == false)
	{
		paddle_pos = 0;
	}
}

// cpp with cocos2d-x
void GameLayer::ccTouchesBegan(CCSet* touches, CCEvent* event)
{
	CCSetIterator it = touches->begin();
	CCTouch* touch = (CCTouch*)(*it);

	CCPoint location = touch->getLocation();


		CCNode* s = getChildByTag(2);
		if(location.x > s->getPosition().x)
		{
			paddle_pos = 250;
		}
		else
		{
			paddle_pos = -250;
		}

		CCNode* left = getChildByTag(3);
		float distance = ccpDistance(left->getPosition(),
			this->touchToPoint(touch));
		if(distance < 100.0f )
		{
			paddle_pos = -250;
		}

		CCNode* right = getChildByTag(4);
		distance = ccpDistance(right->getPosition(),
			this->touchToPoint(touch));
		if(distance < 100.0f )
		{
			paddle_pos = 250;
		}


	CCNode* touchBtn = getChildByTag(5);
	float d = ccpDistance(touchBtn->getPosition(),
		this->touchToPoint(touch));


	CCNode* menuBtn = getChildByTag(6);
	d = ccpDistance(menuBtn->getPosition(),
		this->touchToPoint(touch));
	if(d < 100.0f )
	{
		CCDirector::sharedDirector()->replaceScene(MenuLayerScene::scene());
		CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
	}
}

CCPoint GameLayer::touchToPoint(CCTouch* touch)
{
	// convert the touch object to a position in our cocos2d space
	return CCDirector::sharedDirector()->convertToGL(touch->getLocationInView());
}

void GameLayer::checkAccel(cocos2d::CCAcceleration* pointAccel)
{
		pointAccel->x;                //horizontal acceleration
		pointAccel->y;                //vertical acceleration
		//If you want to move sprite then can use it to change the position..

		if(inputMode)
		{
			paddle_pos = pointAccel->x*15000;
			if ((_paddle->getPosition().x > CCDirector::sharedDirector()->getWinSize().width && paddle_pos > 0) || (_paddle->getPosition().x < 0 && paddle_pos < 0))
			{
				paddle_pos = 0;
			}
		}
}



void GameLayer::backClicked()
{
    CCDirector::sharedDirector()->replaceScene(MenuLayerScene::scene());
	CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
}

void GameLayer::backAction(CCObject* pSender)
{
    CCDirector::sharedDirector()->replaceScene(MenuLayerScene::scene());
	CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
}



