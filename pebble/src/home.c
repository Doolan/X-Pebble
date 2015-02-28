#include <pebble.h>
#include <workout.c>

typedef enum {CLOCK, WORKOUT} WATCHFACE;
    
static Window* window;
static TextLayer* text_layer;
#define BUFF 64
Window *workoutWindow;
WATCHFACE currentWindow;
    





/***************************************************************
*                       Button Listing
***************************************************************/
void down_single_click_handler(ClickRecognizerRef recognizer, void *context) {
    if(currentWindow==CLOCK){
        currentWindow = WORKOUT;
        window_stack_push(workoutWindow,true);
    }
}
void up_single_click_handler(ClickRecognizerRef recognizer, void *context) {
    vibes_short_pulse();

}
void select_single_click_handler(ClickRecognizerRef recognizer, void *context) {
     vibes_long_pulse();
}

void back_single_click_handler(ClickRecognizerRef recognizer, void *context) {
    vibes_double_pulse();
  if(currentWindow != CLOCK)
  {
    currentWindow = CLOCK;
    window_stack_pop(true);
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










    
static void window_load(Window* window) {
    Layer* window_layer = window_get_root_layer(window);
    GRect bounds = layer_get_bounds(window_layer);
  //window_set_background_color(window, GColorOxfordBlue);
    text_layer = text_layer_create((GRect) {
        .origin = {0, 62},
        .size   = {bounds.size.w, 30}
    });
    char* str = "Hello, World";
    text_layer_set_text(text_layer, str);
    text_layer_set_text_alignment(text_layer, GTextAlignmentCenter);
    text_layer_set_background_color(text_layer, GColorClear);
    //  text_layer_set_text_color(text_layer, GColorChromeYellow);
    text_layer_set_font(text_layer, fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD));
    layer_add_child(window_layer, text_layer_get_layer(text_layer));
  
     //Tuplet initial_value[] = {
     //  TupletCString(MONEY, "$12,345,678")
    // };
  
    //app_sync_init(&sync, sync_buffer, sizeof(sync_buffer), initial_value, 
    //             ARRAY_LENGTH(initial_value), sync_success, sync_error, NULL);
}
   
static void window_unload(Window* window) {
     text_layer_destroy(text_layer);
}
    
static void deinit(void) {
     window_destroy(window);
}

static void init(void) {
    window = window_create();
    window_set_window_handlers(window, (WindowHandlers){
        .load = window_load,
        .unload = window_unload
    });
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