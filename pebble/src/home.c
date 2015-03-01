#include <pebble.h>
#include "exercise_codes.h"

enum MsgKeys {
    KEY_WORKOUTPLAN = 0x0
};
typedef enum {CLOCK, WORKOUT} WATCHFACE;
    
static Window* window;
static TextLayer* text_layer;
static Window *workoutWindow;
static GBitmap *clockImage;

WATCHFACE currentWindow;
static uint8_t workoutplan[50];//MUCH BIGGER THAN NEEDED
static int arraySize =0;
int arrayPlace =0;
static int frame_counter = 0;

/***************************************************************
*                      Graphics Misc
***************************************************************/
static void music_bg_update_proc(Layer *layer, GContext *ctx) {
  //Layer *window_layer = window_get_root_layer(window);
  //GRect bounds = layer_get_bounds(window_layer);
  
 
  //graphics_context_set_fill_color(ctx, GColorWhite);
  //graphics_fill_rect(ctx, layer_get_bounds(layer), 0, GCornerNone);
  //graphics_fill_rect(ctx, bounds, 11, GCornerNone);
  //graphics_context_set_fill_color(ctx, GColorWhite);

}
/***************************************************************
*                    Advance to Next
***************************************************************/
 
static void load_next_workout(){
    window_stack_pop(true);
    arrayPlace++;
    if(arrayPlace<arraySize){
        APP_LOG(APP_LOG_LEVEL_DEBUG, "hit--Load new window");
        currentWindow = WORKOUT;
        genterate_workout_window(workoutplan[arrayPlace]);
        
        window_stack_push(workoutWindow,true);
    }    
}

/***************************************************************
*                       Button Listing
***************************************************************/
void down_single_click_handler(ClickRecognizerRef recognizer, void *context) {
    //vibes_long_pulse();
    if(currentWindow==WORKOUT){
        load_next_workout();
    }
}
void up_single_click_handler(ClickRecognizerRef recognizer, void *context) {
    //vibes_short_pulse();

}
void select_single_click_handler(ClickRecognizerRef recognizer, void *context) {
     if(currentWindow==CLOCK && arrayPlace<arraySize){
        currentWindow = WORKOUT;
        genterate_workout_window(workoutplan[arrayPlace]);
        window_stack_push(workoutWindow,true);
    }
    else{
        //start clock, when it finishes, alter the text to done
        center_button__workout_Listener();
    }
}

void back_single_click_handler(ClickRecognizerRef recognizer, void *context) {
    vibes_double_pulse();
  if(currentWindow != CLOCK)
  {
    currentWindow = CLOCK;
    window_stack_pop(true);
    workout_deinit();
  } 
  else
  {
    window_stack_pop_all(true);
  }    
}

void click_config(Window *window){
    window_single_click_subscribe(BUTTON_ID_DOWN, down_single_click_handler);
    window_single_click_subscribe(BUTTON_ID_SELECT, select_single_click_handler);
    window_single_click_subscribe(BUTTON_ID_UP, up_single_click_handler);
    window_single_click_subscribe(BUTTON_ID_BACK, back_single_click_handler);
}
/***************************************************************
*                      App Message
***************************************************************/
static void inbox_received_callback(DictionaryIterator *iterator, void *context) {
    //read first item
    Tuple *t = dict_read_first(iterator);
    static char workoutplan_buffer[64];
      static char workoutsize_buffer[8];
    //For all items
    int lengthtuple = t->length;
    APP_LOG(APP_LOG_LEVEL_DEBUG, "APPMESSAGE %d",lengthtuple);
    memcpy(workoutplan,t->value->data,t->length);
    arraySize = lengthtuple;
}

static void inbox_dropped_callback(AppMessageResult reason, void *context) {
  APP_LOG(APP_LOG_LEVEL_ERROR, "Message dropped!");
}

static void outbox_failed_callback(DictionaryIterator *iterator, AppMessageResult reason, void *context) {
  APP_LOG(APP_LOG_LEVEL_ERROR, "Outbox send failed!");
}

static void outbox_sent_callback(DictionaryIterator *iterator, void *context) {
  APP_LOG(APP_LOG_LEVEL_INFO, "Outbox send success!");
}

/***************************************************************
*                      Load Unload
***************************************************************/
   
static void window_load(Window* window) {
    Layer* window_layer = window_get_root_layer(window);
    GRect bounds = layer_get_bounds(window_layer);
  //window_set_background_color(window, GColorOxfordBlue);
 //init layers
  //init layers
  //Layer *simple_bg_layer = layer_create(bounds);
  ///layer_set_update_proc(simple_bg_layer, music_bg_update_proc);
  //layer_add_child(window_layer, simple_bg_layer);
  
  //background clock
  BitmapLayer *background = bitmap_layer_create(bounds);
  clockImage = gbitmap_create_with_resource(RESOURCE_ID_WATCH1);
  bitmap_layer_set_bitmap(background, clockImage);
  //bitmap_layer_set_alignment(background, GAlignBottom);
  bitmap_layer_set_compositing_mode(background, GCompOpAssign);
  layer_add_child(window_layer, bitmap_layer_get_layer(background));
}

   
static void window_unload(Window* window) {
}
    
static void deinit(void) {
     window_destroy(window);
}

static void init(void) {
    APP_LOG(APP_LOG_LEVEL_DEBUG, "got here");
    window = window_create();
    //window_set_background_color(window, GColorBlack);
    window_set_fullscreen(window, true);
    window_set_window_handlers(window, (WindowHandlers){
        .load = window_load,
        .unload = window_unload
    });
    arrayPlace = 0;
        
    //Register AppMessage events
    // Register callbacks
    app_message_register_inbox_received(inbox_received_callback);
    app_message_register_inbox_dropped(inbox_dropped_callback);
    app_message_register_outbox_failed(outbox_failed_callback);
    app_message_register_outbox_sent(outbox_sent_callback);
    app_message_open(app_message_inbox_size_maximum(), app_message_outbox_size_maximum());    //Largest possible input and output buffer sizes
    
    //Resume basic inint things
    bool animated = true;
    window_stack_push(window, animated);
    workoutWindow = workout_init();
    
    //Listners for Buttons
    window_set_click_config_provider(window, (ClickConfigProvider) click_config);
    window_set_click_config_provider(workoutWindow,(ClickConfigProvider) click_config);    
}
    
int main(void){
    init();
    app_event_loop();
    deinit();
}