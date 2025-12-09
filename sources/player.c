

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "player.h"



void initplayer(Player *player  , int x , int y){

    player->prect.x = x ;

    player->prect.w = PlayerW ;

    player->prect.h = PlayerH ;

    player->speed = SPEEDP ;

    player->flip  = SDL_FLIP_NONE ;

    player->depth = y ; 

    player->prect.y = y ;

    player->is_jumping = 0 ;

    player->is_attacking = 0 ;
 
    player->is_moving = 0 ;

    player->ctr_frame = 0 ;

    player->frame = 0 ; 

    player->is_alive = 1 ;  

    player->current_attack = ATTACK_NONE ; 

    player->attack_frame = 0;
     
    player->ctr_attack_frame = 0 ;
     
    player->attack_frame_speed = 0 ;
     
    player->frame_attack_limit = 0 ;

    player->is_hurt = 0 ; 

    player->hurt_timer = 0 ; 

    player->life = 400 ; 

}


void player_jump(Player *player  ){

    if(!player->is_jumping && player->is_alive ){

        player->prect.y  -=  JUMPP ;
        player->is_jumping = 1 ; 

    }    

    

}



void update_player_posi( Player *player , const Uint8 *keypressed){

    if(!player->is_alive) return ; 
   
	if(!player->is_attacking ){
	
	player->is_moving = 0 ;   
    

		if ( keypressed[SDL_SCANCODE_D] && player->prect.x <= GAME_WIDTH - 50){

			player->flip = SDL_FLIP_NONE ; 
			player->prect.x += player->speed ;
			player->is_moving = 1 ;

		}

		if ( keypressed[SDL_SCANCODE_A] &&  player->prect.x >= 0 ){

			player->flip = SDL_FLIP_HORIZONTAL ;
			player->prect.x =  player->prect.x - player->speed ;
			player->is_moving = 1 ;

		}

		if (keypressed[SDL_SCANCODE_W]) {

			if(player->prect.y > LIMITYW){

			player->depth -= player->speed;
			player->is_moving = 1;
			
			}

		
			if (!player->is_jumping)
				player->prect.y = player->depth;


		}
		
		if (keypressed[SDL_SCANCODE_S]) {

			if(player->prect.y < LIMITYS){
				player->depth += player->speed;
				player->is_moving = 1;
			}    

		
			if (!player->is_jumping)
				player->prect.y = player->depth;

		}

	}

    if (player->is_jumping) {
        if (player->prect.y >= player->depth) {
            player->is_jumping = 0;
            player->prect.y = player->depth;
        }

}
	


}








void renderplayer_attack(SDL_Renderer *renderer, Player *player, 
                  SDL_Texture *punch_1_texture, SDL_Texture *punch_2_texture,
                  SDL_Texture *cut_kick_texture, SDL_Texture *knee_strike_texture,
                  SDL_Texture *jump_kick_texture, SDL_Texture *twist_kick_texture,
                  SDL_Texture *uppercut_texture) {
    
    

    if(!player->is_alive) return ; 

    
	if( player->is_attacking){
       

        switch (player->current_attack){

            case ATTACK_NONE:

                
                break;



            case ATTACK_PUNCH:

                SDL_Rect frames1[2] = { {2, 2, 45, 83},
                                        {47, 2, 68, 83} 
                                    };

                SDL_Rect frames2[2] = { {2, 2, 43, 80},
                                        {45, 2, 70, 80} 
                                    };
                                    
                

                SDL_Texture *tex = (player->punch_rand == 0) ? punch_1_texture : punch_2_texture;

                SDL_Rect current = (player->punch_rand % 2 == 0) ? frames1[player->attack_frame] : frames2[player->attack_frame];

                SDL_RenderCopyEx(renderer, tex, &current, &player->prect, 0, NULL, player->flip);
                
                break;
            

            case ATTACK_KICK: 

                SDL_Rect kick_frames[2] = { {2, 1, 30, 53},
                                            {32, 1, 52, 53} 
                                        };

                SDL_RenderCopyEx(renderer, cut_kick_texture, &kick_frames[player->attack_frame], &player->prect, 0, NULL, player->flip);

                break;
            

            case ATTACK_KNEE:

                SDL_Rect knee_frames[2] = { {2, 2, 43, 84},
                                            {47, 2, 58, 84} 
                                        };

                SDL_RenderCopyEx(renderer, knee_strike_texture, &knee_frames[player->attack_frame], &player->prect, 0, NULL, player->flip);

                break;
            

            case ATTACK_JUMPKICK: 

                SDL_Rect jumpkick_frames[3] = { {2, 2, 32, 54},
                                                {36, 0, 42, 54},
                                                {79, 0, 37, 54} 
                                            };

                SDL_RenderCopyEx(renderer, jump_kick_texture, &jumpkick_frames[player->attack_frame], &player->prect, 0, NULL, player->flip);

                break;
            

            case ATTACK_TWISTKICK: 

                SDL_Rect twistkick_frames[4] = {
                                                {2, 2, 60, 85},
                                                {64, 2, 60, 85},
                                                {128, 2, 60, 85},
                                                {192, 2, 63, 85}
                                            };

                SDL_RenderCopyEx(renderer, twist_kick_texture, &twistkick_frames[player->attack_frame], &player->prect, 0, NULL, player->flip);

                break;
            

            case ATTACK_UPPERCUT: 
            
                SDL_Rect uppercut_frames[3] = {
                                                {2, 2, 35, 63},
                                                {40, 2, 40, 63},
                                                {82, 2, 40, 63}
                                            };


                SDL_RenderCopyEx(renderer, uppercut_texture, &uppercut_frames[player->attack_frame], &player->prect, 0, NULL, player->flip);
                break;
            
                
            

                
        }

            

    }

}



void renderplayer_moving(SDL_Renderer *renderer, Player *player, SDL_Texture *moving_texture){

 
     if(!player->is_alive) return ; 

 
 
    SDL_Rect src;
    src.y = 0;
    if( player->is_moving && !player->is_jumping ){

                    

                    player->frame_switch_speed = 2;

                    if (player->is_moving && !player->is_attacking) {
                        
                        player->ctr_frame++;

                        if (player->ctr_frame > player->frame_switch_speed) {  
                            player->frame++;
                            player->ctr_frame = 0;
                        }

                        if (player->frame > 2) {  
                            player->frame = 0;
                        } 

                        } else {
                            if (player->frame != 0) {
                                player->frame = 0;
                                player->ctr_frame = 0;
                            }
                        }

                        src.x = 57 * player->frame;
                        src.w = 53;
                        src.h = 173;

                        SDL_RenderCopyEx(renderer, moving_texture, &src, &player->prect, 0, NULL, player->flip);
                        
                    }


        else if (!player->is_attacking && !player->is_hurt && !player->is_jumping && !player->is_falling && !player->is_moving ){

            
                src.x = 0;
                src.w = 53;
                src.h = 173;

                SDL_RenderCopyEx(renderer, moving_texture, &src, &player->prect, 0, NULL, player->flip);
        }            
                  
}






void rendererplayer_jump(SDL_Renderer *renderer, Player *player , SDL_Texture *jumping_playerTexture){

        if(!player->is_alive) return ; 

                
        if (player->is_jumping) {
            

            SDL_Rect src = {0, 0, 551, 1019};

            SDL_RenderCopyEx(renderer, jumping_playerTexture, &src, &player->prect, 0, NULL, player->flip);

        }
}





    






 



