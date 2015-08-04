#include <pebble.h>
#include "polygon_font.h"
  
static int32_t RADIAN_TO_ANGLE = (int)(TRIG_MAX_ANGLE/3.14159265/2);
static const uint16_t CHAR_WIDTH = 7;
static const int16_t FONT_MID = 3;
static GPathInfo letter_polygons[3] = 
{//A
{
  .num_points = 4,
  .points = (GPoint []) {{0, 10}, {5, 0}, {5,10}, {0,5}}
},//B
{
  .num_points = 6,
  .points = (GPoint []) {{0, 10}, {0, 0}, {5, 3}, {0, 5}, {5, 8}, {0, 10}}
},//C
{
  .num_points = 3,
  .points = (GPoint []) {{5, 10}, {0, 5}, {5, 0}}
}
};

void draw_text_on_a_line(GContext * ctx, GPoint start, GPoint end, int32_t angle, const char *text){
  int16_t text_len = strlen(text);
  int16_t dx = (end.x - start.x)/text_len;
  int16_t dy = (end.y - start.y)/text_len;
  for (int16_t i = 0; i<text_len; i++){
    if (text[i]==' '){
      continue;
    }
    if (text[i]>='A' && text[i]<='C'){
      GPoint dist = GPoint(start.x + dx*i, start.y+dy*i);
      GPath *path = gpath_create(&letter_polygons[text[i]- 'A']);
      gpath_move_to(path, dist);
      gpath_rotate_to(path, angle);
      gpath_draw_outline_open(ctx, path);
    }
  }
  return;
}



void draw_text_on_an_arc(GContext * ctx, GPoint center, int32_t rad, int32_t start_angle, int32_t end_angle, const char *text){
  int16_t text_len = strlen(text)/sizeof(text[0]);
  int32_t da = (end_angle - start_angle)/text_len;
  for (int32_t i = 0; i<text_len; i++){
    if (text[i]==' '){
      continue;
    }

    int32_t angle = start_angle + i*da;
    
    if (text[i]>='A' && text[i]<='C'){
      GPoint dist = GPoint(center.x+sin_lookup(angle)*rad/TRIG_MAX_RATIO,center.y-cos_lookup(angle)*rad/TRIG_MAX_RATIO);
      GPath *path = gpath_create(&letter_polygons[text[i]- 'A']);
      gpath_move_to(path, dist);
      gpath_rotate_to(path, angle);
      gpath_draw_outline_open(ctx, path);
    }
  }

}


void draw_text_on_arc_around(GContext * ctx, GPoint center, int32_t rad, int32_t angle, const char *text){
  uint16_t text_len = strlen(text);
  uint32_t linear_len = text_len*CHAR_WIDTH;
  uint32_t angle_len = linear_len*RADIAN_TO_ANGLE/rad;
  draw_text_on_an_arc(ctx, center, rad, angle -angle_len/2, angle+angle_len/2, text);
  // linearlen/2/pi
}