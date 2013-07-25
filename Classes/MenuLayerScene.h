#ifndef _MENU_LAYER_SCENE_H_
#define _MENU_LAYER_SCENE_H_

#include "cocos2d.h"

class MenuLayerScene : public cocos2d::CCLayer
{
private:
	cocos2d::CCLabelTTF * label;
	
	cocos2d::CCMenu * itemMenu;
	cocos2d::CCMenuItemLabel * play;
	cocos2d::CCMenuItemLabel * settings;
	cocos2d::CCMenuItemLabel * quit;
	
	void backPressed(cocos2d::CCObject* pSender);
	void returnMenu(cocos2d::CCNode* sender);
	// void endKey();

public:

	 bool input;
	
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();

    MenuLayerScene();
    ~MenuLayerScene();


    // implement the "static node()" method manually
    CREATE_FUNC(MenuLayerScene);
};


class MainMenuLayer : public cocos2d::CCLayer
{
private:	
    void update(cocos2d::CCTime dt);

public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    MainMenuLayer();
    ~MainMenuLayer();

    // implement the "static node()" method manually
    CREATE_FUNC(MainMenuLayer);
};


#endif // _Menu_Layer_SCENE_H__
