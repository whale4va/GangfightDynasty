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
    
    // 背景图片的贴图集路径
    static const char* backgroundPictureAtlas;
    
    // 按钮贴图集文件&路径
    static const char* buttonPictureAtlas;
    // 按钮的图片资源
    static const char* okButtonPictureName;
    static const char* cancelButtonPictureName;
    static const char* tabviewDismissButtonPictureName;
    
};

#endif
