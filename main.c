// This is a test/example of library usage

#include "drawing.h"
#include <math.h>
#include <stdio.h>

int main(){

    Draw* d = drawInit();
    d->animation = 0;
    //d->fps = 45;

    line(d, d->width/2, d->height/2, 0, 0);
    line(d, d->width/2, d->height/2, d->width, 0);
    render(d);

    drawDestroy(d);

    return 0;
}