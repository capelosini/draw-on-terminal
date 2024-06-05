int nanosleep(const struct timespec *rqtp, struct timespec *rmtp);

struct Draw;
typedef struct Draw Draw;
Draw* drawInit();
void drawDestroy(Draw* draw);
void setPixel(Draw* draw, int x, int y);
char getPixel(Draw* draw, int x, int y);
void clearPixel(Draw* draw, int x, int y);
void clearCanva(Draw* draw);
long calculateFPS(Draw* draw);
void render(Draw* draw);
void square(Draw* draw, int x, int y, int size);
void circle(Draw* draw, int x, int y, int r);
void line(Draw* draw, int x1, int y1, int x2, int y2);
void point(Draw* draw, int x, int y);

struct Draw{
    int width;
    int height;
    char strokeChar;
    char backgroundChar;
    char animation;
    char *canva;
    float xScale; // This's a number to make the size of drawn object almost the same in coords x and y, because letters has a larger y than x
    unsigned char fps;
};