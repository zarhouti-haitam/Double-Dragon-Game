
#include "player.h"
#include "enemies.h"


void CleanResources(SDL_Window *w , SDL_Renderer *r , SDL_Texture *t);


int check_collision(SDL_Rect player, SDL_Rect enemy);


SDL_Texture* LoadTexture(SDL_Renderer *renderer, const char *path, SDL_Window *window);


void update_hurt_timer(Enemy *enemy , Player *player);
