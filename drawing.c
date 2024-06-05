#include <sys/ioctl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include "drawing.h"

Draw* drawInit(){
    Draw* draw = (Draw*)malloc(sizeof(Draw));
    struct winsize size;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
    draw->width = size.ws_col;
    draw->height = size.ws_row;
    draw->canva = (char*)malloc(sizeof(char)*draw->width*draw->height);
    draw->strokeChar = '#';
    draw->backgroundChar = ' ';
    draw->animation = 0;
    draw->xScale = 1.5;
    draw->fps = 24;
    return draw;
}

void drawDestroy(Draw* draw){
    free(draw->canva);
    free(draw);
}

void setPixel(Draw* draw, int x, int y){
    if( (x < draw->width && x >= 0) || (y < draw->height && y >= 0) )
        draw->canva[x + y*draw->width] = 1;
}

char getPixel(Draw* draw, int x, int y){
    if( (x < draw->width && x >= 0) || (y < draw->height && y >= 0) )
        return draw->canva[x + y*draw->width];
    else{
        return 0;
    }
}

void clearPixel(Draw* draw, int x, int y){
    if( (x < draw->width && x >= 0) || (y < draw->height && y >= 0) )
        draw->canva[x + y*draw->width] = 0;
}

void clearCanva(Draw* draw){
    for(int i = 0; i < draw->width*draw->height; i++)
       draw->canva[i] = 0;
    //free(draw->canva);
    //draw->canva = malloc(sizeof(char)*draw->width*draw->height);
}

long calculateFPS(Draw* draw){
    // Calculate the sleep value in nanoseconds based in the fps value
    return 1000000000/draw->fps;
}

void render(Draw* draw){
    for(int y = 0; y < draw->height; y++){
        for(int x = 0; x < draw->width; x++){
            if(draw->canva[x + y*draw->width] == 1)
                printf("%c", draw->strokeChar);
            else
                printf("%c", draw->backgroundChar);
        }
        if (y != draw->height-1)
            printf("\n");
    }
    if (draw->animation)
        clearCanva(draw);
        long s = calculateFPS(draw);
        struct timespec* value;
        if (s > 999999999){
            value = &(struct timespec){1,0};
        } else{
            value = &(struct timespec){0,s};
        }
        nanosleep(value, NULL);
}

void square(Draw* draw, int x, int y, int size){
    for(int i = 0; i < size; i++){
        setPixel(draw, x, y+i);
    }
    for(int i = 0; i < size*draw->xScale; i++){
        setPixel(draw, x+i, y);
    }
    x=x+(size*draw->xScale);
    y=y+(size-1);
    for(int i = 0; i < size; i++){
        setPixel(draw, x, y-i);
    }
    for(int i = 0; i < size*draw->xScale; i++){
        setPixel(draw, x-i, y);
    }
}

void circle(Draw* draw, int x, int y, int r){
    for(int ang=0; ang<45; ang++){
        setPixel(draw, x+(r*draw->xScale)*cos(ang), y+r*sin(ang));
    }
}

void line(Draw* draw, int x1, int y1, int x2, int y2){
    int dx = abs(x2-x1);
    int dy = abs(y2-y1);
    int sx = x1<x2 ? 1 : -1;
    int sy = y1<y2 ? 1 : -1;
    int err = dx-dy;
    while(1){
        setPixel(draw, x1, y1);
        if (x1==x2 && y1==y2) break;
        int e2 = 2*err;
        if (e2 > -dy){ err -= dy; x1 += sx; }
        if (e2 < dx){ err += dx; y1 += sy; }
    }
}

void point(Draw* draw, int x, int y){
    setPixel(draw, x, y);
}