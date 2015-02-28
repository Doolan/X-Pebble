//IMPORTS
#include <pebble.h>

//WINDOWS
Window *workoutWindow;
char* workoutImageID;
char* workoutDisplayText;

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
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);

  //init layers
  Layer *simple_bg_layer = layer_create(bounds);
  layer_set_update_proc(simple_bg_layer, cage_bg_update_proc);
  layer_add_child(window_layer, simple_bg_layer);
  
  //background 
  BitmapLayer *background = bitmap_layer_create(bounds);
  GBitmap *workoutImage = gbitmap_create_with_resource(RESOURCE_ID_BARBELLS);
  bitmap_layer_set_bitmap(background, workoutImage);
  bitmap_layer_set_alignment(background, GAlignCenter);
  bitmap_layer_set_compositing_mode(background, GCompOpAssign);
  layer_add_child(window_layer, bitmap_layer_get_layer(background));
}

static void workout_window_unload(Window *window) {
}
/***************************************************************
*                       INT and DE INT
***************************************************************/
static Window* workout_init(void) {
  workoutWindow = window_create();
  window_set_window_handlers(workoutWindow, (WindowHandlers) {
    .load = workout_window_load,
    .unload = workout_window_unload,
  });
//  spriteCount =0;
  return workoutWindow;
}


static void workout_deinit(void) {

 window_destroy(workoutWindow);
}



