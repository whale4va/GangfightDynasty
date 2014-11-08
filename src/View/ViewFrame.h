#ifndef VIEWFRAME_H_HEADER_INCLUDED_AD80F808
#define VIEWFRAME_H_HEADER_INCLUDED_AD80F808
#include "ViewEventResponder.h"

//##ModelId=522B2F960307
class ViewFrame : public ViewEventResponder
{
private:
    ViewFrame();
    
  public:
    //##ModelId=522B302F01A5
    virtual void Display();
    
    //##ModelId=5241A9870215
    virtual void Dismiss();
    
    /** @brief the view fram is dismissed also destoried,all allocated
     resources are relased. */
    //##ModelId=526D09020223
    virtual void Destory();

    //##ModelId=522F2F76005E
    inline void SetDimension(Dimension d)
    {
        dimension.w = d.w;
        dimension.h = d.h;
    }

    //##ModelId=523F067B0278
    inline void SetPoint(Point p)
    {
        position.x = p.x;
        position.y = p.y;
        position.z = p.z;
    }

    //##ModelId=5246FF590152
    inline bool GetFull() { return full; }

    //##ModelId=5246FF6E0003
    inline void SetFull(bool f) { full = f; }

    //##ModelId=526CDC920159
    inline void SetId(Uint32 i) { _id = i; }

    //##ModelId=526CDC990101
    inline Uint32 GetId() { return _id; }

    //##ModelId=522B2FCE0308
    Point position;
    //##ModelId=522B2FF901A6
    Dimension dimension;
    //##ModelId=522B301001E6
    ViewFrame* parentView;
    //##ModelId=523F02BE0313
    ViewEventResponder* responder;
    //##ModelId=5246FF3F0284
    bool full;
    /** Every view has an id, it can be unique for all views or unique only as
    parent view. It's used by parent view to understand what's the subview is & can
    arrange different operation for different subview. */
    //##ModelId=5265C3AA01B8
    Uint32 _id;
    /** list of subviews of current view */
    //##ModelId=5265C44201B1
    List<ViewFrame*> subview;
    
    ViewFrame(CCNode* node) : ViewEventResponder(node), subview(true),
    _id(GAME_INVALID_ID), full(false), parentView(NULL), responder(NULL)
    {
        position.x = position.y = position.z = 0.0;
        dimension.w = dimension.h = 0.0;
    }
    ViewFrame(const ViewFrame& orig) : ViewEventResponder((ViewEventResponder)orig),
        subview(orig.subview), _id(orig._id), full(orig.full), parentView(orig.parentView), responder(orig.responder),
        position(orig.position), dimension(orig.dimension) {}
    
    ViewFrame& operator=(const ViewFrame& orig)
    {
        if (this != & orig)
        {
            *((ViewEventResponder*)this) = (ViewEventResponder)orig;
            subview = orig.subview;
            _id = orig._id;
            full = orig.full;
            parentView = orig.parentView;
            responder = orig.responder;
            position = orig.position;
            dimension = orig.dimension;
        }
        return *this;
    }
    
    virtual ~ViewFrame()
    {
    	Destory();
    }

    
    inline void SetParentView(ViewFrame* v) { assert(v); parentView = v; }
    inline ViewFrame* GetParentView() { return parentView; }
    inline void SetResponder(ViewEventResponder* res) { assert(res); responder = res; }
    inline ViewEventResponder* GetResponder() { return responder; }
    
    /**
     * cocos2d-x specific methods
     */
    inline cocos2d::CCRect GetCCRect()
    {
        return cocos2d::CCRect(position.x, position.y,
                               dimension.w, dimension.h);
    }
    
    inline bool IsContainCCPoint(cocos2d::CCPoint point)
    {
        if (dimension.IsValid())
        {
            if (point.x >= position.x - dimension.w/2 &&
                point.x <= position.x + dimension.w/2 &&
                point.y >= position.y - dimension.h/2 &&
                point.y <= position.y + dimension.h/2)
                return true;
        }
        return false;
    }
};

/**
 * @brief static class provides static methods to load sprite frames from file once
 */
class CCSpriteFrameLoader
{
public:
	static bool loaded;
	inline static void Load()
	{
		cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(ResourceUri::buttonPictureAtlas);
		cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(ResourceUri::backgroundPictureAtlas);
		loaded = true;
	}

private:
	CCSpriteFrameLoader();
};

/**
 * @brief CCSpriteBatchNode manager. manage all CCSpriteBatchNodes
 */
using cocos2d::CCSpriteBatchNode;
class CCSpriteBatchNodeManager
{
public:
    static List<cocos2d::CCSpriteBatchNode*> batchNodes;
    static List<String> nodeNames;
    static CCSpriteBatchNode* GetSpriteBatchNodeByName(String name);
    
    static void RemoveSpriteBatchNodeByName(String name);
    static void ReleaseSpriteBatchNodes();
};


#endif /* VIEWFRAME_H_HEADER_INCLUDED_AD80F808 */
