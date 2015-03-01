#include <pebble.h>
    
Window* workout_init();

void workout_deinit(void);

void center_button__workout_Listener();

void set_exercise_type(uint32_t imageID, char* imageStr, int interval,  bool animate);