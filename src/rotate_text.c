#include <pebble.h>
#include "polygon_font.h"
  
static Window *s_main_window;
static Layer *s_canvas_layer;
//static GBitmap *buffer;
//static GBitmap *subBuffer;
//static uint8_t* bufferData;
//static GBitmap *city1;
//static uint8_t* cityBufferData;

static void canvas_update_proc(Layer *this_layer, GContext *ctx) {
  GRect bounds = layer_get_bounds(this_layer);

  // Get the center of the screen (non full-screen)
  GPoint center = GPoint(bounds.size.w / 2, (bounds.size.h / 2));

  graphics_context_set_text_color(ctx, GColorBlack);
  GRect textRect = GRect(0, 0, 65, 21);
  //graphics_draw_text(ctx, "Moscow", fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD), textRect, GTextOverflowModeTrailingEllipsis, GTextAlignmentCenter, NULL);
  //buffer = graphics_capture_frame_buffer(ctx);
  //subBuffer = gbitmap_create_as_sub_bitmap(buffer, textRect);
  
  //uint16_t bytesPerRow = gbitmap_get_bytes_per_row(subBuffer);
 // bufferData = gbitmap_get_data(subBuffer);
  
  //uint16_t totalSize = bytesPerRow*textRect.size.h;
  
  //cityBufferData = malloc(totalSize);
  //memcpy(cityBufferData, bufferData, totalSize);

  //city1 = gbitmap_create_blank(textRect.size,gbitmap_get_format(subBuffer));
  //gbitmap_set_data(city1, cityBufferData, gbitmap_get_format(subBuffer), bytesPerRow, true);
    //TODO free the memory;
  //cityBufferData = malloc(bufferData)
  //graphics_release_frame_buffer(ctx, buffer);
  
  //int32_t max_i = 6;
  //for (int32_t i = 0; i<max_i; ++i){
  // GPoint offset = GPoint(center.x+sin_lookup(i*TRIG_MAX_ANGLE/max_i)*60/TRIG_MAX_RATIO, center.y-cos_lookup(i*TRIG_MAX_ANGLE/max_i)*60/TRIG_MAX_RATIO);
  //  graphics_draw_rotated_bitmap(ctx, city1, GPoint(33, 11), i*TRIG_MAX_ANGLE/max_i, offset);
  //}
  
  graphics_context_set_antialiased(ctx, true);
  graphics_context_set_stroke_color(ctx, GColorBlack);
  graphics_context_set_stroke_width(ctx, 1);
  
  draw_text_on_a_line(ctx, GPoint(60, 60), GPoint(100,100), TRIG_MAX_ANGLE/8, "ABCABBB");
  
  //draw_text_on_an_arc(ctx, center, 50, 0, TRIG_MAX_ANGLE-1, "BAAAAACBBBBBBAAAAACBBBBB");
  draw_text_on_an_arc(ctx, center, 61, 0, TRIG_MAX_ANGLE-1, "BAAAAACBB BAAAAACBB BAAAAACBB BAAAAACBB BAAAAACBB ");
  graphics_context_set_stroke_color(ctx, GColorDarkGray);
  
  draw_text_on_an_arc(ctx, center, 72, 0, TRIG_MAX_ANGLE-1, "BAAAAACBB BAAAAACBB BAAAAACBB BAAAAACBB BAAAAACBB BAAAAACBB ");
  //graphics_context_set_stroke_color(ctx, GColorDarkCandyAppleRed);
  
  draw_text_on_an_arc(ctx, center, 84, -TRIG_MAX_ANGLE/6, TRIG_MAX_ANGLE/6, "BAAAAACBB BAAAAACBB BAAAAACBB");
  draw_text_on_an_arc(ctx, center, 83, -TRIG_MAX_ANGLE/6+TRIG_MAX_ANGLE/2, TRIG_MAX_ANGLE/6+TRIG_MAX_ANGLE/2, "BAAAAACBB BAAAAACBB BAAAAACBB");
  
  
    //(ctx, city1, GPoint(32,-40), TRIG_MAX_ANGLE/8,center);
  
  
  // Draw the 'loop' of the 'P'
  //graphics_context_set_fill_color(ctx, GColorBlack);
  //graphics_fill_circle(ctx, center, 40);
  //graphics_context_set_fill_color(ctx, GColorWhite);
  //graphics_fill_circle(ctx, center, 35);

  // Draw the 'stalk'
  //graphics_context_set_fill_color(ctx, GColorBlack);
  //graphics_fill_rect(ctx, GRect(32, 40, 5, 100), 0, GCornerNone);
}

static void main_window_load(Window *window) {
  //window->fullscreen = true;
  Layer *window_layer = window_get_root_layer(window);
  GRect window_bounds = layer_get_bounds(window_layer);

  // Create Layer
  s_canvas_layer = layer_create(GRect(0, 0, window_bounds.size.w, window_bounds.size.h));
  layer_add_child(window_layer, s_canvas_layer);

  // Set the update_proc
  layer_set_update_proc(s_canvas_layer, canvas_update_proc);
}

static void main_window_unload(Window *window) {
  // Destroy Layer
  layer_destroy(s_canvas_layer);
  //gbitmap_destroy(city1);
  //free(cityBufferData);
}

static void init(void) {
  // Create main Window
  s_main_window = window_create();
  
  window_set_window_handlers(s_main_window, (WindowHandlers) {
    .load = main_window_load,
    .unload = main_window_unload,
  });
  window_stack_push(s_main_window, true);
}

static void deinit(void) {
  // Destroy main Window
  window_destroy(s_main_window);
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}