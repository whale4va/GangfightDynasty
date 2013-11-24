#ifndef RICHTEXTVIEW_H_HEADER_INCLUDED_AD80DDDE
#define RICHTEXTVIEW_H_HEADER_INCLUDED_AD80DDDE
class ViewFrame;

//##ModelId=522C6B21010F
class RichTextView
{
  public:
    //##ModelId=522F2B4A00FC
    AddViewWithIndex();

    //##ModelId=523DB1F801FE
    SortByIndex();

  private:
    //##ModelId=522C6B73009F
    List<ViewFrame*> views;
    //##ModelId=522C6BDF008B
    List<Uint32> rowIndex;
    //##ModelId=522C6BEB0097
    List<Uint32> columnIndex;
};



#endif /* RICHTEXTVIEW_H_HEADER_INCLUDED_AD80DDDE */
