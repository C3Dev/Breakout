//
//  WinGameLayer.cpp
//  Breakout
//
//  Created by Corey Crooks on 3/6/13.
//
//
#include "GameOverScene.h" 
#include "HelloWorldScene.h"

using namespace cocos2d;

bool GameOverScene::init()
{
    if( CCScene::init() )
    {
        this->_layer = GameOverLayer::create();
        this->_layer->retain();
        this->addChild(_layer);

        return true;
    }
    else
    {
        return false;
    }
}

GameOverScene::~GameOverScene()
{
    if (_layer)
    {
        _layer->release();
        _layer = NULL;
    }
}

bool GameOverLayer::init()
{
    if ( CCLayerColor::initWithColor( ccc4(255,255,255,255) ) )
    {
        CCSize windowSize = CCDirector::sharedDirector()->getWinSize();
      
        CCSprite* pSprite = CCSprite::create("gameover.jpg");
        
        pSprite->setPosition(ccp(windowSize.width/2,windowSize.height/2));
        this->addChild(pSprite,0);
        
        
       

        this->runAction( CCSequence::create(
                                CCDelayTime::create(3),
                                CCCallFunc::create(this, 
                                callfunc_selector(GameOverLayer::gameOverDone)),
                                NULL));

        return true;
    }
    else
    {
        return false;
    }
}

void GameOverLayer::gameOverDone()
{
    CCDirector::sharedDirector()->replaceScene(GameLayer::scene());
}

GameOverLayer::~GameOverLayer()
{
    if (_label)
    {
        _label->release();
        _label = NULL;
    }
}
