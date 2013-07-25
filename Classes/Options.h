#ifndef _OPTIONS_SCENE_H_
#define _OPTIONS_SCENE_H_

#include "cocos2d.h"

class Options : public cocos2d::CCLayer
{
private:

	bool sound;
	
	cocos2d::CCLabelTTF * label;
	
	cocos2d::CCMenu * itemMenu;
	
	cocos2d::CCMenuItemLabel * soundItem;
	cocos2d::CCMenuItemLabel * menuReturn;
	
	void menuCallback(cocos2d::CCNode* sender);

public:

	bool inputMode;
	
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();

    Options();
    ~Options();


    // implement the "static node()" method manually
    CREATE_FUNC(Options);
};


class OptionsLayer : public cocos2d::CCLayer
{
private:	
    void update(cocos2d::CCTime dt);

public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    OptionsLayer();
    ~OptionsLayer();

    // implement the "static node()" method manually
    CREATE_FUNC(OptionsLayer);
};


#endif // _OPTIONS_SCENE_H__
