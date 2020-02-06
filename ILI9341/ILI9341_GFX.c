#include "ILI9341_STM32_Driver.h"
#include "ILI9341_GFX.h"
#include "logo.h"

extern SPI_HandleTypeDef HSPI_INSTANCE;

/*Draws a full screen picture from flash. Image converted from RGB .jpeg/other to C array using online converter*/
//USING CONVERTER: http://www.digole.com/tools/PicturetoC_Hex_converter.php
//65K colour (2Bytes / Pixel)
void ILI9341_Draw_Image(const char* Image_Array, uint8_t Orientation)
{
	if(Orientation == SCREEN_HORIZONTAL_1)
	{
		ILI9341_Set_Rotation(SCREEN_HORIZONTAL_1);
		ILI9341_Set_Address(0,0,ILI9341_SCREEN_WIDTH,ILI9341_SCREEN_HEIGHT);

		HAL_GPIO_WritePin(LCD_DC_PORT, LCD_DC_PIN, GPIO_PIN_SET);
		HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_RESET);

		unsigned char Temp_small_buffer[BURST_MAX_SIZE];
		uint32_t counter = 0;
		for(uint32_t i = 0; i < ILI9341_SCREEN_WIDTH*ILI9341_SCREEN_HEIGHT*2/BURST_MAX_SIZE; i++)
		{
				for(uint32_t k = 0; k< BURST_MAX_SIZE; k++)
				{
					Temp_small_buffer[k]	= Image_Array[counter+k];
				}
				HAL_SPI_Transmit(HSPI_INSTANCE_PTR, (unsigned char*)Temp_small_buffer, BURST_MAX_SIZE, 10);
				counter += BURST_MAX_SIZE;
		}
		HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_SET);
	}
	else if(Orientation == SCREEN_HORIZONTAL_2)
	{
		ILI9341_Set_Rotation(SCREEN_HORIZONTAL_2);
		ILI9341_Set_Address(0,0,ILI9341_SCREEN_WIDTH,ILI9341_SCREEN_HEIGHT);

		HAL_GPIO_WritePin(LCD_DC_PORT, LCD_DC_PIN, GPIO_PIN_SET);
		HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_RESET);

		unsigned char Temp_small_buffer[BURST_MAX_SIZE];
		uint32_t counter = 0;
		for(uint32_t i = 0; i < ILI9341_SCREEN_WIDTH*ILI9341_SCREEN_HEIGHT*2/BURST_MAX_SIZE; i++)
		{
				for(uint32_t k = 0; k< BURST_MAX_SIZE; k++)
				{
					Temp_small_buffer[k]	= Image_Array[counter+k];
				}
				HAL_SPI_Transmit(HSPI_INSTANCE_PTR, (unsigned char*)Temp_small_buffer, BURST_MAX_SIZE, 10);
				counter += BURST_MAX_SIZE;
		}
		HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_SET);
	}
	else if(Orientation == SCREEN_VERTICAL_2)
	{
		ILI9341_Set_Rotation(SCREEN_VERTICAL_2);
		ILI9341_Set_Address(0,0,ILI9341_SCREEN_HEIGHT,ILI9341_SCREEN_WIDTH);

		HAL_GPIO_WritePin(LCD_DC_PORT, LCD_DC_PIN, GPIO_PIN_SET);
		HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_RESET);

		unsigned char Temp_small_buffer[BURST_MAX_SIZE];
		uint32_t counter = 0;
		for(uint32_t i = 0; i < ILI9341_SCREEN_WIDTH*ILI9341_SCREEN_HEIGHT*2/BURST_MAX_SIZE; i++)
		{
				for(uint32_t k = 0; k< BURST_MAX_SIZE; k++)
				{
					Temp_small_buffer[k]	= Image_Array[counter+k];
				}
				HAL_SPI_Transmit(HSPI_INSTANCE_PTR, (unsigned char*)Temp_small_buffer, BURST_MAX_SIZE, 10);
				counter += BURST_MAX_SIZE;
		}
		HAL_GPIO_WritePin(GPIOC, LCD_CS_PIN, GPIO_PIN_SET);
	}
	else if(Orientation == SCREEN_VERTICAL_1)
	{
		ILI9341_Set_Rotation(SCREEN_VERTICAL_1);
		ILI9341_Set_Address(0,0,ILI9341_SCREEN_HEIGHT,ILI9341_SCREEN_WIDTH);

		HAL_GPIO_WritePin(LCD_DC_PORT, LCD_DC_PIN, GPIO_PIN_SET);
		HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_RESET);

		unsigned char Temp_small_buffer[BURST_MAX_SIZE];
		uint32_t counter = 0;
		for(uint32_t i = 0; i < ILI9341_SCREEN_WIDTH*ILI9341_SCREEN_HEIGHT*2/BURST_MAX_SIZE; i++)
		{
				for(uint32_t k = 0; k< BURST_MAX_SIZE; k++)
				{
					Temp_small_buffer[k]	= Image_Array[counter+k];
				}
				HAL_SPI_Transmit(HSPI_INSTANCE_PTR, (unsigned char*)Temp_small_buffer, BURST_MAX_SIZE, 10);
				counter += BURST_MAX_SIZE;
		}
		HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_SET);
	}
}


uint16_t draw_text(const char *string, uint16_t x, uint16_t y,
                const unsigned char *font,
                unsigned char spacing, uint16_t color, uint8_t drawBackground) {
    uint16_t xAtBegin = x;

	while (*string != 0) {

        unsigned char c = *string ++;

        switch(c) {
            case 194:
                c = *string ++;
                c = 148;
                break;
            case 195: {
                c = *string ++;
                switch(c) {
                    case 161:
                        c = 127;
                        break;
                    case 169:
                        c = 128;
                        break;
                    case 173:
                        c = 129;
                        break;
                    case 179:
                        c = 130;
                        break;
                    case 182:
                        c = 131;
                        break;
                    case 186:
                        c = 133;
                        break;
                    case 188:
                        c = 134;
                        break;
                    case 164:
                        c = 136;
                        break;
                    case 159:
                        c = 137;
                        break;
                    case 129:
                        c = 138;
                        break;
                    case 137:
                        c = 139;
                        break;
                    case 141:
                        c = 140;
                        break;
                    case 147:
                        c = 141;
                        break;
                    case 150:
                        c = 142;
                        break;
                    case 154:
                        c = 144;
                        break;
                    case 156:
                        c = 145;
                        break;
                    case 132:
                        c = 147;
                        break;
                    default:
                        continue;
                }
                break;
            }
            case 197: {
                c = *string ++;
                switch(c) {
                    case 144:
                        c = 143;
                        break;
                    case 145:
                        c = 132;
                        break;
                    case 176:
                        c = 146;
                        break;
                    case 177:
                        c = 135;
                        break;
                    default:
                        continue;
                }
                break;
            }
            default:
                break;
        }

		x += draw_char(c, x, y, font, color,spacing, drawBackground);
	}

    return x - xAtBegin;
}

unsigned char draw_char(unsigned char c, uint16_t x, uint16_t y, const unsigned char *font, uint16_t color, uint8_t spacing, uint8_t drawBackground) {
	unsigned short pos;
	unsigned char width;

	// Read first byte, should be 0x01 for proportional
	if (font[FONT_HEADER_TYPE] != FONT_TYPE_PROPORTIONAL) return 0;

	// Check second byte, should be 0x02 for "vertical ceiling"
	if (font[FONT_HEADER_ORIENTATION] != FONT_ORIENTATION_VERTICAL_CEILING) return 0;

	// Check that font start + number of bitmaps contains c
	if (!(c >= font[FONT_HEADER_START] && c <= font[FONT_HEADER_START] + font[FONT_HEADER_LETTERS])) return 0;

	// Adjust for start position of font vs. the char passed
	c -= font[FONT_HEADER_START];

	// Work out where in the array the character is
	pos = font[c * FONT_HEADER_START + 5];
	pos <<= 8;
	pos |= font[c * FONT_HEADER_START + 6];

	// Read first byte from this position, this gives letter width
	width = font[pos];

	// Draw left to right
	unsigned char i;
	for (i = 0; i < width; i++) {

		// Draw top to bottom
		for (unsigned char j = 0; j < font[FONT_HEADER_HEIGHT]; j++) {
			// Increment one data byte every 8 bits, or
			// at the start of a new column  HiTech optimizes
			// the modulo, so no need to try and avoid it.
			if (j % 8 == 0) pos++;

			if (font[pos] & 1 << (j % 8)) {
				ILI9341_Draw_Pixel(x + i, y + j, color);
			}
            else if (drawBackground){
                    ILI9341_Draw_Pixel(x + i, y + j,
                    ILI9341_ReadPixelFromBgArray(x + i, y + j));
            }
		}
	}

    if (drawBackground) {
        uint8_t fontHeight = font[4] * 1.2;
        x+=width;

        for (uint8_t i = 0; i < spacing; i ++) {

            for (uint8_t j = 0; j < fontHeight; j++){
                ILI9341_Draw_Pixel(x + i, y + j,
                ILI9341_ReadPixelFromBgArray(x + i, y + j));
            }
        }
    }

    return width + spacing;
}


void drawBitmap(uint16_t x, uint16_t y, uint16_t w, uint16_t h,
                const unsigned char * bmp, uint16_t color){

    uint8_t tmpbyte = 0;      // Aktuális tömbelem átmeneti tárolója
    signed char n;  //Az éppen vizsgálandó bit helyiértéke
    uint16_t sor = x;
    uint16_t oszlop = y;
    unsigned int elemek = (w / 8)* (h);     // Az olvasott tömb elemeinek száma
    unsigned int olvasd;

    for(olvasd = 0; olvasd < elemek; olvasd++)
    {
        // Kiírja a soron következő tömb elemét
        tmpbyte = bmp[olvasd];
        for (n=7; n >= 0; n--)
        {
            if (sor == (w + x))
            {
                oszlop++;
                sor = x;
            }
            if ( tmpbyte & (1 << n)) ILI9341_Draw_Pixel(sor, oszlop, color);
            sor++;
        }
    }
}

/*Draw hollow circle at X,Y location with specified radius and colour. X and Y represent circles center */
void ILI9341_Draw_Hollow_Circle(uint16_t X, uint16_t Y, uint16_t Radius, uint16_t Colour)
{
	int x = Radius-1;
    int y = 0;
    int dx = 1;
    int dy = 1;
    int err = dx - (Radius << 1);

    while (x >= y)
    {
        ILI9341_Draw_Pixel(X + x, Y + y, Colour);
        ILI9341_Draw_Pixel(X + y, Y + x, Colour);
        ILI9341_Draw_Pixel(X - y, Y + x, Colour);
        ILI9341_Draw_Pixel(X - x, Y + y, Colour);
        ILI9341_Draw_Pixel(X - x, Y - y, Colour);
        ILI9341_Draw_Pixel(X - y, Y - x, Colour);
        ILI9341_Draw_Pixel(X + y, Y - x, Colour);
        ILI9341_Draw_Pixel(X + x, Y - y, Colour);

        if (err <= 0)
        {
            y++;
            err += dy;
            dy += 2;
        }
        if (err > 0)
        {
            x--;
            dx += 2;
            err += (-Radius << 1) + dx;
        }
    }
}

/*Draw filled circle at X,Y location with specified radius and colour. X and Y represent circles center */
void ILI9341_Draw_Filled_Circle(uint16_t X, uint16_t Y, uint16_t Radius, uint16_t Colour)
{

		int x = Radius;
    int y = 0;
    int xChange = 1 - (Radius << 1);
    int yChange = 0;
    int radiusError = 0;

    while (x >= y)
    {
        for (int i = X - x; i <= X + x; i++)
        {
            ILI9341_Draw_Pixel(i, Y + y,Colour);
            ILI9341_Draw_Pixel(i, Y - y,Colour);
        }
        for (int i = X - y; i <= X + y; i++)
        {
            ILI9341_Draw_Pixel(i, Y + x,Colour);
            ILI9341_Draw_Pixel(i, Y - x,Colour);
        }

        y++;
        radiusError += yChange;
        yChange += 2;
        if (((radiusError << 1) + xChange) > 0)
        {
            x--;
            radiusError += xChange;
            xChange += 2;
        }
    }
		//Really slow implementation, will require future overhaul
		//TODO:	https://stackoverflow.com/questions/1201200/fast-algorithm-for-drawing-filled-circles
}

/*Draw a hollow rectangle between positions X0,Y0 and X1,Y1 with specified colour*/
void ILI9341_Draw_Hollow_Rectangle_Coord(uint16_t X0, uint16_t Y0, uint16_t X1, uint16_t Y1, uint16_t Colour)
{
	uint16_t 	X_length = 0;
	uint16_t 	Y_length = 0;
	uint8_t		Negative_X = 0;
	uint8_t 	Negative_Y = 0;
	float 		Calc_Negative = 0;

	Calc_Negative = X1 - X0;
	if(Calc_Negative < 0) Negative_X = 1;
	Calc_Negative = 0;

	Calc_Negative = Y1 - Y0;
	if(Calc_Negative < 0) Negative_Y = 1;


	//DRAW HORIZONTAL!
	if(!Negative_X)
	{
		X_length = X1 - X0;
	}
	else
	{
		X_length = X0 - X1;
	}
	ILI9341_Draw_Horizontal_Line(X0, Y0, X_length, Colour);
	ILI9341_Draw_Horizontal_Line(X0, Y1, X_length, Colour);



	//DRAW VERTICAL!
	if(!Negative_Y)
	{
		Y_length = Y1 - Y0;
	}
	else
	{
		Y_length = Y0 - Y1;
	}
	ILI9341_Draw_Vertical_Line(X0, Y0, Y_length, Colour);
	ILI9341_Draw_Vertical_Line(X1, Y0, Y_length, Colour);

	if((X_length > 0)||(Y_length > 0))
	{
		ILI9341_Draw_Pixel(X1, Y1, Colour);
	}

}

/*Draw a filled rectangle between positions X0,Y0 and X1,Y1 with specified colour*/
void ILI9341_Draw_Filled_Rectangle_Coord(uint16_t X0, uint16_t Y0, uint16_t X1, uint16_t Y1, uint16_t Colour)
{
	uint16_t 	X_length = 0;
	uint16_t 	Y_length = 0;
	uint8_t		Negative_X = 0;
	uint8_t 	Negative_Y = 0;
	int32_t 	Calc_Negative = 0;

	uint16_t X0_true = 0;
	uint16_t Y0_true = 0;

	Calc_Negative = X1 - X0;
	if(Calc_Negative < 0) Negative_X = 1;
	Calc_Negative = 0;

	Calc_Negative = Y1 - Y0;
	if(Calc_Negative < 0) Negative_Y = 1;


	//DRAW HORIZONTAL!
	if(!Negative_X)
	{
		X_length = X1 - X0;
		X0_true = X0;
	}
	else
	{
		X_length = X0 - X1;
		X0_true = X1;
	}

	//DRAW VERTICAL!
	if(!Negative_Y)
	{
		Y_length = Y1 - Y0;
		Y0_true = Y0;
	}
	else
	{
		Y_length = Y0 - Y1;
		Y0_true = Y1;
	}

	ILI9341_Draw_Rectangle(X0_true, Y0_true, X_length, Y_length, Colour);
}

uint16_t ILI9341_ReadPixelFromBgArray(uint16_t x, uint16_t y) {
    uint32_t pos;

    if (x >= 320 && y >= 240) return 0;
    pos = (x * 2) + (y * 640);

    return (bg[pos] << 8) | bg[pos + 1];
}

void redrawBgArea(uint16_t x, uint16_t y, uint16_t w, uint16_t h){

    signed char n;  //Az éppen vizsgálandó bit helyiértéke
    uint16_t sor = x;
    uint16_t oszlop = y;
    uint32_t elemek = (w / 8)* (h);     // Az olvasott tömb elemeinek száma
    uint32_t olvasd;

    for(olvasd = 0; olvasd < elemek; olvasd++)
    {
        for (n=7; n >= 0; n--)
        {
            if (sor == (w + x))
            {
                oszlop++;
                sor = x;
            }
            ILI9341_Draw_Pixel(sor, oszlop,
                               ILI9341_ReadPixelFromBgArray(sor, oszlop));
            sor++;
        }
    }
}


void ILI9341_drawBackground(void) {

    ILI9341_Draw_Image(bg, SCREEN_HORIZONTAL_2);
}

void drawStartLogo(void) {

    drawBitmap(32, 70 , 256, 64, logo, WHITE);
}

void ILI9341_Line(int X1, int Y1,int X2,int Y2, uint16_t color)
{
int CurrentX, CurrentY, Xinc, Yinc,
    Dx, Dy, TwoDx, TwoDy,
	TwoDxAccumulatedError, TwoDyAccumulatedError;

Dx = (X2-X1); // obliczenie sk³adowej poziomej
Dy = (Y2-Y1); // obliczenie sk³adowej pionowej

TwoDx = Dx + Dx; // podwojona sk³adowa pozioma
TwoDy = Dy + Dy; // podwojona sk³adowa pionowa

CurrentX = X1; // zaczynamy od X1
CurrentY = Y1; // oraz Y1

Xinc = 1; // ustalamy krok zwiêkszania pozycji w poziomie
Yinc = 1; // ustalamy krok zwiêkszania pozycji w pionie

if(Dx < 0) // jesli sk³adowa pozioma jest ujemna
  {
  Xinc = -1; // to bêdziemy siê "cofaæ" (krok ujemny)
  Dx = -Dx;  // zmieniamy znak sk³adowej na dodatni
  TwoDx = -TwoDx; // jak równie¿ podwojonej sk³adowej
  }

if (Dy < 0) // jeœli sk³adowa pionowa jest ujemna
  {
  Yinc = -1; // to bêdziemy siê "cofaæ" (krok ujemny)
  Dy = -Dy; // zmieniamy znak sk³adowej na dodatki
  TwoDy = -TwoDy; // jak równiez podwojonej sk³adowej
  }

ILI9341_Draw_Pixel(X1,Y1, color); // stawiamy pierwszy krok (zapalamy pierwszy piksel)

if ((Dx != 0) || (Dy != 0)) // sprawdzamy czy linia sk³ada siê z wiêcej ni¿ jednego punktu ;)
  {
  // sprawdzamy czy sk³adowa pionowa jest mniejsza lub równa sk³adowej poziomej
  if (Dy <= Dx) // jeœli tak, to idziemy "po iksach"
    {
    TwoDxAccumulatedError = 0; // zerujemy zmienn¹
    do // ruszamy w drogê
	  {
      CurrentX += Xinc; // do aktualnej pozycji dodajemy krok
      TwoDxAccumulatedError += TwoDy; // a tu dodajemy podwojon¹ sk³adow¹ pionow¹
      if(TwoDxAccumulatedError > Dx)  // jeœli TwoDxAccumulatedError jest wiêkszy od Dx
        {
        CurrentY += Yinc; // zwiêkszamy aktualn¹ pozycjê w pionie
        TwoDxAccumulatedError -= TwoDx; // i odejmujemy TwoDx
        }
       ILI9341_Draw_Pixel(CurrentX,CurrentY, color);// stawiamy nastêpny krok (zapalamy piksel)
       }while (CurrentX != X2); // idziemy tak d³ugo, a¿ osi¹gniemy punkt docelowy
     }
   else // w przeciwnym razie idziemy "po igrekach"
      {
      TwoDyAccumulatedError = 0;
      do
	    {
        CurrentY += Yinc;
        TwoDyAccumulatedError += TwoDx;
        if(TwoDyAccumulatedError>Dy)
          {
          CurrentX += Xinc;
          TwoDyAccumulatedError -= TwoDy;
          }
         ILI9341_Draw_Pixel(CurrentX,CurrentY, color);
         }while (CurrentY != Y2);
    }
  }
}
