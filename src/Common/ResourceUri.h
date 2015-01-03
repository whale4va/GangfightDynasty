//
//  ResourceUri.h
//  GangfightDynasty
//
//  Created by Foraby.Va on 14-6-10.
//  存储资源的名称字符串的类，类中导出静态的字符串，表明一些公关的资源
//

#ifndef GangfightDynasty_ResourceUri_h
#define GangfightDynasty_ResourceUri_h

class ResourceUri
{
    // 注意：拷贝构造 & 赋值的时候 cocos2d-x里面的资源指针，链表指针，均赋值为NULL，避免多个对象操作同一个cocos2d-x资源冲突
public:
    
    // 图片文字的路径
    static const char* bitmapFontFileName;
    
    // 城市策略字符串
    static const char* StrategyName[];
    
    // 兵种类型的图片资源
    static const char* WeaponTypePictureName[];
    
    // 背景图片的贴图集路径
    static const char* backgroundPictureAtlas;
    static const char* tabviewBackgroundPictureName;
    
    // 按钮贴图集文件&路径
    static const char* buttonPictureAtlas;
    // 按钮的图片资源
    static const char* okButtonPictureName;
    static const char* cancelButtonPictureName;
    static const char* tabviewDismissButtonPictureName;
    static const char* enterCityButtonPictureName;
    
    // 数字键盘按钮的图片资源
    static const char* button1PictureName;
    static const char* button2PictureName;
    static const char* button3PictureName;
    static const char* button4PictureName;
    static const char* button5PictureName;
    static const char* button6PictureName;
    static const char* button7PictureName;
    static const char* button8PictureName;
    static const char* button9PictureName;
    static const char* button0PictureName;
    static const char* button00PictureName;
    static const char* button000PictureName;
    
    // 数字键盘额外键的图片资源
    static const char* backspaceButtonPictureName;
    static const char* maxButtonPictureName;
    static const char* clearButtonPictureName;
    
    // 备选军队列表的取消按钮图片资源
    static const char* armyReadyViewCancelButtonPictureName;
    // 备选军队列表的背景图片资源
    static const char* armyReadyBackgroundPictureName;
    
    
    // ListView选中高亮背景图片资源
    static const char* listViewHighLightPictureName;
    
    
    // 将领图片
    static const char* leaderDefaultPictureName;
};


#endif
