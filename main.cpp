/*Memory
  Allan Legemaate
  28/08/13
*/

//Includes
#include "globals.h"
#include "card.h"
#include "button.h"

using namespace std;

//Define all of the possible game screens
#define SPLASH 0
#define MENU 1
#define HIGHSCORES 2
#define HELP 3
#define ABOUT 4
#define LEVELSELECT 5
#define INGAME 6

// Close button
volatile int close_button_pressed = FALSE;

//Create variables
int gameScreen = SPLASH;
bool closeGame;
bool showFPS;

//extreme = 10, hard = 8, medium = 6, easy = 4
int difficulty = 4;
int moves;

// Holds highscores (temp)
string scores[10][2];
string fileName;
int scoreDifficulty = 4;

//Text input
string  edittext = "";
string::iterator iter = edittext.begin();

//Create fonts
FONT *f1, *f2, *f3, *f4, *f5; 

//Create images
BITMAP* buffer;
BITMAP* intro;
BITMAP* background;
BITMAP* background_menu;

BITMAP* levelSelect;
BITMAP* levelSelectLeft;
BITMAP* levelSelectRight;
BITMAP* difficultyImages[4];

//Create sounds
SAMPLE* click;

//Objects
vector<card> cards;

Button button_start( 320, 275, 640, 120);
Button button_highscores( 320, 405, 640, 120);
Button button_quit( 320, 535, 640, 120);

//FPS System
volatile int ticks = 0;
int updates_per_second = 100;
volatile int game_time = 0;

int fps;
int frames_done;
int old_time;

void draw( bool toScreen);

void ticker(){
    ticks++;
}
END_OF_FUNCTION(ticker)

void game_time_ticker(){
    game_time++;
}
END_OF_FUNCTION(ticker)

void close_button_handler(void){
  close_button_pressed = TRUE;
}
END_OF_FUNCTION(close_button_handler)

//Load all ingame content
void setup(bool first){
  //Runs only the first time
  if(first){
    //Set screenmode
    if(false == true){
      resDiv = 1;
      if(set_gfx_mode( GFX_AUTODETECT_FULLSCREEN, 1280, 960, 0, 0) !=0){
        resDiv = 2;
        if(set_gfx_mode( GFX_AUTODETECT_FULLSCREEN, 640, 480, 0, 0) !=0){
          resDiv = 4;
          if(set_gfx_mode( GFX_AUTODETECT_FULLSCREEN, 320, 240, 0, 0) !=0){
            set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
          	allegro_message("Unable to go into fullscreen graphic mode\n%s\n", allegro_error);
            exit(1);
          }
        }
      }
    }
    else{
      resDiv = 1;
      if(set_gfx_mode( GFX_AUTODETECT_WINDOWED, 1280, 960, 0, 0) !=0){
        resDiv = 2;
        if(set_gfx_mode( GFX_AUTODETECT_WINDOWED, 640, 480, 0, 0) !=0){
          resDiv = 4;
          if(set_gfx_mode( GFX_AUTODETECT_WINDOWED, 320, 240, 0, 0) !=0){
            set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
          	allegro_message("Unable to set any windowed graphic mode\n%s\n", allegro_error);
            exit(1);
          }
        }
      }
    }

    //Creates a random number generator (based on time)
    srand (time(NULL));
    
    //Setup for FPS system
    LOCK_VARIABLE(ticks);
    LOCK_FUNCTION(ticker);
    install_int_ex(ticker, BPS_TO_TIMER(updates_per_second));
    
    LOCK_VARIABLE(game_time);
    LOCK_FUNCTION(game_time_ticker);
    install_int_ex(game_time_ticker, BPS_TO_TIMER(10));
    
    // Close button
    LOCK_FUNCTION(close_button_handler);
    set_close_button_callback(close_button_handler);
    
    //Creates a buffer
    buffer = create_bitmap( 1280, 960);
    intro = load_bitmap( "img/intro.bmp", NULL);
    background = load_bitmap( "img/backgrounds/background.bmp", NULL);
    background_menu = load_bitmap( "img/backgrounds/background_menu.bmp", NULL);
    
    //Level Select Images
    levelSelect = load_bitmap ( "img/selector/levelSelect.bmp", NULL);
    levelSelectLeft = load_bitmap ( "img/selector/levelSelectLeft.bmp", NULL);
    levelSelectRight = load_bitmap ( "img/selector/levelSelectRight.bmp", NULL);
    
    difficultyImages[0] = load_bitmap ( "img/selector/easy.bmp", NULL);
    difficultyImages[1] = load_bitmap ( "img/selector/medium.bmp", NULL);
    difficultyImages[2] = load_bitmap ( "img/selector/hard.bmp", NULL);
    difficultyImages[3] = load_bitmap ( "img/selector/extreme.bmp", NULL);
    
    
    // Button images
    button_start.setImages( "img/buttons/button_start.bmp", "img/buttons/button_start_hover.bmp");
    button_highscores.setImages( "img/buttons/button_scores.bmp", "img/buttons/button_scores_hover.bmp");
    button_quit.setImages( "img/buttons/button_quit.bmp", "img/buttons/button_quit_hover.bmp");
    
    // Load sounds
    click = load_sample("sfx/click.wav");
    
    //Sets Font
    f1 = load_font("fonts/arial_black.pcx", NULL, NULL);
    f2 = extract_font_range(f1, ' ', 'A'-1);
    f3 = extract_font_range(f1, 'A', 'Z');
    f4 = extract_font_range(f1, 'Z'+1, 'z');
    
    //Merge fonts 
    font = merge_fonts(f4, f5 = merge_fonts(f2, f3));
    
    //Destroy temporary fonts
    destroy_font(f1);
    destroy_font(f2);
    destroy_font(f3);
    destroy_font(f4);
    destroy_font(f5); 
  }
  
  //Reset moves
  moves = 0;
  
  //Clear cards (new game)
  cards.clear();
  
  //Creates 10 blank cards
  for(int i = 0; i < difficulty; i++){
    for(int t = 0; t < difficulty; t++){
      card newCard( i * 800/difficulty + 250, t * 800/difficulty + 80, -1, 700/difficulty);
      cards.push_back( newCard);
    }
  }
  
  //Adds types in sets of 2
  for(int i = 0; i < cards.size()/2; i++){
    int cardType = random(0,5);
    cards.at(i).setType(cardType);
    
    bool placeFound = false;
    while(!placeFound){
      int newPlace = random(cards.size()/2,cards.size()-1);
      if(cards.at(newPlace).getType() == -1){
        cards.at(newPlace).setType(cardType);
        placeFound = true;
      }
    }
  }
}

//Read High Scores
void updateScores(int newDifficulty){
  if(newDifficulty == 4){
    fileName = "data/highscores_easy.dat";
  }
  else if(newDifficulty == 6){
    fileName = "data/highscores_medium.dat";
  }
  else if(newDifficulty == 8){
    fileName = "data/highscores_hard.dat";
  }
  else if(newDifficulty == 10){
    fileName = "data/highscores_extreme.dat";
  }
  
  ifstream read(fileName.c_str());
  
  for (int i = 0; i < 10; i++){      
    for( int t = 0; t < 2; t++){
      read>>scores[i][t];
    }
  }
  read.close();
}

//Add score
void addScore(string name){
  //Update table
  updateScores(difficulty);
  
  //Prevent crashing
  if(name == ""){
    name = "player"; 
  }
  
  //Update List
  for (int i = 0; i < 10; i++){      
    if(moves < atoi(scores[i][1].c_str())){
      for (int t = 9; t > i; t--){
        scores[t][1] = scores[t - 1][1];
        scores[t][0] = scores[t - 1][0];
      }
      scores[i][1] = convertInt(moves);
      scores[i][0] = name;
      break;
    }
  }
  
  //Save Scores
  ofstream saveFile;
  saveFile.open(fileName.c_str());
  
  for (int i = 0; i < 10; i++){      
    for( int t = 0; t < 2; t++){
      saveFile<<scores[i][t]<<" ";
    }
  }       
  saveFile.close();
}

//Run the game loops
void game(){
  if(gameScreen == SPLASH){
    fade_in(intro,16);
    rest(2000);
    //FSOUND_Stream_Play(1,menuMusic);
    fade_out(16);
    gameScreen = MENU;
    draw( false);
    fade_in(buffer,16); 
  }
  else if(gameScreen == MENU){
    if(mouse_b & 1){
      if(button_start.getHover()){
        fade_out(16);
        gameScreen = LEVELSELECT;
        draw( false);
        fade_in(buffer,16);
      }
      else if(button_highscores.getHover()){
        fade_out(16);
        gameScreen = HIGHSCORES;
        draw( false);
        fade_in(buffer,16);
      }
      else if(button_quit.getHover()){
        closeGame = true;
      }
    }
  }
  else if(gameScreen == HIGHSCORES){
    
    updateScores( scoreDifficulty);
    
    //Go to menu
    if(key[KEY_M]){
      setup(false);
      fade_out(16);
      gameScreen = MENU;  
      draw( false);
      fade_in(buffer,16);
    }

    //Click buttons
    if(collision(mouse_x,mouse_x,-1,200,mouse_y,mouse_y, 0, 920) || key[KEY_LEFT]){
      if(mouse_b & 1 || key[KEY_LEFT]){
        if(scoreDifficulty > 4){
          scoreDifficulty -= 2;
          play_sample(click,255,125,1000,0);
        }
        rest(200);
      }
    }
    else if(collision(mouse_x,mouse_x,1080,1280,mouse_y,mouse_y, 0, 920) || key[KEY_RIGHT]){
      if(mouse_b & 1 || key[KEY_RIGHT]){     
        if(scoreDifficulty < 10){
          scoreDifficulty += 2;
          play_sample(click,255,125,1000,0);
        }
        rest(200);
      }
    }
  }
  else if(gameScreen == LEVELSELECT){
    
    //Go to menu
    if(key[KEY_M]){
      setup(false);
      fade_out(16);
      gameScreen = MENU;  
      draw( false);
      fade_in(buffer,64);
    }

    //Click buttons
    if(collision(mouse_x,mouse_x,-1,200,mouse_y,mouse_y, 0, 920) || key[KEY_LEFT]){
      if(mouse_b & 1 || key[KEY_LEFT]){
        if(difficulty > 4){
          difficulty -= 2;
          play_sample(click,255,125,1000,0);
        }
        rest(200);
      }
    }
    else if(collision(mouse_x,mouse_x,1080,1280,mouse_y,mouse_y, 0, 920) || key[KEY_RIGHT]){
      if(mouse_b & 1 || key[KEY_RIGHT]){     
        if(difficulty < 10){
          difficulty += 2;
          play_sample(click,255,125,1000,0);
        }
        rest(200);
      }
    }
    else if(collision(mouse_x,mouse_x,250,1050,mouse_y,mouse_y, 185, 785) || key[KEY_ENTER]){
      if(mouse_b & 1 || key[KEY_ENTER]){
        fade_out(16);
        setup(false);
        gameScreen = INGAME;
        draw( false);
        fade_in(buffer,16);    
      }
    }
  }
  else if(gameScreen == INGAME){
    //End game
    if(cards.size() == 0){
      //Name input
      if(keypressed()){
        int  newkey   = readkey();
        char ASCII    = newkey & 0xff;
        char scancode = newkey >> 8;
        
        // a character key was pressed; add it to the string
        if(ASCII >= 32 && ASCII <= 126 && edittext.length() < 25 && scancode != KEY_SPACE){
          // add the new char
          iter = edittext.insert(iter, ASCII);
          // increment both the caret and the iterator
          iter++;
        }
        // some other, "special" key was pressed; handle it here
        else{
          if(scancode == KEY_DEL){
            if(iter != edittext.end()){
              iter = edittext.erase(iter);
            }
          }
          if(scancode == KEY_BACKSPACE){
            if(iter != edittext.begin()){
               iter--;
               iter = edittext.erase(iter);
            }
          }
          if(scancode == KEY_RIGHT){
            if(iter != edittext.end()){ 
              iter++;
            }
          }
          if(scancode == KEY_LEFT){
            if(iter != edittext.begin()){ 
              iter--;
            }
          }
          if(scancode == KEY_ENTER){
            fade_out(16);
            gameScreen = MENU;
            addScore( edittext);
            draw( false);
            fade_in(buffer,16);
          }
        }
      }
    }
    //Go to menu
    else if(key[KEY_M]){
      fade_out(16);
      gameScreen = MENU;
      draw( false);
      fade_in(buffer,16);
    }
    
    // Card logic
    // Count number of flipped cards
    numberSelected = 0;
    for(int i = 0; i < cards.size(); i++){
      if(cards.at(i).getSelected()){
        numberSelected++;
      }
    }
    
    // Do card logic
    for(int i = 0; i < cards.size(); i++){
      cards.at(i).logic();
    }
    
    // Find the placing of the two flipped cards
    if(numberSelected > 0){
      for(int i = 0; i < cards.size(); i++){
        if(cards.at(i).getSelected()){
          cardSelected1 = i;
          break;
        }
      }
      for(int i = 0; i < cards.size(); i++){
        if(cards.at(i).getSelected()){
          if(cardSelected1 != i){
            cardSelected2 = i;
            break;
          }
        }
      }
    }
    
    if(numberSelected == 2 && cards.at(cardSelected1).getAnimationDone() && cards.at(cardSelected2).getAnimationDone() && cards.at(cardSelected1).getSelected() && cards.at(cardSelected2).getSelected()){ 
      if(cards.at(cardSelected1).getType() == cards.at(cardSelected2).getType()){
        if(!cards.at(cardSelected1).getMatched()){
          cards.at(cardSelected1).setMatched(true);
          cards.at(cardSelected2).setMatched(true);
        }
        if(cards.at(cardSelected1).getOffScreen() && cards.at(cardSelected2).getOffScreen()){
          cards.erase(cards.begin() + cardSelected1);
          cards.erase(cards.begin() + cardSelected2 - 1);
          moves++;
        }
      }
      else{
        cards.at(cardSelected1).setSelected(false);
        cards.at(cardSelected2).setSelected(false);
        moves++;
      }
    }
  }
  
  //Exit game
  if(key[KEY_ESC]){
    while(key[KEY_ESC]){
      
    }
    if(gameScreen == INGAME){
      while(true){
        draw_sprite( buffer, background_menu, 0, 0);
        textprintf_centre_ex( buffer, font, 640, 400, makecol(0,0,0), -1, "Press escape again to go to the main menu.");
        textprintf_centre_ex( buffer, font, 640, 440, makecol(0,0,0), -1, "Press any other key to go back.");
        stretch_sprite( screen, buffer, 0, 0, SCREEN_W, SCREEN_H);
        clear_keybuf();
        readkey();
        if(key[KEY_ESC]){
          gameScreen = MENU;
          break;
        }
        else{
          break;
        }
      }
    }
    else if(gameScreen != MENU){
      gameScreen = MENU;
    }
  }
  
  //Counter for FPS
  frames_done++;
}

//Draw images
void draw( bool toScreen){
  if(gameScreen == SPLASH){
    
  }
  else if(gameScreen == MENU){
    draw_sprite( buffer, background_menu, 0, 0);
    button_start.draw( buffer);
    button_highscores.draw( buffer);
    button_quit.draw( buffer);
  }
  else if(gameScreen == HIGHSCORES){
    // Background
    draw_sprite(buffer,levelSelect,0,0);
    
    //Titles
    if(scoreDifficulty  == 4){
      textprintf_centre_ex( buffer, font, 640, 100, makecol(0,0,0), -1, "Easy");
    }
    else if(scoreDifficulty == 6){
      textprintf_centre_ex( buffer, font, 640, 100, makecol(0,0,0), -1, "Medium");
    }
    else if(scoreDifficulty == 8){
      textprintf_centre_ex( buffer, font, 640, 100, makecol(0,0,0), -1, "Hard");
    }
    else if(scoreDifficulty == 10){
      textprintf_centre_ex( buffer, font, 640, 100, makecol(0,0,0), -1, "EXTREME");
    }
    
    //Click buttons
    if(collision(mouse_x,mouse_x,-1,200,mouse_y,mouse_y, 0, 920) || key[KEY_LEFT]){
      draw_sprite(buffer, levelSelectLeft, 0, 0);
    }
    else if(collision(mouse_x,mouse_x,1080,1280,mouse_y,mouse_y, 0, 920) || key[KEY_RIGHT]){
      draw_sprite(buffer, levelSelectRight, 1080, 0);
    }
    
    // Draw scores
    for(int i = 0; i < 10; i++){
      string name = scores[i][0];
      textout_ex(buffer, font, name.c_str(), 400, (i * 50) + 200, makecol(0,0,0), -1);
      
      name = scores[i][1];
      textout_right_ex(buffer, font, name.c_str(), 860, (i * 50) + 200, makecol(0,0,0), -1);
    }
  }
  else if(gameScreen == LEVELSELECT){
    // Background
    draw_sprite(buffer,levelSelect,0,0);
    
    //Click buttons
    if(collision(mouse_x,mouse_x,-1,200,mouse_y,mouse_y, 0, 920) || key[KEY_LEFT]){
      draw_sprite(buffer, levelSelectLeft, 0, 0);
    }
    else if(collision(mouse_x,mouse_x,1080,1280,mouse_y,mouse_y, 0, 920) || key[KEY_RIGHT]){
      draw_sprite(buffer, levelSelectRight, 1080, 0);
    }
    
    // Draw difficulty demos
    if(difficulty == 4){
      draw_sprite( buffer, difficultyImages[0], 250, 185);
    }
    else if(difficulty == 6){
      draw_sprite( buffer, difficultyImages[1], 250, 185);
    }
    else if(difficulty == 8){
      draw_sprite( buffer, difficultyImages[2], 250, 185);
    }
    else if(difficulty == 10){
      draw_sprite( buffer, difficultyImages[3], 250, 185);
    }
  }
  else if(gameScreen == INGAME){
    //Background
    draw_sprite( buffer, background, 0, 0);
    
    //Show Moves
    rectfill( buffer, 15, 15, 200, 70, makecol(255,255,255));
    textprintf_ex( buffer, font, 20, 20, makecol(0,0,0), -1, "Moves:%i", moves);
    
    // Draw cards
    for(int i = 0; i < cards.size(); i++){
      cards.at(i).draw(buffer);
    }
    
    if(cards.size() == 0){
      //Create gui
      textprintf_centre_ex(buffer,font,640,310, makecol(0,0,0),-1,"Congratulations! Enter Your Name");
      
      //Input rectangle
      rectfill(buffer, 400, 408, 892, 452, makecol(0,0,0));
      rectfill(buffer, 402, 410, 890, 450, makecol(255,255,255));
      
      // Output the string to the screen
      textout_ex(buffer, font, edittext.c_str(), 410, 410, makecol(0,0,0), -1);
      
      // Draw the caret
      vline(buffer, text_length(font, edittext.c_str()) + 410, 412, 448, makecol(0,0,0));  
    }
  }
  
  //FPS counter
  if(showFPS){
    textprintf_ex(buffer,font,0,80,makecol(0,0,0),-1,"FPS-%i", fps);
  }

  //Draw cursor
  circlefill( buffer, mouse_x * resDiv, mouse_y * resDiv, 10, makecol(255,0,0));
    
  if(toScreen){
    //Draws buffer
    stretch_sprite( screen, buffer, 0, 0, SCREEN_W, SCREEN_H);
  }
}

int main(){	
  //Initializing
  FSOUND_Init (44100, 32, 0);
  allegro_init();
  install_keyboard();
  install_timer();
  install_mouse();
  install_sound(DIGI_AUTODETECT,MIDI_AUTODETECT,".");
  
  set_color_depth(32);
  
  set_window_title("Memory");
  
  //Setup game
  setup(true);
  
  //Starts Game
  while(!closeGame && !close_button_pressed){
    //Runs FPS system
    while(ticks == 0){
      rest(1);
    }
    while(ticks > 0){
      int old_ticks = ticks;
      //Update always
      game();
      ticks--;
      if(old_ticks <= ticks){  
        break; 
      }
    }
    if(game_time - old_time >= 10){
      fps = frames_done;
      frames_done = 0;
      old_time = game_time;
    }
    //Update every set amount of frames
    draw( true);
  }
  
  allegro_exit();
     
  return 0; 
}
END_OF_MAIN();
