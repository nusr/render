#include "svpng.inc"
#include <stdio.h>
#include <stdlib.h>
#include "geometry.h"

const Color WHITE = {COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX};
const Color BlACK = {COLOR_MIN, COLOR_MIN, COLOR_MIN, COLOR_MAX};
const Color BLUE = {COLOR_MIN, COLOR_MIN, COLOR_MAX, COLOR_MAX};
const Color RED = {COLOR_MAX, COLOR_MIN, COLOR_MIN, COLOR_MAX};
const int IMAGE_WIDTH = 256;
const int IMAGE_HEIGHT = 256;
const int BYTE_SIZE = 4;
unsigned char rgba[IMAGE_WIDTH * IMAGE_HEIGHT * BYTE_SIZE], *p = rgba;
const char *FILE_NAME = "output.png";
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
void readModel(const char * fileName){
    FILE *fp = fopen(FILE_NAME, "r");
    char buff[2000];
    fgets(buff, 255, fp);
    printf("%s\n", buff);
    fclose(fp);
}
void generateImage()
{
    FILE *fp = fopen(FILE_NAME, "wb");
    svpng(fp, IMAGE_WIDTH, IMAGE_HEIGHT, rgba, 1);
    fclose(fp);
}
void drawDot(int x, int y, Color color)
{

    int index = ((IMAGE_HEIGHT - y - 1) * IMAGE_WIDTH + x + 1) * BYTE_SIZE;
    rgba[index] = color.r;
    rgba[index + 1] = color.g;
    rgba[index + 2] = color.b;
    rgba[index + 3] = color.a;
}
void drawLine2(int x0, int y0, int x1, int y1, Color color) {
    int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
    int dy = abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
    int err = (dx > dy ? dx : -dy) / 2;

    while (drawDot(x0, y0, color), x0 != x1 || y0 != y1) {
        int e2 = err;
        if (e2 > -dx) { err -= dy; x0 += sx; }
        if (e2 <  dy) { err += dx; y0 += sy; }
    }
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
    for (y = 0; y < IMAGE_WIDTH; y++)
    {
        for (x = 0; x < IMAGE_HEIGHT; x++)
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
    drawLine2(0, 0, 100, 200, BLUE);
    drawLine2(0, 0, 100, 100, RED);
    drawLine2(0, 0, 100, 50, WHITE);
    drawLine2(50, 0, 50, 200, BLUE);
    generateImage();
}

int main(void)
{
    outPutImage(BlACK);
    // readModel("./obj/african_head.obj");
    return 0;
}
