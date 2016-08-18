#include "Turtle.h"
#include <math.h>
Turtle::Turtle(int startX , int startY)
{
    //ctor
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_GetDisplayBounds(0, &screen);
    window = SDL_CreateWindow("Turtle window",0,0,screen.w,screen.h,SDL_WINDOW_BORDERLESS);
    Main_Renderer = SDL_CreateRenderer(window,0,SDL_RENDERER_ACCELERATED|SDL_RENDERER_TARGETTEXTURE);
    Tex = SDL_CreateTexture(Main_Renderer,SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_TARGET,screen.w,screen.h);
    SDL_SetRenderTarget(Main_Renderer,Tex);
    SDL_SetRenderDrawColor(Main_Renderer,255,255,255,255);
    SDL_RenderClear(Main_Renderer);
    SDL_SetRenderDrawColor(Main_Renderer,0,0,0,255);

    x = startX;
    y = startY;
    prevX = x;
    prevY = x;
    penDown = false;
    savedPoint = false;
    angle = 0;
    r = 0;
    g = 0;
    b = 0;
    a = 10;

}

Turtle::~Turtle()
{
    //dtor
    SDL_DestroyTexture(Tex);
    SDL_DestroyRenderer(Main_Renderer);
    SDL_DestroyWindow(window);
}

void Turtle::PenDown(){
    penDown = true;
}
void Turtle::PenUp(){
    penDown = false;
}

void Turtle::Forward(int length){
    prevX = x;
    prevY = y;
    x += cos(angle) * length;
    y += sin(angle) * length;
    if(penDown){
        SDL_RenderDrawLine(Main_Renderer,round(prevX),round(prevY),round(x),round(y));
    }
}

void Turtle::Turn(double radians){
    angle += radians;
    angle = remainder(angle, 2*M_PI);
    if(angle < 0){
        angle += 2 * M_PI;
    }
}

void Turtle::SavePoint(){
    savedX.push_back(x);
    savedY.push_back(y);
    savedAngle.push_back(angle);
}

void Turtle::SetCustomSavePoint(int destX, int destY, double destAngle){
    savedAngle.push_back(destAngle);
    savedX.push_back(destX);
    savedY.push_back(destY);
}

void Turtle::ReturnToSavedPoint(){

    if(savedX.size() > 0){
        prevX = x;
        prevY = y;
        x = savedX.back();
        y = savedY.back();
        angle = savedAngle.back();
        savedAngle.erase(savedAngle.begin() + savedAngle.size() - 1);
        savedX.erase(savedX.begin() + savedX.size() - 1);
        savedY.erase(savedY.begin() + savedY.size() - 1);
//        savedY.pop_back();
//        savedX.pop_back();


    }
}

void Turtle::GoTo(int destX, int destY){
    prevX = x;
    prevY = y;
    x = destX;
    y = destY;
}

void Turtle::SetAngle(double destAngle){
    angle = destAngle;
}

std::vector<double> Turtle::GetSavedX(){
    return savedX;
}
std::vector<double> Turtle::GetSavedY(){
    return savedY;
}
std::vector<double> Turtle::GetSavedAngle(){
    return savedAngle;
}



void Turtle::Render(){
//    r += 1;if(r > 255)r = 15;
//    g += 1;if(g > 255)g = 15;
//    b += 1;if(b > 255)b = 15;
    SDL_SetRenderTarget(Main_Renderer,NULL);
    SDL_SetRenderDrawColor(Main_Renderer,255,255,255,255);
    SDL_RenderClear(Main_Renderer);
    SDL_SetRenderDrawColor(Main_Renderer,r,g,b,100);
    SDL_RenderCopyEx(Main_Renderer,Tex,NULL,NULL,0,NULL,SDL_FLIP_VERTICAL);
    SDL_RenderPresent(Main_Renderer);
    SDL_SetRenderTarget(Main_Renderer,Tex);
}
