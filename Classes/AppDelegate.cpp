//
//  AppDelegate.cpp
//  Breakout
//
//  Created by Corey Crooks on 2/27/13.
//
//

#include "AppDelegate.h"

#include "cocos2d.h"
#include "HelloWorldScene.h"
#include "MenuLayerScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

using namespace CocosDenshion;

AppDelegate::AppDelegate()
{

}

AppDelegate::~AppDelegate()
{
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());

    // turn on display FPS
    pDirector->setDisplayStats(false);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    CCScene *pScene = MenuLayerScene::scene();

    // run
    pDirector->runWithScene(pScene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->pause();
	CCUserDefault *def = CCUserDefault::sharedUserDefault ();
	if(def->getBoolForKey("sound", true))
	{
		SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
	}
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->resume();
    CCUserDefault *def = CCUserDefault::sharedUserDefault ();
	if(def->getBoolForKey("sound", true))
	{
		SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
	}
}
