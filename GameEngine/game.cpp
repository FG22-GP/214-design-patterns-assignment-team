#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include "RespawningEnemy.h"



const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;

const char* MainCharacterImage = "img/pikachu.png";


SDL_Texture* LoadTexture(SDL_Renderer* renderer, const char* imagePath);
SDL_Texture* RenderText(SDL_Renderer* renderer, TTF_Font* font, const char* text, SDL_Color textColor, int& width, int& height);

int main(int argc, char* args[])
{
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return -1;
    }

    SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE, &window, &renderer);
    if (!window)
    {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return -1;
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
    {
        printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
        return -1;
    }

    if (TTF_Init() == -1)
    {
        printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
        return -1;
    }

    // Initialize RespawningEnemy and its object pool
    RespawningEnemy& respawningEnemy = RespawningEnemy::getInstance();
    respawningEnemy.initializeObjectPool(5); // pool size

    SDL_Texture* mainCharacter = LoadTexture(renderer, MainCharacterImage);
    if (!mainCharacter)
        return -1;

    TTF_Font* font = TTF_OpenFont("font/lazy.ttf", 100);
    if (!font)
    {
        printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
        return -1;
    }

    int textWidth, textHeight;
    SDL_Texture* textTexture = RenderText(renderer, font, "Awoooooooooga", { 0xff, 0xff, 0xff }, textWidth, textHeight);
    if (!textTexture)
        return -1;

    SDL_Event e;
    bool quit = false;

    int mainCharacter_x = 0, mainCharacter_y = 0;
    int mainCharacter_w = 200, mainCharacter_h = 200;
    bool pikachuMoveRight = false;

    while (!quit)
    {
        
        while (SDL_PollEvent(&e))
        {
            switch (e.type) {
                case SDL_QUIT:
                    quit = true;
                    break;
                case SDL_KEYDOWN:
                    
                    break;
            }
        }
        

        const Uint8* keystate = SDL_GetKeyboardState(NULL);
        if (keystate[SDL_SCANCODE_UP] && mainCharacter_y > 0)
            mainCharacter_y--;
        if (keystate[SDL_SCANCODE_DOWN] && mainCharacter_y < SCREEN_HEIGHT - 200)
            mainCharacter_y++;
        if (keystate[SDL_SCANCODE_LEFT] && mainCharacter_x > 0)
            mainCharacter_x--;
        if (keystate[SDL_SCANCODE_RIGHT] && mainCharacter_x < SCREEN_WIDTH - 200)
            mainCharacter_x++;

        SDL_SetRenderDrawColor(renderer, 100, 60, 100, 255);
        SDL_RenderClear(renderer);

        SDL_Rect characterRect = { mainCharacter_x, mainCharacter_y, mainCharacter_w, mainCharacter_h };
        SDL_RenderCopy(renderer, mainCharacter, NULL, &characterRect);

        if (respawningEnemy.checkCollisionWithPlayer(characterRect))
        {
            // Handle collision response maybe
        }
        
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Set color to red
        // Render enemies
        for (const SDL_Rect& enemyRect : respawningEnemy.getObjectPool()) {
            SDL_RenderDrawRect(renderer, &enemyRect);  // drawing rectangles for enemies
        }

        SDL_Rect textRect = { SCREEN_WIDTH / 2 - textWidth / 2, SCREEN_HEIGHT / 2, textWidth, textHeight };
        SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

        SDL_RenderPresent(renderer);

        SDL_Delay(0);
    }

    SDL_DestroyTexture(mainCharacter);
    SDL_DestroyTexture(textTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_CloseFont(font);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();

    return 0;
}

SDL_Texture* LoadTexture(SDL_Renderer* renderer, const char* imagePath)
{
    SDL_Texture* texture = nullptr;
    SDL_Surface* loadedSurface = IMG_Load(imagePath);
    if (loadedSurface == NULL)
    {
        printf("Unable to load image %s! SDL_image Error: %s\n", imagePath, IMG_GetError());
    }
    else
    {
        texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if (texture == NULL)
        {
            printf("Unable to create texture from %s! SDL Error: %s\n", imagePath, SDL_GetError());
        }
        SDL_FreeSurface(loadedSurface);
    }
    return texture;
}

SDL_Texture* RenderText(SDL_Renderer* renderer, TTF_Font* font, const char* text, SDL_Color textColor, int& width, int& height)
{
    SDL_Texture* texture = nullptr;
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text, textColor);
    if (textSurface == NULL)
    {
        printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
    }
    else
    {
        texture = SDL_CreateTextureFromSurface(renderer, textSurface);
        if (texture == NULL)
        {
            printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
        }
        width = textSurface->w;
        height = textSurface->h;
        SDL_FreeSurface(textSurface);
    }
    return texture;
}