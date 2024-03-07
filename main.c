// This is a test/example of library usage

#include "drawing.h"
#include <math.h>
#include <stdio.h>

int main(){

    Draw* d = drawInit();

    square(d, 3, 3, 3);

    render(d);

    scanf("%d");

    return 0;
}