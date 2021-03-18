#include <stdlib.h>

class pipe {
    public:
        double x;
        int height;
        void drawPipe(int screenHeight){
            DrawRectangle(x,0,100,(screenHeight-height)- 200,GREEN);
            DrawRectangle(x,(screenHeight-height),100,height,GREEN);
    }
};

int resetPipe(int screenHeight){
    //return rand() % 100 + (screenHeight-350);
    return rand() % 100 + 100;
}
