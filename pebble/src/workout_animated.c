/*
 * main.c
 * Sets up a Window, BitmapLayer and blank GBitmap to be used as the display
 * container for the GBitmapSequence. It also counts the number of frames.
 *
 * Animation source:
 * BASE VERSION FROM COIPED FROM PEBBLE @
 * http://developer.getpebble.com/guides/pebble-apps/resources/animated-pngs/#using-apngs-in-code
 */

//static Window *workoutWindow;

//static GBitmap *workoutImage = NULL;
//static BitmapLayer *background;
static GBitmapSequence *workout_sequence = NULL;

static int frame_counter = 0;

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
/***********************************************
*  LOADING
************************************************/


//static void workout_window_load(Window *window) {
  //Layer *window_layer = window_get_root_layer(window);
  //GRect bounds = layer_get_bounds(window_layer);

  ///background = bitmap_layer_create(bounds);
  layer_add_child(window_layer, bitmap_layer_get_layer(background));

  load_sequence();
//}

//static void main_window_unload(Window *window) {
  gbitmap_sequence_destroy(workout_sequence);
 // bitmap_layer_destroy(background);
//}

//static void init() {
  //workoutWindow = window_create();
  window_set_fullscreen(workoutWindow, true);
//  window_set_window_handlers(workoutWindow, (WindowHandlers) {
 //   .load = main_window_load,
//    .unload = main_window_unload,
 // });
  //window_stack_push(workoutWindow, true);
//}

//static void deinit() {
//  window_destroy(workoutWindow);
//}