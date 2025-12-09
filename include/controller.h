
#include "enemies.h"
#include "SDLFcts.h"
#include "player.h"



void gravity(Player *player , Enemy *enemy);


void update_player_attack(Player *player ,  Enemy *enemy);


void update_enemy_posi( Enemy *enemy , Player *player);


void update_player_hitting(Player *player , Enemy *enemy);


void update_player_getting_hit(Player *player , Enemy *enemy );



void renderplayer_getting_hit(SDL_Renderer *renderer, Player *player,  Enemy *enemy ,
                              SDL_Texture *falling_texture,
                              SDL_Texture *getting_hit_1,
                              SDL_Texture *getting_hit_2);

void update_enemy_attack(Enemy *enemy , Player *player);


void enemy_attack_ai(Enemy *enemy, Player *player);


void update_enemy_hitting(Enemy *enemy , Player *player);


void update_enemy_getting_hit(Enemy *enemy , Player *player);



void renderenemy1_getting_hit(SDL_Renderer *renderer, Enemy *enemy, Player *player,
                              SDL_Texture *falling_texture,
                              SDL_Texture *getting_hit_1,
                              SDL_Texture *getting_hit_by_cutkick
                              );
