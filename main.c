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
unsigned char rgba[width * width * 4], *p = rgba;
void generateImage(const char *fileName)
{
    FILE *fp = fopen(fileName, "wb");
    svpng(fp, width, height, rgba, 1);
    fclose(fp);
}
void drawDot(int x, int y, Color color)
{
    int index = (x * width + y) * 4;
    rgba[index] = color.r;
    rgba[index + 1] = color.g;
    rgba[index + 2] = color.b;
    rgba[index + 3] = color.a;
}
void drawLine(int x0, int y0, int x1, int y1, Color color)
{
    float k = (y1 - y0) / (float)(x1 - x0);
    float b = y0 * 1.0 - k * x0;
    int y;
    for (int x = x0; x < x1; x++)
    {
        y = k * x + b;
        drawDot(x, y, color);
    }
}
void outPutImage(const char *fileName, Color background)
{

    unsigned x, y;
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
    // drawDot(0,0,RED);
    // drawDot(100,100,RED);
    drawLine(0, 0, 100, 200, BLUE);
    drawLine(0, 0, 100, 100, RED);
    drawLine(0, 0, 100, 50, WHITE);
    generateImage(fileName);
}

int main(void)
{
    const char *output = "output.png";
    outPutImage(output, BlACK);
    return 0;
}
