#include <pebble.h>
#include "workout.h"
    
    
/**************************************************************
*                     IMAGE IDENTIFIERS
**************************************************************/
/**uint32_t barbellsID = RESOURCE_ID_BARBELLS; char* barbellsStr = "barbells";
uint32_t joggingID = RESOURCE_ID_JOG; char * joggingStr = "Jogging";


Window workoutWindow = set_exercise_type(barbellsID, barbellsStr);**/

void genterate_workout_window(uint8_t id){
    //int idINT = (int) id;
    APP_LOG(APP_LOG_LEVEL_DEBUG, "building window # %d",id);
    switch(id)
    {
        case 1:
            set_exercise_type(RESOURCE_ID_PUSH_UPS, "pushups", (int) 60000);
            break;
        case 2:
            set_exercise_type(RESOURCE_ID_PLANKS, "planks", (int) 120000);
            break;
        case 3:
            set_exercise_type(RESOURCE_ID_CRUNCHES, "crunches", (int) 60000);
            break;
        case 4:
            set_exercise_type(RESOURCE_ID_SQUATS, "squats", 60000);
            break;
        case 5:
            set_exercise_type(RESOURCE_ID_BICEP_CURLS, "bicep curls", (int) 45000);
            break;
        case 6:
            set_exercise_type(RESOURCE_ID_BENCH_PRESS, "bench press", (int) 90000);
            break;
        case 7:
            set_exercise_type(RESOURCE_ID_LAT_PULL_DOWN, "lat pull down", (int) 60000);
            break;
        case 8:
            set_exercise_type(RESOURCE_ID_TRICEP_PUSH_DOWN, "tricep push down", (int) 60000);
            break;
        case 9:
            set_exercise_type(RESOURCE_ID_TOE_TOUCH, "toe touch",30000);
            break;
        case 10:
            set_exercise_type(RESOURCE_ID_SIDE_LUNGE, "side lunge",30000);
            break;
        case 11:
            set_exercise_type(RESOURCE_ID_BUTTERFLY, "butterfly",30000);
            break;
        case 12:
            set_exercise_type(RESOURCE_ID_ARMBAR, "armbar",30000);
            break;
        case 13:
            set_exercise_type(RESOURCE_ID_TREE_POSE, "tree pose",90000);
            break;
        case 14:
            set_exercise_type(RESOURCE_ID_DOWNWARD_DOG, "downward facing dog",90000);
            break;
        case 15:
            set_exercise_type(RESOURCE_ID_UPWARD_DOG, "upward facing dog",90000);
            break;
         case 16:
            set_exercise_type(RESOURCE_ID_WARRIOR, "warrior",90000);
            break;
        default:
            // end of workout/error message
            set_exercise_type(RESOURCE_ID_TRICEP_PUSH_DOWN, "tricep push down", (int) 60000);
    }
}