#include "LTimer.h"
#include "LDot.h"
#include "LParticle.h"
#include "LSlider.h"
#include "headers.h"
#include <string>
#include <sstream>

using std::string;

SDL_Renderer* gRenderer = NULL;
SDL_Surface* gScreenSurface = NULL; 
SDL_Surface* gCurrentSurface = NULL; 
SDL_Window* gWindow = NULL;
TTF_Font* gFont = NULL;
LTexture gRedTexture,
         gGreenTexture,
         gBlueTexture,
         gShimmerTexture,
         gDotTexture;

int main(int argc, char* args[])
{
	//Start up SDL and create window
	if(!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		//Load media
		if(!loadMedia())
		{
			printf("Failed to load media!\n");
		}
        else {
            bool quit = false;
            SDL_Event e;
            LSlider slider(70, 25, ((SCREEN_WIDTH / 2) - 150 / 2), ((SCREEN_HEIGHT / 2) - 25 / 2));
            while(!quit)
            {
                SDL_Point mouse;
                SDL_GetMouseState( &mouse.x, &mouse.y );
                //Handle events on queue
                while(SDL_PollEvent(&e) != 0)
                {
                    //User requests quit
                    if(e.type == SDL_QUIT)
                    {
                        quit = true;
                    }
                    //Handle button events
                    slider.handleEvents(&e, mouse);
                }

                if(slider.getMouseFollow()) {
                    slider.handleMotion(mouse);
                }

                //Clear screen
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                SDL_RenderClear( gRenderer );

                slider.renderSlider();
                slider.renderVolume();

                //Update screen
                SDL_RenderPresent( gRenderer );
            }
        }
    }
    //Free resources and close SDL
	close();

	return 0;
}
