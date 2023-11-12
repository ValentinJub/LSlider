#include "headers.h"

#ifndef LTEXTURE_H
#define LTEXTURE_H

using std::string;

class LTexture {
    public:
    LTexture(int x = 0, int y = 0);
    ~LTexture();
    #if defined(SDL_TTF_MAJOR_VERSION)
    ////Creates image from font string
    bool loadFromRenderedText( std::string textureText, SDL_Color textColor );
    #endif 
    //Render at given pos, clip, rotate flip
    void render( int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );
    //Load IMG from file
    bool loadFromFile(std::string path);
    //Destroy texture 
    void free();
    //Set color modulation
    void setColor(Uint8 red, Uint8 green, Uint8 blue);
    //Set blending
    void setBlendMode(SDL_BlendMode blending);
    //Set Alpha 
    void setAlpha(Uint8 alpha);
    //Move texture up
    void moveUp(); 
    void moveDown(); 
    void moveLeft(); 
    void moveRight(); 
    int x(); 
    int y(); 

    //Gets image dimensions
    int getWidth();
    int getHeight();

    private:
    SDL_Texture* mTexture;
    int mWidth;
    int mHeight;
    int mX;
    int mY;
};

#endif