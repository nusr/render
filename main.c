#include "svpng.inc"
#include <stdio.h>
typedef struct
{
    int r, g, b, a;
} Color;
const int COLOR_MAX = 255;
const int COLOR_MIN = 0;
const Color WHITE = {COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX};
const Color BlACK = {COLOR_MIN, COLOR_MIN, COLOR_MIN, COLOR_MAX};
const Color BLUE = {COLOR_MIN, COLOR_MIN, COLOR_MAX, COLOR_MAX};
const Color RED = {COLOR_MAX, COLOR_MIN, COLOR_MIN, COLOR_MAX};
const int width = 256;
const int height = 256;
const int BYTE_SIZE = 4;
unsigned char rgba[width * width * BYTE_SIZE], *p = rgba;
const char *FILE_NAME = "output.png";
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
void generateImage()
{
    FILE *fp = fopen(FILE_NAME, "wb");
    svpng(fp, width, height, rgba, 1);
    fclose(fp);
}
void drawDot(int x, int y, Color color)
{

    int index = ((height - y) * width + x + 1) * BYTE_SIZE;
    rgba[index] = color.r;
    rgba[index + 1] = color.g;
    rgba[index + 2] = color.b;
    rgba[index + 3] = color.a;
}
void drawLine(int x0, int y0, int x1, int y1, Color color)
{
    if(x0 == x1){
        if(y0 > y1){
            swap(&y0,&y1);
        }
        for(int y = y0; y < y1;y++){
            drawDot(x0, y, color);
        }
        return;
    }
    if(x0 > x1){
        swap(&x0,&x1);
        swap(&y0,&y1);
    }
    float k = (y1 - y0) / (float)(x1 - x0);
    float b = y0 * 1.0 - k * x0;
    int y;
    for (int x = x0; x < x1; x++)
    {
        y = k * x + b;
        drawDot(x, y, color);
    }
}
void initImage(Color background){
    unsigned x;
    unsigned y;
    for (y = 0; y < width; y++)
    {
        for (x = 0; x < height; x++)
        {
            *p++ = background.r; /* R */
            *p++ = background.g; /* G */
            *p++ = background.b; /* B */
            *p++ = background.a; /* A */
        }
    }
}
void outPutImage(Color background)
{

    initImage(background);
    // drawDot(0,0,RED);
    // drawDot(100,100,RED);
    drawLine(0, 0, 100, 200, BLUE);
    drawLine(0, 0, 100, 100, RED);
    drawLine(0, 0, 100, 50, WHITE);
    drawLine(50, 0, 50, 200, BLUE);
    generateImage();
}

int main(void)
{
    outPutImage(BlACK);
    return 0;
}
