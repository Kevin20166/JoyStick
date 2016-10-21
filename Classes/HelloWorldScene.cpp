#include "HelloWorldScene.h"

#include "JoyStick.hpp"

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    rocker = JoyStick::create();
    rocker->setPosition(Vec2::ZERO);
    addChild(rocker);
    
    
    /*加载精灵帧播放图片*/
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("ButterFly.plist", "ButterFly.png");
    __Dictionary* dic = __Dictionary::createWithContentsOfFile("ButterFly.plist");
    __Dictionary* dic2 = dynamic_cast<__Dictionary*>(dic->objectForKey("frames"));
    Sprite* sp = Sprite::createWithSpriteFrameName("fish_001.png");
    sp->setFlippedX(true);
    sp->setTag(159);
    sp->setPosition(Vec2(480, 320));
    addChild(sp);
    Vector<SpriteFrame*> allFrame;
    for (int i = 1; i <= dic2->count(); i++) {
        SpriteFrame* sf = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("fish_0%02d.png",i));
        allFrame.pushBack(sf);
    }
    
    Animation* animtaion = Animation::createWithSpriteFrames(allFrame, 0.1);
    
    
    Animate* animte = Animate::create(animtaion);
    
    sp->runAction(RepeatForever::create(animte));
    
    /*开启检查调度*/
    schedule(CC_CALLBACK_1(HelloWorld::schedulePos,this), "POS");
    return true;
}

/*让我们的精灵按照摇杆的力度移动距离*/
void HelloWorld::schedulePos(float dt)
{
    /*获取摇杆到圆点的位置*/
    auto dis = rocker->getRocker()->getPosition().distance(rocker->getRockerBg()->getPosition());
    dis /= 20.0;
    log("%f", dis);
    auto hero = getChildByTag(159);
    float angle = rocker->getAngle();
   
    switch (rocker->getDir()) {
        case RDIRECTION::UP:
            hero->setPositionY(hero->getPositionY()+dis);
            break;
        case RDIRECTION::DOWN:
            log("xia");
            hero->setPositionY(hero->getPositionY()-dis);
            break;
        case RDIRECTION::LEFT:
            hero->setPositionX(hero->getPositionX()-dis);
            break;
        case RDIRECTION::RIGHT:
            hero->setPositionX(hero->getPositionX()+dis);
            break;
        case RDIRECTION::L_UP:
            hero->setPosition(hero->getPosition()+Vec2(dis*cos(angle),dis*sin(angle)));
            break;
        case RDIRECTION::R_UP:
            hero->setPosition(hero->getPosition()+Vec2(dis*cos(angle),dis*sin(angle)));
            break;
        case RDIRECTION::L_DOWN:
            hero->setPosition(hero->getPosition()+Vec2(dis*cos(angle),-dis*sin(angle)));
            break;
        case RDIRECTION::R_DOWN:
            hero->setPosition(hero->getPosition()+Vec2(dis*cos(angle),-dis*sin(angle)));
            break;
            
        default:
            break;
    }
}