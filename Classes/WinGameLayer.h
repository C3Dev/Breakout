//
//  WinGameLayer.h
//  Breakout
//
//  Created by Corey Crooks on 3/7/13.
//
//

#ifndef _WIN_GAME_LAYER_H_
#define _WIN_GAME_LAYER_H_

#include "cocos2d.h"

class WinLayer : public cocos2d::CCLayerColor
{
public:
    WinLayer():_label(NULL) {};
    virtual ~WinLayer();
    bool init();
    CREATE_FUNC(WinLayer);
    
    void WinGameDone();
    
    CC_SYNTHESIZE_READONLY(cocos2d::CCLabelTTF*, _label, Label);
};

class WinGameLayer : public cocos2d::CCScene
{
public:
    WinGameLayer():_layer(NULL) {};
    ~WinGameLayer();
    bool init();
    CREATE_FUNC(WinGameLayer);
    
    CC_SYNTHESIZE_READONLY(WinLayer*, _layer, Layer);
};

#endif  //_WIN_GAME_LAYER_H_
