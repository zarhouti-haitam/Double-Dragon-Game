#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "controller.h"
#include <time.h>













void gravity(Player *player , Enemy *enemy){


    if(player->prect.y < player->depth){

        player->prect.y  +=  GRAVITYP ;
        player->is_jumping = 1 ; 
    
    }

    if(player->prect.y >= player->depth){

        player->prect.y  = player->depth ;
        player->is_jumping = 0 ;
        player->is_falling = 0 ;   
    }

      if (player->prect.y >= LIMITYS ) {
        player->prect.y = LIMITYS;
        player->depth =LIMITYS ;
        player->is_jumping = 0;  
    }






    if(enemy->enrect.y < enemy->depth){

        enemy->enrect.y  +=  GRAVITYP ;
        enemy->is_jumping = 1 ; 
    
    }

    if (enemy->enrect.y >= enemy->depth) {
        enemy->enrect.y  = enemy->depth ;
        enemy->is_jumping = 0 ;
        enemy->is_falling = 0; 
}


      if (enemy->enrect.y >= LIMITYS ) {
        enemy->enrect.y = LIMITYS;
        enemy->depth =LIMITYS ;
        enemy->is_jumping = 0;  
    }


    
    
}


/////////////////////////////////////////// EVERYTHING RELATED TO PLAYER /////////////////////////////////////////////////////////////





void update_player_attack(Player *player, Enemy *enemy){
    
      if(!player->is_alive && !enemy->is_alive) return ; 

    
    
    
    if( player->is_attacking && !player->is_moving){

    switch (player->current_attack){


        case ATTACK_PUNCH:
            
            
            enemy->is_falling = 0 ; 
            player->is_moving = 0 ;
            player->frame_attack_limit = 1;
            player->attack_frame_speed = 5 ;
            break ; 
            

        case ATTACK_KICK:
            
            
            enemy->is_falling = 0 ; 
            player->is_moving = 0 ;
            player->frame_attack_limit = 1;
            player->attack_frame_speed = 4;
            break;

        case ATTACK_KNEE:

            
            enemy->is_falling = 0 ; 
            player->is_moving = 0 ;
            player->frame_attack_limit = 1;
            player->attack_frame_speed = 5;
            break;

        case ATTACK_JUMPKICK:
            
            
            
            player->is_moving = 0 ;
            player->frame_attack_limit = 2;
            player->attack_frame_speed = 6;
            player->is_jumping = 0; 

            if (player->flip == SDL_FLIP_NONE){
                player->prect.x += 4;
                }

            else{
                 player->prect.x -= 4;
                }  

            if (player->attack_frame == 0 && player->ctr_attack_frame == 0){
                player->prect.y -= JUMPP / 1.2;
            }
            
                break;

        case ATTACK_UPPERCUT:
            
            
            
            player->is_moving = 0 ;
            player->frame_attack_limit = 2;
            player->attack_frame_speed = 4;

            break;

        case ATTACK_TWISTKICK:
            
            
        
            player->is_moving = 0 ;
            player->frame_attack_limit = 3;
            player->attack_frame_speed = 4;

            break;
         
           case ATTACK_NONE :

            player->is_attacking = 0 ;
            player->has_hit_enemy= 0 ;
            enemy->is_falling = 0 ;
            break ; 
    }


        if (!player->is_attacking  ) return;

        player->ctr_attack_frame++;
        
        
        if (player->ctr_attack_frame >= player->attack_frame_speed  ) {

            player->attack_frame++;
            player->ctr_attack_frame = 0;

        }

    
        if (player->attack_frame > player->frame_attack_limit) {

            
            player->attack_frame = 0;
            player->ctr_attack_frame = 0;
            player->has_hit_enemy = 0;
            player->current_attack = ATTACK_NONE;
            player->is_attacking = 0;
            
        }


        if (player->current_attack == ATTACK_JUMPKICK && !player->is_attacking){
        
            player->prect.y = player->depth;   
        }
    
    
    }

    return ;

}





void update_player_hitting(Player *player , Enemy *enemy){

           
    if (enemy == NULL || !enemy->is_alive ) return;

   

    int offset_kick = (-(PlayerW + 6)) ;



    const AttackInfo attack_table[7] = {

    [ATTACK_NONE]     = {0,  -1,   0,   0},
    [ATTACK_PUNCH]    = {10,  1,   5,  14},
    [ATTACK_KICK]     = {15,  1,  offset_kick , 22},
    [ATTACK_KNEE]     = {12,  1,   4,  18},
    [ATTACK_JUMPKICK] = {20,  1,  10,  25},
    [ATTACK_UPPERCUT] = {25,  2,   5,  20},
    [ATTACK_TWISTKICK]= {30,  3,   9,  30}
};



    if (player->current_attack == ATTACK_NONE) return;

    AttackInfo attack_info = attack_table[player->current_attack];

    
    if (player->attack_frame != attack_info.hit_frame) return;

    SDL_Rect hitbox = player->prect;

    hitbox.w += attack_info.extra_width;

    if (player->flip == SDL_FLIP_NONE) {

        hitbox.x += attack_info.offset_x;

    } else {

        hitbox.x -= (attack_info.extra_width + attack_info.offset_x);
    }

    if (check_collision(hitbox, enemy->enrect)) {
        if (!enemy->is_hurt && !player->has_hit_enemy) {
            player->has_hit_enemy = 1;
            
            if ( enemy->life < 10) {
                enemy->is_falling = 1 ;
                enemy->is_hurt = 1 ; 
            }

            if(enemy->life > 0){

                enemy->life -= attack_info.damage;
                enemy->is_hurt = 1;
                enemy->hurt_timer = 20;  

                printf("Enemy hit! Remaining HP: %d\n", enemy->life);
                
            }else{
                printf("enemy is Eliminated\n");
                enemy->is_alive = 0 ;
            }
        }
    } else {
        player->has_hit_enemy = 0; // Reset when no hit
        
    }
}  




void update_player_getting_hit(Player *player , Enemy *enemy ) {

    
    
    if(!player->is_alive) return ; 

    
    if (!player->is_hurt) return;

        // Knockback
        
        if(player->is_falling){
             if (player->flip == SDL_FLIP_NONE ) {
                player->prect.x -= 4;
            } else {
                player->prect.x += 4;
        }

        }else if (player->flip == SDL_FLIP_NONE ) {
            player->prect.x -= 2;
            } else {
            player->prect.x += 2;
            }






        player->is_moving = 0;
        player->is_attacking = 0;

       

    player->ctr_getting_hit_frame++;

    if (player->ctr_getting_hit_frame >= 20) {
        player->getting_hit_frame++;

        player->ctr_getting_hit_frame = 0;

        if (player->getting_hit_frame >= 1) {
            player->getting_hit_frame = 0;
            player->is_hurt = 0;
            enemy->has_hit_player = 0 ; 
            player->is_moving = 1 ; 
        }
    }

    
}










void renderplayer_getting_hit(SDL_Renderer *renderer, Player *player,  Enemy *enemy ,
                              SDL_Texture *falling_texture,
                              SDL_Texture *getting_hit_1,
                              SDL_Texture *getting_hit_2) {

    
    
     if(!player->is_alive) return ; 

     if (!player->is_hurt) return;

    SDL_Texture *hit_texture = NULL;
    SDL_Rect frames[2];

    if (player->is_falling) {
        hit_texture = falling_texture;
        frames[0] = (SDL_Rect){3, 1, 40, 48};
        frames[1] = (SDL_Rect){47, 1, 64, 48};

        SDL_RenderCopyEx(renderer, hit_texture, &frames[player->getting_hit_frame], &player->prect, 0, NULL, player->flip);
    
    } else {

        switch (enemy->current_attack) {

            case ATTACK_PUNCH:
                hit_texture = getting_hit_1;
                frames[0] = (SDL_Rect){2, 2, 43, 85};
                frames[1] = frames[0];
                break;

            case ATTACK_KNEE:
                hit_texture = getting_hit_1;
                frames[0] = (SDL_Rect){2, 2, 40, 60};
                frames[1] = frames[0];
                break;

            case ATTACK_KICK:
                hit_texture = getting_hit_2;
                frames[0] = (SDL_Rect){2, 2, 42, 83};
                frames[1] = frames[0];
                break;

            case ATTACK_JUMPKICK:
            case ATTACK_UPPERCUT:
            case ATTACK_TWISTKICK:
                hit_texture = falling_texture;
                frames[0] = (SDL_Rect){3, 1, 40, 48};
                frames[1] = (SDL_Rect){47, 1, 64, 48};
                break;
            default:
                player->is_hurt = 0 ; 
        }

        SDL_RenderCopyEx(renderer, hit_texture, &frames[player->getting_hit_frame], &player->prect, 0, NULL, player->flip);
    }
}






/////////////////////////////////////////// EVERYTHING RELATED TO ENEMY /////////////////////////////////////////////////////////////










void update_enemy_posi(Enemy *enemy, Player *player) {
    
    if (!enemy->is_alive) return;

    if (enemy->is_attacking) return;

    enemy->is_moving = 0;

    int dx = player->prect.x - enemy->enrect.x;
    int dy = player->depth - enemy->depth;

    int abs_dx = abs(dx);
    int abs_dy = abs(dy);

    if (abs_dx > ATTACK_RANGE_X -5) {
        enemy->enrect.x += (dx < 0 ? -enemy->speed : enemy->speed);
        enemy->flip = (dx < 0) ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
        enemy->is_moving = 1;
    }

    if (abs_dy > ATTACK_RANGE_DEPTH - 10) {
        enemy->depth += (dy < 0 ? -enemy->speed : enemy->speed);
        enemy->is_moving = 1;
    }

    if (enemy->depth > LIMITYS) {
        enemy->depth = LIMITYS;
    }

    if (enemy->is_moving) {
        if (++enemy->ctr_frame >= enemy->frame_switch_speed) {
            enemy->frame = (enemy->frame + 1) % 9;  
            enemy->ctr_frame = 0;
        }
    } else {
        enemy->ctr_frame = 0;
        enemy->frame = 0;
    }
}








void update_enemy_attack(Enemy *enemy , Player *player){

    
        
    if(!enemy->is_alive) return ; 


    
    if( enemy->is_attacking  && !player->is_attacking){


    switch (enemy->current_attack){


        case ATTACK_PUNCH:
            
            enemy->is_moving = 0 ;
            enemy->frame_attack_limit = 1;
            enemy->attack_frame_speed = 4 ;
            break ; 
            

        case ATTACK_KICK:
            
            enemy->is_moving = 0 ;
            enemy->frame_attack_limit = 1;
            enemy->attack_frame_speed = 4;
            break;

        case ATTACK_KNEE:

            enemy->is_moving = 0 ;
            enemy->frame_attack_limit = 1;
            enemy->attack_frame_speed = 5;
            break;

        case ATTACK_JUMPKICK:
            
            enemy->is_moving = 0 ;
            enemy->frame_attack_limit = 2;
            enemy->attack_frame_speed = 4;
            enemy->is_jumping = 0; 

            if (enemy->flip == SDL_FLIP_NONE){

                enemy->enrect.x += 4;
                }

            else{
                 enemy->enrect.x -= 4;
                }  

            if (enemy->attack_frame == 0 && enemy->ctr_attack_frame == 0){
                
                enemy->enrect.y -= JUMPP / 1.2;
            }
            
                break;

        case ATTACK_UPPERCUT:
            
            enemy->is_moving = 0 ;
            enemy->frame_attack_limit = 2;
            enemy->attack_frame_speed = 4;

            break;

        case ATTACK_TWISTKICK:
            
            enemy->is_moving = 0 ;
            enemy->frame_attack_limit = 3;
            enemy->attack_frame_speed = 4;

            break;
         
           case ATTACK_NONE :
            enemy->is_attacking = 0 ;
            break ; 
    }


        if (!enemy->is_attacking  ) return;

        enemy->ctr_attack_frame++;
        
        
        if (enemy->ctr_attack_frame >= enemy->attack_frame_speed) {

            enemy->attack_frame++;
            enemy->ctr_attack_frame = 0;

        }

    
        if (enemy->attack_frame > enemy->frame_attack_limit) {

            
            enemy->attack_frame = 0;
            enemy->ctr_attack_frame = 0;
            enemy->has_hit_player = 0;
            enemy->current_attack = ATTACK_NONE;
            player->is_hurt = 0 ; 
            return;
        }


        if (enemy->current_attack == ATTACK_JUMPKICK && !enemy->is_attacking){
        
            enemy->enrect.y = enemy->depth;   
        }
    
    
    }




}



void enemy_attack_ai(Enemy *enemy, Player *player) {


    if(!enemy->is_alive) return ; 

    if (enemy->is_attacking) return;



    if (enemy->attack_cooldown > 0) {

        enemy->attack_cooldown--;

        return;
    }

    int dx = abs(player->prect.x - enemy->enrect.x);
    int dy = abs(player->depth - enemy->depth);  

    if (dx < ATTACK_RANGE_X && dy < ATTACK_RANGE_DEPTH) {

        int r = rand() % 100;

        if (r < 25)

            enemy->current_attack = ATTACK_PUNCH;
        
        else if (r < 50)

            enemy->current_attack = ATTACK_JUMPKICK;

        else if (r < 70)
        
            enemy->current_attack = ATTACK_PUNCH;

        else if (r < 85)

            enemy->current_attack = ATTACK_PUNCH;

        else

        enemy->current_attack = ATTACK_PUNCH;
        
        enemy->is_attacking = 1;

    
        enemy->attack_cooldown = ATTACK_COOLDOWN;


    }

    
}







void update_enemy_hitting(Enemy *enemy, Player *player) {
    
    if(!enemy->is_alive || !enemy->is_attacking) return;

    
    const AttackInfo attack_table[7] = {

    [ATTACK_NONE]     = {0,  -1,   0,   0},
    [ATTACK_PUNCH]    = {5,  1,  3,  4},
    [ATTACK_KICK]     = {10,  1,  3,  5},
    [ATTACK_KNEE]     = {8,  1,   2,  4},
    [ATTACK_JUMPKICK] = {15,  2,  6,  5},
    [ATTACK_UPPERCUT] = {7,  2,  3,  10},
    [ATTACK_TWISTKICK]= {20,  3,  5,  10}
};



    if (enemy->current_attack == ATTACK_NONE) return;

    AttackInfo attack_info = attack_table[enemy->current_attack];

    
    if (enemy->attack_frame != attack_info.hit_frame) return;

    SDL_Rect hitbox = enemy->enrect;

    hitbox.w += attack_info.extra_width;

    if (enemy->flip == SDL_FLIP_NONE) {

        hitbox.x += attack_info.offset_x;

    } else {

        hitbox.x -= (attack_info.extra_width + attack_info.offset_x);
    }

    if (check_collision(hitbox, player->prect)) {

        if (!player->is_hurt && !enemy->has_hit_player) {
        
          
            
            if ( player->life < 10) {
                player->is_falling = 1 ;
                player->is_hurt = 1 ; 

            }
                


            if(player->life > 0){
                
                player->life = (player->life - attack_info.damage < 0) ? 0 : player->life - attack_info.damage;
                enemy->has_hit_player = 1;
                player->is_attacking = 0 ; 

                player->is_hurt = 1;
                player->hurt_timer = 20;  
                printf("player hit! Remaining HP: %d\n", player->life);
                return ; 
                

            }else{
                
                printf("Plyaer is Eliminated ;; You won \n");
                player->is_alive = 0 ; 
                
            }

        }

    } else {

        enemy->has_hit_player = 0; // Reset when no hit
        player->is_hurt = 0 ;
    }
}  





void update_enemy_getting_hit(Enemy *enemy, Player *player) {
    
    if(!enemy->is_alive) return;
    if (!enemy->is_hurt) return;

    // Add bounds check
    

    // Knockback
    if(enemy->is_falling){
        if (enemy->flip == SDL_FLIP_NONE ) {
            enemy->enrect.x -= 4;
        } else {
            enemy->enrect.x += 4;
        }
    } else if (enemy->flip == SDL_FLIP_NONE ) {
        enemy->enrect.x -= 2;
    } else {
        enemy->enrect.x += 2;
    }

    enemy->is_moving = 0;
    enemy->is_attacking = 0;

    enemy->ctr_getting_hit_frame++;

    if (enemy->ctr_getting_hit_frame >= 20) {
        enemy->getting_hit_frame++;

        enemy->ctr_getting_hit_frame = 0;

        if (enemy->getting_hit_frame > 1) {
            enemy->getting_hit_frame = 0;
            enemy->is_hurt = 0;
            player->has_hit_enemy = 0 ; 
            enemy->is_moving = 1 ; 
            
        }

        if (!enemy->is_hurt && !player->is_attacking) player->is_moving = 1 ; 
    }
}






void renderenemy1_getting_hit(SDL_Renderer *renderer, Enemy *enemy, Player *player,
                              SDL_Texture *falling_texture,
                              SDL_Texture *getting_hit_1,
                              SDL_Texture *getting_hit_by_cutkick) {

   
   
    if(!enemy->is_alive || enemy->is_attacking || enemy->is_moving) return ; 
     
    if (!enemy->is_hurt && !player->has_hit_enemy  ) return ;

    
     if (!falling_texture || !getting_hit_1 || !getting_hit_by_cutkick) {
        printf("Error: Missing required texture in renderenemy1_getting_hit\n");
        return;
    }
    player->is_attacking = 1 ;
    enemy->is_moving = 0 ; 

    

    SDL_Texture *hit_texture = NULL;
    SDL_Rect frames[2];

    switch (player->current_attack) {
        
        case ATTACK_PUNCH:
            hit_texture = getting_hit_1;
            frames[0] = (SDL_Rect){2, 2, 40, 60};
            frames[1] = (SDL_Rect){2, 2, 40, 60};
            
            break;

        
        case ATTACK_KICK:
        case ATTACK_TWISTKICK:
            hit_texture = getting_hit_by_cutkick;
            frames[0] = (SDL_Rect){2, 2, 40, 60};
            frames[1] = (SDL_Rect){2, 2, 40, 60};
            
            break;

        case ATTACK_JUMPKICK:
        case ATTACK_UPPERCUT:
        case ATTACK_KNEE:
            hit_texture = falling_texture;
            frames[0] = (SDL_Rect){50, 3, 64, 52};
            frames[1] = (SDL_Rect){50, 3, 64, 52};
            
            break;

        default:
            enemy->is_hurt = 0 ; 
            return ; 
    }

    if (!hit_texture) {
    printf("ERROR: hit_texture is NULL for attack %d\n", player->current_attack);
    return;
}

if (enemy->getting_hit_frame < 0 || enemy->getting_hit_frame >= 2) {
    printf("ERROR: Invalid getting_hit_frame: %d\n", enemy->getting_hit_frame);
    return;
}

SDL_RenderCopyEx(renderer, hit_texture, &frames[enemy->getting_hit_frame], &enemy->enrect, 0, NULL, enemy->flip);
}