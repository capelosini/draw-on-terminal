#include <sys/ioctl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

struct Draw{
    int width;
    int height;
    char pixelChar;
    char backgroundChar;
    char animation;
    char *canva;
};

typedef struct Draw Draw;

Draw* drawInit(){
    Draw* draw = malloc(sizeof(Draw));
    struct winsize size;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
    draw->width = size.ws_col;
    draw->height = size.ws_row;
    draw->canva = malloc(sizeof(char)*draw->width*draw->height);
    draw->pixelChar = '#';
    draw->backgroundChar = ' ';
    draw->animation = 0;
    return draw;
}

void setPixel(Draw* draw, int x, int y){
    if( (x < draw->width && x >= 0) || (y < draw->height && y >= 0) )
        draw->canva[x + y*draw->width] = 1;
}

void clearCanva(Draw* draw){
    for(int i = 0; i < draw->width*draw->height; i++)
       draw->canva[i] = 0;
    //free(draw->canva);
    //draw->canva = malloc(sizeof(char)*draw->width*draw->height);
}

void render(Draw* draw){
    if (draw->animation == 1)
        clearCanva(draw);
    for(int y = 0; y < draw->height; y++){
        for(int x = 0; x < draw->width; x++){
            if(draw->canva[x + y*draw->width] == 1)
                printf("%c", draw->pixelChar);
            else
                printf("%c", draw->backgroundChar);
        }
        if (y != draw->height-1)
            printf("\n");
    }
}

void square(Draw* draw, int x, int y, int size){
    for(int i = 0; i < size; i++){
        setPixel(draw, x, y+i);
    }
    for(int i = 0; i < size*1.5; i++){
        setPixel(draw, x+i, y);
    }
    x=x+(size*1.5);
    y=y+(size-1);
    for(int i = 0; i < size; i++){
        setPixel(draw, x, y-i);
    }
    for(int i = 0; i < size*1.5; i++){
        setPixel(draw, x-i, y);
    }
}
