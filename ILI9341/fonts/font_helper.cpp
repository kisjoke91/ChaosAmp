#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <cstring>
#include <vector>
#include "Tahoma12.h"

using namespace std;
string output;

vector <vector<uint32_t> > characters;

uint16_t getFontStartIndex(uint16_t c) {

    uint16_t pos;

    c -= font[2];
	// Work out where in the array the character is
	pos = font[c * 2 + 5];
	pos <<= 8;
	pos |= font[c * 2 + 6];

    return pos;
}

vector <uint32_t> getCharacter(uint16_t c) {

    vector <uint32_t> ch;
    uint16_t startIndex = getFontStartIndex(c);
    uint8_t columns = font[startIndex];

    startIndex ++;

    for(uint16_t i = 0; i < columns; i ++) {

        uint32_t x;

        x = font[startIndex + (i * 3)];
        x |= (font[startIndex + (i * 3) + 1]) << 8;
        x |= (font[startIndex + (i * 3) + 2]) << 16;

        ch.push_back(x);
    }

    return ch;
}

//assumes little endian
void printBits(size_t const size, void const * const ptr)
{
    unsigned char *b = (unsigned char*) ptr;
    unsigned char byte;
    int i, j;

    for (i=size-1;i>=0;i--)
    {
        for (j=7;j>=0;j--)
        {
            byte = (b[i] >> j) & 1;
            if (byte)
            printf("@");
            else printf(".");
        }
    }
    puts("");
}

int main() {

    for(int it = 32; it < 149; it ++) {
        characters.push_back(getCharacter(it));
    }

    int offset = 239;

    for(int i = 0; i < characters.size(); i ++) {

        printf("    0x%.2X, 0x%.2X, // Index %d (offset: %d)\n", offset >> 8, offset & 0xFF,i, offset);

        offset += characters[i].size() * 3;
        offset ++;
    }

    printf("\n");

    for(int i = 0; i < characters.size(); i ++) {

        vector <uint32_t> ch = characters[i];

        printf("    /* Index %d, character %d \"%c\" (width: %d pixels) */\n",
                i, i + 32, i + 32, (int)ch.size());

        printf("    0x%.2X, ", (int)ch.size());

        for(int it = 0; it < ch.size(); it ++) {

            uint8_t top, center, bottom;

            top = ch[it] & 0xFF;
            center = (ch[it] >> 8) & 0xFF;
            bottom = (ch[it] >> 16) & 0xFF;
            printf("0x%.2X,0x%.2X,0x%.2X,",top, center, bottom);
        }
        printf("\n\n");
    }


    for(int i = 0; i < characters.size(); i ++) {

        vector <uint32_t> ch = characters[i];

        for(int it = 0; it < ch.size(); it ++) {

            printBits(sizeof(ch[it]), &ch[it]);
        }
        printf("\n\n");
    }

    printf("\n\n\n");


    return 0;
}
