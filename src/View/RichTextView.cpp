#include "RichTextView.h"

float RichTextView::rowHeight = 24.0;
float RichTextView::rowDividerH = 3.0;

void RichTextView::Display()
{
	if (needParse)
		ParseFormatContent();

	for (int i = 0; i < ccList.GetLength(); i++)
	{
		CCNode* pn = ccList[i];
		if (pn)
		{
			if (pn->getParent() == NULL)
				_node->addChild(pn, pn->getZOrder());
		}
	}
}

void RichTextView::Dismiss()
{
	for (int i = 0; i < ccList.GetLength(); i++)
	{
		CCNode* pn = ccList[i];
		if (pn)
		{
			if (pn->getParent())
			{
				_node->removeChild(pn);
			}
		}
	}
}

void RichTextView::Destory()
{
	Dismiss();
	CCNode* pn = NULL;
	for (int i = ccList.GetLength() - 1; i >=0; i--)
	{
		pn = ccList[i];
		if (pn)
			delete pn;
		ccList.Remove(i);
	}

	RichTextElement* pe = NULL;
	for (int i = elementList.GetLength(); i >=0; i--)
	{
		pe = elementList[i];
		if (pe)
			delete pe;
		elementList.Remove(i);
	}
}

void RichTextView::ParseFormatContent() throw (ExceptionId)
{
	if (formatContent.empty())
		return;
	if (dimension.w < FLOAT_MINOR_LIMIT || dimension.h < FLOAT_MINOR_LIMIT)
		return;		// the rich text object dimension is not set yet.

	if (!ccList.Empty())
	{
		Dismiss();
		ccList.Release();
	}

	String curStr, leftStr;
	int pos, rteIndex;
	Point curOriginal;	// current element original point.

	// every element anchor point at its left top corner
	cocos2d::CCPoint anchor;
	anchor.x = 0.0;
	anchor.y = 1.0;

	curOriginal.x = position.x - dimension.w/2;
	curOriginal.y = position.y + dimension.h/2 - rowDividerH;
	curOriginal.z = position.z;
	leftStr = formatContent;
	rteIndex = 0;
	do
	{
		pos = leftStr.find('{');
		if (pos == 0)
		{	// start with {T/P}, do special process.
			pos = leftStr.find('}');
			if (pos == String::invalidIndex)
			{
				// release already constructed object
				if (!ccList.Empty())
					ccList.Release();
				throw Invalid_RichTextFormat;
			}
			else
			{
				pos++;		// Since started from {T/P}, need pos + 1.
			}
		}

		if (pos != String::invalidIndex)
		{
			curStr = leftStr.substr(0, pos);
			try
			{
				leftStr = leftStr.substr(pos);
			}
			catch (ExceptionId& ec)
			{
				if (ec == Invalid_Index && pos == leftStr.GetLength())
					leftStr = "";
				else
				{
					// release already constructed object
					if (!ccList.Empty())
						ccList.Release();
					throw ec;
				}
			}
		}
		else	// can't find {T/P} in format string
		{
			curStr = leftStr;
			leftStr = "";
		}

		if (curStr[0] == '{')
		{	// special character of element indicator
			if (curStr == RICH_TEXT_TE)
			{
				RichTextElement* prte = elementList[rteIndex];
				if (prte->type != Text || prte->name.empty())
				{;
					if (!ccList.Empty())
						ccList.Release();
					throw (Invalid_RichTextElement);
				}
				if (prte->content.empty())
				{
					rteIndex++;
					continue;
				}
				cocos2d::CCLabelBMFont* pLabel = new CCLabelBMFont();
				pLabel->initWithString((const char*)prte->content, (const char*)prte->name);
				cocos2d::CCSize labelSize = pLabel->getContentSize();
				float scaleRatio = rowHeight/labelSize.height*prte->scale;
				if (curOriginal.x + scaleRatio*labelSize.width > position.x + dimension.w/2)
				{	// move current original point to next row
					curOriginal.x = position.x - dimension.w/2;
					curOriginal.y -= (rowHeight + rowDividerH);
				}

				pLabel->setColor(ToColor3B(prte->color));
				pLabel->setScale(scaleRatio);
				pLabel->setAnchorPoint(anchor);
				pLabel->setPosition(ToCCPoint(curOriginal));
				pLabel->setZOrder((int)curOriginal.z);
				ccList.Add(pLabel);

				curOriginal.x += scaleRatio*labelSize.width;
				rteIndex++;
			}
			else if (curStr == RICH_TEXT_PE)
			{
				RichTextElement* prte = elementList[rteIndex];
				if (prte->type != Picture || prte->name.empty())
				{
					if (!ccList.Empty())
						ccList.Release();
					throw (Invalid_RichTextElement);
				}
				cocos2d::CCSprite* pSprite = new cocos2d::CCSprite();
				pSprite->initWithFile((const char*)prte->name);
				cocos2d::CCSize picSize = pSprite->getContentSize();
				float scaleRatio = rowHeight/picSize.height;
				if (curOriginal.x + scaleRatio*picSize.width > position.x + dimension.w/2)
				{	// move current original point to next row
					curOriginal.x = position.x - dimension.w/2;
					curOriginal.y -= (rowHeight + rowDividerH);
				}

				pSprite->setScale(scaleRatio);
				pSprite->setAnchorPoint(anchor);
				pSprite->setPosition(ToCCPoint(curOriginal));
				pSprite->setZOrder((int)curOriginal.z);
				ccList.Add(pSprite);

				// original point updated
				curOriginal.x += scaleRatio*picSize.width;
				rteIndex++;
			}
			else
			{
				// release already constructed object
				if (!ccList.Empty())
					ccList.Release();
				throw Invalid_RichTextFormat;
			}
		}
		else
		{	// normal string will break into two lines if its width is too large
			if (formatFont.empty())
			{
				if (!ccList.Empty())
					ccList.Release();
				throw Invalid_RichTextFormat;
			}
			cocos2d::CCLabelBMFont* pLabel = new CCLabelBMFont();
			pLabel->initWithString((const char*)curStr, (const char*)formatFont);
			cocos2d::CCSize labelSize = pLabel->getContentSize();
			float scaleRatio = rowHeight/labelSize.height;
//			float aveCharWidth = labelSize.width/curStr.GetLength()*scaleRatio;
			float aveCharWidth = labelSize.width/curStr.CharNumber()*scaleRatio;
			cocos2d::CCLabelBMFont* pLabel2 = NULL;
			if (curOriginal.x + labelSize.width*scaleRatio > position.x + dimension.w/2)
			{
				float firstRowRatio = (position.x+dimension.w-curOriginal.x)/(labelSize.width*scaleRatio);
				int dividerCharIndex = int(((float)curStr.CharNumber())*firstRowRatio);
				// need more than one line
				if (position.x + dimension.w/2 - curOriginal.x < aveCharWidth || dividerCharIndex == 0)
				{	// no need to divide, just directly put in new text area
					curOriginal.x = position.x-dimension.w/2;
					curOriginal.y -= (rowHeight+rowDividerH);
					pLabel->setAnchorPoint(anchor);
					pLabel->setScale(scaleRatio);
					pLabel->setPosition(ToCCPoint(curOriginal));
					pLabel->setZOrder((int)curOriginal.z);
					pLabel->setColor(ToColor3B(formatColor));
					ccList.Add(pLabel);

					int rowCharNum = (int)dimension.w/aveCharWidth;
					int rows = curStr.CharNumber()/rowCharNum;
					int lastCharNum = curStr.CharNumber() - (rowCharNum*rows);
					if (lastCharNum < 0)
					{
						CCLOG("rows=%d, rowCharNum=%d, lastCharNum=%d, aveCharWidth=%f, curStr=%s\n",
								rows, rowCharNum, lastCharNum, aveCharWidth, (const char*)curStr);
						if (!ccList.Empty())
							ccList.Release();
						throw Format_Parsing_Error;
					}
					curOriginal.y -= rows*(rowHeight+rowDividerH);
					curOriginal.x = position.x - dimension.w/2 + aveCharWidth*lastCharNum;
				}
				else
				{	// can divider string to more than one line
					dividerCharIndex = curStr.LocateChar(dividerCharIndex);	// convert to array index.
					try
					{
						String firstStr = curStr.substr(0, dividerCharIndex);
						String secondStr = curStr.substr(dividerCharIndex);
						pLabel->setCString((const char*)firstStr);
						pLabel->setAnchorPoint(anchor);
						pLabel->setScale(scaleRatio);
						pLabel->setPosition(ToCCPoint(curOriginal));
						pLabel->setZOrder((int)curOriginal.z);
						pLabel->setColor(ToColor3B(formatColor));
						ccList.Add(pLabel);
						curOriginal.x = position.x-dimension.w/2;
						curOriginal.y -= (rowHeight+rowDividerH);

						cocos2d::CCLabelBMFont* pLabel2 = new CCLabelBMFont();
						pLabel2->initWithString((const char*)secondStr, (const char*)formatFont);
						pLabel2->setWidth(dimension.w);
						pLabel2->setAnchorPoint(anchor);
						pLabel2->setScale(scaleRatio);
						pLabel2->setPosition(ToCCPoint(curOriginal));
						pLabel2->setZOrder((int)curOriginal.z);
						pLabel2->setColor(ToColor3B(formatColor));
						ccList.Add(pLabel2);
						int rowCharNum = (int)dimension.w/aveCharWidth;
						int rows = secondStr.CharNumber()/rowCharNum;
						int lastCharNum = secondStr.CharNumber() - (rowCharNum*rows);
						if (lastCharNum < 0)
						{
							CCLOG("rows=%d, rowCharNum=%d, lastCharNum=%d, aveCharWidth=%f, secondStr=%s\n",
									rows, rowCharNum, lastCharNum, aveCharWidth, (const char*)secondStr);
							if (!ccList.Empty())
								ccList.Release();
							throw Format_Parsing_Error;
						}
						curOriginal.y -= rows*(rowHeight+rowDividerH);
						curOriginal.x = position.x - dimension.w/2 + aveCharWidth*lastCharNum;
					}
					catch (ExceptionId& ec)
					{
						if (ec == Invalid_Index)
							CCLOG("firstRowRatio=%f, dividerCharIndex=%d, curStr=%s\n",
									firstRowRatio, dividerCharIndex, (const char*)curStr);
						if (!ccList.Empty())
							ccList.Release();
						throw Format_Parsing_Error;
					}
				}
			}
			else
			{	// one line is enough
				pLabel->setAnchorPoint(anchor);
				pLabel->setScale(scaleRatio);
				pLabel->setPosition(ToCCPoint(curOriginal));
				pLabel->setZOrder((int)curOriginal.z);
				pLabel->setColor(ToColor3B(formatColor));
				ccList.Add(pLabel);
				curOriginal.x += scaleRatio*labelSize.width;
			}
		}

		// deal with current format sub string finished. go to next round.
	}while(!leftStr.empty());

	needParse = false;
	return;
}
