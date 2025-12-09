
#ifndef ENEMIES_H
#define ENEMIES_H
#include "player.h"

#define ATTACK_RANGE_X 60      
#define ATTACK_RANGE_DEPTH 20     
#define ATTACK_COOLDOWN 10
#define FALL_TIMER 20





typedef struct enemy_ {
    
    SDL_Rect enrect;      // position et taille de l'enemy 
    
    int speed; 
    int punch_rand ; 
    int depth ; 
    
    int is_jumping ; 
    
    int is_moving; //  j'ai 3 images =>  || 120 / 3 = 40 px
    int frame; // frame actuelle qui est rendu
    int ctr_frame;  //ctr de mes frames  (relation avec frame_switch_speed)
    int frame_switch_speed ; //pour controller la vitesse de l'animation (combien de temps pour switcher entre les frames)

    int is_attacking ;
    int attack_frame;
    int ctr_attack_frame;
    int attack_frame_speed;
    int frame_attack_limit;    

    int getting_hit_frame ; 
    int ctr_getting_hit_frame;

    int is_falling ; 
    int falling_frame ;
      


    int life ; 

    int is_hurt ; 
    int hurt_timer ;


    int attack_timer ; 
    int attack_cooldown ; 

    int has_hit_player ; 
    int fall_ctr ; 


    int is_alive ; 

    AttackType current_attack ; 
    
    
    SDL_RendererFlip flip;
    
}Enemy;



void initenemy(Enemy *enemy  , int x , int y);


void renderenemy_moving();


void renderenemy1_attack(SDL_Renderer *renderer, Enemy *enemy,  SDL_Texture *punch_1_enemy_texture  , SDL_Texture *punch_2_enemy_texture   , SDL_Texture *punch_3_enemy_texture , SDL_Texture *jump_kick_enemy_texture);


void enemy_jump(Enemy *enemy);


void render_enemy_dead(SDL_Renderer *renderer, Enemy *enemy, SDL_Texture *dead_texture);






#endif
