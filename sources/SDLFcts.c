
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "SDLFcts.h"


void CleanResources(SDL_Window *w , SDL_Renderer *r , SDL_Texture *t){

    if(t != NULL) SDL_DestroyTexture(t);

    if(w != NULL) SDL_DestroyWindow(w);

    if(r != NULL) SDL_DestroyRenderer(r);

    SDL_Quit();

    /* Cette fonction est là pour clean les résidus de memoire crée par 
    les T R W */
     
    
}



int check_collision(SDL_Rect player, SDL_Rect enemy){

    return SDL_HasIntersection(&player, &enemy);

}






SDL_Texture* LoadTexture(SDL_Renderer *renderer, const char *path, SDL_Window *window) {
   
    SDL_Surface *surface = IMG_Load(path);
    
    if (!surface) {
        
        fprintf(stderr, "Erreur chargement image '%s': %s\n", path, IMG_GetError());
        CleanResources(window, renderer, NULL);
        exit(EXIT_FAILURE);
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    if (!texture) {
        
        fprintf(stderr, "Erreur création texture '%s': %s\n", path, IMG_GetError());
        CleanResources(window, renderer, NULL);
        exit(EXIT_FAILURE);
    }

    return texture;
}





void update_hurt_timer(Enemy *enemy , Player *player) {

    if (enemy->is_hurt) {
        enemy->hurt_timer--;

        if (enemy->hurt_timer <= 0) {
            enemy->is_hurt = 0;
            enemy->hurt_timer = 0;
        }
    }



    if (player->is_hurt) {
        player->hurt_timer--;

        if (player->hurt_timer <= 0) {
            player->is_hurt = 0;
            player->hurt_timer = 0;
        }
    }

    



}




