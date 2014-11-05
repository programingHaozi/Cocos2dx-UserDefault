#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include <tinyxml2/tinyxml2.h>
#include <json/document.h>
USING_NS_CC;

using namespace cocostudio::timeline;

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
    
    /*~~~~~~~~~UserDefault~~~~~~~~~*/
    UserDefault::getInstance()->setStringForKey("data", "UserDefault");
    log("%s",UserDefault::getInstance()->getStringForKey("data", "helloWorld").c_str());
    
    
    
    /*~~~~~~~~~TXT文件~~~~~~~~~*/
    auto fu = FileUtils::getInstance();
    FILE *f = fopen(fu ->fullPathFromRelativeFile("data.plist", fu ->getWritablePath()).c_str(), "w");
    fprintf(f, "TXT文件\n ");
    fclose(f);
    
    
    Data d = fu ->getDataFromFile(fu->fullPathFromRelativeFile("data.plist", fu ->getWritablePath()));
    log("%s",d.getBytes());
    
    
    
    /*~~~~~~~~~Plist文件~~~~~~~~~*/
    //字典类型plist
    ValueMap vm = fu ->getValueMapFromFile("data.plist");
    log("%s",vm["name"].asString().c_str());
    log("%s",vm["array"].asValueVector()[0].asString().c_str());
    log("%d",vm["array"].asValueVector()[1].asInt());
    
    //数组类型plist
    ValueVector vv = fu ->getValueVectorFromFile("data2.plist");
    log("%d",vv[0].asValueMap()["age"].asInt());
    log("%s",vv[1].asString().c_str());
    log("%d",vv[2].asInt());
    
    
    
    /*~~~~~~~~~XML文件~~~~~~~~~*/
    //需要导入 <tinyxml2/tinyxml2.h>
    auto doc = new tinyxml2::XMLDocument();
    doc ->Parse(FileUtils::getInstance()->getStringFromFile("data.xml").c_str());
    log("\n%s",FileUtils::getInstance()->getStringFromFile("data.xml").c_str());
    
    //获取根节点
    auto root = doc ->RootElement();
    //遍历子节点
    for (auto e = root ->FirstChildElement(); e; e = e ->NextSiblingElement()) {
        
        std::string str;
        
        //遍历子节点属性
        for (auto attr = e ->FirstAttribute(); attr; attr = attr ->Next()) {
            //属性名称
            str += attr ->Name();
            str += ":";
            //属性值
            str += attr ->Value();
            str += ",";
        }
        log("%s",str.c_str());
    }
    
    
    
    /*~~~~~~~~~JSON文件~~~~~~~~~*/
    rapidjson::Document jDoc;
    jDoc.Parse<0>(FileUtils::getInstance()->getStringFromFile("data.json").c_str());
    log("name:%s,age:%d\nname:%s,age:%d",jDoc[(int)0]["name"].GetString(),jDoc[(int)0]["age"].GetInt(),jDoc[(int)1]["name"].GetString(),jDoc[(int)1]["age"].GetInt());
    
    return true;
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
