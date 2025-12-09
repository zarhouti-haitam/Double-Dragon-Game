

#ifndef PLAYER_H
#define PLAYER_H

#define GAME_HEIGHT 1000
#define GAME_WIDTH 1500

#define PlayerH 200
#define PlayerW 70

#define JUMPP 150
#define SPEEDP 4

#define GROUNDY 620
#define LIMITYS 630
#define LIMITYW 500
#define GROUNDX 50
#define GRAVITYP 10



typedef enum {

     ATTACK_NONE,
     ATTACK_PUNCH,
     ATTACK_KICK,
     ATTACK_KNEE,
     ATTACK_JUMPKICK,
     ATTACK_UPPERCUT,
     ATTACK_TWISTKICK

} AttackType;


typedef struct {

    int damage;
    int hit_frame;
    int offset_x; // pour que les attack vont vers l'avant et ne restent pas dans le rectangle de leur Rect de base
    int extra_width;

} AttackInfo;



typedef struct player_ {
    
    SDL_Rect prect;      // position et taille du joueur
    int speed; 
    int depth ; 
    
    int is_jumping;   //relation avec les future jump kick (similaire à street fighter)
    int is_moving; //  j'ai 3 images =>  || 120 / 3 = 40 px
    
    int frame; // frame actuelle qui est rendu
    int ctr_frame;  //ctr de mes frames  (relation avec frame_switch_speed)
    int frame_switch_speed ; //pour controller la vitesse de l'animation (combien de temps pour switcher entre les frames)
    int frame_limit ; 
    int punch_rand ; 
    

    int is_attacking;
    int attack_frame;    // tout ce qui est related au frames de l'attack 
    int ctr_attack_frame;  // après plusieur test pour automatiser l'attaque et le mouvement avec les meme frame ;; j'ai conclut que ce n'est pas une très bonne idée ,, parceque les update_frame d'attaque et de mouvemet utilisaient la meme variable
    int attack_frame_speed;
    int frame_attack_limit;

   
    int has_hit_enemy;
    int life ;   
    int is_hurt ; 
    int hurt_timer ; 

    int getting_hit_frame ; 
    int ctr_getting_hit_frame;

    int is_falling ; 
    int falling_frame ;

    int is_alive ;     
    
    AttackType current_attack;

    

    SDL_RendererFlip flip;



   
}Player;






void initplayer(Player *player  , int x , int y);


void update_player_posi( Player *player , const Uint8 *keypressed);


void player_jump(Player *player);




void renderplayer_attack(SDL_Renderer *renderer, Player *player ,
                  SDL_Texture *punch_1_texture, SDL_Texture *punch_2_texture,
                  SDL_Texture *cut_kick_texture, SDL_Texture *knee_strike_texture,
                  SDL_Texture *jump_kick_texture, SDL_Texture *twist_kick_texture,
                  SDL_Texture *uppercut_texture);

void renderplayer_moving(SDL_Renderer *renderer, Player *player, SDL_Texture *moving_texture) ;               


void rendererplayer_jump(SDL_Renderer *renderer, Player *player , SDL_Texture *jumping_playerTexture);


void renderidle (SDL_Renderer *renderer, Player *player, SDL_Texture *moving_texture);




#endif