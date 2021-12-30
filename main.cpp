#include "C:\Users\globi\Desktop\TX\TXlib.h"

struct SpaceShip{
    double x, y;
    double speed_x, speed_y;
    double ax, ay;
    double m;
};

void move(SpaceShip* Ship, double dt);
int control(SpaceShip* Ship);
void draw(const SpaceShip* Ship, HDC picture);
double vec_lenth(double x, double y);

int main() {
    SpaceShip Ship = {100, 100, 5.7, 1, 2, 3, 1};
    double dt = 0.2;
    const double critical_y = 540;
    txCreateWindow(800, 600);
    txBegin();
    HDC picture = txLoadImage("Spaceship.bmp");
    if (picture == NULL) txMessageBox("Spaceship.bmp can not be loaded");

    HDC space_picture = txLoadImage("SpacePicture.bmp");
    if (space_picture == NULL) txMessageBox("SpacePicture.bmp can not be loaded");


    while(1) {

        move(&Ship, dt);
        if(control(&Ship) == 1) break;

        //printf("x = %d, y = %d, r = %d\n", x, y, r);
        printf("Speed = %lg\n", vec_lenth(Ship.speed_x, Ship.speed_y));

        if (Ship.y > critical_y){
            if (vec_lenth(Ship.speed_x, Ship.speed_y) > 50)
                txMessageBox("You lost");
            else txMessageBox("You won");

            Ship.x = 100;
            Ship.y = 100;
        }
        txBitBlt(0, 0, space_picture);
        draw(&Ship, picture);

        txSleep(20);

    }
    _getch();
    txDeleteDC(picture);
    txDeleteDC(space_picture);
    return 0;
}

void move(SpaceShip* Ship, double dt){

    Ship -> speed_x += Ship -> ax * dt;
    Ship -> speed_y += Ship -> ay * dt;

    Ship -> x += Ship -> speed_x * dt;
    Ship -> y += Ship -> speed_y * dt;

    if (Ship -> x >= 800) {
        Ship -> speed_x *= -1;
        Ship -> x = 800 - (Ship -> x - 800);
    }

    if (Ship -> x <= 0) {
        Ship -> speed_x *= -1;
        Ship -> x *= -1;
    }

    if (Ship -> y >= 600) {
        Ship -> speed_y *= -1;
        Ship -> y = 600 - (Ship -> y - 600);
    }

    if (Ship -> y <= 0) {
        Ship -> speed_y *= -1;
        Ship -> y *= -1;
    }
}

int control(SpaceShip* Ship){

    double force = 5;

    if (GetAsyncKeyState(VK_SHIFT)) force = 10;
    else                            force = 5;

    if (GetAsyncKeyState(VK_RIGHT)) Ship -> speed_x += force;
    if (GetAsyncKeyState(VK_LEFT)) Ship -> speed_x -= force;
    if (GetAsyncKeyState(VK_UP)) Ship -> speed_y -= force;
    if (GetAsyncKeyState(VK_DOWN)) Ship -> speed_y += force;

    if (GetAsyncKeyState(VK_F1)) Ship -> speed_x = Ship -> speed_y = Ship -> ax = Ship -> ay = 0;

    if (GetAsyncKeyState(VK_ESCAPE)) return 1;
    else                             return 0;
}

void draw(const SpaceShip* Ship, HDC picture){
    /*txSetColor(TX_LIGHTRED);
    txSetFillColor(TX_RED);
    txCircle(x, y, r);*/
    txTransparentBlt(Ship -> x, Ship -> y, picture, RGB(255, 0, 255));
}

double vec_lenth(double x, double y){
    return sqrt(x * x + y * y);
}
