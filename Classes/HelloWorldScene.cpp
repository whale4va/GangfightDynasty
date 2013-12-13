#include "HelloWorldScene.h"

USING_NS_CC;

static TextView* holdView = NULL;
static PictureView* holdPic = NULL;
static CommonButton* holdButton = NULL;
static PureColorBar* holdColorBar = NULL;
static ButtonGroupPopupView* holdButtonGroup = NULL;
static RichTextView* holdRichText = NULL;
static TabGroupView* holdTabGroup = NULL;
static CCScene* holdScene = NULL;


CCScene* HelloWorld::scene()
{
    // 'scene' is an auto release object
    CCScene *scene = CCScene::create();
    holdScene = scene;
    
    // 'layer' is an auto release object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

void HelloWorld::OnExit()
{
    if (holdView)
        delete holdView;
    if (holdPic)
        delete holdPic;
    if (holdButton)
        delete holdButton;
    if (holdColorBar)
        delete holdColorBar;
    if (holdButtonGroup)
    	delete holdButtonGroup;
    if (holdRichText)
    	delete holdRichText;
    if (holdTabGroup)
    	delete holdTabGroup;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    CCLOG("ox=%d(%f), oy=%d(%f); w=%d(%f), h=%d(%f)\n", (int)origin.x, origin.x, (int)origin.y, origin.y,
          (int)visibleSize.width, visibleSize.width, (int)visibleSize.height, visibleSize.height);

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(HelloWorld::menuCloseCallback));
    
	pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
                                origin.y + pCloseItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    CCLabelTTF* pLabel = CCLabelTTF::create("Hello World", "Arial", 24);

    // position the label on the center of the screen
    pLabel->setPosition(ccp(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - pLabel->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(pLabel, 1);

    // add "HelloWorld" splash screen"
    CCSprite* pSprite = CCSprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(pSprite, 0);
    

    try
    {
    	THROW(Invalid_Dimension);
    }
    catch (ExceptionId& ec)
    {
    	CCLOG("Try self THROW macro, catch exception id = %d\n", (int)ec);
    }

    /**
     *  Text View
     */
    TextView* pt = new TextView(this);
    pt->SetColor(0xFF0000FF);
    //pt->SetContent("Just show TextView");
    pt->SetContent("長安");
    pt->SetBMFont(true);
    Point pos;
    pos.x = origin.x + visibleSize.width/2;
    pos.y = visibleSize.height/2 + origin.y;
    pos.z = 5;
    pt->SetPoint(pos);
    //pt->SetFont("BiauKai");
    //pt->SetFont("DFKaiSUBold-B5");
    //pt->SetFont("WenQuanYi Micro Hei");
    pt->SetFont("fonts/characters.fnt");
    //pt->SetDimension(mkDimension(200, 200));
    pt->Display();
    
    if (holdView == NULL)
        holdView = pt;
    
    /**
     * Picture view
     */
    PictureView* pPic = new PictureView(this, "horsing.jpg");
    pPic->SetPoint(mkPoint(200, 100));
    pPic->SetDimension(mkDimension(100, 100));
    pPic->Display();
    if (holdPic == NULL)
        holdPic = pPic;
    
    /**
     * Sigle common button
     */
    holdButton = new CommonButton(this, "ok_button_normal.png");
    holdButton->SetPoint(mkPoint(64, 200, 5));
    holdButton->SetDimension(mkDimension(32, 32));
    holdButton->Display();
    
    /**
     * Pure color bar
     */
    holdColorBar = new PureColorBar(this, 0xFF0000FF, 0x00FFFFFF);
    holdColorBar->SetPercentage(30);
    holdColorBar->SetDimension(mkDimension(64, 40));
    holdColorBar->SetPoint(mkPoint(40, 240, 6));
    holdColorBar->Display();

    /**
     * Button group
     */
    holdButtonGroup = new ButtonGroupPopupView(this, 2, 2);
    holdButtonGroup->SetBackgroundReourceName("PopupBackground.png");
    holdButtonGroup->SetDimension(mkDimension(128, 40));
    holdButtonGroup->SetPoint(mkPoint(100, 300, 6));
    try
    {
    	holdButtonGroup->AddCommonButtonAt(0, 0, "assign_weapon_normal.png");
    	holdButtonGroup->AddCommonButtonAt(0, 1, "cancel_army_normal.png");
    	holdButtonGroup->AddCommonButtonAt(1, 0, "create_army_normal.png");
    	holdButtonGroup->AddCommonButtonAt(1, 1, "split_army_normal.png");
    }
    catch(ExceptionId& ec)
    {
        CCLOG("button group exception id = %d\n", (int)ec);
    }
    holdButtonGroup->Display();

    /**
     * Rich text view
     */
    holdRichText = new RichTextView(this, "看看{T}效果{P}洛陽長安桂陽{T}", 0xFF0000FF, "fonts/characters.fnt");
    RichTextElement* rte = new RichTextElement("fonts/characters.fnt", "戰業", 0x0000FFFF);
    holdRichText->AddRichTextElement(rte);
    rte = new RichTextElement("Icons/gold.png");
    holdRichText->AddRichTextElement(rte);
    rte = new RichTextElement("fonts/characters.fnt", "銀錢國", 0x00FF00FF);
    holdRichText->AddRichTextElement(rte);
    holdRichText->SetDimension(mkDimension(200, 100));
    holdRichText->SetPoint(mkPoint(600, 300, 6));
    try
    {
    	holdRichText->Display();
    }
    catch(ExceptionId& ec)
    {
    	CCLOG("RichTextView display exception id=%d\n", (int)ec);
    }

    /**
     * Tab group view
     */
    holdTabGroup = new TabGroupView(this);
    holdTabGroup->init();
    holdTabGroup->SetDimension(mkDimension(300, 160));
    holdTabGroup->SetPoint(mkPoint(600, 100, 7));
    TabView* pTab = new TabView(holdTabGroup, "桂陽");
    holdTabGroup->AddTab(pTab);
    pTab = new TabView(holdTabGroup, "洛陽");
    holdTabGroup->AddTab(pTab);
    pTab = new TabView(holdTabGroup, "晉陽");
    holdTabGroup->AddTab(pTab);
    try
    {
    	holdTabGroup->Display();
    }
    catch (ExceptionId& ec)
    {
    	CCLOG("TabGroupVIew display exception id=%d\n", (int)ec);
    }

    return true;
}

static int endcounter = 0;
void HelloWorld::menuCloseCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
    if (endcounter == 0)
    {
        endcounter++;
        holdView->Dismiss();
        holdPic->Dismiss();
        //holdButton->Dismiss();
        holdButton->SetEnable(false);
        holdColorBar->SetPercentage(80);
        holdColorBar->SetLeftColor(0x00FF00FF);
        holdColorBar->SetRightColor(0x0000FFFF);
        holdButtonGroup->Dismiss();
        holdRichText->Dismiss();
        holdTabGroup->Dismiss();
        return;
    }
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
}
