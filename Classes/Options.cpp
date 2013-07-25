//
//  Options.cpp
//  Breakout
//
//  Created by Corey Crooks on 3/5/13.
//
//

#include "Options.h" 
#include "MenuLayerScene.h" 
#include "HelloWorldScene.h"
#include "GameOverScene.h"

using namespace cocos2d;

CCScene* Options::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    OptionsLayer *optionsLayer = OptionsLayer::create();

    // add layer as a child to scene
    scene->addChild(optionsLayer);

    // 'layer' is an autorelease object
    Options *layer = Options::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

OptionsLayer::OptionsLayer(){}
OptionsLayer::~OptionsLayer(){}

bool OptionsLayer::init()
{
    if(! CCLayer::init()){
        return false;
    }
    this->setTouchEnabled(false);
    return true;
}

void OptionsLayer::update(cocos2d::CCTime dt){
}


Options::Options()
{
}

Options::~Options()
{
}


bool Options::init()
{

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
	
    CCSize windowSize = CCDirector::sharedDirector()->getWinSize();
	
    CCSprite* pSprite = CCSprite::create("background.jpeg");
    
    pSprite->setPosition(ccp(windowSize.width/2,windowSize.height/2));
    this->addChild(pSprite,0);
    
	
	label = CCLabelTTF::create("Settings","Courier", 55);
	label->setPosition(ccp(windowSize.width/2,windowSize.height-100));
	label->setColor( ccc3(255,255,255) );
	addChild(label);
	
	
    
    CCUserDefault *def = CCUserDefault::sharedUserDefault ();
	sound = def->getBoolForKey("sound", true);
	CCLabelTTF *lb = CCLabelTTF::create(" ","Courier",58);
	
	
	if(sound)
	{
		lb = CCLabelTTF::create("Sound On","Courier",45);
		def->setBoolForKey("sound", true);
	}
	else
	{
		lb = CCLabelTTF::create("Sound Off","Courier",45);
		def->setBoolForKey("sound", false);
	}
	lb->setColor( ccc3(255,255,255) );
	soundItem = CCMenuItemLabel::create(lb,this,menu_selector(Options::menuCallback));
	soundItem->setPosition(ccp(windowSize.width/2,windowSize.height-200-300)); // set position by CCMenuItemLabel
	
	lb = CCLabelTTF::create("Main Menu","Courier",45);
	lb->setColor( ccc3(255,255,255) );
	menuReturn = CCMenuItemLabel::create(lb,this,menu_selector(Options::menuCallback));
	menuReturn->setPosition(ccp(windowSize.width/2,windowSize.height-200-300)); // set position by CCMenuItemLabel
	
	CCMenu* itemMenu = CCMenu::create(soundItem, menuReturn, NULL);
    itemMenu->alignItemsVertically();
	
	addChild(itemMenu);
	
	
    bRet = true;
	
    return bRet;
}

void Options::menuCallback(CCNode* sender){

    if(sender == soundItem)
	{
		CCUserDefault *def = CCUserDefault::sharedUserDefault ();
		char t[256];

		if(def->getBoolForKey("sound", false))
		{
			sprintf(t,"Sound Off");
			def->setBoolForKey ("sound", false);
		}
		else
		{
			sprintf(t,"Sound On");
			def->setBoolForKey ("sound", true);
		}
		soundItem->setString(t);
	}
	else if(sender == menuReturn)
	{	
		MenuLayerScene *mm = MenuLayerScene::create();
		CCDirector::sharedDirector()->replaceScene(MenuLayerScene::scene());
	}
}
