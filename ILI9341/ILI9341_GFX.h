#ifndef ILI9341_GFX_H
#define ILI9341_GFX_H

#include "main.h"

#define HORIZONTAL_IMAGE	0
#define VERTICAL_IMAGE		1

#define FONT_HEADER_TYPE		            0
#define FONT_HEADER_ORIENTATION	            1
#define FONT_HEADER_START		            2
#define FONT_HEADER_LETTERS		            3
#define FONT_HEADER_HEIGHT		            4
#define FONT_TYPE_FIXED			            0
#define FONT_TYPE_PROPORTIONAL	            1
#define FONT_ORIENTATION_VERTICAL_CEILING	2


uint16_t draw_text(const char *string, uint16_t x, uint16_t y,
                const unsigned char *font,
                unsigned char spacing, uint16_t color, uint8_t drawBackground);

unsigned char draw_char(unsigned char c, uint16_t x, uint16_t y,
                        const unsigned char *font, uint16_t color, uint8_t spacing, uint8_t drawBackground);

void drawBitmap(uint16_t x, uint16_t y, uint16_t w, uint16_t h,
                const unsigned char * bmp, uint16_t color);
void drawStartLogo(void);

//USING CONVERTER: http://www.digole.com/tools/PicturetoC_Hex_converter.php
//65K colour (2Bytes / Pixel)
void ILI9341_Draw_Image(const char* Image_Array, uint8_t Orientation);

void ILI9341_Draw_Hollow_Circle(uint16_t X, uint16_t Y, uint16_t Radius, uint16_t Colour);
void ILI9341_Draw_Filled_Circle(uint16_t X, uint16_t Y, uint16_t Radius, uint16_t Colour);
void ILI9341_Draw_Hollow_Rectangle_Coord(uint16_t X0, uint16_t Y0, uint16_t X1, uint16_t Y1, uint16_t Colour);
void ILI9341_Draw_Filled_Rectangle_Coord(uint16_t X0, uint16_t Y0, uint16_t X1, uint16_t Y1, uint16_t Colour);
uint16_t ILI9341_ReadPixelFromBgArray(uint16_t x, uint16_t y);
void ILI9341_drawBackground(void);
void redrawBgArea(uint16_t x, uint16_t y, uint16_t w, uint16_t h);
void ILI9341_Line(int X1, int Y1,int X2,int Y2, uint16_t color);

#endif
