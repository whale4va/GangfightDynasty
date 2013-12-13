#include "CommonButton.h"

//##ModelId=522F2443033C
Uint32 CommonButton::GetId()
{
    return _id;
}

//##ModelId=522F266301A2
void CommonButton::SetEnable(bool en)
{
    enabled = en;
    if (pButton)
        pButton->setEnabled(enabled);
}

//##ModelId=522F266F035D
void CommonButton::SetVisible(bool vi)
{
    visible = vi;
    if (pButton)
        pButton->setVisible(visible);
}

void CommonButton::Display()
{
    if (pButton == NULL)
    {
        if (!CCSpriteFrameLoader::loaded)
        	CCSpriteFrameLoader::Load();
        DeducePictureName();
        pButton = new cocos2d::CCMenuItemImage;
        assert(pButton);
        pButton->initWithTarget(this, menu_selector(CommonButton::MenuHandler));
        pButton->setNormalSpriteFrame(cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->
                                      spriteFrameByName((const char*)normalPic));
        pButton->setSelectedSpriteFrame(cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->
                                        spriteFrameByName((const char*)selectedPic));
        pButton->setDisabledSpriteFrame(cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->
                                        spriteFrameByName((const char*)disabledPic));
        
        if (pButtonContainer == NULL)
        {
            pButtonContainer = new cocos2d::CCMenu;
            assert(pButtonContainer);
            cocos2d::CCArray* pArray = cocos2d::CCArray::create(pButton, NULL);
            pButtonContainer->initWithArray(pArray);
        }
        else
        {
            pButtonContainer->addChild(pButton);
        }
    }
    
    if (dimension.w != 0 && dimension.h != 0)
    {
        cocos2d::CCSize buttonSize = pButton->getContentSize();
        float scaleX = (float)dimension.w/buttonSize.width;
        float scaleY = (float)dimension.h/buttonSize.height;
        pButton->setScaleX(scaleX);
        pButton->setScaleY(scaleY);
        //pButtonContainer->setScaleX(scaleX);
        //pButtonContainer->setScaleY(scaleY);
        //CCLOG("Button content size = (%f, %f)\n", buttonSize.width, buttonSize.height);
    }
    
    //pButton->setPosition(ToCCPoint(position));
    if (pButtonContainer->getParent() == NULL)
    {
        pButtonContainer->setPosition(ToCCPoint(position));
        _node->addChild(pButtonContainer, position.z);
    }
}

void CommonButton::DeducePictureName() throw (ExceptionId)
{
    /**
     The naming rule just as:
     name(*)_button(*)_mode([normal|selected|disabled]).png(*)
     so the substring between '_' and '.' is replaced with dedicate mode.
     
     resourceName is superseded from PictureView, which can be any mode name.
     */
    int len = resourceName.GetLength();
    if (len == 0)
        THROW(Invalid_ResourceName);
    
    int pos = resourceName.find('.');
    if (pos == String::invalidIndex)
        THROW(Invalid_ResourceName);

    String fileType = resourceName.substr(pos);
    
    pos = resourceName.rfind('_');
    if (pos == String::invalidIndex)
        THROW(Invalid_ResourceName);
    
    normalPic = resourceName.substr(0, pos);
    normalPic = normalPic + fileType;
    selectedPic = normalPic;
    disabledPic = normalPic;
    
    normalPic.insert("_normal", pos);
    selectedPic.insert("_selected", pos);
    disabledPic.insert("_disabled", pos);
    
    CCLOG("nf=%s, sf=%s, df=%s\n", (const char*)normalPic,
          (const char*)selectedPic, (const char*)disabledPic);
    
    return;
}

void CommonButton::MenuHandler(cocos2d::CCObject* pSender)
{
    CCLOG("Common button (%s) id=%d was clicked\n", (const char*)resourceName, _id);
    if (responder)
    {
        responder->SetSenderId(_id);
        if (responder->OnButton())
            return;
    }
    if (parentView)
    {
        parentView->SetSenderId(_id);
        parentView->OnButton();
    }
}

CommonButton::CommonButton(const CommonButton& cb) : PictureView(cb._node)
{
    enabled = cb.enabled;
    visible = cb.visible;
    
    pButtonContainer = cb.pButtonContainer;     // put into same menu as default
    dimension = cb.dimension;
    position.x = position.y = 0;       // put new button at 0,0 first as default
    position.z = cb.position.z;
    pButton = NULL;     // set the new button as NULL as default, create at Display
    resourceName = cb.resourceName;
    framesFileName = cb.framesFileName;
    inGroup = cb.inGroup;
}

CommonButton& CommonButton::operator=(const CommonButton& cb)
{
    if (this == &cb)
        return (*this);
    
    if (pButton)
    {
        if (pButtonContainer)
        {
            pButtonContainer->removeChild(pButton, true);
            if (!inGroup)
            {
                delete pButtonContainer;
                pButtonContainer = NULL;
            }
        }
        
        delete pButton;
        pButton = NULL;
    }
    
    enabled = cb.enabled;
    visible = cb.visible;
    
    pButtonContainer = cb.pButtonContainer;     // put into same menu as default
    dimension = cb.dimension;
    position.x = position.y = 0;       // put new button at 0,0 first as default
    position.z = cb.position.z;
    pButton = NULL;     // set the new button as NULL as default, create at Display
    resourceName = cb.resourceName;
    framesFileName = cb.framesFileName;
    inGroup = cb.inGroup;
    
    return (*this);
}
