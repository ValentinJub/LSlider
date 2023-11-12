#ifndef LPARTICLE_H
#define LPARTICLE_H

#include "headers.h"
#include "LTexture.h"

//Particle count
const int TOTAL_PARTICLES = 20;

class LParticle
{
    public:
        //Initialize position and animation
        LParticle( int x, int y );

        //Shows the particle
        void render();

        //Checks if particle is dead
        bool isDead();

    private:
        //Offsets
        int mPosX, mPosY;

        //Current frame of animation
        int mFrame;

        //Type of particle
        LTexture *mTexture;
};

#endif
