

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "include/SDLFcts.h"
#include <time.h>
#include "include/player.h"
#include "include/enemies.h"
#include "include/controller.h"


int main() {

    
    // General Rendering //


    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Texture *texture = NULL;
    SDL_Texture *firstdisplay = NULL ;
    SDL_Texture *seconddisplay = NULL ;
    SDL_Texture  *swore_torev = NULL ; 
    SDL_Texture *you_won = NULL ;
    


    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "Erreur SDL_Init: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    window = SDL_CreateWindow("Affichage", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, GAME_WIDTH, GAME_HEIGHT, 0);
    if (!window) {
        fprintf(stderr, "Erreur SDL_CreateWindow: %s\n", SDL_GetError());
        CleanResources(NULL, NULL, NULL);
        exit(EXIT_FAILURE);
    }
    

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        fprintf(stderr, "Erreur SDL_CreateRenderer: %s\n", SDL_GetError());
        CleanResources(window, NULL, NULL);
        exit(EXIT_FAILURE);
    }

     /// General ///


    texture = LoadTexture(renderer, "media/images/backgrounds/BG ISEN.png", window);


    firstdisplay = LoadTexture(renderer , "media/images/backgrounds/First Display.PNG" , window) ; 


    seconddisplay = LoadTexture(renderer , "media/images/backgrounds/MADE WITH “AMOUR“ BY ZARHOUTI HAITAM.png" , window) ; 


    swore_torev = LoadTexture(renderer , "media/images/backgrounds/swore_togetrevenge.PNG" , window) ; 


    you_won = LoadTexture(renderer , "media/images/backgrounds/you_won.PNG" , window) ; 


    


    // Related to PLAYER //
    
    SDL_Texture *myPlayerTexture = NULL;
    Player *myPlayer  ;

    SDL_Texture *jumping_playerTexture = NULL ;

    SDL_Texture *punch_1_texture = NULL ;
    SDL_Texture *punch_2_texture = NULL ;

    SDL_Texture *cut_kick_Texture = NULL ; 

    SDL_Texture *jump_kick_texture = NULL;

    SDL_Texture *knee_strike_texture = NULL;

    SDL_Texture *twist_kick_texture = NULL ;

    SDL_Texture *uppercut_texture = NULL ; 

    SDL_Texture *player_gettinghit_1_Texture = NULL ; 

    SDL_Texture *player_falling_Texture = NULL ; 

    
    
    myPlayerTexture = LoadTexture(renderer , "media/images/player/Standing(Walking).png" , window);

   
    jumping_playerTexture = LoadTexture(renderer , "media/images/player/jumping_player.PNG" , window);


    punch_1_texture = LoadTexture(renderer , "media/images/player/attacks/punch_1.png" , window);
    

    punch_2_texture = LoadTexture(renderer , "media/images/player/attacks/punch_2.png" , window);
    

    cut_kick_Texture = LoadTexture(renderer , "media/images/player/attacks/cut_kick.png" , window);    

    
    jump_kick_texture = LoadTexture(renderer , "media/images/player/attacks/jump_kick.png" , window); 
    

    knee_strike_texture = LoadTexture(renderer , "media/images/player/attacks/chigi.png" , window);
    

    twist_kick_texture = LoadTexture(renderer , "media/images/player/attacks/twist_kick.png" , window);
    

    uppercut_texture = LoadTexture(renderer , "media/images/player/attacks/upercut.png" , window);

    
    player_gettinghit_1_Texture = LoadTexture(renderer , "media/images/player/getting hit/getting_hit_1.png" , window);


    player_falling_Texture = LoadTexture(renderer , "media/images/player/getting hit/player_falling.png" , window);



    

    // Related to Enemy //

    SDL_Texture *myEnemyTexture = NULL ; 
    Enemy *myEnemy = NULL ; 

    SDL_Texture *enemy1_punch_1_Texture = NULL ; 

    SDL_Texture *enemy1_punch_2_Texture = NULL ; 

    SDL_Texture *enemy1_punch_3_Texture = NULL ; 

    SDL_Texture *enemy1_jumpkick_Texture = NULL ; 

    SDL_Texture *enemy1_gettinghit_2_Texture = NULL ; 

    SDL_Texture *enemy1_gettinghit_with_cut_kick_Texture = NULL ;

    SDL_Texture *enemy1_falling_Texture = NULL ;



    
    myEnemyTexture = LoadTexture(renderer , "media/images/enemies/enemy1/enemyMoving__1.png" , window);

    enemy1_punch_1_Texture = LoadTexture(renderer , "media/images/enemies/enemy1/attacks/punch_1_enemy.png" , window);
    
    enemy1_punch_2_Texture = LoadTexture(renderer , "media/images/enemies/enemy1/attacks/punch_2_enemy.png" , window);

    enemy1_punch_3_Texture = LoadTexture(renderer , "media/images/enemies/enemy1/attacks/punch_3_enemy.png" , window);

    enemy1_jumpkick_Texture = LoadTexture(renderer , "media/images/enemies/enemy1/attacks/jumpkick_enemy.png" , window);


    enemy1_gettinghit_2_Texture = LoadTexture(renderer , "media/images/enemies/enemy1/attacks/getting_hit_2_enemy.png" , window);

    enemy1_gettinghit_with_cut_kick_Texture = LoadTexture(renderer , "media/images/enemies/enemy1/attacks/getting_hit_with_cut_kick_enemy.png" , window);

    enemy1_falling_Texture = LoadTexture(renderer , "media/images/enemies/enemy1/attacks/falling_enemy.png" , window);






    


    
    

    SDL_Rect src_rect = {0, 0, GAME_WIDTH, GAME_HEIGHT};

    SDL_Rect dest_rect = {0, 0, GAME_WIDTH, GAME_HEIGHT}; 


    myPlayer = malloc(sizeof(Player));
    if (!myPlayer) {
        fprintf(stderr, "Erreur d'allocation du joueur\n");
        exit(EXIT_FAILURE);
    }

    myEnemy = malloc(sizeof(Enemy));
    if(!myEnemy){
        fprintf(stderr, "Erreur d'allocation de l'enemi\n");
        exit(EXIT_FAILURE);
    }

    
    initplayer ( myPlayer , GROUNDX , GROUNDY);
    initenemy (myEnemy , GAME_WIDTH - 500 , GROUNDY - 20);
    

    
    ///// image du lanching qui dure pendant 4 sec //
    
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, seconddisplay, &src_rect, &dest_rect);
    SDL_RenderPresent(renderer);
    SDL_Delay(2500);
    
    
    
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, firstdisplay, &src_rect, &dest_rect);
    SDL_RenderPresent(renderer);
    

        // Image du start avec un event  keypress //
        SDL_Event launch_event;
        int wait_for_start = 1;
        
        while (wait_for_start) {
            while (SDL_PollEvent(&launch_event)) {
                if (launch_event.type == SDL_QUIT) {
                    wait_for_start = 0;
                    exit(EXIT_SUCCESS);
                }
                if (launch_event.type == SDL_KEYDOWN) {
                    wait_for_start = 0;  // Exit the waiting loop and start the game
                }
            }
    }


    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, swore_torev, &src_rect, &dest_rect);
    SDL_RenderPresent(renderer);
    SDL_Delay(1200);



        
    
    
    int running = 1; 
    SDL_Event event;
    srand(time(NULL));

    while (running) {

           
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                
                printf("Quit\n");
                running = 0;
            }
            else{
                
                
                if (event.type == SDL_KEYDOWN){
                    
                    switch(event.key.keysym.sym){
                        
                        case  SDLK_SPACE :

                            player_jump(myPlayer);
                            break ;
                        
                        case SDLK_p: // Punch

                            if ( !myPlayer->is_attacking  && !myPlayer->is_jumping) {
                                
                                
                                myPlayer->is_attacking = 1 ;
                                myPlayer->is_moving = 0 ;
                                myPlayer->current_attack = ATTACK_PUNCH;
                                myPlayer->punch_rand = (myPlayer->punch_rand + 1) % 2;
                                myPlayer->has_hit_enemy = 0;
                                
                            }
                            break;
                        
                        case SDLK_k: // Kick

                            if (!(myPlayer->current_attack == ATTACK_KICK) && !myPlayer->is_jumping) {
                                
                                myPlayer->is_attacking = 1 ;
                                myPlayer->is_moving = 0 ;
                                myPlayer->current_attack = ATTACK_KICK;
                                myPlayer->has_hit_enemy = 0;
                            }
                            break;
                            
                            

                        case SDLK_m: // JumpKick

                            if (!(myPlayer->current_attack == ATTACK_JUMPKICK) && !myPlayer->is_jumping){
                                
                                myPlayer->is_attacking = 1 ;
                                myPlayer->is_moving = 0 ;
                                myPlayer->current_attack = ATTACK_JUMPKICK;
                                myPlayer->has_hit_enemy = 0;
                                                        
                            }
                            break;    

                        
                        case SDLK_n: // Knee Strike
                            if (!(myPlayer->current_attack == ATTACK_KNEE) && !(myPlayer->current_attack == ATTACK_KICK)) {
                                
                                myPlayer->is_attacking = 1 ;
                                myPlayer->is_moving = 0 ;
                                myPlayer->current_attack = ATTACK_KNEE;
                                myPlayer->has_hit_enemy = 0;
                            }
                            break;   
                            
                        case SDLK_t:
                            if (!(myPlayer->current_attack == ATTACK_TWISTKICK) && !(myPlayer->current_attack == ATTACK_PUNCH) && !(myPlayer->current_attack == ATTACK_KICK)) {
                                
                                myPlayer->is_attacking = 1 ;
                                myPlayer->is_moving = 0 ;
                                myPlayer->current_attack = ATTACK_TWISTKICK;
                                myPlayer->has_hit_enemy = 0;
                            }
                            break; 
                        
                            case SDLK_u: 
                            if (!(myPlayer->current_attack == ATTACK_UPPERCUT) && !(myPlayer->current_attack == ATTACK_PUNCH) && !(myPlayer->current_attack == ATTACK_KICK)) {
                                
                                myPlayer->is_attacking = 1 ;
                                myPlayer->is_moving = 0 ;
                                myPlayer->current_attack = ATTACK_UPPERCUT;
                                myPlayer->has_hit_enemy = 0;
                            }
                            break ;
                    }
                }

            } 
               
        }
     
        const Uint8 *keypressed = SDL_GetKeyboardState(NULL); 

        
        update_player_posi( myPlayer , keypressed);
        update_enemy_posi(myEnemy , myPlayer);

        gravity(myPlayer , myEnemy);

        update_player_attack(myPlayer , myEnemy);
        update_player_hitting(myPlayer , myEnemy);

        update_hurt_timer(myEnemy , myPlayer);
        

        update_enemy_attack(myEnemy , myPlayer);
        enemy_attack_ai(myEnemy, myPlayer);
        update_enemy_hitting(myEnemy , myPlayer);




        
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, &src_rect, &dest_rect);
        
            
            update_enemy_getting_hit(myEnemy , myPlayer) ;
            renderenemy1_getting_hit(renderer, myEnemy , myPlayer ,
                              enemy1_falling_Texture,
                              enemy1_gettinghit_2_Texture,
                              enemy1_gettinghit_with_cut_kick_Texture);
            
            update_player_getting_hit(myPlayer , myEnemy) ;
            renderplayer_getting_hit(renderer, myPlayer , myEnemy ,
                              player_falling_Texture,
                              player_gettinghit_1_Texture,
                              player_gettinghit_1_Texture);

        
        
           
            
            if(myPlayer->is_attacking ){
               
                renderplayer_attack(renderer , myPlayer ,  punch_1_texture , punch_2_texture , cut_kick_Texture , knee_strike_texture ,  jump_kick_texture , twist_kick_texture , uppercut_texture );
            }

            else if(myPlayer->is_jumping){
                rendererplayer_jump(renderer , myPlayer , jumping_playerTexture);
            }
            

            renderplayer_moving(renderer , myPlayer , myPlayerTexture);
            
            
            

            renderenemy_moving(renderer , myEnemyTexture , myEnemy);
        
         if(myEnemy->is_attacking){

            renderenemy1_attack(renderer , myEnemy , enemy1_punch_1_Texture , enemy1_punch_2_Texture , enemy1_punch_3_Texture , enemy1_jumpkick_Texture );
        }

        static Uint32 death_time = 0;
        static int enemy_death_handled = 0;

    if (!myEnemy->is_alive && !enemy_death_handled) {
    
        death_time = SDL_GetTicks();
        enemy_death_handled = 1;
    }

    if (enemy_death_handled) {
    
        if (SDL_GetTicks() - death_time < 3000) {
            render_enemy_dead(renderer, myEnemy, enemy1_falling_Texture);
        } else {
            SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer, you_won, &src_rect, &dest_rect);
            SDL_RenderPresent(renderer);
            SDL_Delay(1000);
            running = 0; 
        }
    }

        SDL_RenderPresent(renderer);
        
    }

    CleanResources(window, renderer, texture);
    free(myPlayer);
    free(myEnemy);
    return 0;
}