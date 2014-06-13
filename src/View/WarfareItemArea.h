#ifndef WARFAREITEMAREA_H_HEADER_INCLUDED_AD80D743
#define WARFAREITEMAREA_H_HEADER_INCLUDED_AD80D743

#include "../Common/types.h"
#include "../Model/Warfare.h"

//##ModelId=522C856303B9
class WarfareItemArea
{
  public:
    /** @brief intial & display warfare item view for specific warfare */
    //##ModelId=526D31D402A9
    void PrepareItemView(Warfare* war);

    /** @brief show warfare items between specific interval in responding user
    tap move operation */
    //##ModelId=526D31E402BE
    void ShowItemBetween();

    /** @brief destory & dismiss specific war item view for dedicated warfare
    because the war has finished */
    //##ModelId=526D3252033A
    void DestoryItemView(Warfare* war);

  private:
    //##ModelId=522C857D0065
    Uint32 itemNumber;
    //##ModelId=522C8589037D
    Uint32 maxShowItem;
    //##ModelId=522C859B0237
    Uint32 currentItemInterval[2];
};



#endif /* WARFAREITEMAREA_H_HEADER_INCLUDED_AD80D743 */
