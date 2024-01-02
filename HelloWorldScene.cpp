/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "rule.h"
#include "network/WebSocket.h"
USING_NS_CC;


class WebSocketClient : public cocos2d::network::WebSocket::Delegate
{
public:
    // WebSocket 事件回调
    virtual void onOpen(cocos2d::network::WebSocket* ws) override
    {
        CCLOG("WebSocket connection opened");
    }

    virtual void onMessage(cocos2d::network::WebSocket* ws, const cocos2d::network::WebSocket::Data& data) override
    {
        std::string message(data.bytes, data.len);
        CCLOG("Received message: %s", message.c_str());
    }

    virtual void onClose(cocos2d::network::WebSocket* ws) override
    {
        CCLOG("WebSocket connection closed");
    }

    virtual void onError(cocos2d::network::WebSocket* ws, const cocos2d::network::WebSocket::ErrorCode& error) override
    {
        CCLOG("WebSocket error with code: %d", static_cast<int>(error));
    }
};


Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////   
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.



    std::string url = "ws://100.81.202.165:8080";
    auto websocket = new cocos2d::network::WebSocket();
    websocket->init(*new WebSocketClient(),url);
   
    // 发送消息给服务器
    std::string message = "Hello, server!";
    websocket->send(message);





    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
        "CloseNormal.png",
        "CloseSelected.png",
        CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 2;
        float y = origin.y + closeItem->getContentSize().height / 2;
        closeItem->setPosition(Vec2(x, y));
    }

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label

    auto label = Label::createWithTTF("TFT", "fonts/Marker Felt.ttf", 24);
    if (label == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        // position the label on the center of the screen
        label->setPosition(Vec2(origin.x + visibleSize.width / 2,
            origin.y + visibleSize.height - label->getContentSize().height));
        // add the label as a child to this layer
        this->addChild(label, 1);
    }




    auto rules = Sprite::create("rules.png");
    rules->setPosition(Vec2(origin.x + visibleSize.width / 2,
        origin.y + visibleSize.height / 2));
    this->addChild(rules);

    auto _mouseListener = EventListenerTouchOneByOne::create();
    _mouseListener->onTouchBegan = CC_CALLBACK_2(HelloWorld::touchBeganButtonStart, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(_mouseListener, rules);


    


    return true;
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
    EventCustom customEndEvent("game_scene_close_event");
    _eventDispatcher->dispatchEvent(&customEndEvent);
}

bool HelloWorld::touchBeganButtonStart(cocos2d::Touch* touch, cocos2d::Event* event)
{
    Vec2 touPoint = touch->getLocation();
    auto sprite = static_cast<Sprite*>(event->getCurrentTarget());
    if (sprite->getBoundingBox().containsPoint(touPoint)) {
        auto targetScene = rule::create();
        Director::getInstance()->pushScene(targetScene);
        
        return true;
    }
    return false;

}

