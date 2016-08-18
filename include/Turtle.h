#ifndef TURTLE_H
#define TURTLE_H
#include <SDL2/SDL.h>
#include <vector>

class Turtle
{
    public:
        Turtle(int startX, int startY);
        virtual ~Turtle();
        void PenDown();
        void PenUp();
        void Forward(int length);
        void Turn(double radians);
        void SavePoint();
        void ReturnToSavedPoint();
        void GoTo(int destX, int destY);
        void SetCustomSavePoint(int destX, int destY, double destAngle);
        void SetAngle(double destAngle);
        std::vector<double> GetSavedAngle();
        std::vector<double> GetSavedX();
        std::vector<double> GetSavedY();
        void Render();

    protected:
    private:
    SDL_Window* window;
    SDL_Rect screen;
    SDL_Renderer* Main_Renderer;
    SDL_Texture* Tex;

    double x,y,prevX,prevY;
    int r,g,b,a;
    std::vector<double> savedX;
    std::vector<double> savedY;
    std::vector<double> savedAngle;
    double angle;
    bool penDown,savedPoint;
};

#endif // TURTLE_H
