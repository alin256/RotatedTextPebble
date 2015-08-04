#pragma once
#include <pebble.h>
  

void draw_text_on_a_line(GContext * ctx, GPoint start, GPoint end, int32_t angle, const char *text);
void draw_text_on_an_arc(GContext * ctx, GPoint center, int32_t rad, int32_t start_angle, int32_t end_angle, const char *text);
