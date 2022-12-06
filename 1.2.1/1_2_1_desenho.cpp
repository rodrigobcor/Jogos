#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include <cmath>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

bool init();
bool loadMedia();
void close();

SDL_Texture* loadTexture( std::string path );
SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
bool init()
{
	bool success = true;

	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
			}
		}
	}

	return success;
}

bool loadMedia()
{
	bool success = true;
	return success;
}

void close()
{
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	IMG_Quit();
	SDL_Quit();
}

SDL_Texture* loadTexture( std::string path )
{
	SDL_Texture* newTexture = NULL;

	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
		if( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}

		SDL_FreeSurface( loadedSurface );
	}

	return newTexture;
}

int main( int argc, char* args[] )
{
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		if( !loadMedia() )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{
			bool quit = false;

			SDL_Event e;

			while( !quit )
			{
				while( SDL_PollEvent( &e ) != 0 )
				{
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}
				}

				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );

				//retangulos
				SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0x00 );
                SDL_Rect outlineRect1 = { SCREEN_WIDTH / 8, SCREEN_HEIGHT / 6, SCREEN_WIDTH / 8, SCREEN_HEIGHT / 6 };
				SDL_RenderDrawRect( gRenderer, &outlineRect1 );
				SDL_Rect outlineRect2 = { SCREEN_WIDTH / 8 * 6, SCREEN_HEIGHT / 6, SCREEN_WIDTH / 8, SCREEN_HEIGHT / 6 };
				SDL_RenderDrawRect( gRenderer, &outlineRect2 );
				SDL_Rect outlineRect3 = { SCREEN_WIDTH / 8, SCREEN_HEIGHT / 6 * 4, SCREEN_WIDTH / 8, SCREEN_HEIGHT / 6 };
				SDL_RenderDrawRect( gRenderer, &outlineRect3 );
				SDL_Rect outlineRect4 = { SCREEN_WIDTH / 8 * 6, SCREEN_HEIGHT / 6 * 4, SCREEN_WIDTH / 8, SCREEN_HEIGHT / 6 };
				SDL_RenderDrawRect( gRenderer, &outlineRect4 );

                //linha azul
                SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0xFF, 0xFF );
                SDL_RenderDrawLine( gRenderer, 0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2 );

                //conexoes
                SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0x00 );
                for( int i = 0; i < 320; i += 4 )
                {
                    SDL_RenderDrawPoint( gRenderer, SCREEN_WIDTH / 4 + i, SCREEN_HEIGHT / 6 + i );
                    SDL_RenderDrawPoint( gRenderer, SCREEN_WIDTH / 8 * 6 - i, SCREEN_HEIGHT / 6 + i );
                }
                for( int i = 0; i < 320; i += 4 )
                {
                    SDL_RenderDrawPoint( gRenderer, SCREEN_WIDTH / 4 + i, SCREEN_HEIGHT / 3 + i / 2 );
                    SDL_RenderDrawPoint( gRenderer, SCREEN_WIDTH / 8 * 6 - i, SCREEN_HEIGHT / 3 + i / 2 );
                }
                for( int i = 0; i < 480; i += 4 )
                {
                    SDL_RenderDrawPoint( gRenderer, SCREEN_WIDTH / 8 + i, SCREEN_HEIGHT / 3 + i / 3 );
                    SDL_RenderDrawPoint( gRenderer, SCREEN_WIDTH / 8 * 7 - i, SCREEN_HEIGHT / 3 + i / 3 );
                }


				SDL_RenderPresent( gRenderer );
			}
		}
	}

	close();

	return 0;
}
