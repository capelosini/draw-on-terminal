#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "drawing.h"


int main(int argc, char* argv[]){
    Draw* d = drawInit();
    srand(time(NULL));

    if (argc != 2){
        printf("Usage: %s <int POPULATION>\n", argv[0]);
        return 1;
    }

    for (int i = 0; i < atoi(argv[1]); i++){
        setPixel(d, rand()%d->width, rand()%d->height);
    }
    render(d);
    sleep(2);

    while (1){
        //sleep(1);
        Draw* tempDraw = drawInit();
        for (int y=0; y<d->height; y++){
            for (int x=0; x<d->width; x++){
                int n = 0;
                char alive = getPixel(d, x, y);
                for(int i=-1; i<=1; i++){
                    for(int j=-1; j<=1; j++){
                        if (j==0 && i==0) continue;
                        if (getPixel(d, x+j, y+i)) n++;
                    }
                }
                //n-=alive;
                //printf("%d\n", n);
                if (!alive && n == 3) setPixel(tempDraw, x, y);
                //else if (alive && n > 3) clearPixel(d, x, y);
                else if (alive && (n == 2 || n == 3)) setPixel(tempDraw, x, y);
                else clearPixel(tempDraw, x, y);
            }
        }
        render(tempDraw);
        free(d->canva);
        d->canva = tempDraw->canva;
        //free(tempDraw);
    }

    drawDestroy(d);

    return 0;
}