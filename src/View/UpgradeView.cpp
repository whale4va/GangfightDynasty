#include "UpgradeView.h"

float UpgradeViewTab::executorTextXp = 0.23;
float UpgradeViewTab::executorTextYp = 0.95;
float UpgradeViewTab::executorTextWp = 0.4;
float UpgradeViewTab::executorTextHp = 0.06;

float UpgradeViewTab::executorListXp = 0.5;
float UpgradeViewTab::executorListYp = 0.55;
float UpgradeViewTab::executorListWp = 0.94;
float UpgradeViewTab::executorListHp = 0.7;

float UpgradeViewTab::resultViewXp = 0.38;
float UpgradeViewTab::resultViewYp = 0.1;
float UpgradeViewTab::resultViewWp = 0.7;
float UpgradeViewTab::resultViewHp = 0.15;

float UpgradeViewTab::okButtonXp = 0.87;
float UpgradeViewTab::okButtonYp = 0.1;
float UpgradeViewTab::okButtonWp = 0.2;
float UpgradeViewTab::okButtonHp = 0.15;

Uint32 UpgradeViewTab::expectedResultColor = 0x00FF00FF;
Uint32 UpgradeViewTab::expenseColor = 0xFF0000FF;

// set dimension and add content vies of list views.
void UpgradeViewTab::SetDimension(Dimension dim)
{
    if (!dim.IsValid())
        THROW(Invalid_Dimension);
    
    dimension = dim;
    
    // In Tab group view, Point is set first before dimension
    // So the point is valid here.
    Point lp = position;
    lp.x -= dim.w/2;
    lp.y -= dim.h/2;
    
    Point sp;
    Dimension sd;
    
    // result view dimension
    sp.x = lp.x + dimension.w * resultViewXp;
    sp.y = lp.y + dimension.h * resultViewYp;
    resultView.SetPoint(sp);
    sd.w = dimension.w * resultViewWp;
    sd.h = dimension.h * resultViewHp;
    resultView.SetDimension(sd);
    
    // ok button view dimension
    sp.x = lp.x + dimension.w * okButtonXp;
    sp.y = lp.y + dimension.h * okButtonYp;
    sd = dimension;
    sd.w *= okButtonWp;
    sd.h *= okButtonHp;
    okButton.SetPoint(sp);
    okButton.SetDimension(sd);
    
    // executor list view dimension
    sp = lp;
    sp.x += dimension.w * executorListXp;
    sp.y += dimension.h * executorListYp;
    sd = dimension;
    sd.w *= executorListWp;
    sd.h *= executorListHp;
    executorsList.SetPoint(sp);
    executorsList.SetDimension(sd);
    
    // executor text view dimension
    sp = lp;
    sp.x += dimension.w * executorTextXp;
    sp.y += dimension.h * executorTextYp;
    sd = dimension;
    sd.w *= executorTextWp;
    sd.h *= executorTextHp;
    executorText.SetPoint(sp);
    executorText.SetDimension(sd);
    
    // fill in sub views of list view.
    FillInListViews();
}

void UpgradeViewTab::FillInListViews()
{
    // 1. get all available leaders
    executors = Leader::QueryAvailableLeaders();
    
    // 2. fill in title views;
    TextView* ct1 = new TextView(_node, "名称", true);
    TextView* ct2 = NULL;
    if (Upgrade_Security == type)
        ct2 = new TextView(_node, "武力", true);
    else
        ct2 = new TextView(_node, "文智", true);
    TextView* ct3 = new TextView(_node, "效果", true);
    TextView* ct4 = new TextView(_node, "花费", true);
    executorsList.AddTitleView(ct1);
    executorsList.AddTitleView(ct2);
    executorsList.AddTitleView(ct3);
    executorsList.AddTitleView(ct4);
    
    // 3. fill in content views
    TextView* cc1, *cc2, *cc3, *cc4;
    for (int i = 0; i < executors.GetLength(); i++)
    {
        cc1 = new TextView(_node, executors[i]->GetName(), true);
        if (Upgrade_Security == type)
        {
            cc2 = new TextView(_node, executors[i]->GetPower(), true);
            cc3 = new TextView(_node, UPGRADE_EFFORT*executors[i]->GetPower(), true);
        }
        else
        {
            cc2 = new TextView(_node, executors[i]->GetSmart(), true);
            cc3 = new TextView(_node, UPGRADE_EFFORT*executors[i]->GetSmart(), true);
        }
        cc4 = new TextView(_node, UPGRADE_COST, true);
        executorsList.AddContentView(cc1);
        executorsList.AddContentView(cc2);
        executorsList.AddContentView(cc3);
        executorsList.AddContentView(cc4);
    }
}

bool UpgradeViewTab::OnButton()
{
    CCLOG("UpgradeViewTab button clicked on %d(0x%X).\n", _senderId, _senderId);
	bool ret = false;
	switch (_senderId)
	{
	case BTN_OK:
		Destory();
        // generate upgrade event.
        EventQueue::GetInstance()->AddEvent(GenerateEvent());
		ret = true;
		break;
	default:
		break;
	}
	return ret;
}

bool UpgradeViewTab::OnListItemSelected(int rowIndex)
{
    // update result view.
    expense += UPGRADE_COST;
    if (Upgrade_Security == type)
        expectedResult += UPGRADE_EFFORT*executors[rowIndex]->GetPower();
    else
        expectedResult += UPGRADE_EFFORT*executors[rowIndex]->GetSmart();
    
    usedLeaders.Add(executors[rowIndex]);
    String resultStr("+",expectedResult);
    String expenseStr("-",expense);
    resultView.Dismiss();
    resultView.GetRichTextElementAt(0)->Set(
                    ResourceUri::bitmapFontFileName,
                    resultStr, expectedResultColor);
    resultView.GetRichTextElementAt(1)->Set(
                    ResourceUri::bitmapFontFileName,
                    expenseStr, expenseColor);
    resultView.Display();
    
    return true;
}

bool UpgradeViewTab::OnListItemUnselected(int rowIndex)
{
    // update result view.
    expense -= UPGRADE_COST;
    if (Upgrade_Security == type)
        expectedResult -= UPGRADE_EFFORT*executors[rowIndex]->GetPower();
    else
        expectedResult -= UPGRADE_EFFORT*executors[rowIndex]->GetSmart();
    
    int findIndex = usedLeaders.Find(executors[rowIndex]);
    if (usedLeaders.invalidIndex != findIndex)
        usedLeaders.Remove(findIndex);
    
    String resultStr("+",expectedResult);
    String expenseStr("-",expense);
    resultView.Dismiss();
    resultView.GetRichTextElementAt(0)->Set(
                    ResourceUri::bitmapFontFileName,
                    resultStr, expectedResultColor);
    resultView.GetRichTextElementAt(1)->Set(
                    ResourceUri::bitmapFontFileName,
                    expenseStr, expenseColor);
    resultView.Display();
    
    return true;
}

//##ModelId=52691B08002A
Event* UpgradeViewTab::GenerateEvent()
{
    Event* pEvent = new Event();
    
    pEvent->SetTargetCityId(targetId);
    pEvent->SetExecuteLeaders(usedLeaders);
    pEvent->SetUpgradeResult(expectedResult);
    pEvent->SetType(Event_Upgrade_Done);
    GameDate curDate = GameDate::GetCurrentDate();
    curDate.ForwardDays(GameDate::upgradeNeedDays);
    pEvent->SetDeadLine(curDate);
    
    
    for (int i = 0; i < usedLeaders.GetLength(); i++)
    {
        usedLeaders[i]->SetAssignTask(pEvent);
    }
    
    return pEvent;
}

//##ModelId=522C6CF80198
void UpgradeView::ShowCandidateLeaderList()
{
}

//##ModelId=522C6D0C01C2
void UpgradeView::RefreshResultView()
{
}

//##ModelId=526919130240
void UpgradeView::InitWithUpgradeType(UpgradeType type)
{
}



