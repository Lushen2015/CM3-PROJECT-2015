#include <allegro5\allegro.h>
#include <allegro5\allegro_font.h>						//font header files
#include <allegro5\allegro_ttf.h>
#include <allegro5\allegro_primitives.h>	//primitive header file
#include "Objects.h"
#include<allegro5\allegro_image.h>

enum Keys{ A, S, D, W, SPACE };
int res_x = 1280;
int res_y = 820;
int pos_x = 0;
int checkpoint = 4000;
int blockNum = 0;
const int num_proj = 5;
using namespace std;


struct person{
	int r = 20;
	int feet = res_y - 55;
	int x = 200;
	int y = feet - (3 * r);
	int j_height = res_y - 450;
	int ms = 5;
	int jumpspeed = 7;
	int lives = 3;//********************************
	int score = 0;//********************************


}player;
int deathDelay = 0;
int c = 0;
int box_width = player.r * 2 + 15;
int box_bounds = box_width;
int pipe_width = 120;
int pipe_bounds = pipe_width;
int spike_height = 50;
int spike_width = 20;
bool deathPause = false;


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



void HittingBlocks(Projectiles proj[], int size, int sizeB, block blocks[]);
void HittingPipes(Projectiles proj[], int size, int sizeP, Pipe pipes[]);

int const num_enemies = 22;
bool shot = false;

enemies guys[num_enemies];


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


int main(void)
{
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
	bool keys[5] = { false, false, false, false, false };
	int const FPS = 60;
	bool Gamerunning = true;





	Projectiles proj[5];
	bool enemycheck = false;

	
	

	bool enemycheck2 = false;	

	SetEnemies(guys, num_enemies);







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

	if (!al_init())										//initialize Allegro
		return -1;

	display = al_create_display(res_x, res_y);			//create our display object

	if (!display)										//test display object

		return -1;

	al_init_image_addon();
	al_init_font_addon();
	al_init_ttf_addon();								//allows for text
	al_init_primitives_addon();
	al_install_keyboard();							// allows to work with keyboard keys.
	al_install_mouse();
	al_hide_mouse_cursor(display);
	timer = al_create_timer(1.0 / FPS);
	srand(time(NULL));
	initproj(proj, num_proj);


	image = al_load_bitmap("8-Bit_Luigi.png");

	imageWidth = al_get_bitmap_width(image);
	imageHeight = al_get_bitmap_height(image);

	al_set_target_bitmap(image);

	al_set_target_bitmap(al_get_backbuffer(display));
	event_queue = al_create_event_queue();
	ALLEGRO_FONT *font12 = al_load_font("arial.ttf", 18, 0);		//allows for fonts...
	al_register_event_source(event_queue, al_get_keyboard_event_source());	//register keyboard to events.
	al_register_event_source(event_queue, al_get_display_event_source(display)); // Register events from display.
	al_register_event_source(event_queue, al_get_mouse_event_source());//register mouse input to events
	al_register_event_source(event_queue, al_get_timer_event_source(timer));//registers timer 

	al_start_timer(timer);


	while (Gamerunning)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);


		if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch (ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_W:
				if (!deathPause)
				{
					fall = false;
					if (feet_check)
						feet_check = false;
				}


				break;

			case ALLEGRO_KEY_D:
				if (!deathPause)
					keys[D] = true;
				break;
			case ALLEGRO_KEY_A:
				if (!deathPause)
					keys[A] = true;
				break;

			case ALLEGRO_KEY_SPACE:
				if (!deathPause){
					keys[SPACE] = true;
					shoot(proj, num_proj);
				}
				break;
			}

		}
		else if (ev.type == ALLEGRO_EVENT_KEY_UP)
		{
			switch (ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_ESCAPE:
				Gamerunning = false;
				break;
			case ALLEGRO_KEY_L:
				resize(50);
				break;

			case ALLEGRO_KEY_W:
				if (!jump_h&&!feet_check)
					fall = true;
				break;

			case ALLEGRO_KEY_D:
				keys[D] = false;
				break;
			case ALLEGRO_KEY_A:
				keys[A] = false;
				break;
			case ALLEGRO_KEY_SPACE:
				if (deathPause)
				{
					player.score -= 50;
					player.lives--;
					pos_x = checkpoint;
					ISEEDEADPEOPLE(guys, num_enemies);
					deathPause = false;
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
						player.j_height = res_y - blocks[blockNum].y + 250;
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

			if (box_right(blocks, num_blocks) && pipe_right(pipes, num_pipes))	//***********************************************
				pos_x += keys[D] * player.ms;
			if (box_left(blocks, num_blocks) && pipe_left(pipes, num_pipes))  //***********************************************
				pos_x -= keys[A] * player.ms;							// MOVES CHARACTER









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
				}
			}
			if (enemycheck2)
			{
				c -= 3;
				if (c <= 0)
				{
					enemycheck2 = false;
				}
			}


			StartEnemies(guys, num_enemies);

			Collision(proj, num_proj, guys, num_enemies, c);

			//END MOVING ENEMY


			HittingPipes(proj, num_proj, num_pipes, pipes);
			HittingBlocks(proj, num_proj, num_blocks, blocks);


			if (CollideEnemy(guys, num_enemies, c) || spikeCollide(spikes, num_spikes))//DEATH OF CHARA
			{

				keys[A] = false;
				keys[D] = false;
				deathPause = true;

			}
			if (!deathPause)
			{

				al_draw_scaled_bitmap(image, 0, 0, imageWidth, imageHeight, player.x - player.r, player.y - player.r, imageWidth*0.6, imageHeight*0.6, 0);
			}
			if (deathPause)
			{
				deathDelay++;
				if (deathDelay % 10 == 0)
					al_draw_scaled_bitmap(image, 0, 0, imageWidth, imageHeight, player.x - player.r, player.y - player.r, imageWidth*0.6, imageHeight*0.6, 0);
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
		al_draw_filled_rectangle(0, res_y - 50, res_x, res_y, al_map_rgb(139, 69, 19));//Ground		
		//al_draw_filled_circle(player.x, player.y, player.r, al_map_rgb(0, 128, 0));//player
		if (!deathPause)
			al_draw_scaled_bitmap(image, 0, 0, imageWidth, imageHeight, player.x - player.r, player.y - player.r, imageWidth*0.6, imageHeight*0.6, 0);

		al_draw_textf(font12, al_map_rgb(200, 0, 0), 30, 20, 0, "LIVES:       %d", player.lives);
		al_draw_textf(font12, al_map_rgb(210, 0, 0), 29, 40, 0, "SCORE:    %d", player.score);







		drawproj(proj, num_proj);

		al_flip_display();
		al_clear_to_color(al_map_rgb(50, 100, 200));

	}
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


//***************************************************************BLOCKS*******************************************************************************
void initblock(block B[], int size)
{


	B[1].x = 1000;
	for (int i = 1; i < 5; i++)
		B[i + 1].x = B[i].x + box_width + 5;


	B[6].x = 1600;
	for (int i = 6; i < 10; i++)
		B[i + 1].x = B[i].x + box_width + 5;




	B[11].x = 2000;
	B[12].x = B[11].x + box_width + 5;

	for (int i = 0; i <4; i++)
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
	B[22].x = B[21].x + box_width + 5;
	B[23].x = B[22].x + box_width + 5;
	B[24].x = B[23].x + box_width + 5;
	B[25].x = B[24].x + box_width + 5;
	B[26].x = B[25].x + box_width + 5;
	B[27].x = B[26].x + box_width + 5;
	B[28].x = B[27].x + box_width + 5;
	B[29].x = B[28].x + box_width + 5;
	B[30].x = B[29].x + box_width + 5;
	B[31].x = B[30].x + box_width + 5;
	B[32].x = B[31].x + box_width + 5;
	B[33].x = B[32].x + box_width + 5;
	B[34].x = B[33].x + box_width + 5;
	B[35].x = B[34].x + box_width + 5;
	for (int i = 19; i <= 20; i++)
	{
		B[i].y = 550;
	}
	for (int i = 21; i <= 35; i++)
	{
		B[i].y = 470;
	}


	B[36].x = 6400;
	B[37].x = B[36].x + box_width + 5;
	B[38].x = B[37].x + box_width + 5;
	B[39].x = B[38].x + box_width + 5;
	B[40].x = B[39].x + box_width + 5;
	for (int i = 36; i <= 40; i++)
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

	B[41].x = 6200;
	B[41].y = 550;




}
void create(block B[], int size)

{

	for (int i = 0; i < size; i++)
		al_draw_filled_rectangle(B[i].x - pos_x, B[i].y, B[i].x + box_width - pos_x, B[i].y - box_width, al_map_rgb(139, 69, 19));

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
	for (int i = 0; i < size; i++)
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
//*************************************************************************************************************************************************





//**********************************************************PIPES***************************************************************************************

void initPipe(Pipe pipes[], int size)
{

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

	pipes[7].x = 7030;
	pipes[7].y = 550;

	//pipes[8].x = 7200;
	//pipes[8].y = 550;

	pipes[9].x = 8200;
	pipes[9].y = 550;

}
void createPI(Pipe pipes[], int size)
{
	for (int i = 0; i <= 10; i++)
	{


		al_draw_filled_rectangle(pipes[i].x - pos_x, res_y - 50, pipes[i].x + pipe_width - pos_x, pipes[i].y, al_map_rgb(0, 255, 0));
		al_draw_filled_rectangle(pipes[i].x - 20 - pos_x, pipes[i].y, pipes[i].x + pipe_width + 20 - pos_x, pipes[i].y + 50, al_map_rgb(0, 255, 0));
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

//*************************************************************************************************************************************************


//*********************************************************SPIKES**************************************************************************************


void initSpike(spike spikes[], int size)
{
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
	int count = 16;
	for (int i = 6000; i <= 7000; i += spike_width * 2)
	{
		spikes[count].x = i;
		spikes[count].y = 720;
		count++;



	}


}
void createSpike(spike spikes[], int size)
{

	for (int i = 0; i < size; i++)
		al_draw_filled_triangle(spikes[i].x - pos_x, spikes[i].y + spike_height, spikes[i].x + spike_width - pos_x, spikes[i].y, spikes[i].x + 2 * spike_width - pos_x, spikes[i].y + spike_height, al_map_rgb(255, 0, 0));

}
bool spikeCollide(spike spikes[], int size)
{

	bool dead = false;

	for (int i = 0; i < size; i++)
	{
		for (int j = 10; j < 3 * spike_width + 8; j++)
		{
			if (spikes[i].x == player.x + player.r + pos_x - j)
			{
				for (int j = 0; j<spike_width; j++)
				if (player.feet>spikes[i].y + j && (player.y + player.r) < spikes[i].y + 50)//********************************
				{
					dead = true;

				}
			}
		}
	}
	return dead;
}


//***********************************************************************************************************************************************





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

void shoot(Projectiles proj[], int size)
{
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

void update(Projectiles proj[], int size)
{
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


void SetEnemies(enemies guys[], int size)
{
	for (int i = 0; i < size; i++)
	{
		guys[i].ID = ENEMY;
		guys[i].alive = false;
		guys[i].boundx = 22;
		guys[i].boundy = 22;
	}
}
void CreateEnemies(enemies guys[], int size, int counter)
{
	guys[0].x = 700;
	guys[21].x = guys[2].x + 800;
	guys[1].x = guys[0].x + 750;
	guys[2].x = guys[1].x + 100;
	guys[3].x = guys[2].x + 710;
	guys[4].x = guys[3].x + 1100;
	guys[5].x = guys[4].x + 1000;
	guys[6].x = guys[5].x + 340;
	guys[7].x = guys[6].x + 500;
	guys[8].x = guys[7].x + 910;
	guys[9].x = guys[8].x + 900;
	guys[10].x = guys[9].x + 1000;
	guys[11].x = guys[10].x + 400;
	guys[12].x = guys[11].x + 950;
	guys[13].x = guys[12].x + 910;
	guys[14].x = guys[13].x + 200;
	guys[15].x = guys[14].x + 1000;
	guys[16].x = guys[15].x + 905;
	guys[17].x = guys[16].x + 950;
	guys[18].x = guys[17].x + 700;
	guys[19].x = guys[18].x + 900;
	guys[20].x = guys[19].x + 200;

	for (int i = 0; i < size; i++)
	{
		guys[i].y = res_y - 115;
	}

	guys[1].y = 450;
	//guys[2].y = 350;
	guys[3].y = 400;
	guys[6].y = 380;
}
void DrawEnemies(enemies guys[], int size, int counter)
{
	for (int i = 0; i < size; i++)
	{
		if (guys[i].alive)
		{
			al_draw_filled_circle(guys[i].x - pos_x + counter, guys[i].y, 25, al_map_rgb(0, 0, 0));
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
					if (proj[i].x >((guys[j].x - pos_x + counter) - guys[j].boundx) && proj[i].x<((guys[j].x - pos_x + counter) + guys[j].boundx) && proj[i].y>(guys[j].y - guys[j].boundy) && proj[i].y < (guys[j].y + guys[j].boundy))
					{

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
						//player.score += 100;
						proj[j].live = false;
						//guys[j].alive = false;
						//shot = true;				
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
						proj[j].live = false;
					}
				}
			}
		}
	}
}

//***********************************************************************************************************************************************

