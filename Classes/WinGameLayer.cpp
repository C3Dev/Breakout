//
//  WinGameLayer.cpp
//  Breakout
//
//  Created by Corey Crooks on 3/7/13.
//
//

#include "WinGameLayer.h"
#include "GameOverScene.h"
#include "HelloWorldScene.h"

using namespace cocos2d;

bool WinGameLayer::init()
{
    if( CCScene::init() )
    {
        this->_layer = WinLayer::create();
        this->_layer->retain();
        this->addChild(_layer);
        
        return true;
    }
    else
    {
        return false;
    }
}

WinGameLayer::~WinGameLayer()
{
    if (_layer)
    {
        _layer->release();
        _layer = NULL;
    }
}

bool WinLayer::init()
{
    if ( CCLayerColor::initWithColor( ccc4(255,255,255,255) ) )
    {
        CCSize windowSize = CCDirector::sharedDirector()->getWinSize();
        
        CCSprite* sprite = CCSprite::create("win.jpeg");
        
        sprite->setPosition(ccp(windowSize.width/2,windowSize.height/2));
        this->addChild(sprite,0);
        
        
        
        
        this->runAction( CCSequence::create(
                                            CCDelayTime::create(3),
                                            CCCallFunc::create(this,callfunc_selector(WinLayer::WinGameDone)),
                                            NULL));
        
        return true;
    }
    else
    {
        return false;
    }
}

void WinLayer::WinGameDone()
{
    CCDirector::sharedDirector()->replaceScene(GameLayer::scene());
}

WinLayer::~WinLayer()
{
    if (_label)
    {
        _label->release();
        _label = NULL;
    }
}
