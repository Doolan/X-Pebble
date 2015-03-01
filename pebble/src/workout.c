//IMPORTS
#include <pebble.h>
#include "home.h"
   
    
//WINDOWS
static Window *workoutWindow;//THIS
static char* workoutImageID;
static char* workoutDisplayText;//EXERCISE TEXT
static Layer *window_layer;

static TextLayer* text_layer;//EXERCISE NAME
static TextLayer* start_Text_Layer;//START
static TextLayer* finshed_Text_Layer;//NEXT

static BitmapLayer* background;
static GBitmap* workoutImage;
static uint32_t currentImage;//CODE
static char* workoutString;
static int workoutcycle[] = {};
static int workoutinterval = 0;
AppTimer * apptimer;
static bool forward = true;
//Rotations
static GBitmapSequence *workout_sequence = NULL;
static int frame_counter = 0;
static bool animated = false;

/************************************************************
*                    Animation
************************************************************/
static void load_sequence();

static void timer_handler(void *context) {
  uint32_t next_delay;

  // Advance to the next APNG frame
  if(gbitmap_sequence_update_bitmap_next_frame(workout_sequence, workoutImage, &next_delay)) {
    bitmap_layer_set_bitmap(background, workoutImage);
    layer_mark_dirty(bitmap_layer_get_layer(background));

    // Timer for that delay
    app_timer_register(next_delay, timer_handler, NULL);

    frame_counter++;
  } else {
    // Start again
    load_sequence();

    APP_LOG(APP_LOG_LEVEL_INFO, "Frames: %d", frame_counter);
    frame_counter = 0;
  }
}

static void load_sequence() {
  // Free old data
  if(workout_sequence) {
    gbitmap_sequence_destroy(workout_sequence);
    workout_sequence = NULL;
  }
  if(workoutImage) {
    gbitmap_destroy(workoutImage);
    workoutImage = NULL;
  }

  // Create sequence
  workout_sequence = gbitmap_sequence_create_with_resource(RESOURCE_ID_ANIMATION);

  // Create GBitmap
  workoutImage = gbitmap_create_blank(gbitmap_sequence_get_bitmap_size(workout_sequence), GBitmapFormat8Bit);

  // Begin animation
  app_timer_register(1, timer_handler, NULL);
}


/***************************************************************
*                      Timing
***************************************************************/

static void finished(void *data){
    vibes_long_pulse();
    APP_LOG(APP_LOG_LEVEL_DEBUG, "hit--apptimer");
    layer_add_child(window_layer, text_layer_get_layer(finshed_Text_Layer));   
    
    //send AJAX CODE THAT EVENT IS DONE?
}

static void runtimer(){
    APP_LOG(APP_LOG_LEVEL_DEBUG, "hit--apptimer");
   AppTimer * apptimer = app_timer_register(workoutinterval, finished, NULL);
}

 void center_button__workout_Listener(){
     if(forward){
        layer_remove_from_parent(text_layer_get_layer(start_Text_Layer));
        text_layer_destroy(start_Text_Layer);
        runtimer();
        forward = false;
     }
}



/***************************************************************
*                      Graphics Misc  BW
***************************************************************/
static void workoutImage_bg_update_proc(Layer *layer, GContext *ctx) {
    Layer *window_layer = window_get_root_layer(workoutWindow);
    GRect bounds = layer_get_bounds(window_layer);  
 
    graphics_context_set_fill_color(ctx, GColorBlack);
    graphics_fill_rect(ctx, layer_get_bounds(layer), 0, GCornerNone);
    graphics_fill_rect(ctx, bounds, 11, GCornerNone);
    graphics_context_set_fill_color(ctx, GColorWhite);

}

/************************************************************
*                    Animation
************************************************************/
static void load_sequence();

static void timer_handler(void *context) {
  uint32_t next_delay;

  // Advance to the next APNG frame
  if(gbitmap_sequence_update_bitmap_next_frame(workout_sequence, workoutImage, &next_delay)) {
    bitmap_layer_set_bitmap(background, workoutImage);
    layer_mark_dirty(bitmap_layer_get_layer(background));

    // Timer for that delay
    app_timer_register(next_delay, timer_handler, NULL);

    frame_counter++;
  } else {
    // Start again
    load_sequence();

    APP_LOG(APP_LOG_LEVEL_INFO, "Frames: %d", frame_counter);
    frame_counter = 0;
  }
}

static void load_sequence() {
  // Free old data
  if(workout_sequence) {
    gbitmap_sequence_destroy(workout_sequence);
    workout_sequence = NULL;
  }
  if(workoutImage) {
    gbitmap_destroy(workoutImage);
    workoutImage = NULL;
  }

  // Create sequence
  workout_sequence = gbitmap_sequence_create_with_resource(RESOURCE_ID_ANIMATION);

  // Create GBitmap
  workoutImage = gbitmap_create_blank(gbitmap_sequence_get_bitmap_size(workout_sequence), GBitmapFormat8Bit);

  // Begin animation
  app_timer_register(1, timer_handler, NULL);

/***************************************************************
*                       LOAD and UNLOAD
***************************************************************/
static void workout_window_load(Window *window) {
     window_layer = window_get_root_layer(window);
     GRect bounds = layer_get_bounds(window_layer);
    //background 
    background = bitmap_layer_create(bounds);

    if(!animated)
    {//init layers BW
        Layer *simple_bg_layer = layer_create(bounds);
        layer_set_update_proc(simple_bg_layer, workoutImage_bg_update_proc);
        layer_add_child(window_layer, simple_bg_layer);
        workoutImage = gbitmap_create_with_resource(currentImage);
        bitmap_layer_set_bitmap(background, workoutImage);
        bitmap_layer_set_alignment(background, GAlignCenter);
        bitmap_layer_set_compositing_mode(background, GCompOpAssign);
        layer_add_child(window_layer, bitmap_layer_get_layer(background));
    }
    else
    {//animations
        layer_add_child(window_layer, bitmap_layer_get_layer(background));
        load_sequence();
    }

         
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
            .size   = {50, 30}
    });
    text_layer_set_text(finshed_Text_Layer, "Next");
    text_layer_set_font(finshed_Text_Layer, fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD));
    
    
}

static void workout_window_unload(Window *window) {
    if(animated){
        gbitmap_sequence_destroy(workout_sequence);
    }
    layer_remove_child_layers(window_layer);//marks all children as dirty and their memory should get returned
    gbitmap_destroy(workoutImage);
    bitmap_layer_destroy(background);
    text_layer_destroy(text_layer);    
}
/***************************************************************
*                 Set up Exercises and What not
***************************************************************/
void set_exercise_type(uint32_t imageID, char* imageStr, int interval, bool animate){
    animated = animate;
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
    
    window_set_fullscreen(workoutWindow, true);
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



