/*
LSlider.h
by Valentin
--------------
Prototypes and const for LSlider class


This class is used to create a slider that can be moved horizontally.
The slider is a rectangle with a width and a height containing a bar and a dot button that can be moved horizontally.
The slider is used to change the volume of the music and the sound effects.

*/
#ifndef LSLIDER_H
#define LSLIDER_H

#include "headers.h"
#include "LTexture.h"
#include "LDot.h"


//The mouse button
class LSlider
{
    public:
        LSlider(int width = 0, int height = 0, int posX = 0, int posY = 0);
        // sets the slider position (horizontal bar, starting from top left corner)
        void setSliderPosition( int x, int y );
        // sets the slider width and height
        void setSliderWidthAndHeight(int width, int height);

        // sets the dot position 
        void setDotPosition();

        // handles mouse events
        bool handleEvents ( SDL_Event* e, SDL_Point mouse );

        void handleMotion( SDL_Point mouse );
    
        //Shows button sprite
        void renderSlider();
        
        // gets the slider x position
        int getX() const;
        // gets the slider y position
        int getY() const;
        // gets the slider width
        int getW() const;
        // gets the slider height
        int getH() const;

        int getVolume() const;
        void renderVolume();

        bool getMouseFollow() const;

    private:
        void setMouseFollow(bool follow);
        bool mMouseFollow;
        LDot* mDot;
        //Top left position
        SDL_Point mSliderPosition;
        LTexture* mVolumeTexture;
        // slider width and height
        int mSliderWidth,
            mSliderHeight;
        

};

#endif
