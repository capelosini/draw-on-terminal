// This is a test/example of library usage

#include "drawing.h"
#include <math.h>
#include <stdio.h>

int main(){

    Draw* d = drawInit();
    d->animation = 1;
    d->fps = 45;

    for (int i=0; i<=d->height; i++){
        circle(d, d->width/2+i, 3+i, 3);
        render(d);
    }

    drawDestroy(d);

    return 0;
}