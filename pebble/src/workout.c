//IMPORTS
#include <pebble.h>

//WINDOWS
static Window *workoutWindow;
static char* workoutImageID;
static char* workoutDisplayText;
static TextLayer* text_layer;
static BitmapLayer* background;
static GBitmap* workoutImage;
static uint32_t currentImage;
static char* workoutString;
static int workoutcycle[] = {};


/***************************************************************
*                      Timing
***************************************************************/







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
    background = bitmap_layer_create(bounds);
    //char * resource = "RESOURCE_ID_";
    //char * workout = "BARBELLS";
    //strcat(resource, workout);
    //uint32_t currentImage = *resource;
    //char * currentImage = resource + workout;    
    
    workoutImage = gbitmap_create_with_resource(currentImage);
    bitmap_layer_set_bitmap(background, workoutImage);
    bitmap_layer_set_alignment(background, GAlignCenter);
    bitmap_layer_set_compositing_mode(background, GCompOpAssign);
    layer_add_child(window_layer, bitmap_layer_get_layer(background));
  
    text_layer = text_layer_create((GRect) {
        .origin = {2, 120},
            .size   = {bounds.size.w, 30}
    });
    text_layer_set_text(text_layer, workoutString);
    text_layer_set_font(text_layer, fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD));
    layer_add_child(window_layer, text_layer_get_layer(text_layer));  
}

static void workout_window_unload(Window *window) {
    gbitmap_destroy(workoutImage);
    bitmap_layer_destroy(background);
    text_layer_destroy(text_layer);    
}
/***************************************************************
*                       INT and DE INT
***************************************************************/
Window* workout_init(uint32_t imageID, char* imageStr, int interval) {
    currentImage = imageID;
    workoutString = imageStr;
    
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



