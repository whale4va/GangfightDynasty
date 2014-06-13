#ifndef FORWARDPATH_H_HEADER_INCLUDED_AC6D43E4
#define FORWARDPATH_H_HEADER_INCLUDED_AC6D43E4

#include "../Common/types.h"
#include "../Common/List.h"

//##ModelId=522893FD001E
class ForwardPath
{
    /** List<Uint32> */
    //##ModelId=5228961100A5
    List<Uint32> roadIdList;
    /** List<bool>, indicate every road in the forward path is inversed or not.
    Inversed means that the sequence of cities reside at road two sides are
    inversed.
 */
    //##ModelId=52289620034F
    List<Uint32> inverseOrderList;
    //##ModelId=522C845D0011
    Uint32 segmentNumber;
};



#endif /* FORWARDPATH_H_HEADER_INCLUDED_AC6D43E4 */
