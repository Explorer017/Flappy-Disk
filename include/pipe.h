#include <stdlib.h>
int screenWidth = 854;
int screenHeight = 480;

class pipe {
    public:
        double x;
        int height;
        Rectangle Rec1;
        Rectangle Rec2;
        //pipe(){
        //    Rectangle Rec1 = {x,0,100,(screenHeight-height)- 200};
        //    Rectangle Rec2 = {x,(screenHeight-height),100,height};
       // }
        void drawPipe(int screenHeight){
            Rec1 = {x,0,100,(screenHeight-height)- 200};
            Rec2 = {x,(screenHeight-height),100,height};

            DrawRectangleRec(Rec1,GREEN);
            DrawRectangleRec(Rec2,GREEN);
    }
};

int resetPipe(int screenHeight){
    return rand() % 100 + 100;
}

