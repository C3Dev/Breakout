//
//  MenuLayerScene.cpp
//  Breakout
//
//  Created by Corey Crooks on 3/1/13.
//
//
#include "MenuLayerScene.h" 
#include "HelloWorldScene.h"
#include "Options.h"

using namespace cocos2d;

CCScene* MenuLayerScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    MainMenuLayer *mmLayer = MainMenuLayer::create();

    // add layer as a child to scene
    scene->addChild(mmLayer);

    // 'layer' is an autorelease object
    MenuLayerScene *layer = MenuLayerScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

MainMenuLayer::MainMenuLayer(){}
MainMenuLayer::~MainMenuLayer(){}

bool MainMenuLayer::init()
{
    if(! CCLayer::init()){
        return false;
    }

    

    this->setTouchEnabled(false);
    return true;
}

void MainMenuLayer::update(cocos2d::CCTime dt){
}


MenuLayerScene::MenuLayerScene()
{
}

MenuLayerScene::~MenuLayerScene()
{
}


bool MenuLayerScene::init()
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
	this->isKeypadEnabled();
    // cpp with cocos2d-x
	
	// create background image (sprite background)
    CCSize windowSize = CCDirector::sharedDirector()->getWinSize();
    CCSprite* pSprite = CCSprite::create("1974steve_jobs_breakout.jpg");
    
    pSprite->setPosition(ccp(windowSize.width/2,windowSize.height/2));
    this->addChild(pSprite,0);
    
    
    //-------------------Set menu labels-----------------------
	
	CCLabelTTF *lb = CCLabelTTF::create("New Game","Impact",64.0);
	lb->setColor( ccc3(0,0,0) );
	play = CCMenuItemLabel::create(lb,this,menu_selector(MenuLayerScene::returnMenu));
    play->setPosition(ccp(windowSize.width-300-665,windowSize.height-200-230)); // set position by CCMenuItemLabel

	
	lb = CCLabelTTF::create("Settings","Impact", 64.0);
	lb->setColor( ccc3(0,0,0) );
	settings = CCMenuItemLabel::create(lb,this,menu_selector(MenuLayerScene::returnMenu));
	settings->setPosition(ccp(windowSize.width-300-680,windowSize.height-200-315)); // set position by CCMenuItemLabel
	
	
	lb = CCLabelTTF::create("Quit","Impact",64.0);
	lb->setColor( ccc3(0,0,0) );
	quit = CCMenuItemLabel::create(lb,this,menu_selector(MenuLayerScene::returnMenu));
	quit->setPosition(ccp(windowSize.width-300-745,windowSize.height-200-400)); // set position by CCMenuItemLabel
	

	//set text for my name


	CCMenu* itemMenu = CCMenu::create(play, settings, quit, NULL);

	
    
	addChild(itemMenu);
	
	
    bRet = true;
	
    return bRet;
}

void MenuLayerScene::returnMenu(CCNode* sender){
	if(sender == play)
	{
		GameLayer *mg = GameLayer::create();
		CCDirector::sharedDirector()->replaceScene(GameLayer::scene());
	}
	else if(sender == settings)
	{
		CCDirector::sharedDirector()->replaceScene(Options::scene());
	}
	else
	{
		CCDirector::sharedDirector()->end();
	} 

}

void MenuLayerScene::backPressed(CCObject* pSender)
{
   CCDirector::sharedDirector()->end();
}
