#ifndef WARFAREITEMVIEW_H_HEADER_INCLUDED_AD80F426
#define WARFAREITEMVIEW_H_HEADER_INCLUDED_AD80F426
#include "PictureView.h"
#include "TextView.h"
#include "../Model/Warfare.h"
#include "PureColorBar.h"

//##ModelId=522C6FCC0303
class WarfareItemView
{
  public:
    //##ModelId=526D33BF0146
    void InitWithWarfare(Warfare* war);

  private:
    //##ModelId=522C70480095
    Warfare* warfare;
    //##ModelId=522C705D035E
    PictureView countryFlags[2];
    //##ModelId=522C707601A2
    TextView name;
    //##ModelId=522C708B0314
    PictureView warFlag;
    //##ModelId=522C709603BA
    PureColorBar compareBar;
};



#endif /* WARFAREITEMVIEW_H_HEADER_INCLUDED_AD80F426 */
