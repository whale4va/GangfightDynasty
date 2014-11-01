/*
 * SceneScheduler.h
 *
 *  Created on: 8 Sep, 2014
 *      Author: Foraby.Va
 *
 *  @brief scene scheduler is charging for change scene
 */

#ifndef SCENESCHEDULER_H_
#define SCENESCHEDULER_H_

#include "../Model/City.h"

/**
 * @brief class used for schedule scene
 */
class SceneScheduler
{

public:
    // switch to city scene with specific city object
    static void SwitchToCityScene(City* pCity);
    
};


#endif /* SCENESCHEDULER_H_ */
