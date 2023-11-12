#include "headers.h"
#include "LTexture.h"

extern SDL_Renderer* gRenderer;
extern SDL_Surface* gScreenSurface; 
extern SDL_Surface* gCurrentSurface; 
extern SDL_Window* gWindow;
extern TTF_Font* gFont;
extern LTexture gDotTexture;
extern LTexture gGreenTexture;
extern LTexture gRedTexture;
extern LTexture gBlueTexture;
extern LTexture gShimmerTexture;

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
		success = false;
        return success;
	}
    //Set texture filtering to linear
    if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
    {
        std::cerr << "Warning: Linear texture filtering not enabled!" << std::endl;
		success = false;
        return success;
    }
    //Create window
    if(!(gWindow = SDL_CreateWindow("LSilder", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0)))
    {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
		success = false;
        return success;
    }
    //Create renderer for window
    if(!(gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC))) {
        std::cerr << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
        success = false;
        return success;
    }
    //Initialize PNG loading
    int imgFlags = IMG_INIT_PNG;
    if(!(IMG_Init(imgFlags) & imgFlags))
    {
        std::cerr << "SDL_image could not initialise! SDL_image Error: " << IMG_GetError() << std::endl;
        success = false;
        return success;
    }
    // initialize SDL_ttf
    if(TTF_Init() == -1) {
        std::cerr << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << std::endl;
        success = false;
        return success;
    }
    else {
        //Open the font
        if(!(gFont = TTF_OpenFont("resources/lazy.ttf", 28))) {
            std::cerr << "Failed to load lazy font! SDL_ttf Error: " << TTF_GetError() << std::endl;
            success = false;
            return success;
        }
    }
    // initialize SDL_mixer
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cerr << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;
        success = false;
        return success;
    }
    return success;
}


SDL_Surface* loadSurface(std::string path)
{
//The final optimized image
SDL_Surface* optimizedSurface = NULL;

//Load image at specified path
SDL_Surface* loadedSurface = IMG_Load(path.c_str());
if(loadedSurface == NULL)
{
    printf("Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
}
else
{
    //Convert surface to screen format
    optimizedSurface = SDL_ConvertSurface(loadedSurface, gScreenSurface->format, 0);
    if(optimizedSurface == NULL)
    {
        printf("Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
    }

    //Get rid of old loaded surface
    SDL_FreeSurface(loadedSurface);
}
	return optimizedSurface;
}

SDL_Texture* loadTexture(std::string path)
{
    //The final texture
    SDL_Texture* newTexture = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if(loadedSurface == NULL)
    {
        printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
    }
    else
    {
        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
        if(newTexture == NULL)
        {
            printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
        }

        //Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
    }

    return newTexture;
}


bool loadMedia() {
    //Loading success flag
    bool success = true;
    if(!(gDotTexture.loadFromFile("resources/dotsmoothed10px.png"))) {
        printf("Unable to load dot.bmp! Error  %s\n", SDL_GetError());
        success = false;
    }
    if(!(gRedTexture.loadFromFile("resources/red.bmp"))) {
        printf("Unable to load red.bmp! Error  %s\n", SDL_GetError());
        success = false;
    }
    if(!(gGreenTexture.loadFromFile("resources/green.bmp"))) {
        printf("Unable to load green.bmp! Error  %s\n", SDL_GetError());
        success = false;
    }
    if(!(gBlueTexture.loadFromFile("resources/blue.bmp"))) {
        printf("Unable to load blue.bmp! Error  %s\n", SDL_GetError());
        success = false;
    }
    if(!(gShimmerTexture.loadFromFile("resources/shimmer.bmp"))) {
        printf("Unable to load shimmer.bmp! Error  %s\n", SDL_GetError());
        success = false;
    }
    //Set texture transparency
    gRedTexture.setAlpha( 192 );
    gGreenTexture.setAlpha( 192 );
    gBlueTexture.setAlpha( 192 );
    gShimmerTexture.setAlpha( 192 );

    return success;
}

void close()
{
	//Destroy window
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
    SDL_DestroyRenderer(gRenderer);
    gRenderer = NULL;
    gRedTexture.free();
    gGreenTexture.free();
    gBlueTexture.free();
    gShimmerTexture.free();
    gDotTexture.free();
    gFont = NULL;
	//Quit SDL subsystems
	SDL_Quit();
    IMG_Quit();
}
