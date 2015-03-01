#include <pebble.h>
#include "workout.h"
    
    
/**************************************************************
*                     IMAGE IDENTIFIERS
**************************************************************/
void genterate_workout_window(uint8_t id){
    //APP_LOG(APP_LOG_LEVEL_DEBUG, "building window # %d",id);
    switch(id)
    {
        case 1:
            set_exercise_type(RESOURCE_ID_PUSH_UPS, "pushups", 60000, false);
            break;
        case 2:
            set_exercise_type(RESOURCE_ID_PLANKS, "planks", 120000, false);
            break;
        case 3:
            set_exercise_type(RESOURCE_ID_CRUNCHES, "crunches", 60000, false);
            break;
        case 4:
            set_exercise_type(RESOURCE_ID_SQUATS, "squats", 60000, false);
            break;
        case 11:
            set_exercise_type(RESOURCE_ID_BICEP_CURLS, "bicep curls", 45000, false);
            break;
        case 13:
            set_exercise_type(RESOURCE_ID_BENCH_PRESS, "bench press", 90000, false);
            break;
        case 15:
            set_exercise_type(RESOURCE_ID_LAT_PULL_DOWN, "lat pull down", 60000, false);
            break;
        case 16:
            set_exercise_type(RESOURCE_ID_TRICEP_PUSH_DOWN, "tricep push down", 60000, false);
            break;
        case 19:
            set_exercise_type(RESOURCE_ID_TOE_TOUCH, "toe touch",30000, false);
            break;
        case 20:
            set_exercise_type(RESOURCE_ID_SIDE_LUNGE, "side lunge",30000, false);
            break;
        case 21:
            set_exercise_type(RESOURCE_ID_BUTTERFLY, "butterfly",30000, false);
            break;
        case 22:
            set_exercise_type(RESOURCE_ID_ARMBAR, "armbar",30000, false);
            break;
        case 23:
            set_exercise_type(RESOURCE_ID_TREE_POSE, "tree pose",90000, false);
            break;
        case 24:
            set_exercise_type(RESOURCE_ID_DOWNWARD_DOG, "downward facing dog",90000, false);
            break;
        case 25:
            set_exercise_type(RESOURCE_ID_UPWARD_DOG, "upward facing dog",90000, false);
            break;
         case 26:
            set_exercise_type(RESOURCE_ID_WARRIOR, "warrior",90000, false);
            break;
        default:
            // end of workout/error message
            set_exercise_type(RESOURCE_ID_TRICEP_PUSH_DOWN, "tricep push down", 60000, false);
    }
}