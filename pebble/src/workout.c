//IMPORTS
#include <pebble.h>
#include "home.h"
   
    
//WINDOWS
static Window *workoutWindow;
static char* workoutImageID;
static char* workoutDisplayText;
static Layer *window_layer;
static TextLayer* text_layer;
static TextLayer* start_Text_Layer;
static TextLayer* finshed_Text_Layer;
static BitmapLayer* background;
static GBitmap* workoutImage;
static uint32_t currentImage;
static char* workoutString;
static int workoutcycle[] = {};
static int workoutinterval = 0;
AppTimer * apptimer;
static bool forward = true;





/***************************************************************
*                      Timing
***************************************************************/

static void finished(void *data){
    vibes_long_pulse();
    //load_next_workout();
    APP_LOG(APP_LOG_LEVEL_DEBUG, "hit--apptimer");
    layer_add_child(window_layer, text_layer_get_layer(finshed_Text_Layer));   
    //vibes_long_pulse();
    
    //send AJAX CODE THAT EVENT IS DONE?
}

static void runtimer(){
    APP_LOG(APP_LOG_LEVEL_DEBUG, "hit--apptimer");
   AppTimer * apptimer = app_timer_register(workoutinterval, finished, NULL);
}
//AppTimer * app_timer_register(6000, AppTimerCallback callback, void * callback_data)

/**timeout_ms
The expiry time in milliseconds from the current time
callback
The callback that gets called at expiry time
callback_data
The data that will be passed to callback**/


 void center_button__workout_Listener(){
     if(forward){
        layer_remove_from_parent(text_layer_get_layer(start_Text_Layer));
        text_layer_destroy(start_Text_Layer);
        runtimer();
        forward = false;
     }
}



/***************************************************************
*                      Graphics Misc
***************************************************************/
static void cage_bg_update_proc(Layer *layer, GContext *ctx) {
    Layer *window_layer = window_get_root_layer(workoutWindow);
    GRect bounds = layer_get_bounds(window_layer);  
 
    graphics_context_set_fill_color(ctx, GColorBlack);
    graphics_fill_rect(ctx, layer_get_bounds(layer), 0, GCornerNone);
    graphics_fill_rect(ctx, bounds, 11, GCornerNone);
    graphics_context_set_fill_color(ctx, GColorWhite);

}
/***************************************************************
*                       LOAD and UNLOAD
***************************************************************/
static void workout_window_load(Window *window) {
     window_layer = window_get_root_layer(window);
     GRect bounds = layer_get_bounds(window_layer);

  //init layers
    Layer *simple_bg_layer = layer_create(bounds);
    layer_set_update_proc(simple_bg_layer, cage_bg_update_proc);
    layer_add_child(window_layer, simple_bg_layer);

    //background 
    background = bitmap_layer_create(bounds);    
    workoutImage = gbitmap_create_with_resource(currentImage);
    bitmap_layer_set_bitmap(background, workoutImage);
    bitmap_layer_set_alignment(background, GAlignCenter);
    bitmap_layer_set_compositing_mode(background, GCompOpAssign);
    layer_add_child(window_layer, bitmap_layer_get_layer(background));
          
    //Text Work Out Name
    text_layer = text_layer_create((GRect) {
        .origin = {2, 120},
            .size   = {bounds.size.w, 30}
    });
    text_layer_set_text(text_layer, workoutString);
    text_layer_set_font(text_layer, fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD));
    layer_add_child(window_layer, text_layer_get_layer(text_layer));  
    
    //Text Work Out Name
    start_Text_Layer = text_layer_create((GRect) {
        .origin = {2, 20},
            .size   = {50, 30}
    });
    text_layer_set_text(start_Text_Layer, "Start");
    text_layer_set_font(start_Text_Layer, fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD));
    layer_add_child(window_layer, text_layer_get_layer(start_Text_Layer));      
    
    //Finished Layer (does not get pushed on until after the timer is done)
   finshed_Text_Layer = text_layer_create((GRect) {
        .origin = {2, 20},
            .size   = {70, 30}
    });
    text_layer_set_text(finshed_Text_Layer, "Next");
    text_layer_set_font(finshed_Text_Layer, fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD));
    
    
}

static void workout_window_unload(Window *window) {
    layer_remove_child_layers(window_layer);//marks all children as dirty and their memory should get returned
    gbitmap_destroy(workoutImage);
    bitmap_layer_destroy(background);
    text_layer_destroy(text_layer);    
}
/***************************************************************
*                 Set up Exercises and What not
***************************************************************/
void set_exercise_type(uint32_t imageID, char* imageStr, int interval){
    currentImage = imageID;
    workoutString = imageStr;
    workoutinterval = interval;
    forward = true;
}



/***************************************************************
*                       INT and DE INT
***************************************************************/
Window* workout_init() {
    currentImage = RESOURCE_ID_PUSH_UPS;
    workoutString = "pushups";
    
    //START TEXT
    workoutWindow = window_create();
    window_set_window_handlers(workoutWindow, (WindowHandlers) {
        .load = workout_window_load,
        .unload = workout_window_unload,
    });
    return workoutWindow;
}


void workout_deinit(void) {

   window_destroy(workoutWindow);
}



