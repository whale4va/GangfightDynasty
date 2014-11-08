#include "ViewFrame.h"

//##ModelId=522B302F01A5
void ViewFrame::Display()
{
}

//##ModelId=5241A9870215
void ViewFrame::Dismiss()
{
}

//##ModelId=526D09020223
void ViewFrame::Destory()
{
}

/**
//##ModelId=522F2F76005E
void ViewFrame::SetDimension()
{
}

//##ModelId=523F067B0278
void ViewFrame::SetPoint()
{
}

//##ModelId=5246FF590152
bool ViewFrame::GetFull()
{
}

//##ModelId=5246FF6E0003
void ViewFrame::SetFull(bool full)
{
}

//##ModelId=526CDC920159
void ViewFrame::SetId(Uint32 id)
{
}

//##ModelId=526CDC990101
Uint32 ViewFrame::GetId()
{
}
*/


bool CCSpriteFrameLoader::loaded = false;

List<CCSpriteBatchNode*> CCSpriteBatchNodeManager::batchNodes(true);
List<String> CCSpriteBatchNodeManager::nodeNames;

cocos2d::CCSpriteBatchNode* CCSpriteBatchNodeManager::GetSpriteBatchNodeByName(
 String name)
{
    if (name.GetLength() == 0)
        return NULL;
    
    int index = nodeNames.Find(name);
    if (nodeNames.invalidIndex != index)
    {
        return batchNodes[index];
    }
    else
    {
        cocos2d::CCSpriteBatchNode* pNode = new CCSpriteBatchNode();
        pNode->initWithFile((const char*)name, 200);
        batchNodes.Add(pNode);
        nodeNames.Add(name);
        return pNode;
    }
}

void CCSpriteBatchNodeManager::RemoveSpriteBatchNodeByName(String name)
{
    int index = nodeNames.Find(name);
    if (nodeNames.invalidIndex != index)
    {
        nodeNames.Remove(index);
        batchNodes.Remove(index);
    }
}

void CCSpriteBatchNodeManager::ReleaseSpriteBatchNodes()
{
    nodeNames.Release();
    batchNodes.Release();
}


