//
//  ResourceUri.cpp
//  GangfightDynasty
//
//  Created by Foraby.Va on 14-6-10.
//  定义一些资源的公用名称
//

#include "ResourceUri.h"

// 图片文字路径
const char* ResourceUri::bitmapFontFileName = "fonts/characters.fnt";

// 背景图片的贴图集文件路径
const char* ResourceUri::backgroundPictureAtlas = "Backgrounds/backgrounds.plist";
const char* ResourceUri::tabviewBackgroundPictureName = "TabViewBackground.png";

// 按钮图片集的文件路径
const char* ResourceUri::buttonPictureAtlas = "Buttons/buttons.plist";
// 按钮图片资源  按钮图片都放在统一的贴图集
const char* ResourceUri::okButtonPictureName = "ok_button_normal.png";
const char* ResourceUri::cancelButtonPictureName = "cancel_button_normal.png";
const char* ResourceUri::tabviewDismissButtonPictureName = "tabview_dismiss_normal.png";
const char* ResourceUri::enterCityButtonPictureName = "enter_city_button_normal.png";
// 备选军队列表的取消按钮图片资源
const char* ResourceUri::armyReadyViewCancelButtonPictureName = "cancel_button_normal.png";

// 数字键盘按钮的图片资源
const char* ResourceUri::button0PictureName = "0_button_normal.png";
const char* ResourceUri::button1PictureName = "1_button_normal.png";
const char* ResourceUri::button2PictureName = "2_button_normal.png";
const char* ResourceUri::button3PictureName = "3_button_normal.png";
const char* ResourceUri::button4PictureName = "4_button_normal.png";
const char* ResourceUri::button5PictureName = "5_button_normal.png";
const char* ResourceUri::button6PictureName = "6_button_normal.png";
const char* ResourceUri::button7PictureName = "7_button_normal.png";
const char* ResourceUri::button8PictureName = "8_button_normal.png";
const char* ResourceUri::button9PictureName = "9_button_normal.png";
const char* ResourceUri::button00PictureName = "00_button_normal.png";
const char* ResourceUri::button000PictureName = "000_button_normal.png";

const char* ResourceUri::backspaceButtonPictureName = "backspace_button_normal.png";
const char* ResourceUri::maxButtonPictureName = "max_button_normal.png";
const char* ResourceUri::clearButtonPictureName = "clear_button_normal.png";
const char* ResourceUri::armyReadyBackgroundPictureName = "army_ready_bg_normal.png";

// 城市策略字符串
const char* ResourceUri::StrategyName[] =
{
    "内政优先",
    "攻略优先"
};

// 兵种类型的图片名称
const char* ResourceUri::WeaponTypePictureName[] =
{
    "nothing",              // nothing 占位
    "sword_normal.png",     //刀剑
    "spear_normal.png",     //枪
    "horse_normal.png",     //骑兵
    "arrow_normal.png"      //弓箭
};

// ListView选中高亮背景图片资源
const char* ResourceUri::listViewHighLightPictureName = "list_view_high_light.png";
