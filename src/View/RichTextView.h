#ifndef RICHTEXTVIEW_H_HEADER_INCLUDED_AD80DDDE
#define RICHTEXTVIEW_H_HEADER_INCLUDED_AD80DDDE
#include "ViewFrame.h"
class ViewFrame;
class String;
using cocos2d::CCLabelBMFont;
using cocos2d::CCSprite;

#define RICH_TEXT_TE "{T}"	// this field is replaced with text element
#define RICH_TEXT_PE "{P}"	// this field in Rich Text View is replaced with picture

typedef enum _RichTextElementType
{
	Unknown = 0,
	Picture,
	Text
}RichTextElementType;

typedef struct _RichTextElement
{
	RichTextElementType type;
	String name;	// picture name or font name
	String content;
	Uint32 color;
	float scale;
//	Dimension dimension;

	_RichTextElement(String picName) : type(Picture), name(picName),
			color(0x00000000), scale(1.0) {} //, dimension(dim){}

	_RichTextElement(String fontName, String str, Uint32 c) : type(Text),
			name(fontName), scale(1.0), color(c), content(str) {}
    
    _RichTextElement(const _RichTextElement& orig) : type(orig.type), name(orig.name),
            content(orig.content), scale(orig.scale), color(orig.color) {}

	inline void Set(String picName, Dimension dim)
	{
		type = Picture;
		name = picName;
//		dimension = dim;
	}

	inline void Set(String fontname, String str, Uint32 c)
	{
		type = Text;
		name = fontname;
		content = str;
		color = c;
	}

	inline void SetScale(float s) { scale=s; }

//	_RichTextElement() : type(Unknown), scale(1.0), color(0x00000000) {}

	_RichTextElement& operator=(const _RichTextElement& rte)
	{
		if (this == &rte)
			return *this;

		type = rte.type;
		name = rte.name;
		color = rte.color;
		scale = rte.scale;
//		dimension = rte.dimension;
		content = rte.content;
		return *this;
	}
private:
	_RichTextElement();

}RichTextElement;

//##ModelId=522C6B21010F
class RichTextView : public ViewFrame
{
  public:
	RichTextView(CCNode* n) : ViewFrame(n), elementList(true), formatColor(0xFFFFFFFF),
	formatScale(1.0), ccList(true), needParse(true)
    {
        formatFont = ResourceUri::bitmapFontFileName;
    }
    
	RichTextView(CCNode* n, String str) : ViewFrame(n), elementList(true), needParse(true),
			formatContent(str), formatScale(1.0), formatColor(0xFFFFFFFF), ccList(true)
    {
        formatFont = ResourceUri::bitmapFontFileName;
    }
    
	RichTextView(CCNode* n, String str, Uint32 color) : ViewFrame(n), elementList(true),
			formatContent(str), formatScale(1.0), formatColor(color), ccList(true), needParse(true)
    {
        formatFont = ResourceUri::bitmapFontFileName;
    }
    
	RichTextView(CCNode* n, String str, Uint32 color, String font) : ViewFrame(n), elementList(true),
			formatContent(str), formatScale(1.0), formatColor(color), ccList(true), needParse(true), formatFont(font) {}
    
    // 注意：拷贝构造 & 赋值的时候 cocos2d-x里面的资源指针，链表指针，均赋值为NULL，避免多个对象操作同一个cocos2d-x资源冲突
    RichTextView(const RichTextView& orig):ViewFrame(orig), elementList(orig.elementList), formatColor(orig.formatColor),
            formatContent(orig.formatContent), formatScale(orig.formatScale), formatFont(orig.formatFont),
            ccList(true), needParse(orig.needParse) {}
    // 注意：拷贝构造 & 赋值的时候 cocos2d-x里面的资源指针，链表指针，均赋值为NULL，避免多个对象操作同一个cocos2d-x资源冲突
    RichTextView& operator=(const RichTextView& orig)
    {
       if (this != &orig)
       {
           *((ViewFrame*)this) = (ViewFrame)orig;
           elementList = orig.elementList;
           formatColor = orig.formatColor;
           formatContent = orig.formatContent;
           formatFont = orig.formatFont;
           formatScale = orig.formatScale;
           ccList.Release();
           needParse = orig.needParse;
       }
        return *this;
    }

	virtual inline ~RichTextView()
	{
		Destory();
	}

	inline void AddRichTextElement(RichTextElement* rte)
	{
		if (rte)
			elementList.Add(rte);
	}
    
    inline RichTextElement* GetRichTextElementAt(int index)
    {
        return elementList[index];
    }

	inline void SetFontScale(float scale) { formatScale = scale; needParse = true; }
	inline void SetFormatContent(const String& str) { formatContent = str; needParse = true; }
	inline void SetFormatColor(Uint32 c) { formatColor = c; needParse = true; }
	inline void SetFormatFont(const String& font) { formatFont = font; needParse = true; }

	void Display();
	void Dismiss();
	void Destory();

  private:
	RichTextView();
    List<RichTextElement*> elementList;
    String formatContent;	// formatted string of the rich text view.
    Uint32 formatColor;		// formatted string color
    String formatFont;		// formatted string font name
    float formatScale;		// formatted string scale ratio
    bool needParse;			// need parse or not indicator

    // all picture element are scaled to the row height.
    static float rowHeight, rowDividerH; // height of one row and row divider.

    /**
     * @brief parse format content and generate
     * cocos2d-x node list.
     */
    void ParseFormatContent() throw (ExceptionId);

    /**
     * @brief cocos2d-x elements to show every rich text element
     * They are all belong to CCNode, are put into a list
     * The list is generated by ParseFormatContent() method
     * every element dimension was computed too.
     */
    List<CCNode*> ccList;
};


#endif /* RICHTEXTVIEW_H_HEADER_INCLUDED_AD80DDDE */
