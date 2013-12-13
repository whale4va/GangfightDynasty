#include "TextView.h"

/**
 @brief show text content in CCLabelTTF object
 */
void TextView::Display()
{
	if (content.empty())
		return;

	if (bmfont)
	{
		if (pBMlabel == NULL)
		{
			pBMlabel = new cocos2d::CCLabelBMFont();
			pBMlabel->initWithString((const char*)content, (const char*)fontName);
		}
		else
		{
			pBMlabel->setCString((const char*)content);
		}
		cocos2d::CCSize labelSize = pBMlabel->getContentSize();
		float scaleRatio = ((float)size)/labelSize.height;
		pBMlabel->setScale(scaleRatio);
		pBMlabel->setPosition(ToCCPoint(position));
		pBMlabel->setColor(ToColor3B(color));
		if (pBMlabel->getParent() == NULL)
			_node->addChild(pBMlabel, (int)position.z);
//		if (pBMlabel == NULL)
//		{
//			pBMlabel = new cocos2d::CCLabelBMFont();
//			pBMlabel->initWithString((const char*)content, (const char*)fontName);
//			cocos2d::CCSize labelSize = pBMlabel->getContentSize();
//			float scaleRatio = ((float)size)/labelSize.height;
//			pBMlabel->setScale(scaleRatio);
//			pBMlabel->setColor(ToColor3B(color));
//			pBMlabel->setPosition(ToCCPoint(position));
//			if (pBMlabel->getParent() == NULL)
//				_node->addChild(pBMlabel, (int)position.z);
//		}
	}
	else
	{
	    if (plabel == NULL)
	    {
	        plabel = new cocos2d::CCLabelTTF();
	        assert(plabel);
	        plabel->initWithString((const char*)content, (const char *)fontName, (float)size);
	    }
	    else
	    {
	        plabel->setString((const char*)content);
	        plabel->setFontSize(size);
	        plabel->setFontName((const char*)fontName);
	    }
	    plabel->setFontFillColor(ToColor3B(color), true);

	    plabel->setPosition(ccp(position.x, position.y));
	    if (dimension.w != 0 && dimension.h != 0)
	    {
	        plabel->setDimensions(ToCCSize(dimension));
	        //plabel->setHorizontalAlignment(cocos2d::kCCTextAlignmentCenter);
	        //plabel->setVerticalAlignment(cocos2d::kCCVerticalTextAlignmentCenter);
	        plabel->setHorizontalAlignment(cocos2d::kCCTextAlignmentLeft);
	        plabel->setVerticalAlignment(cocos2d::kCCVerticalTextAlignmentTop);
	    }
	    if (plabel->getParent() == NULL)
	        _node->addChild(plabel, (int)position.z);
	}
}

/**
 @brief dismiss CCLableTTF that is showing text content
 */
void TextView::Dismiss()
{
    if (plabel && plabel->getParent())
        _node->removeChild(plabel);
    if (pBMlabel && pBMlabel->getParent())
    	_node->removeChild(pBMlabel);
}

/**
 @brief destory cocos2d-X resources if needed
 */
void TextView::Destory()
{
	Dismiss();
    if (plabel)
    {
        delete plabel;
        plabel = NULL;
    }
    if (pBMlabel)
    {
    	delete pBMlabel;
    	pBMlabel = NULL;
    }
}

