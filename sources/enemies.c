

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "enemies.h"
#include <time.h>




void initenemy(Enemy *enemy  , int x , int y){

    enemy->enrect.x = x ;

    enemy->enrect.y = y ;

    enemy->depth = y ; 

    enemy->enrect.w = PlayerW  - 4;

    enemy->enrect.h = PlayerH  ;

    enemy->flip  = SDL_FLIP_HORIZONTAL ;

    enemy->speed = SPEEDP - 2.5 ;

    enemy->is_moving = 0 ;

    enemy->is_attacking = 0 ; 

    enemy->is_jumping = 0 ; 

    enemy->ctr_frame = 0 ;

    enemy->frame = 0 ; 

    enemy->frame_switch_speed = 6 ; //change de frame  après x FPS

    enemy->life = 400 ; 

    enemy->hurt_timer = 0 ; 

    enemy->current_attack = ATTACK_NONE ; 

    enemy->attack_frame = 0;
     
    enemy->ctr_attack_frame = 0 ;
     
    enemy->attack_frame_speed = 0 ;
     
    enemy->frame_attack_limit = 0 ;

    enemy->has_hit_player = 0 ; 

    enemy->attack_timer = 0 ; 

    enemy->attack_cooldown = ATTACK_COOLDOWN ; 

    enemy->is_alive = 1 ; 

    enemy->is_falling = 0 ; 

    enemy->getting_hit_frame = 0;

    enemy->ctr_getting_hit_frame = 0;
    
    enemy->is_hurt = 0;

    

}


void enemy_jump(Enemy *enemy  ){

    
    if(!enemy->is_alive) return ; 

    
    if(!enemy->is_jumping ){

        enemy->enrect.y  -=  JUMPP ;

        enemy->is_jumping = 1 ; 

    }    
    

}


void renderenemy_moving(SDL_Renderer *renderer , SDL_Texture *enemyTexture ,  Enemy *enemy){
    
    


    if(!enemy->is_alive) return ; 

    if(enemy->is_moving){
    SDL_Rect frames[9] = {

        {10, 0, 82, 232},
        {104, 0, 82, 232},
        {202, 0, 82, 232},
        {333, 0, 83, 232},
        {427, 0, 83, 232},
        {539, 0, 125, 232},
        {689, 0, 97, 232},
        {835, 0, 82, 232},
        {947, 0, 124, 232}
    
    };

    SDL_RenderCopyEx(renderer, enemyTexture, &frames[enemy->frame], &enemy->enrect , 0, NULL, enemy->flip);

    }else if (!enemy->is_attacking && !enemy->is_hurt && !enemy->is_jumping && !enemy->is_falling && !enemy->is_moving ){

                SDL_Rect src ;
                src.y = 0 ;
                src.x = 10;
                src.w = 82;
                src.h = 232;

                SDL_RenderCopyEx(renderer, enemyTexture, &src, &enemy->enrect, 0, NULL, enemy->flip);
        }      
}



void renderenemy1_attack(SDL_Renderer *renderer, Enemy *enemy,  SDL_Texture *punch_1_enemy_texture  , SDL_Texture *punch_2_enemy_texture   , SDL_Texture *punch_3_enemy_texture , SDL_Texture *jump_kick_enemy_texture){

    
	if(!enemy->is_alive) return ;
    
    if(enemy->is_attacking){
    
    

        switch (enemy->current_attack){

            case ATTACK_NONE:

                break;



            case ATTACK_PUNCH:
            default :

                SDL_Rect frames1[2] = { {2, 2, 32, 60},
                                        {35, 2, 55, 60} 
                                    };

                SDL_Rect frames2[2] = { {2, 3, 32, 65},
                                        {35, 3, 53, 65} 
                                    };
                
                SDL_Rect frames3[2] = { {2, 3, 32, 63},
                                        {35, 3, 53, 63} 
                                    };

                
                SDL_Texture *tex = NULL;
                SDL_Rect current;
                enemy->punch_rand = rand() % 3;

                switch (enemy->punch_rand) {

                    case 0:

                        tex = punch_1_enemy_texture;
                        current = frames1[enemy->attack_frame];
                        break;

                    case 1:

                        tex = punch_2_enemy_texture;
                        current = frames2[enemy->attack_frame];
                        break;


                    case 2:

                        tex = punch_3_enemy_texture;
                        current = frames3[enemy->attack_frame];
                        break;
                }

                SDL_RenderCopyEx(renderer, tex, &current, &enemy->enrect, 0, NULL, enemy->flip);
                
                break;
            

        
            

            case ATTACK_JUMPKICK: 

                SDL_Rect jumpkick_frames[3] = { {5, 2, 32, 64},
                                                {40, 2, 45, 54},
                                                {88, 2, 39, 54} 
                                            };

                SDL_RenderCopyEx(renderer, jump_kick_enemy_texture, &jumpkick_frames[enemy->attack_frame], &enemy->enrect, 0, NULL, enemy->flip);

                break;
            

    
                
            

                
        }

            

    }

}




void render_enemy_dead(SDL_Renderer *renderer, Enemy *enemy, SDL_Texture *dead_texture) {
    
    
    if (!enemy || !dead_texture || enemy->is_alive) return;

        enemy->is_moving = 0 ; 
        

        
    if (enemy->ctr_attack_frame >= 20) {
        enemy->attack_frame++;
        enemy->ctr_attack_frame = 0;

    } else {
        enemy->ctr_attack_frame++;
    }

    if (enemy->attack_frame >= 1) {
        enemy->attack_frame = 1; // Stay on last frame
    }

    SDL_Rect frames[2] = { { 63 , 0 , 59 , 55} , {0 , 0 , 60 , 55} } ; 
          

    SDL_RenderCopyEx(renderer, dead_texture, &frames[enemy->attack_frame] , &enemy->enrect , 0 ,  NULL, enemy->flip);


}