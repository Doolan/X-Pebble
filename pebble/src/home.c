#include <pebble.h>
#include "exercise_codes.h"

enum MsgKeys {
    KEY_WORKOUTPLAN = 0x0
};
typedef enum {CLOCK, WORKOUT} WATCHFACE;
    
static Window* window;
static TextLayer* text_layer;
static Window *workoutWindow;
static GBitmap *s_bitmap = NULL;
static BitmapLayer *s_bitmap_layer;
static GBitmapSequence *s_sequence = NULL;
WATCHFACE currentWindow;
static uint8_t workoutplan[50];//MUCH BIGGER THAN NEEDED
static int arraySize =0;
int arrayPlace =0;
static int frame_counter = 0;

/***************************************************************
*                    Front Graphics
***************************************************************/
static void load_sequence();

static void timer_handler(void *context) {
  uint32_t next_delay;

  // Advance to the next APNG frame
  if(gbitmap_sequence_update_bitmap_next_frame(s_sequence, s_bitmap, &next_delay)) {
    bitmap_layer_set_bitmap(s_bitmap_layer, s_bitmap);
    layer_mark_dirty(bitmap_layer_get_layer(s_bitmap_layer));

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
  if(s_sequence) {
    gbitmap_sequence_destroy(s_sequence);
    s_sequence = NULL;
  }
  if(s_bitmap) {
    gbitmap_destroy(s_bitmap);
    s_bitmap = NULL;
  }

  // Create sequence
  s_sequence = gbitmap_sequence_create_with_resource(RESOURCE_ID_WATCHFACE_WHITE);

  // Create GBitmap
  s_bitmap = gbitmap_create_blank(gbitmap_sequence_get_bitmap_size(s_sequence), GBitmapFormat8Bit);

  // Begin animation
  app_timer_register(1, timer_handler, NULL);
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
    s_bitmap_layer = bitmap_layer_create(bounds);
    layer_add_child(window_layer, bitmap_layer_get_layer(s_bitmap_layer));
    load_sequence();
}

   
static void window_unload(Window* window) {
    gbitmap_sequence_destroy(s_sequence);
    bitmap_layer_destroy(s_bitmap_layer);
}
    
static void deinit(void) {
     window_destroy(window);
}

static void init(void) {
    APP_LOG(APP_LOG_LEVEL_DEBUG, "got here");
    window = window_create();
    //window_set_background_color(window, GColorBlack);
    window_set_fullscreen(window, true);
    window = window_create();
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