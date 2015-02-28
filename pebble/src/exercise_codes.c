#include <pebble.h>
#include "workout.h"
    
    
/**************************************************************
*                     IMAGE IDENTIFIERS
**************************************************************/
/**uint32_t barbellsID = RESOURCE_ID_BARBELLS; char* barbellsStr = "barbells";
uint32_t joggingID = RESOURCE_ID_JOG; char * joggingStr = "Jogging";


Window workoutWindow = workout_init(barbellsID, barbellsStr);**/

Window* genterate_workout_window(int id){
    switch(id)
    {
        case 1:
            return workout_init(RESOURCE_ID_PUSH_UPS, "pushups", (int) 60000);
            break;
        case 2:
            return workout_init(RESOURCE_ID_PLANKS, "planks", (int) 120000);
            break;
        case 3:
            return workout_init(RESOURCE_ID_CRUNCHES, "crunches", (int) 60000);
            break;
        /**case 4:
            return workout_init(RESOURCE_ID_SQUATS, "squats", 60000);
            break;**/
        case 5:
            return workout_init(RESOURCE_ID_BICEP_CURLS, "bicep curls", (int) 45000);
            break;
        case 6:
            return workout_init(RESOURCE_ID_BENCH_PRESS, "bench press", (int) 90000);
            break;
        case 7:
            return workout_init(RESOURCE_ID_LAT_PULL_DOWN, "lat pull down", (int) 60000);
            break;
        case 8:
            return workout_init(RESOURCE_ID_TRICEP_PUSH_DOWN, "tricep push down", (int) 60000);
            break;
        /**case 9:
            return workout_init(RESOURCE_ID_TOE_TOUCH, "toe touch",30000);
            break;
        case 10:
            return workout_init(RESOURCE_ID_SIDE_LUNGE, "side lunge",30000);
            break;
        case 11:
            return workout_init(RESOURCE_ID_BUTTERFLY, "butterfly",30000);
            break;
        case 12:
            return workout_init(RESOURCE_ID_ARMBAR, "armbar",30000);
            break;
        case 13:
            return workout_init(RESOURCE_ID_TREE_POSE, "tree pose",90000);
            break;
        case 14:
            return workout_init(RESOURCE_ID_DOWNWARD_DOG, "downward dog",90000);
            break;
        case 15:
            return workout_init(RESOURCE_ID_UPWARD_DOG, "upward dog",90000);
            break;
         case 16:
            return workout_init(RESOURCE_ID_WARRIOR, "warrior",90000);
            break;**/
        default:
            // end of workout/error message
            return workout_init(RESOURCE_ID_TRICEP_PUSH_DOWN, "tricep push down", (int) 60000);
    }
}