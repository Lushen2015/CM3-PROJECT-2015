

#include <allegro5\allegro.h>
#include <allegro5\allegro_font.h>						//font header files
#include <allegro5\allegro_ttf.h>
#include <allegro5\allegro_primitives.h>	//primitive header file
#include "Objects.h"
#include<allegro5\allegro_image.h>
#include<allegro5\allegro_audio.h>
#include<allegro5\allegro_acodec.h>



enum Keys{ A, S, D, W, SPACE, L };
int res_x = 1280;
int res_y = 820;
int pos_x = 0;
int checkpoint = 0;
int blockNum = 0;
const int num_proj = 5;
int level = 1;
int g = 1;


struct person{
	int r = 20;
	int feet = res_y - 55;
	int x = 200;
	int y = feet - (3 * r);
	int j_height = res_y - 450;
	int ms = 5;
	int jumpspeed = 7;
	int lives = 5;
	int score = 0;


}player;
int deathDelay = 0;
int c = 0;
int wait = 0;
int box_width = player.r * 2 + 15;
int box_bounds = box_width;
int pipe_width = 120;
int pipe_bounds = pipe_width;
int spike_height = 50;
int spike_width = 20;
bool deathPause = false;
bool LR = false;



void initproj(Projectiles proj[], int size);
void drawproj(Projectiles proj[], int size);
void shoot(Projectiles proj[], int size);
void update(Projectiles proj[], int size);
void SetEnemies(enemies guys[], int size);
void StartEnemies(enemies guys[], int size);
void CreateEnemies(enemies guys[], int size, int counter);
void DrawEnemies(enemies guys[], int size, int counter);
void MoveEnemy(bool check);
void Collision(Projectiles proj[], int sizeP, enemies guys[], int sizeE, int counter);
bool CollideEnemy(enemies guys[], int size, int counter);
void ISEEDEADPEOPLE(enemies guys[], int size);
void Apocalypse(enemies guys[], int size);

int num_bg = 10;
int num_ground = 10;

void GenerateSTART(bool check);

void HittingBlocks(Projectiles proj[], int size, int sizeB, block blocks[]);
void HittingPipes(Projectiles proj[], int size, int sizeP, Pipe pipes[]);

int const num_enemies = 22;
bool shot = false;

enemies guys[num_enemies];




////////////////////ADUIO////////////////////////////////////////////////////////////////////////////
ALLEGRO_SAMPLE *shot1 = NULL;
ALLEGRO_SAMPLE_ID *foo = NULL;

ALLEGRO_SAMPLE *boom = NULL;
ALLEGRO_SAMPLE_ID *foo1 = NULL;

ALLEGRO_SAMPLE *song = NULL;
ALLEGRO_SAMPLE_ID *foo2 = NULL;

ALLEGRO_SAMPLE *jumping = NULL;
ALLEGRO_SAMPLE_ID *foo3 = NULL;

ALLEGRO_SAMPLE *bump = NULL;
ALLEGRO_SAMPLE_ID *foo4 = NULL;

ALLEGRO_SAMPLE *die = NULL;
ALLEGRO_SAMPLE_ID *foo5 = NULL;

ALLEGRO_SAMPLE *pause = NULL;
ALLEGRO_SAMPLE_ID *foo6 = NULL;



ALLEGRO_SAMPLE_INSTANCE *songInstance = NULL;



///////////////////////////////////////////////////////////////////////////////////////////////////////////






void initSpike(spike spikes[], int size);
void createSpike(spike spikes[], int size);
bool spikeCollide(spike spikes[], int size);



void initPipe(Pipe pipes[], int size);
void createPI(Pipe pipes[], int size);
bool checkpipe(Pipe pipes[], int size);
bool pipe_right(Pipe pipes[], int size);
bool pipe_left(Pipe pipes[], int size);



void initblock(block blocks[], int size);
void create(block blocks[], int size);
bool checkblock(block blocks[], int size);
bool block_limit(block blocks[], int size);
bool noblock(block blocks[], int size);//****************************************************************
bool box_right(block blocks[], int size); //****************************************************************
bool box_left(block blocks[], int size);//******************************************************************

void GenerateBG_G();

ALLEGRO_BITMAP *image1 = NULL;//bricks
int image1Height = 0;
int image1Width = 0;


ALLEGRO_BITMAP *image2 = NULL;//goomba
int image2Height = 0;
int image2Width = 0;

ALLEGRO_BITMAP *image3 = NULL;//koopaR
int image3Height = 0;
int image3Width = 0;


ALLEGRO_BITMAP *image4 = NULL;//koopaL
int image4Height = 0;
int image4Width = 0;

ALLEGRO_BITMAP *image5 = NULL;//Spikes
int image5Height = 0;
int image5Width = 0;

ALLEGRO_BITMAP *imageB = NULL;//Ground
int imageBHeight = 0;
int imageBWidth = 0;

ALLEGRO_BITMAP *bgimage = NULL;//Background
int imageBGHeight = 0;
int imageBGWidth = 0;

/////////////////////////////////////////////////////////////////////////////////////////////PAUSE///////////////////////////////////////////
ALLEGRO_BITMAP *WALLimage = NULL;//pause screen
int imageWALLHeight = 0;
int imageWALLWidth = 0;

ALLEGRO_BITMAP *WALLDimage = NULL;//pause screen DEMO
int imageWALLDHeight = 0;
int imageWALLDWidth = 0;

ALLEGRO_BITMAP *WALLQimage = NULL;//pause screen QUIT
int imageWALLQHeight = 0;
int imageWALLQWidth = 0;


/////////////////////////////////////////////////////START////////////////////////////////////////////////////////////////////////////////////////
ALLEGRO_BITMAP *WALL2image = NULL;//start screen
int imageWALL2Height = 0;
int imageWALL2Width = 0;

ALLEGRO_BITMAP *WALL2Dimage = NULL;//start screen
int imageWALL2DHeight = 0;
int imageWALL2DWidth = 0;


ALLEGRO_BITMAP *WALL2Qimage = NULL;//start screen
int imageWALL2QHeight = 0;
int imageWALL2QWidth = 0;


ALLEGRO_BITMAP *loadscreen1 = NULL;
int screen1H = 0;
int screen1W = 0;

ALLEGRO_BITMAP *loadscreen2 = NULL;
int screen2H = 0;
int screen2W = 0;

ALLEGRO_BITMAP *loadscreen3 = NULL;
int screen3H = 0;
int screen3W = 0;


ALLEGRO_BITMAP *deadimage = NULL;
ALLEGRO_BITMAP *gameover = NULL;
ALLEGRO_BITMAP *gameoverFlash = NULL;




///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




int pointer = 400;

int main(void)
{
	bool gamePause = false;
	bool gameStart = false;
	int loadDelay = 0;
	bool loadGame = false;
	bool nextLevel = false;
	int cheatTimer = 0;
	bool cheatEnabled = false;
	bool moveR = false;
	bool moveL = false;
	bool moveU = false;
	bool dying = false;

	int imageHeight = 0;
	int imageWidth = 0;
	int temp = 0;
	bool fallOfPipe = false;

	bool fall = false;
	bool inJmpHeight = false;//*******************
	bool fallOfBlock = false;//*******************
	int delay = 0;
	bool jump_h = false;
	bool feet_check = true;
	int jump_cnt = 0;
	bool keys[6] = { false, false, false, false, false,false };
	int const FPS = 60;
	bool Gamerunning = true;
	bool deathsound = true;
	bool gameOverDelay = false;
	bool start = false;


	Projectiles proj[5];
	bool enemycheck = false;



	bool enemycheck2 = false;
	SetEnemies(guys, num_enemies);


	//////////////////////////////////////////////ANIMATION////////////////////////////////////////////////////
	const int maxFrame = 4;
	int currentF = 0;
	int Fcount = 0;
	int FDelay = 6;




	///////////////////////////////////////////////////////////////////////////////////////////////////////////




	int const num_blocks = 200;
	block blocks[num_blocks];



	int const num_pipes = 200;
	Pipe pipes[num_pipes];


	int const num_spikes = 200;
	spike spikes[num_spikes];



	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_BITMAP *image = NULL;
	ALLEGRO_BITMAP *imageRIGHT[maxFrame];
	ALLEGRO_BITMAP *imageLEFT[maxFrame];
	ALLEGRO_BITMAP *imageUP[2];



	if (!al_init())										//initialize Allegro
		return -1;

	display = al_create_display(res_x, res_y);			//create our display object

	if (!display)										//test display object

		return -1;
	al_install_audio();
	al_init_acodec_addon();
	al_init_image_addon();
	al_init_font_addon();
	al_init_ttf_addon();								//allows for text
	al_init_primitives_addon();
	al_install_keyboard();							// allows to work with keyboard keys.
	al_install_mouse();
	al_hide_mouse_cursor(display);
	timer = al_create_timer(1.0 / FPS);
	srand(time(NULL));
	initproj(proj, num_proj);////////////////////////////////////////////////////LUSHEN/////////////////////////////////////////////////////////////



	al_reserve_samples(10);
	shot1 = al_load_sample("shot.wav");
	boom = al_load_sample("boom.wav");
	song = al_load_sample("song.wav");
	jumping = al_load_sample("jump.wav");
	bump = al_load_sample("bump.wav");
	die = al_load_sample("die.wav");
	pause = al_load_sample("pause.wav");

	songInstance = al_create_sample_instance(song);
	al_set_sample_instance_playmode(songInstance, ALLEGRO_PLAYMODE_LOOP);

	al_attach_sample_instance_to_mixer(songInstance, al_get_default_mixer());

	image = al_load_bitmap("8-Bit_Luigi.png");
	image1 = al_load_bitmap("bricks.png");
	image2 = al_load_bitmap("Goomba.png");
	image3 = al_load_bitmap("Koopa_Right.png");
	image4 = al_load_bitmap("Koopa_Left.png");
	image5 = al_load_bitmap("Spike.png");
	imageB = al_load_bitmap("ground.png");

	WALLimage = al_load_bitmap("Luigi4.jpg");//pause screen
	WALL2image = al_load_bitmap("Luigi3.jpg");//start screen


	WALLDimage = al_load_bitmap("Luigi4D.jpg");//pause screen DEMO
	WALL2Dimage = al_load_bitmap("Luigi3D.jpg");//start screen DEMO

	WALLQimage = al_load_bitmap("Luigi4Q.jpg");//pause screen QUIT
	WALL2Qimage = al_load_bitmap("Luigi3Q.jpg");//start screen QUIT

	loadscreen1 = al_load_bitmap("screen1.jpg");
	loadscreen2 = al_load_bitmap("screen2.jpg");
	loadscreen3 = al_load_bitmap("screen3.jpg");
	gameover = al_load_bitmap("gameover.jpg");
	gameoverFlash = al_load_bitmap("gameoverFlash.jpg");


	deadimage = al_load_bitmap("died.png");

	imageRIGHT[0] = al_load_bitmap("LW1.png");
	imageRIGHT[1] = al_load_bitmap("LW2.png");
	imageRIGHT[2] = al_load_bitmap("LW3.png");
	imageRIGHT[3] = al_load_bitmap("LW4.png");

	imageLEFT[3] = al_load_bitmap("LW1.png");
	imageLEFT[2] = al_load_bitmap("LW2.png");
	imageLEFT[1] = al_load_bitmap("LW3.png");
	imageLEFT[0] = al_load_bitmap("LW4.png");

	imageUP[0] = al_load_bitmap("LJ1.png");
	imageUP[1] = al_load_bitmap("LJ2.png");



	bgimage = al_load_bitmap("back1.png");


	image1Width = al_get_bitmap_width(image1);
	image1Height = al_get_bitmap_height(image1);

	image2Width = al_get_bitmap_width(image2);
	image2Height = al_get_bitmap_height(image2);

	image3Width = al_get_bitmap_width(image3);
	image3Height = al_get_bitmap_height(image3);


	image4Width = al_get_bitmap_width(image4);
	image4Height = al_get_bitmap_height(image4);


	image5Width = al_get_bitmap_width(image5);
	image5Height = al_get_bitmap_height(image5);

	imageBWidth = al_get_bitmap_width(imageB);
	imageBHeight = al_get_bitmap_height(imageB);

	imageBGWidth = al_get_bitmap_width(bgimage);
	imageBGHeight = al_get_bitmap_height(bgimage);
	////////////////////////////////////////////////////////////////////
	imageWALLWidth = al_get_bitmap_width(WALLimage);
	imageWALLHeight = al_get_bitmap_height(WALLimage);

	imageWALL2Width = al_get_bitmap_width(WALL2image);
	imageWALL2Height = al_get_bitmap_height(WALL2image);
	///////////////////////////////////////////////////////////////////
	imageWALLDWidth = al_get_bitmap_width(WALLDimage);
	imageWALLDHeight = al_get_bitmap_height(WALLDimage);

	imageWALL2DWidth = al_get_bitmap_width(WALL2Dimage);
	imageWALL2DHeight = al_get_bitmap_height(WALL2Dimage);
	////////////////////////////////////////////////////////////////////////
	imageWALLQWidth = al_get_bitmap_width(WALLQimage);
	imageWALLQHeight = al_get_bitmap_height(WALLQimage);

	imageWALL2QWidth = al_get_bitmap_width(WALL2Qimage);
	imageWALL2QHeight = al_get_bitmap_height(WALL2Qimage);

	screen1W = al_get_bitmap_width(loadscreen1);
	screen1H = al_get_bitmap_height(loadscreen1);

	screen2W = al_get_bitmap_width(loadscreen2);
	screen2H = al_get_bitmap_height(loadscreen2);

	screen3W = al_get_bitmap_width(loadscreen3);
	screen3H = al_get_bitmap_height(loadscreen3);




	imageWidth = al_get_bitmap_width(image);
	imageHeight = al_get_bitmap_height(image);






	//al_set_target_bitmap(image);


	al_set_target_bitmap(al_get_backbuffer(display));
	event_queue = al_create_event_queue();
	ALLEGRO_FONT *font12 = al_load_font("emulogic.ttf", 20, 0);
	ALLEGRO_FONT *font11 = al_load_font("emulogic.ttf", 85, 0);
	ALLEGRO_FONT *font13 = al_load_font("tlpsmb.ttf", 32, 0);
	//allows for fonts...
	al_register_event_source(event_queue, al_get_keyboard_event_source());	//register keyboard to events.
	al_register_event_source(event_queue, al_get_display_event_source(display)); // Register events from display.
	al_register_event_source(event_queue, al_get_mouse_event_source());//register mouse input to events
	al_register_event_source(event_queue, al_get_timer_event_source(timer));//registers timer 

	al_start_timer(timer);

	bool stage = true;
	while (Gamerunning)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if (!deathPause)
			 al_play_sample_instance(songInstance);
	


		if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch (ev.keyboard.keycode)

			{

			case ALLEGRO_KEY_UP:

				if (gameStart){
					if (!deathPause&&!nextLevel)
					{
						fall = false;
						moveU = true;
						moveR = false;
						moveL = false;
						dying = false;

						if (feet_check)
						{
							al_play_sample(jumping, 1.5, 0, 1, ALLEGRO_PLAYMODE_ONCE, foo3);

							feet_check = false;
						}
					}
				}
				else{ if (pointer > 400)pointer -= 50; }
				break;
			case ALLEGRO_KEY_DOWN:
				if (!gameStart){
					if (pointer < 500)
						pointer += 50;
				}break;
			case ALLEGRO_KEY_RIGHT:
				if (!deathPause&&!nextLevel){
					moveR = true;
					moveL = false;
					moveU = false;
					dying = false;
					keys[D] = true;
				}
				break;
			case ALLEGRO_KEY_LEFT:
				if (!deathPause&&!nextLevel)
				{
					moveL = true;
					moveR = false;
					moveU = false;
					dying = false;
					keys[A] = true;
				}
				break;
			case ALLEGRO_KEY_L:
				if (!cheatEnabled)
					 keys[L] = true;
				break;
			case ALLEGRO_KEY_SPACE:
				if (gameStart){
					if (!deathPause&&!nextLevel){
						keys[SPACE] = true;
						shoot(proj, num_proj);
						//if (stage)
					}
				}
				break;
			}



		}
		else if (ev.type == ALLEGRO_EVENT_KEY_UP)
		{
			switch (ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_ESCAPE:

				al_play_sample(pause, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, foo6);
				stage = false;
				if (gamePause)
				{
					gameStart = true;
				}
				gameStart = false;
				break;
			case ALLEGRO_KEY_L:
				keys[L] = false;
				break;

			case ALLEGRO_KEY_UP:

				if (!jump_h&&!feet_check)
				{
					moveU = false;

					fall = true;
				}
				break;

			case ALLEGRO_KEY_RIGHT:
				keys[D] = false;
				moveR = false;
				break;
			case ALLEGRO_KEY_LEFT:
				keys[A] = false;
				moveL = false;
				break;
			case ALLEGRO_KEY_SPACE:
				if (gameStart){
					if (deathPause)
					{
						player.score -= 50;
						player.lives--;
						if (player.lives > 0)
						{

							pos_x = checkpoint;
							ISEEDEADPEOPLE(guys, num_enemies);
							deathPause = false;
							deathsound = true;
						}
						if (player.lives == 0)
						{

							al_play_sample(pause, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, foo6);//SOME GAME OVER MESSSAGE HERE <----------------------------------------------------------------------------------------------------
							stage = false;
							if (gamePause)
							{
								gameStart = true;
							}
							gameStart = false;

							level = 1;

							pos_x = 0;
							checkpoint = 0;
							player.lives = 5;
							gamePause = false;
							shot = false;
							Apocalypse(guys, num_enemies);
							deathPause = false;
							player.score = 0;
							temp = 0;
							gameOverDelay = true;;
						
							//al_draw_scaled_bitmap(loadscreen1, 0, 0, screen1W, screen1H, 0, 0, screen1W, screen1H, 0);
							//al_draw_scaled_bitmap(gameover, 0, 0, 1280, 820, 0, 0, 1280, 820, 0); ------------------this is the game over screen
							//al_draw_scaled_bitmap(gameoverFlash, 0, 0, 1280, 820, 0, 0, 1280, 820, 0); ------------------this is the game over screen with the press space to continue now put a delay and make them flash wherever you put the game over screen
							//al_draw_textf(font11, al_map_rgb(255, 255, 255), 825, 360, 0, "%d", player.lives);
							//SOME LOADING SCREEN HERE <---------------------------------------------------------------------------
						}
						//al_stop_sample(foo);
					}

				}
				else if (gameOverDelay)
				{ 
					gameOverDelay = false;
				}
				else if (!gameStart &&!gameOverDelay)
				{
					if (pointer == 400)
					{
						gameStart = true;
						gamePause = true;
					}
					else if (pointer == 450)
					{//RUN THE DEMO HERE <------------------------------------------------------------------------------------------------------------
						
							if (!start){
								level = 1;
								
									level = 1;
								
									pos_x = 0;
								checkpoint = 0;
								player.lives = 5;
								gamePause = true;
								gameStart = true;
								shot = false;
								Apocalypse(guys, num_enemies);
								deathPause = false;
								player.score = 0;
								temp = 0;
								pointer = 400;
								
							}
					}
					else if (pointer == 500)
					{
						Gamerunning = false;
					}
				}
				break;
			}

		}

		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			Gamerunning = false;
		}


		else if (ev.type == ALLEGRO_EVENT_TIMER){		//timer starting





			if (pos_x > temp)
			{
				player.score++;
				temp = pos_x;
			}



			if (gameStart){

				if (keys[L])//CHEAT <--- +100 LIVES
					 {
					
						cheatTimer++;
					if (cheatTimer == 200)
						 {
					player.lives += 100;
					cheatEnabled = true;
						
							}
					
						}if (!keys[L] && cheatTimer > 0)
						 {
						cheatTimer -= 2;
						if (cheatTimer <= 0){ cheatEnabled = false; }
						}

				// JUMPING....
				if (!feet_check && !jump_h&&!block_limit(blocks, num_blocks)){

					jump(player.jumpspeed);
					jump_cnt += player.jumpspeed;
					if (jump_cnt >= player.j_height || block_limit(blocks, num_blocks))
					{
						jump_h = true;

					}

					if (fall&& jump_cnt > 200)
						jump_h = true;

				}
				if (jump_h&&!feet_check)
				{
					delay++;
					if (delay >= 10)
					{
						jump(-(player.jumpspeed));
						jump_cnt -= player.jumpspeed;
						if (jump_cnt <= 0)
						{
							player.j_height = res_y - 450;
							jump_h = false;
							feet_check = true;

							delay = 0;
						}
						if (checkblock(blocks, num_blocks))
						{

							jump_h = false;
							feet_check = true;
							player.j_height = res_y - blocks[blockNum].y + 250;//something like this
							delay = 0;
							fallOfBlock = true;
							fallOfPipe = false;
						}



						if (checkpipe(pipes, num_pipes))
						{
							jump_h = false;
							feet_check = true;
							player.j_height = res_y - pipes[blockNum].y + 250;
							delay = 0;
							fallOfPipe = true;
							fallOfBlock = false;
						}


					}

				}
				if (feet_check&&keys[D])
					moveR = true;

				if (feet_check&&fallOfPipe&&!checkpipe(pipes, num_pipes) && fallOfPipe)
				{
					delay = 5;
					jump_h = true;
					feet_check = false;
					fallOfPipe = false;
					fallOfBlock = false;

				}
				if (feet_check&&fallOfBlock&&!checkblock(blocks, num_blocks))
				{
					delay = 5;
					jump_h = true;
					feet_check = false;
					fallOfBlock = false;
					fallOfPipe = false;
				}

				//END JUMPING


				// MOVES CHARACTER
				if (box_right(blocks, num_blocks) && pipe_right(pipes, num_pipes))	//***********************************************
					pos_x += keys[D] * player.ms;
				if (pos_x > -200)
				{
					if (box_left(blocks, num_blocks) && pipe_left(pipes, num_pipes))  //***********************************************
						pos_x -= keys[A] * player.ms;
				}

				if (pos_x >= 10100 && level <= 3){

					shot = false;
					Apocalypse(guys, num_enemies);
					pos_x = 0;
					level++;
					nextLevel = true;
					keys[A] = false;
					keys[D] = false;
					temp = 0;
				}
				if (nextLevel)
				{
					delay++;

					if (delay > 200)
					{



						delay = 0;
						nextLevel = false;
					}



				}
				// END MOVES CHARACTER







				//ENEMY MOVING

				if (keys[SPACE])
				{

					update(proj, num_proj);
				}
				if (!enemycheck2 && c >= 0 && c <= 500)
				{
					c += 3;
					if (c >= 500)
					{
						enemycheck2 = true;
						LR = true;
					}
				}
				if (enemycheck2)
				{
					c -= 3;
					if (c <= 0)
					{
						enemycheck2 = false;
						LR = false;
					}
				}


				StartEnemies(guys, num_enemies);

				Collision(proj, num_proj, guys, num_enemies, c);

				//END MOVING ENEMY

				GenerateBG_G();

				HittingPipes(proj, num_proj, num_pipes, pipes);
				HittingBlocks(proj, num_proj, num_blocks, blocks);

				if (CollideEnemy(guys, num_enemies, c) || spikeCollide(spikes, num_spikes))//DEATH OF CHARA
				{
					al_stop_sample_instance(songInstance);
					if (deathsound)
					{

						al_play_sample(die, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, foo5);
						deathsound = false;

					}


					keys[A] = false;
					keys[D] = false;
					deathPause = true;

				}
				if (!deathPause)
				{
					if (!moveL &&!moveR && !moveU && !dying)
						al_draw_scaled_bitmap(imageRIGHT[3], 0, 0, 64, 128, player.x - player.r, player.y - player.r, 64 * 0.6, 128 * 0.6, 0);

					if (moveR)
					{
						if (++Fcount >= FDelay)
						{
							if (++currentF >= maxFrame)
							{
								currentF = 0;
								Fcount = 0;
							}
						}
						if (feet_check)
							al_draw_scaled_bitmap(imageRIGHT[currentF], 0, 0, 64, 128, player.x - player.r, player.y - player.r, 64 * 0.6, 128 * 0.6, 0);
						else
							al_draw_scaled_bitmap(imageUP[1], 0, 0, 64, 128, player.x - player.r, player.y - player.r, 64 * 0.7, 128 * 0.7, 0);
					}
					if (moveL)
					{
						if (++Fcount >= FDelay)
						{
							if (++currentF >= maxFrame)
							{
								currentF = 0;
								Fcount = 0;
							}
						}

						if (feet_check)
							al_draw_scaled_bitmap(imageLEFT[currentF], 0, 0, 64, 128, player.x - player.r, player.y - player.r, 64 * 0.6, 128 * 0.6, 0);
						else
							al_draw_scaled_bitmap(imageUP[1], 0, 0, 64, 128, player.x - player.r, player.y - player.r, 64 * 0.7, 128 * 0.7, 0);
					}

					if (moveU)
					{
						if (!feet_check)
						{
							al_draw_scaled_bitmap(imageUP[1], 0, 0, 64, 128, player.x - player.r, player.y - player.r, 64 * 0.7, 128 * 0.7, 0);
						}
						else
						{
							al_draw_scaled_bitmap(imageRIGHT[3], 0, 0, 64, 128, player.x - player.r, player.y - player.r, 64 * 0.6, 128 * 0.6, 0);
							moveU = false;
						}

					}

				}
				if (deathPause)
				{

					deathDelay++;
					if (deathDelay % 10 == 0)
					{
						al_draw_scaled_bitmap(deadimage, 0, 0, 64, 128, player.x - player.r, player.y - player.r, 64 * 0.6, 128 * 0.6, 0);

					}
				}


				initblock(blocks, num_blocks);
				create(blocks, num_blocks);
				DrawEnemies(guys, num_enemies, c);
				initPipe(pipes, num_pipes);
				createPI(pipes, num_pipes);
				initSpike(spikes, num_spikes);
				createSpike(spikes, num_spikes);



				//al_draw_filled_rectangle(player.x - player.r, player.y + player.r, player.x + player.r, player.feet, al_map_rgb(0, 128, 0));
				//al_draw_filled_rectangle(0, res_y - 50, res_x, res_y, al_map_rgb(139, 69, 19));//Ground		

				//al_draw_filled_circle(player.x, player.y, player.r, al_map_rgb(0, 128, 0));//player
				if (!deathPause){
					//al_draw_scaled_bitmap(image, 0, 0, 64, 128, player.x - player.r, player.y - player.r, 64 * 0.6, 128 * 0.6, 0);

				}

				al_draw_textf(font12, al_map_rgb(200, 0, 0), 30, 20, 0, "LIVES:  %d", player.lives);
				al_draw_textf(font12, al_map_rgb(200, 0, 0), 29, 40, 0, "SCORE:  %d", player.score);
				al_draw_textf(font12, al_map_rgb(210, 0, 0), 29, 60, 0, "POSITION:    %d", pos_x);
				//al_draw_textf(font12, al_map_rgb(210, 0, 0), 29, 80, 0, "g    %d", g);
				//al_draw_textf(font12, al_map_rgb(210, 0, 0), 29, 100, 0, "Width    %d", imageBGWidth);

				if (cheatEnabled)
					al_draw_text(font12, al_map_rgb(255, 0, 0), 200, res_y / 2, 0, "CHEAT ENABLED");
				if (deathPause)
					al_draw_text(font12, al_map_rgb(222, 0, 0), 200, res_y / 2, 0, "PRESS SPACEBAR TO CONTINUE");
				drawproj(proj, num_proj);
				if (nextLevel)
				{

					if (level == 2)
					{
						//al_draw_filled_rectangle(0, 0, res_x, res_y, al_map_rgb(2, 220, 0));//PUT THE PICTURE HERE LUUUUSHHHHHHHHHHHHHHHHH <-----------------------------------------------------------------------------------------------------------------------------
						al_draw_scaled_bitmap(loadscreen2, 0, 0, screen2W, screen2H, 0, 0, screen2W, screen2H, 0);
						al_draw_textf(font11, al_map_rgb(255, 255, 255), 825, 360, 0, "%d", player.lives);
					}
					if (level == 3)

						al_draw_scaled_bitmap(loadscreen3, 0, 0, screen3W, screen3H, 0, 0, screen3W, screen3H, 0);
					al_draw_textf(font11, al_map_rgb(255, 255, 255), 825, 360, 0, "%d", player.lives);
					//al_draw_filled_rectangle(0, 0, res_x, res_y, al_map_rgb(2, 0, 220));//PUT THE PICTURE HERE LUUUUSHHHHHHHHHHHHHHHHH <-----------------------------------------------------------------------------------------------------------------------------
				}
				al_flip_display();

				al_clear_to_color(al_map_rgb(0, 191, 255));

			}
		}

		if (!gameStart){
			if (!gamePause)
			{
				//al_draw_text(font13, al_map_rgb(255, 255, 255),150, 400, 0, "START GAME");
				stage = false;
				start = true;
			}
			if (gamePause)
			{
				stage = false;
				al_stop_sample_instance(songInstance);
				//al_draw_text(font13, al_map_rgb(255, 255, 255), 150, 400, 0, "RESUME GAME");
				start = false;
			}
			//al_draw_text(font13, al_map_rgb(255, 255, 255), 150, 450, 0, "DEMO");
			//al_draw_text(font13, al_map_rgb(255, 255, 255), 150, 500, 0, "END GAME");
			al_draw_text(font12, al_map_rgb(255, 255, 255), 100, pointer, 0, ">");

			if (loadDelay<100)
			{
				loadDelay++;
				loadGame = true;
				//al_draw_filled_rectangle(0, 0, res_x, res_y, al_map_rgb(255, 0, 0));
			}
			else{ loadGame = false; }

			if (gameOverDelay )
			{
				
				al_draw_filled_rectangle(0, 0, res_x, res_y, al_map_rgb(255, 0, 0));//<------------- GAME OVER THING HERE <---------------------------------
			}
			al_flip_display();

			//al_clear_to_color(al_map_rgb(0, 0, 0));
			//al_draw_scaled_bitmap(WALLimage, 0, 0, imageWALLWidth, imageWALLHeight, 0, 0, imageWALLWidth, imageWALLHeight, 0);
			GenerateSTART(start);
		


		}

	}


	for (int i = 0; i < maxFrame; i++)
	{
		al_destroy_bitmap(imageRIGHT[i]);
	}
	al_destroy_sample(shot1);
	al_destroy_sample(boom);
	al_destroy_sample(song);
	al_destroy_sample_instance(songInstance);
	al_destroy_display(display);
}

void resize(int r1){
	player.r = r1;
	player.y = player.feet - (3 * r1);
	box_bounds = player.r * 2 + 10;;
}
void jump(int y){

	player.feet -= y;
	player.y = player.feet - (3 * player.r);
}

//***************************************************************************STAGE CREATORRRR RRAWWRRRR*****************************************************************************************************
void initblock(block B[], int size)
{
	if (level == 1)//STAGE 1
	{


		for (int i = 0; i < size; i++)
		{
			B[i].x = -1000;						//clears stage
			B[i].y = 0;
		}




		B[1].x = 1000;
		for (int i = 1; i < 5; i++)
			B[i + 1].x = B[i].x + box_width + 5;


		B[6].x = 1600;
		for (int i = 6; i < 10; i++)
			B[i + 1].x = B[i].x + box_width + 5;




		B[11].x = 2000;
		B[12].x = B[11].x + box_width + 5;

		for (int i = 0; i < 4; i++)
		{
			B[i].y = 600;
		}


		B[0].x = 1700;
		B[2].x = B[0].x + box_width + 5;
		B[3].x = B[2].x + box_width + 5;
		B[4].x = B[3].x + box_width + 5;
		B[5].x = B[4].x + box_width + 5;
		for (int i = 0; i <= 5; i++)
		{
			B[i].y = 390;
		}

		B[19].x = 4000;
		B[20].x = B[19].x + box_width + 5;


		B[21].x = 4700;
		for (int i = 22; i <= 35; i++)
		{
			B[i].x = B[i - 1].x + box_width + 5;
		}

		for (int i = 19; i <= 20; i++)
		{
			B[i].y = 550;
		}
		for (int i = 21; i <= 35; i++)
		{
			B[i].y = 470;
		}



		B[35].x = 6300;
		B[36].x = B[35].x + box_width + 5;
		B[37].x = B[36].x + box_width + 5;
		B[38].x = B[37].x + box_width + 5;
		B[39].x = B[38].x + box_width + 5;
		B[40].x = B[39].x + box_width + 5;
		B[41].x = B[40].x + box_width + 5;
		for (int i = 35; i <= 41; i++)
		{
			B[i].y = 400;
		}

		B[13].x = 3300;
		B[14].x = B[13].x + box_width + 5;
		B[15].x = B[14].x + box_width + 5;
		B[16].x = 3680;
		B[17].x = B[16].x + box_width + 5;
		B[18].x = B[17].x + box_width + 5;


		for (int i = 13; i <= 15; i++)
		{
			B[i].y = 550;
		}
		for (int i = 16; i <= 18; i++)
		{
			B[i].y = 390;
		}

		//B[41].x = 6200;
		//B[41].y = 550;

		B[42].x = 7000;
		B[42].y = 450;


		B[42].x = 7600;
		B[43].x = B[42].x + box_width + 5;
		for (int i = 42; i <= 43; i++)
		{
			B[i].y = 550;
		}

		B[44].x = 8000;
		B[44].y = 550;


		B[45].x = 8750;
		//B[46].x = B[45].x + box_width + 5;
		B[45].y = 550;
		//B[46].y = 550;

		B[46].x = 9000;
		for (int i = 47; i <= 57; i++)
		{
			B[i].x = B[i - 1].x + box_width + 5;
		}

		for (int i = 47; i <= 57; i++)
		{
			B[i].y = 400;
		}



	}//END OF STAGE 1


	if (level == 2)
	{//START OF STAGE2
		for (int i = 0; i < size; i++)
		{
			B[i].x = -1000;						//clears stage
			B[i].y = 0;
		}



		B[0].x = 1450;
		B[0].y = 550;

		B[1].x = 1750;				B[1].y = 350;
		B[2].x = 1800;				B[2].y = 350;

		B[3].x = 3650;				B[3].y = 500;
		B[4].x = 3700;				B[4].y = 500;
		B[5].x = 5200;				B[5].y = 450;
		B[6].x = 5250;				B[6].y = 450;
		B[7].x = 5500;				B[7].y = 300;

		B[8].x = 3900;
		for (int i = 9; i <= 14; i++)
		{
			B[i].x = B[i - 1].x + box_width + 5;
		}

		for (int i = 9; i <= 14; i++)
		{
			B[i].y = 350;
		}

		B[15].x = 6400;
		for (int i = 16; i <= 20; i++)
		{
			B[i].x = B[i - 1].x + box_width + 5;
		}

		for (int i = 16; i <= 20; i++)
		{
			B[i].y = 400;
		}

		B[21].x = 7000;				B[21].y = 600;
		B[22].x = 7050;				B[22].y = 600;
		B[23].x = 7100;				B[23].y = 600;
		B[24].x = 7300;				B[24].y = 430;
		B[25].x = 8000;				B[25].y = 600;
		B[26].x = 8050;				B[26].y = 600;
		B[27].x = 8300;				B[27].y = 450;
		B[28].x = 8350;				B[28].y = 450;
		B[29].x = 9300;				B[29].y = 550;
		B[30].x = 9350;				B[30].y = 550;
		B[31].x = 9595;	            B[31].y = 300;
		B[32].x = 9400;				B[32].y = 550;
		B[33].x = 9550;				B[33].y = 600;
		B[34].x = 9600;				B[34].y = 600;
		B[35].x = 9650;	            B[35].y = 300;
		//B[36].x = 9700;	            B[36].y = 300;



	}//END OF STAGE 2 




	if (level == 3)//STAGE 3
	{


		for (int i = 0; i < size; i++)
		{
			B[i].x = -1000;						//clears stage
			B[i].y = 0;
		}


		int count = 0;
		for (int i = 1500; i <= 2500; i += box_width + 5)
		{
			B[count].x = i;

			if (i > 1600 && i < 2000)
				B[count].y = 550;
			count++;

			if (i >= 2000 && i <= 2500)                             //FALLS THROUGH THESE BLOCKS !!!!!!!!! 3RD SET (HIGHEST)
				B[count].y = 330;
		}

		int countA = 0;
		for (int i = 1120; i <= 1440; i += box_width + 5)
		{
			B[count].x = i;
			B[count].y = 350;
			count++;
		}



		B[0].x = 1000;				B[0].y = 250;
		B[1].x = 1060;				B[1].y = 300;
		B[30].x = 3300;				B[30].y = 400;
		B[31].x = 3360;				B[31].y = 450;
		B[32].x = 3420;				B[32].y = 500;
		B[33].x = 3470;				B[33].y = 500;
		B[34].x = 3520;				B[34].y = 500;
		B[35].x = 3570;				B[35].y = 500;
		B[36].x = 3300;				B[36].y = res_y - 55;
		B[37].x = 3360;				B[37].y = res_y - 105;

		B[38].x = 3420;
		for (int i = 38; i <= 51; i++)
		{
			B[i].x = B[i - 1].x + box_width + 5;
		}

		for (int i = 38; i <= 51; i++)
		{
			B[i].y = res_y - 155;
		}

		B[52].x = 3950;				B[52].y = 400;
		B[53].x = 4010;				B[53].y = 400;
		B[54].x = 4500;	            B[54].y = 550;
		B[55].x = 4550;				B[55].y = 550;
		B[56].x = 4600;				B[56].y = 550;

		B[57].x = 5100;
		for (int i = 58; i <= 62; i++)
		{
			B[i].x = B[i - 1].x + box_width + 5;
		}

		for (int i = 58; i <= 62; i++)
		{
			B[i].y = 410;
		}


		B[63].x = 5300;
		for (int i = 64; i <= 67; i++)
		{
			B[i].x = B[i - 1].x + box_width + 5;
		}

		for (int i = 64; i <= 67; i++)
		{
			B[i].y = 650;
		}




		B[68].x = 5660;				B[68].y = 760;
		B[69].x = 5600;	            B[69].y = 710;
		B[70].x = 5800;				B[70].y = 450;


		B[71].x = 6350;
		for (int i = 72; i <= 74; i++)
		{
			B[i].x = B[i - 1].x + box_width + 5;
		}

		for (int i = 72; i <= 74; i++)
		{
			B[i].y = 500;
		}


		B[78].x = 6250;
		for (int i = 74; i <= 76; i++)
		{
			B[i].x = B[i - 1].x + box_width + 5;
		}

		for (int i = 74; i <= 76; i++)
		{
			B[i].y = 250;
		}
		B[78].x = 6470; B[78].y = 190;
		B[79].x = 6410; B[79].y = 140;
		B[80].x = 7100; B[80].y = 550;
		B[81].x = 7430; B[81].y = 350;

		B[91].x = 7700; B[91].y = 450;
		B[92].x = 7760; B[92].y = 450;
		B[93].x = 7820; B[93].y = 450;
		B[94].x = 7880; B[94].y = 450;

		B[82].x = 8000;
		for (int i = 83; i <= 90; i++)
		{
			B[i].x = B[i - 1].x + box_width + 5;
		}

		for (int i = 83; i <= 90; i++)
		{
			B[i].y = 300;
		}

		B[95].x = 3100; B[95].y = 550;
		B[96].x = 9000; B[96].y = 760;
		B[97].x = 9060; B[97].y = 700;
		B[131].x = 8700; B[131].y = 500;
		B[132].x = 8640; B[132].y = 500;


		B[98].x = 9060;
		for (int i = 99; i <= 104; i++)
		{
			B[i].x = B[i - 1].x + box_width + 5;
		}

		for (int i = 99; i <= 104; i++)
		{
			B[i].y = 640;
		}


		B[105].x = 9700;
		for (int i = 106; i <= 113; i++)
		{
			B[i].x = B[i - 1].x + box_width + 5;
		}

		for (int i = 106; i <= 113; i++)
		{
			B[i].y = 640;
		}
		B[113].x = 10180; B[113].y = 700;
		B[114].x = 10240; B[114].y = 760;


		B[116].x = 9200;
		for (int i = 117; i <= 128; i++)
		{
			B[i].x = B[i - 1].x + box_width + 5;
		}

		for (int i = 117; i <= 128; i++)
		{
			B[i].y = 350;
		}
		B[129].x = 9480; B[129].y = 700;
		B[130].x = 9540; B[130].y = 760;
	}//END OF STAGE 3
}
void initPipe(Pipe pipes[], int size)
{
	if (level == 1)//STAGE 1
	{

		for (int i = 0; i < size; i++)
		{
			pipes[i].x = 0;						//clears stage
			pipes[i].y = 0;
		}



		pipes[0].x = 550;
		pipes[0].y = 650;

		pipes[1].x = 1300;
		pipes[1].y = 550;

		pipes[2].x = 2200;
		pipes[2].y = 550;

		pipes[3].x = 3100;
		pipes[3].y = 650;

		pipes[4].x = 4300;
		pipes[4].y = 300;

		//pipes[5].x = 6500;
		//pipes[5].y = 550;

		pipes[6].x = 5880;
		pipes[6].y = 550;

		pipes[7].x = 7040;
		pipes[7].y = 550;

		//pipes[8].x = 7200;
		//pipes[8].y = 550;

		pipes[9].x = 8200;
		pipes[9].y = 550;
	}//STAGE 1


	if (level == 2)
	{//START OF STAGE2
		for (int i = 0; i < size; i++)
		{
			pipes[i].x = 0;						//clears stage
			pipes[i].y = 0;
		}

		pipes[0].x = 3200;         	pipes[0].y = 650;
		pipes[1].x = 4800;			pipes[1].y = 650;
		pipes[2].x = 6000;			pipes[2].y = 450;
		pipes[3].x = 7700;			pipes[3].y = 550;
		pipes[4].x = 8800;			pipes[4].y = 450;
		pipes[5].x = 10000;			pipes[5].y = 550;



	}//END OF STAGE 2


	if (level == 3)//STAGE 3
	{

		for (int i = 0; i < size; i++)
		{
			pipes[i].x = 0;						//clears stage
			pipes[i].y = 0;
		}

		pipes[0].x = 2900;         	pipes[0].y = 250;      //CHANGE Y TO 250 ONCE BLOCKS ARE FIXED      
		pipes[1].x = 4800;			pipes[1].y = 650;
		pipes[2].x = 6000;			pipes[2].y = 400;


		pipes[3].x = 6850;			pipes[3].y = 550;
		/*pipes[4].x = 8800;			pipes[4].y = 450;*/

		pipes[5].x = 7730;			pipes[5].y = 550;
		//pipes[6].x = 8800;			pipes[6].y = 450;



	}//END OF STAGE 3

}
void initSpike(spike spikes[], int size)
{
	if (level == 1)//STAGE 1
	{
		for (int i = 0; i < size; i++)
		{
			spikes[i].x = -1000;						//clears stage
			spikes[i].y = 1000;
			spikes[i].d = false;
			spikes[i].r = false;
			spikes[i].l = false;
		}



		for (int i = 0; i < size; i++)
			spikes[i].y = 720;


		for (int i = 0; i < size; i++)
			spikes[i].y = 720;


		spikes[0].x = 400;
		spikes[1].x = 850;

		spikes[2].x = 950;

		spikes[3].x = 1200;
		spikes[4].x = 2000;
		spikes[5].x = 2500;
		spikes[6].x = 3305;
		spikes[7].x = 3400;
		spikes[8].x = 3600;
		spikes[9].x = 3700;
		spikes[10].x = 3800;
		spikes[11].x = 850;
		spikes[12].x = 950;
		spikes[13].x = 1200;
		spikes[14].x = 2000;
		spikes[15].x = 1820;
		spikes[6].y = 445;



		/*int count = 16;
		for (int i = 6000; i <= 10000; i += spike_width * 2)
		if ((i < 7030 || i >7030 + pipe_width) && (i < 8200 || i >= 8200 + pipe_width))
		{
		spikes[count].x = i;
		spikes[count].y = 720;
		count++;

		}*/


	}//END OF STAGE 1

	if (level == 2)
	{//START OF STAGE2

		for (int i = 0; i < size; i++)
		{
			spikes[i].x = -1000;						//clears stage
			spikes[i].y = 1000;
			spikes[i].d = false;
			spikes[i].r = false;
			spikes[i].l = false;
		}

		int count = 0;
		for (int i = 1500; i <= 2500; i += spike_width * 2)
			//if ((i < 7030 || i >7030 + pipe_width) && (i < 8200 || i >= 8200 + pipe_width))
		{
			spikes[count].x = i;
			spikes[count].y = 720;
			count++;

		}


		int A = 25;
		for (int i = 4250; i <= 10000; i += spike_width * 2)
		if ((i <= 4790 || i >= 4800 + pipe_width) && (i <= 6000 || i >= 6000 + pipe_width) && (i <= 7700 || i >= 7700 + pipe_width) && (i <= 8800 || i >= 8800 + pipe_width) && (i <= 10000 || i >= 10000 + pipe_width))

		{

			spikes[A].x = i;
			spikes[A].y = 720;
			A++;
		}
		////int B = 60;
		////for (int i = 7700+pipe_width; i <= 8800; i += spike_width * 2)
		////	//if ((i < 7030 || i >7030 + pipe_width) && (i < 8200 || i >= 8200 + pipe_width))
		////{
		////	spikes[B].x = i;
		////	spikes[B].y = 720;
		////	B++;

		////}
		////int c = 80;
		////for (int i = 8800+ pipe_width; i <= 9950; i += spike_width * 2)
		////	//if ((i < 7030 || i >7030 + pipe_width) && (i < 8200 || i >= 8200 + pipe_width))
		////{
		////	spikes[c].x = i;
		////	spikes[c].y = 720;
		////	c++;

		////}


		spikes[0].x = 3720;
		spikes[0].y = 395;

		spikes[1].x = 7118;
		spikes[1].y = 495;

		spikes[2].x = 9425;
		spikes[2].y = 445;

		spikes[3].x = 9490; spikes[3].l = true;
		spikes[3].y = 280;

	}//END OF STAGE 2




	if (level == 3)//STAGE 3
	{
		for (int i = 0; i < size; i++)
		{
			spikes[i].x = -1000;						//clears stage
			spikes[i].y = 1000;
			spikes[i].d = false;
			spikes[i].r = false;
			spikes[i].l = false;
		}



		spikes[0].y = 528;
		spikes[0].x = 1518; spikes[0].l = true;
		spikes[1].x = 1800;
		spikes[1].y = 445;
		spikes[2].x = 1400; spikes[2].d = true;
		spikes[2].y = 390;
		spikes[3].x = 2108; spikes[3].y = 370; spikes[3].d = true;
		spikes[4].x = 2155; spikes[4].y = 590; spikes[4].r = true;
		spikes[5].x = 3370; spikes[5].y = 345;



		int count = 6;
		for (int i = 3600; i <= 4210; i += spike_width * 2)
			//if ((i < 7030 || i >7030 + pipe_width) && (i < 8200 || i >= 8200 + pipe_width))
		{
			spikes[count].x = i;
			spikes[count].y = 560;
			count++;

		}




		spikes[25].x = 4560; spikes[25].y = 445;
		//	spikes[26].x = 2000 ; spikes[26].y = 315; spikes[26].l = true;
		spikes[27].x = 4950; spikes[27].y = spikes[28].y = spikes[29].y = spikes[30].y = res_y - 100;
		spikes[28].x = 5000;
		spikes[29].x = 5050;
		spikes[30].x = 5100;
		spikes[31].x = 5058; spikes[31].y = 390; spikes[31].l = true;
		spikes[32].x = 5365; spikes[32].y = 545;

		int  count1 = 33;
		for (int i = 6000 + pipe_width; i <= 7700; i += spike_width * 2)
		if ((i < 7700 || i >= 7700 + pipe_width) && (i < 6850 || i >= 6850 + pipe_width))
		{
			spikes[count1].x = i;
			spikes[count1].y = 720;
			count1++;
		}


		spikes[80].x = 6538; spikes[80].y = 290; spikes[80].d = true;
		spikes[81].x = 7705; spikes[81].y = 345;
		spikes[82].x = 7895; spikes[82].y = 345;
		spikes[83].x = 7955; spikes[83].y = 280; spikes[83].l = true;
		spikes[84].x = 8200; spikes[84].y = 195;
		spikes[85].x = 8400; spikes[85].y = 195;
		spikes[86].x = 9150; spikes[86].y = 535;
		spikes[87].x = 9065; spikes[87].y = 593;
		spikes[88].x = 9400; spikes[88].y = 535;
		spikes[89].x = 9800; spikes[89].y = 535;
		spikes[90].x = 10000; spikes[90].y = 535;
		spikes[91].x = 9550; spikes[91].y = 390;  spikes[91].d = true;
		spikes[92].x = 9610; spikes[92].y = 390; spikes[92].d = true;
		spikes[93].x = 9670; spikes[93].y = 390; spikes[93].d = true;
		spikes[94].x = 9490; spikes[94].y = 595;
		spikes[95].x = 9300; spikes[95].y = 390; spikes[95].d = true;
		spikes[96].x = 8720; spikes[96].y = 395;
		spikes[97].x = 9550; spikes[97].y = 653;
		//*/
	}//END OF STAGE 3

}
void CreateEnemies(enemies guys[], int size, int counter){
	if (level == 1)
	{

		for (int i = 0; i < size; i++){
			guys[i].x = -10000;						//clears stage
			guys[i].y = -1000;
		}


		guys[0].x = 660; guys[0].y = 550;

		guys[1].x = 1410;
		guys[2].x = 1510;
		guys[21].x = 2490;
		guys[3].x = 2220;          //3050
		guys[4].x = 3370;
		guys[5].x = 4570;         //5150
		guys[6].x = 4470;
		guys[7].x = 4970;
		guys[8].x = 5880;
		guys[9].x = 6180;
		guys[10].x = 7250;
		guys[11].x = 7580;
		guys[12].x = 9020;
		guys[13].x = 9930;
		guys[14].x = 10130;
		guys[15].x = 11130;
		guys[16].x = 12035;
		guys[17].x = 12985;
		guys[18].x = 13685;
		guys[19].x = 14585;
		//guys[20].x = guys[19].x + 200;


		for (int i = 1; i < size; i++)
		{
			guys[i].y = res_y - 115;
		}

		guys[1].y = 450;
		//guys[2].y = 350;
		guys[3].y = 400;
		guys[6].y = 380;
		guys[12].y = 280;
		guys[9].y = 280;
		guys[8].y = 500;

	}//END OF STAGE 



	if (level == 2)
	{//START OF STAGE2

		for (int i = 0; i < size; i++){
			guys[i].x = -10000;						//clears stage
			guys[i].y = -1000;
		}

		guys[0].x = 500;				guys[0].y = res_y - 115;
		guys[1].x = 1000;               guys[1].y = res_y - 115;
		guys[2].x = 2100;				guys[2].y = 550;
		guys[3].x = 3370;				guys[3].y = res_y - 115;
		guys[4].x = 2650;				guys[4].y = res_y - 115;
		guys[5].x = 3770;				guys[5].y = 660;
		guys[6].x = 4350;				guys[6].y = 350;
		guys[7].x = 5000;				guys[7].y = 550;
		guys[8].x = 5800;				guys[8].y = 390;
		guys[9].x = 9500;				guys[9].y = 495;
		guys[10].x = 8300;				guys[10].y = 350;
		guys[11].x = 8000;				guys[11].y = 500;
		guys[12].x = 6800;				guys[12].y = 400;
		guys[13].x = 9500;				guys[13].y = 360;
		guys[14].x = 8900;				guys[14].y = 400;
		//	guys[15].x = 9540;				guys[15].y = res_y-115;
		/*	guys[16].x = 500;				guys[16].y = 500;
		guys[17].x = 500;				guys[17].y = 500;
		guys[18].x = 500;				guys[18].y = 500;
		*/





	}//END OF STAGE 2



	if (level == 3)//STAGE 3
	{

		for (int i = 0; i < size; i++){
			guys[i].x = -10000;						//clears stage
			guys[i].y = -1000;
		}



		guys[0].x = 500;				guys[0].y = res_y - 115;
		guys[1].x = 2400;               guys[1].y = res_y - 115;
		guys[2].x = 1500;				guys[2].y = 340;
		guys[3].x = 10100;				guys[3].y = 550;
		guys[4].x = 8500;				guys[4].y = res_y - 115;
		guys[5].x = 3450;				guys[5].y = 400;
		guys[6].x = 3850;				guys[6].y = 300;
		guys[7].x = 5000;				guys[7].y = 455;
		guys[8].x = 5160;				guys[8].y = res_y - 115;
		guys[9].x = 6850;				guys[9].y = 465;
		guys[10].x = 7000;				guys[10].y = 250;
		guys[11].x = 8100;				guys[11].y = 170;
		guys[12].x = 8800;				guys[12].y = 395;
		guys[15].x = 9650;				guys[15].y = res_y - 115;
		guys[16].x = 9200;				guys[16].y = 250;
		guys[17].x = 9550;				guys[17].y = 470;
	}//END OF STAGE 3
}


//*************************************************************************************************************************************************************************************************




//***************************************************************BLOCKS*******************************************************************************

void create(block B[], int size)

{

	for (int i = 0; i < size; i++)
		al_draw_scaled_bitmap(image1, 0, 0, image1Width, image1Height, ((B[i].x - pos_x)), B[i].y - box_width, image1Width*0.07, image1Height*0.07, 0);
}
bool block_limit(block B[], int size)
{
	bool check = false;
	for (int i = 0; i < size; i++)
	{
		for (int j = -player.r; j < box_bounds * 2 - player.r + 8; j++)
		{
			if (B[i].x == player.x - j + pos_x)
			{
				for (int k = 0; k < player.jumpspeed; k++)
				{
					if ((B[i].y + box_width) == (player.y + player.r) + k + 5)
					{
						check = true;
					}
				}
			}
		}
	}
	return check;

}
bool checkblock(block B[], int size)
{
	bool check = false;
	for (int i = -10; i < size; i++)
	{
		for (int j = -player.r; j < box_bounds * 2 - player.r + 3; j++)
		{
			if (B[i].x == player.x - j + pos_x)
			{
				for (int k = 0; k < player.jumpspeed; k++)
					if (player.feet == B[i].y + k - (player.jumpspeed * 9))
					{
					check = true;
					blockNum = i;
					}
			}

		}
	}
	return check;
}
bool box_right(block B[], int size)
{

	bool check = true;
	for (int i = 0; i < size; i++)
	{
		for (int k = 0; k < 10; k++)
			if (B[i].x == player.x + player.r + pos_x - k)
			{
			for (int j = 0; j<box_width; j++)
				if (player.feet>B[i].y - j && (player.y + player.r) < B[i].y)
					check = false;

			}
	}
	return check;
}
bool box_left(block B[], int size)
{

	bool check = true;
	for (int i = 0; i < size; i++)
	{
		for (int k = 0; k < 10; k++)
			if (B[i].x + box_width == player.x - player.r + pos_x + k)
			{
			for (int j = 0; j<box_width; j++)
				if (player.feet>B[i].y - j && (player.y + player.r) < B[i].y)
					check = false;

			}
	}
	return check;
}
bool noblock(block B[], int size)
{
	bool check = false;
	for (int i = 0; i < size; i++)
	{
		for (int j = -player.r; j < box_bounds + 10 - player.r; j++)
		{
			if (B[i].x == player.x - j + pos_x)
			{
				check = true;
			}
		}
	}
	return check;
}






//**********************************************************PIPES***************************************************************************************

void createPI(Pipe pipes[], int size)
{
	for (int i = 0; i <= 10; i++)
	{

		al_draw_rectangle(pipes[i].x - pos_x, res_y - 50, pipes[i].x + pipe_width - pos_x, pipes[i].y, al_map_rgb(0, 100, 0), 5);//main pipe outline 
		al_draw_filled_rectangle(pipes[i].x - pos_x, res_y - 50, pipes[i].x + pipe_width - pos_x, pipes[i].y, al_map_rgb(28, 175, 28));//main pipe

		//////////////////////////////////////////////////////////SHADES MAIN///////////////////////////////////////////////////////////////////////////////////////
		al_draw_filled_rectangle(pipes[i].x - pos_x + 75, res_y - 50, pipes[i].x + 95 - pos_x, pipes[i].y, al_map_rgb(50, 205, 50));//RHS//main pipe shade light green
		al_draw_filled_rectangle(pipes[i].x - pos_x + 100, res_y - 50, pipes[i].x + 108 - pos_x, pipes[i].y, al_map_rgb(50, 205, 50));//RHS//main pipe shade light green

		al_draw_filled_rectangle(pipes[i].x - pos_x, res_y - 50, pipes[i].x + 25 - pos_x, pipes[i].y, al_map_rgb(10, 138, 10));//main pipe shade darker light green
		al_draw_filled_rectangle(pipes[i].x - pos_x + 30, res_y - 50, pipes[i].x + 35 - pos_x, pipes[i].y, al_map_rgb(10, 138, 10));
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



		al_draw_rectangle(pipes[i].x - 20 - pos_x, pipes[i].y, pipes[i].x + pipe_width + 20 - pos_x, pipes[i].y + 50, al_map_rgb(0, 100, 0), 5);//upper head outline 
		al_draw_filled_rectangle(pipes[i].x - 20 - pos_x, pipes[i].y, pipes[i].x + pipe_width + 20 - pos_x, pipes[i].y + 50, al_map_rgb(28, 175, 28));//upper head 



		//////////////////////////////////////////////////////////////SHADES UPPER//////////////////////////////////////////////////////////
		al_draw_filled_rectangle(pipes[i].x - pos_x + 85, pipes[i].y, pipes[i].x + 105 - pos_x, pipes[i].y + 50, al_map_rgb(50, 205, 50));//upper head light green
		al_draw_filled_rectangle(pipes[i].x - pos_x + 110, pipes[i].y, pipes[i].x + 118 - pos_x, pipes[i].y + 50, al_map_rgb(50, 205, 50));//upper head light green

		al_draw_filled_rectangle(pipes[i].x - pos_x - 20, pipes[i].y, pipes[i].x + 10 - pos_x, pipes[i].y + 50, al_map_rgb(10, 138, 10));
		al_draw_filled_rectangle(pipes[i].x - pos_x + 15, pipes[i].y, pipes[i].x + 20 - pos_x, pipes[i].y + 50, al_map_rgb(10, 138, 10));

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	}
}
bool checkpipe(Pipe pipes[], int size)
{
	bool check = false;
	for (int i = 0; i < size; i++)
	{
		for (int j = -player.r - 30; j < pipe_bounds * 2 - 50 - (player.r + 8); j++)
		{
			if (pipes[i].x == (player.x) - j + pos_x)
			{
				for (int k = 0; k < player.jumpspeed; k++)
					if (player.feet == pipes[i].y + k - (player.jumpspeed))
					{
					check = true;
					blockNum = i;
					}
			}
		}
	}
	return check;
}
bool pipe_right(Pipe pipes[], int size)
{

	bool check = true;
	for (int i = 0; i < size; i++)
	{
		for (int k = 0; k < 10; k++)
			if (pipes[i].x == player.x + player.r + pos_x + k + 20)
			{
			for (int j = 0; j<pipe_width; j++)
				if (player.feet>pipes[i].y + j && (player.y + player.r) < res_y - 50)
					check = false;

			}
	}
	return check;
}
bool pipe_left(Pipe pipes[], int size)
{

	bool check = true;
	for (int i = 0; i < size; i++)
	{
		for (int k = 0; k < 10; k++)
			if (pipes[i].x + pipe_width == player.x - player.r + pos_x + k - 20)
			{
			for (int j = 0; j<pipe_width; j++)
				if (player.feet>pipes[i].y + j && (player.y + player.r) <  res_y - 50)
					check = false;

			}
	}
	return check;
}



//*********************************************************SPIKES**************************************************************************************



void createSpike(spike spikes[], int size)
{

	for (int i = 0; i < size; i++)
	{
		float degree = 90;
		if (!spikes[i].r&&!spikes[i].l)
			al_draw_scaled_bitmap(image5, 0, 0, image5Width, image5Height, spikes[i].x + spike_width - pos_x - 25, spikes[i].y - spike_height + 15, image5Width*0.8, image5Height*0.8, spikes[i].d * 2);
		//al_draw_filled_triangle(spikes[i].x - pos_x, spikes[i].y + spike_height, spikes[i].x + spike_width - pos_x, spikes[i].y, spikes[i].x + 2 * spike_width - pos_x, spikes[i].y + spike_height, al_map_rgb(255, 0, 0));
		//al_draw_filled_triangle(spikes[],)
		else
			al_draw_rotated_bitmap(image5, image5Width, 0 / 2, spikes[i].x + spike_width - pos_x - 25, spikes[i].y - spike_height + 15, (spikes[i].l*degree * 2 + degree)*3.1415 / 180, 0);

	}
}
bool spikeCollide(spike spikes[], int size)
{

	bool dead = false;

	for (int i = 0; i < size; i++)
	{
		for (int j = 10 - (spikes[i].r * 100); j < 3 * spike_width + 8 + (spikes[i].l * 60) - (spikes[i].r * 40); j++)
		{
			if (spikes[i].x == player.x + player.r + pos_x - j)
			{
				for (int j = 0; j<spike_width; j++)
					if (player.feet>spikes[i].y + j - (spikes[i].l * 20) - (spikes[i].r * 40) && (player.y + player.r) < spikes[i].y + 75 - (spikes[i].l * 50) - (spikes[i].r * 100))
					{

					dead = true;
					//al_stop_sample_instance(songInstance);

					}
			}
		}
	}
	return dead;
}



//***************************************************PROJECTILES********************************************************************************************



void initproj(Projectiles proj[], int size)
{
	for (int i = 0; i < size; i++)
	{
		proj[i].ID = PROJECTILES;
		proj[i].speed = 10;
		proj[i].live = false;
	}
}
void drawproj(Projectiles proj[], int size)
{
	for (int i = 0; i < size; i++)
	{
		if (proj[i].live)
		{
			al_draw_filled_circle(proj[i].x, proj[i].y, 5, al_map_rgb(0, 0, 0));

		}
	}
}
void shoot(Projectiles proj[], int size){
	al_play_sample(shot1, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, foo);

	for (int i = 0; i < size; i++)
	{
		if (!proj[i].live)
		{
			proj[i].x = player.x + 20;
			proj[i].y = player.y;
			proj[i].live = true;
			break;
		}

	}
}
void update(Projectiles proj[], int size){


	for (int i = 0; i < size; i++)
	{
		if (proj[i].live)
		{
			proj[i].x += proj[i].speed;

			if (proj[i].x > res_x)
			{
				proj[i].live = false;

			}
		}
	}
}
void HittingPipes(Projectiles proj[], int size, int sizeP, Pipe pipes[])
{
	for (int i = 0; i < sizeP; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (proj[j].live)
			{
				for (int k = 0; k < 11; k++)
				{
					if (proj[j].x == (pipes[i].x - 20 - pos_x + k) && proj[j].y > pipes[i].y)
					{
						al_play_sample(bump, 1.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, foo4);
						proj[j].live = false;

					}
				}
			}
		}
	}
}
void HittingBlocks(Projectiles proj[], int size, int sizeB, block blocks[])
{
	for (int i = 0; i < sizeB; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (proj[j].live)
			{
				for (int k = 0; k < 11; k++)
				{
					if (proj[j].x == (blocks[i].x - (pos_x)+k) && proj[j].y >blocks[i].y - box_width && proj[j].y < blocks[i].y)
					{
						al_play_sample(bump, 1.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, foo4);
						proj[j].live = false;
					}
				}
			}
		}
	}
}




//***************************************************ENEMIES********************************************************************************************

void SetEnemies(enemies guys[], int size)
{
	for (int i = 0; i < size; i++)
	{
		guys[i].ID = ENEMY;
		guys[i].alive = false;
		guys[i].boundx = 25;
		guys[i].boundy = 25;
	}
}
void DrawEnemies(enemies guys[], int size, int counter)
{
	for (int i = 0; i < size; i++)
	{
		if (guys[i].alive)
		{
			if (guys[i].y >= 705)
			{
				al_draw_scaled_bitmap(image2, 0, 0, image2Width, image2Height, guys[i].x - pos_x + counter - 65, guys[i].y - 20, image2Width*0.11, image2Height*0.11, 0);
				//al_draw_filled_circle(guys[i].x - pos_x + counter, guys[i].y, 25, al_map_rgb(0, 0, 0));

			}
			if (guys[i].y < 705)
			{
				if (!LR)
				{

					al_draw_scaled_bitmap(image3, 0, 0, image3Width, image3Height, (guys[i].x - pos_x + counter) - 30, guys[i].y - 40, image3Width*0.7, image3Height*0.7, 0);
					//al_draw_filled_circle(guys[i].x - pos_x + counter, guys[i].y, 25, al_map_rgb(0, 0, 0));
				}
				else
				{
					al_draw_scaled_bitmap(image4, 0, 0, image4Width, image4Height, (guys[i].x - pos_x + counter) - 30, guys[i].y - 40, image4Width*0.7, image4Height*0.7, 0);
					//al_draw_filled_circle(guys[i].x - pos_x + counter, guys[i].y, 25, al_map_rgb(0, 0, 0));
				}
			}
		}


	}
}
void StartEnemies(enemies guys[], int size)
{


	for (int i = 0; i < size; i++)
	{
		if (!guys[i].alive)
		{
			if (!shot)
			{
				guys[i].alive = true;
				CreateEnemies(guys, num_enemies, c);
				break;
			}
		}
	}
}
void Collision(Projectiles proj[], int sizeP, enemies guys[], int sizeE, int counter)
{
	for (int i = 0; i < sizeP; i++)
	{
		if (proj[i].live)
		{
			for (int j = 0; j < sizeE; j++)
			{
				if (guys[j].alive)
				{
					if (proj[i].x >((guys[j].x - pos_x + counter) - guys[j].boundx) &&
						proj[i].x<((guys[j].x - pos_x + counter) + guys[j].boundx) && proj[i].y>(guys[j].y - guys[j].boundy - 10) && proj[i].y < (guys[j].y + guys[j].boundy))
					{

						al_play_sample(boom, 1.6, 0, 1, ALLEGRO_PLAYMODE_ONCE, foo1);
						proj[i].live = false;
						guys[j].alive = false;
						shot = true;
						player.score += 100;

					}
				}
			}
		}
	}
}
bool CollideEnemy(enemies guys[], int size, int counter)
{

	bool dead = false;
	for (int i = 0; i < size; i++)
	{
		if (guys[i].alive)
		{
			if (((guys[i].x - pos_x + counter) - guys[i].boundx) < (player.x + player.r) && (guys[i].x - pos_x + counter) + guys[i].boundx > (player.x - player.r) && (guys[i].y - guys[i].boundy)<(player.y + 3 * player.r) && (guys[i].y + guys[i].boundy)>(player.y - player.r))
			{

				al_stop_sample_instance(songInstance);
				dead = true;

			}
		}
	}return dead;
}
void ISEEDEADPEOPLE(enemies guys[], int size)
{

	for (int i = 0; i < size; i++)
		guys[i].alive = true;
}



void Apocalypse(enemies guys[], int size){
	for (int i = 0; i < size; i++)
	{
		guys[i].alive = false;
	}

}

//***********************************************************************************************************************************************
void GenerateBG_G()
{
	al_draw_scaled_bitmap(bgimage, 0, 0, imageBGWidth + 1250, imageBGHeight, 0 - 200 - pos_x, 0, imageBGWidth, imageBGHeight, 0);
	al_draw_scaled_bitmap(imageB, 0, 0, imageBWidth, imageBHeight, (1280 * 0) - 200 - pos_x, res_y - 50, imageBWidth, imageBHeight, 0);

	for (int i = 0; i <num_bg; i++)
	{

		al_draw_scaled_bitmap(bgimage, 0, 0, imageBGWidth, imageBGHeight, (1280 * i) - pos_x, 0, imageBGWidth, imageBGHeight, 0);


	}

	for (int i = 0; i < num_ground; i++)
	{

		al_draw_scaled_bitmap(imageB, 0, 0, imageBWidth, imageBHeight, (1280 * i) - pos_x, res_y - 50, imageBWidth, imageBHeight, 0);
	}


}
void GenerateSTART(bool check)
{
	if (check)
	{


		if (pointer == 400)
			al_draw_scaled_bitmap(WALL2image, 0, 0, imageWALL2Width, imageWALL2Height, 0, 0, imageWALL2Width, imageWALL2Height, 0);//start screen
		if (pointer == 450)
			al_draw_scaled_bitmap(WALL2Dimage, 0, 0, imageWALL2DWidth, imageWALL2DHeight, 0, 0, imageWALL2DWidth, imageWALL2DHeight, 0);//start screen
		if (pointer == 500)
			al_draw_scaled_bitmap(WALL2Qimage, 0, 0, imageWALL2QWidth, imageWALL2QHeight, 0, 0, imageWALL2QWidth, imageWALL2QHeight, 0);//start screen

	}
	else
	{

		if (pointer == 400)
			al_draw_scaled_bitmap(WALLimage, 0, 0, imageWALLWidth, imageWALLHeight, 0, 0, imageWALLWidth, imageWALLHeight, 0);//PAUSE screen
		if (pointer == 450)
			al_draw_scaled_bitmap(WALLDimage, 0, 0, imageWALLDWidth, imageWALLDHeight, 0, 0, imageWALLDWidth, imageWALLDHeight, 0);//PAUSE screen
		if (pointer == 500)
			al_draw_scaled_bitmap(WALLQimage, 0, 0, imageWALLQWidth, imageWALLQHeight, 0, 0, imageWALLQWidth, imageWALLQHeight, 0);//PAUSE screen

	}


}


