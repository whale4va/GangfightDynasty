#ifndef EVENTQUEUE_H_HEADER_INCLUDED_AC6D2E12
#define EVENTQUEUE_H_HEADER_INCLUDED_AC6D2E12

#include "Event.h"

/** @brief singleton object holding all events in the game. */
//##ModelId=522B2AB90204
class EventQueue
{
  public:
    /** @brief add event (update or anything else) into event queue to manage,
    AND invoking StaticResourceManager::SpreadUpgrade if the event is one of
    upgrading type. */
    //##ModelId=522B2B6403A4
    void AddEvent(Event* event);

    /** @brief This should be a call back function invoked by <Total Timer>
    after every day passed. */
    //##ModelId=5275F3660221
    void DateUpdateNotify();

  private:
    //##ModelId=522B2B280276
    Uint32 eventNumber;
    //##ModelId=522B2B3C011B
    List<Event*> eventList;
};



#endif /* EVENTQUEUE_H_HEADER_INCLUDED_AC6D2E12 */
