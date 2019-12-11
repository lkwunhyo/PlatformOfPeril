// Library Includes
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <cab202_graphics.h>
#include <cab202_sprites.h>
#include <cab202_timers.h>

// Configuration
#define DELAY (10) /* Millisecond delay between game updates */

#define HERO_WIDTH (3)
#define HERO_HEIGHT (3)
#define ZOMBIE_WIDTH (4)
#define ZOMBIE_HEIGHT (4)
#define MONSTER_WIDTH (3)
#define MONSTER_HEIGHT (2)
#define EXIT_WIDTH (4)
#define EXIT_HEIGHT (4)

#define KEY_DOWN	0402		/* down-arrow key */
#define KEY_UP		0403		/* up-arrow key */
#define KEY_LEFT	0404		/* left-arrow key */
#define KEY_RIGHT	0405		/* right-arrow key */

// Function Declarations
void restart_level( void );
void level1( void );
void level2( void );
void level3( void );
void level4( void );
void level5( void );


// Game states
bool game_over = false;
bool update_screen = true;
bool boulderRoll = true;
bool stuck = true;
bool nopit = true;
bool nopitB = true;
bool treasure = true;
bool bar_key = true;
bool nokey = true;
bool is_barrier = true;
bool jump = false;
bool monstercol = true;


// Game status information
time_t seconds = 0;
time_t minutes = 0;
time_t time = 0;
//time_t jump_time = 0;


int lives = 10;
int score = 0;
int level = 1;

// Sprite images
char * hero_image =
/**/	" o "
/**/	"/S\\"
/**/	"/ \\";

char * hjump_image =
/**/	"\\o/"
/**/	" S "
/**/	"/ \\";

char * hexit_image =
/**/	" o "
/**/	"/S/"
/**/	"/ /";

char * zombie1_image =
/**/	"ZZZZ"
/**/	"  Z "
/**/	" Z  "
/**/	"ZZZZ";

char * mons_image =
/**/	"\\ /"
/**/	" | ";

char * mons2_image =
/**/	" | "
/**/	"/ \\";

char * bould_image =
/**/	"/``\\"
/**/	"\\__/";

char * treas_image =
/**/	"$";

char * tsparkle_image =
/**/	" `   "
/**/	"    `"
/**/	"    `";

char * tsparkle2_image =
/**/	"`   `"
/**/	"   ` "
/**/	"`    ";

char * key_image =
/**/	"0-+";

char * ksparkle_image =
/**/	"         "
/**/	"  `    ` "
/**/	"      `  "
/**/	"    `    "
/**/	"         ";

char * ksparkle2_image =
/**/	"   `    `"
/**/	"`        "
/**/	"        `"
/**/	"         "
/**/	"`   `   `";

char * exitd_image = 
/**/	"EXIT"
/**/	"|  |"
/**/	"| .|"
/**/	"|  |";

char * top_plat_image = 
/**/	"_____________________________________________________________________________________________________________________________________________________________________________________________________________________________________________";

char * plat_image = 
/**/	"=============================================================================================================================================================================================================================================";

char * pit_image = 
/**/	"                                                                                                                                                                                                                                             ";

char * singlep = 
/**/	"=";

char * wall_image = 
/**/	"|"
/**/	"|"
/**/	"|"
/**/	"|"
/**/	"|"
/**/	"|"
/**/	"|"
/**/	"|"
/**/	"|"
/**/	"|"
/**/	"|"
/**/	"|";

char * bar_image = 
/**/	"[]"
/**/	"[]"
/**/	"[]"
/**/	"[]"
/**/	"[]"
/**/	"[]"
/**/	"[]"
/**/	"[]"
/**/	"[]"
/**/	"[]"
/**/	"[]"
/**/	"[]"
/**/	"[]";

// Sprite declarations
sprite_id hero;
sprite_id hjump;
sprite_id hexit;
sprite_id zombie;
sprite_id mons;
sprite_id mons1;
sprite_id bat;
sprite_id bat1;
sprite_id bould;
sprite_id exitd;
sprite_id treas;
sprite_id sparkle;
sprite_id sparkle2;
sprite_id key;
sprite_id ksparkle;
sprite_id ksparkle2;
sprite_id top_plat;
sprite_id plat;
sprite_id plat1;
sprite_id plat2;
sprite_id plat3;
sprite_id pit;
sprite_id wall;
sprite_id barrier;


void setup( void ) {
	
	// Setup hero initial position.
	int hero_x;
	int hero_y;
	
	hero_x = 4;
	hero_y = round(screen_height() - HERO_HEIGHT - 1);
	
	hero = sprite_create(hero_x, hero_y, HERO_WIDTH, HERO_HEIGHT, hero_image);
	//hjump = sprite_create(hero_x, hero_y, HERO_WIDTH, HERO_HEIGHT, hjump_image);
	
	
	//sprite_turn_to(hero, sprite_dx(hero), -0.2);
	
	// Setup Exit Door Position.
	int exitd_x;
	int exitd_y;
	
	exitd_x = round(screen_width() - 8);
	exitd_y = round(screen_height() - 5);
	
	exitd = sprite_create(exitd_x, exitd_y, EXIT_WIDTH, EXIT_HEIGHT, exitd_image);
	
	hexit = sprite_create(exitd_x - HERO_WIDTH, hero_y, HERO_WIDTH, HERO_HEIGHT, hexit_image);
	
	// LEVEL 1
	// Setup zombie initial position.
	int zombie_x;
	int zombie_y;
	
	zombie_x = round(screen_width() -8);
	zombie_y = round(screen_height() - 5);
	
	zombie = sprite_create(zombie_x, zombie_y, ZOMBIE_WIDTH, ZOMBIE_HEIGHT, zombie1_image);
	
	// Initiate zombie movement.
	sprite_turn_to(zombie, -0.2, 0);

	
	//LEVEL 2
	// Setup monster initial position.
	int mons_x;
	int mons_y;
	
	mons_x = round(screen_width() - 9);
	mons_y = round(screen_height() - 4);
	
	mons = sprite_create(mons_x, mons_y, MONSTER_WIDTH, MONSTER_HEIGHT, mons_image);
	mons1 = sprite_create(mons_x, mons_y, MONSTER_WIDTH, MONSTER_HEIGHT, mons2_image);

	
	// Initiate monster movement.
	sprite_turn_to(mons, -0.2, 0);
	sprite_turn_to(mons1, -0.2, 0);
	
	//LEVEL 3
	// Setup monster initial position.
	int bat_x;
	int bat_y;
	
	bat_x = round(screen_width() - 9);
	bat_y = screen_height() - HERO_HEIGHT * 3.5 - HERO_HEIGHT * 3.5 - MONSTER_HEIGHT - 3;
	
	bat = sprite_create(bat_x, bat_y, MONSTER_WIDTH, MONSTER_HEIGHT, mons_image);
	bat1 = sprite_create(bat_x, bat_y, MONSTER_WIDTH, MONSTER_HEIGHT, mons2_image);
	
	// Initiate monster movement.
	sprite_turn_to(bat, -0.2, 0);
	sprite_turn_to(bat1, -0.2, 0);

	// LEVEL 5.
	
	//Middle platform.	
	int plat_x2;
	int plat_y2;
	
	plat_x2 = 1;
	plat_y2 = (screen_height() - 1 - (HERO_HEIGHT * 3.5)) - (HERO_HEIGHT * 3.5);
	
	plat2 = sprite_create(plat_x2, plat_y2 - 1, ((screen_width() - 1) * 0.33) * 2, 1, plat_image);
	
	// Initiate platform2 movement.
	sprite_turn_to(plat2, 0.2, 0);

	
}


void level5_setup( void ) {
	//LEVEL 5

	// Setup boulder initial position.
	int bould_x;
	//int bould_y;
	
	bould_x = round(screen_width() - 7);
	//bould_y = screen_height() - 1 - (3 * (HERO_HEIGHT * 3.5));
	
	bould = sprite_create(bould_x, 3, 4, 2, bould_image);
	
	// Initiate monster movement.
	sprite_turn_to(bould, -0.2 * 0.33 - 0.2, 0.4);
	
}


void draw_border() {
	// Setup the border.
	int left;
	int top;
	int right;
	int bottom;
	
	left = 0;
	top = 2;
	right = screen_width() - 1;
	bottom = screen_height() - 1;

	draw_line(left, top, left, bottom, ']');
	draw_line(right, top, right, bottom, '[');
	
	top_plat = sprite_create(left, top, screen_width(), 1, top_plat_image);
	
	sprite_draw(top_plat);
	
	
	//draw_line(left, top, right, top, '_');
	
	int plat_x;
	int plat_y;
	
	plat_x = 0;
	plat_y = screen_height() - 1;
	
	
	plat = sprite_create(plat_x, plat_y, screen_width(), 1, plat_image);
	
	sprite_draw(plat);
	
}


void display_status() {
	int width = screen_width() / 4;
	draw_formatted(2, 1, "Time: %02d:%02d", minutes, seconds);
	draw_formatted(1 * width, 1, " Lives: %d", lives);
	draw_formatted(2 * width, 1, "Level: %d", level);
	draw_formatted(3 * width, 1, "Score: %d", score);
	
}

void timer() {
	time++;
	if (time == 100) {
		seconds++;
		time = 0;
		if (seconds == 60) {
			seconds = 0;
			minutes++;
		}
	}
		
}


void gameover_screen() {
	int width;
	int height;
	
	width = screen_width() / 2;
	height = screen_height() / 2;

	while (get_char() <= 0) {
		draw_string(width - 4, height - 2, "Game Over");
		draw_string(width - 10, height, "Press any key to exit");
		show_screen();
	}
	//int enter = wait_char();
	//if (enter) {
		game_over = true;
		
	//}
	return;

}


void finish_screen() {
	clear_screen();
	int width;
	int height;
	
	width = screen_width() / 2;
	height = screen_height() / 2 - 2;
	
	int final_score = score;
	
	while (get_char() <= 0) {
		draw_string(width - 7, height, "Congratulations");
		int score_width = 0;
		if(final_score == 0) {
			score_width = 11;
		} else if (final_score > 9 && final_score < 100) {
			score_width = 11;
		} else {
			score_width = 12;
		}
		draw_formatted(width - score_width, height + 2, "Your final score was %d", final_score);
		draw_string(width - 10, height + 4, "Press any key to exit");
		show_screen();
	}

	//int enter = wait_char();
	//if (enter) {
		game_over = true;
		
	//}

	
	return;
	
}


void restart_level() {
	// Preparing for another try of the same level.
	setup();
	level5_setup();
	clear_screen();
	draw_border();
	display_status();
	if (level == 1) {
		level1();
	} else if (level == 2) {
		level2();
	} else if (level == 3) {
		level3();
	} else if (level == 4) {
		level4();
	} else {
		level5();
	}
	show_screen();
	
} 


// Taken from an existing AMS exercise (copy and paste)
bool sprites_collided(sprite_id sprite_1, sprite_id sprite_2) {
    int sprite_1_top = round(sprite_y(sprite_1)),
        sprite_1_bottom = sprite_1_top + sprite_height(sprite_1) - 1,
        sprite_1_left = round(sprite_x(sprite_1)),
        sprite_1_right = sprite_1_left + sprite_width(sprite_1) - 1;

    int sprite_2_top = round(sprite_y(sprite_2)),
        sprite_2_bottom = sprite_2_top + sprite_height(sprite_2) - 1,
        sprite_2_left = round(sprite_x(sprite_2)),
        sprite_2_right = sprite_2_left + sprite_width(sprite_2) - 1;

    return !(
        sprite_1_bottom < sprite_2_top
        || sprite_1_top > sprite_2_bottom
        || sprite_1_right < sprite_2_left
        || sprite_1_left > sprite_2_right
        );
}


void gravity ( void ) {
	
	int hero_x = sprite_x(hero);
	int hero_y = sprite_y(hero);
	//double hdy = sprite_dy(hero);
	//double bdy = sprite_dy(bould);	
	
	// Hitting the floor.
	if (nopit) {
		if (sprites_collided(hero, plat)) {
				sprite_move(hero, 0, -1);
				sprite_turn_to(hero, sprite_dx(hero), 0);
		}
	}
	
		// Hitting the bottom of the ceiling.
	if (sprites_collided(hero, top_plat) && hero_y - HERO_HEIGHT < sprite_y(top_plat)) {
		sprite_move(hero, 0, 1);
		sprite_turn_to(hero, sprite_dx(hero), 0);
	}
	
	// To get unstuck from walls.
	if (stuck) {
		// Hitting the walls like an idiot.
			// When you aren't jumping.
		if (hero_x < 1 && sprite_dy(hero) == 0) {
			sprite_turn_to(hero, 0, 0);
			stuck = false;
		}
			
		if (hero_x > screen_width() - HERO_WIDTH - 2 && sprite_dy(hero) == 0) {
			sprite_turn_to(hero, 0, 0);
			stuck = false;
		}
		
			// When you are jumping.
		// When the hero is falling down/jumping up (LEFT)
		if (hero_x < 1 && sprite_dy(hero) > 0) {
			sprite_turn_to(hero, 0, sprite_dy(hero));
			stuck = false;
		}
		if (hero_x < 1 && sprite_dy(hero) < 0) {
			sprite_turn_to(hero, 0, sprite_dy(hero));
			stuck = false;
		}
		
		// When the hero is falling down/jumping up (RIGHT)
		if (hero_x > screen_width() - HERO_WIDTH - 2 && sprite_dy(hero) > 0) {
			sprite_turn_to(hero, 0, sprite_dy(hero));
			stuck = false;
		}
		if (hero_x > screen_width() - HERO_WIDTH - 2 && sprite_dy(hero) < 0) {
			sprite_turn_to(hero, 0, sprite_dy(hero));
			stuck = false;
		}
		
	}
	
	if (hero_x > 1 && hero_x < screen_width() - HERO_WIDTH - 1) {
			stuck = true;
		}

}


void level1( void ) {
	
	//int hero_x, 
	int hero_y;
	//hero_x = sprite_x(hero);
	hero_y = sprite_y(hero);
	
	// Create the platform.
	int plat_x;
	int plat_y;
	
	plat_x = round(screen_width() * 0.33);
	plat_y = (screen_height() - 1) - (HERO_HEIGHT * 3.5);
	
	plat1 = sprite_create(plat_x, plat_y, plat_x, 1, plat_image);
	plat2 = sprite_create(0, 0, 1, 1, pit_image);
	plat3 = sprite_create(0, 0, 1, 1, pit_image);
	
	
	// Initiate zombie motion.	
		
	sprite_step(zombie);
		
	int zombie_x;
	//int zombie_y;
		
	zombie_x = round(sprite_x(zombie));
	//zombie_y = round(sprite_y(zombie));
		
	double zdx;
	//double zdy;
		
	zdx = sprite_dx(zombie);
	//zdy = sprite_dy(zombie);	
		
		
	if (zombie_x <= 1) 
	{
		zdx = fabs(zdx);
	} 
	else if (zombie_x >= screen_width() - ZOMBIE_WIDTH - 1)
	{
		zdx = -fabs(zdx);
	}
		
	
	if (zdx != sprite_dx(zombie)) {
		sprite_back(zombie);
		sprite_turn_to(zombie, zdx, 0);
	}
	
	// Zombie collision.
	if (sprites_collided(hero, zombie)) {
		if (monstercol) {
		lives--;
		restart_level();
		}
	}
	
	// Platform collision.
	
		// Hitting the bottom of platform 1.
	if (sprites_collided(hero, plat1) && hero_y - HERO_HEIGHT < sprite_y(plat1)) {
		sprite_move(hero, 0, 1);
		sprite_turn_to(hero, sprite_dx(hero), 0);
	}
	
		// Landing on top of platform 1.
	if (sprites_collided(hero, plat1) && hero_y + HERO_HEIGHT > sprite_y(plat1) - 1) {
		sprite_move(hero, 0, -2);
		sprite_turn_to(hero, sprite_dx(hero), 0);
	}
	
	// Exit door collision.
	sprite_draw(exitd);
	if (sprites_collided(hero, exitd)) {
		monstercol = false;
		sprite_hide(hero);
		sprite_hide(hjump);
		sprite_turn_to(hero, 0, 0);
		sprite_draw(hexit);
		sprite_step(hexit);
		sprite_turn_to(hexit, 0.05, 0);
		if (sprite_x(hexit) + 3 > sprite_x(exitd) + 3) {
			score += 100;
			level++;
			monstercol = true;
			restart_level();
		}
		
	}  

	
	sprite_draw(zombie);
	
}

void level2( void ) {
	
	//int hero_x, 
	int hero_y;
	//hero_x = sprite_x(hero);
	hero_y = sprite_y(hero);
	
	// Create the platforms.
	// Lower platform.
	int plat_x;
	int plat_y;
	
	plat_x = (screen_width() + 2) * 0.33;
	plat_y = (screen_height() - 1) - (HERO_HEIGHT * 3.5);
	
	plat1 = sprite_create(plat_x, plat_y, plat_x, 1, plat_image);
	plat3 = sprite_create(0, 0, 1, 1, pit_image);
	
	// Upper platform.
	int plat_x2;
	int plat_y2;
	
	plat_x2 = plat_x + round(plat_x * 0.33);
	plat_y2 = plat_y - (HERO_HEIGHT * 3.5);
	
	plat2 = sprite_create(plat_x2, plat_y2, plat_x * 0.33, 1, plat_image);
	
	// Setup treasure position.
	int treas_x;
	int treas_y;
	
	treas_x = (screen_width() - 1) / 2;
	treas_y = plat_y2 - (HERO_HEIGHT * 3.5);
	
	treas = sprite_create(treas_x, treas_y, 1, 1, treas_image);
	
	sparkle = sprite_create(treas_x - 2, treas_y - 1, 5, 3, tsparkle_image);
	sparkle2 = sprite_create(treas_x - 2, treas_y - 1, 5, 3, tsparkle2_image);
	
	if (treasure) {
		sprite_draw(treas);
		
		if (time < 50) {
		sprite_draw(sparkle);
		} else {
			sprite_draw(sparkle2);
		}
		
		if (sprites_collided(hero, treas)) {
			score += 50;
			sprite_hide(treas);
			sprite_hide(sparkle);
			sprite_hide(sparkle2);
			treasure = false;
		}
	}
	
	
	
	// Initiate monster motion.	
	sprite_step(mons);
		
	int mons_x;
	//int mons_y;
		
	mons_x = round(sprite_x(mons));
	//mons_y = round(sprite_y(mons));
		
	double zdx;
	//double zdy;
		
	zdx = sprite_dx(mons);
	//zdy = sprite_dy(mons);	
		
		
	if (mons_x <= 1) 
	{
		zdx = fabs(zdx);
	} 
	else if (mons_x >= screen_width() - MONSTER_WIDTH - 1)
	{
		zdx = -fabs(zdx);
	}
		
		
	if (zdx != sprite_dx(mons)) {
		sprite_back(mons);
		sprite_turn_to(mons, zdx, 0);
	}
	
	sprite_step(mons1);
		
	int mons_x1;
	//int mons_y1;
		
	mons_x1 = round(sprite_x(mons1));
	//mons_y1 = round(sprite_y(mons1));
		
	double zdx1;
	//double zdy1;
		
	zdx1 = sprite_dx(mons1);
	//zdy1 = sprite_dy(mons1);	
		
	if (mons_x1 <= 1) 
	{
		zdx1 = fabs(zdx1);
	} 
	else if (mons_x1 >= screen_width() - MONSTER_WIDTH - 1)
	{
		zdx1 = -fabs(zdx1);
	}
		
		
	if (zdx1 != sprite_dx(mons1)) {
		sprite_back(mons1);
		sprite_turn_to(mons1, zdx1, 0);
	}
	
	// Zombie collision.
	if (sprites_collided(hero, mons)) {
		if (monstercol) {
			lives--;
			restart_level();
		}
	}
	
	// Platform collision.
	
		// Hitting the bottom of platform 1.
	if (sprites_collided(hero, plat1) && hero_y - HERO_HEIGHT < sprite_y(plat1)) {
		sprite_move(hero, 0, 1);
		sprite_turn_to(hero, sprite_dx(hero), 0);
	}
	
		// Landing on top of platform 1.
	if (sprites_collided(hero, plat1) && hero_y + HERO_HEIGHT > sprite_y(plat1) - 1) {
		sprite_move(hero, 0, -2);
		sprite_turn_to(hero, sprite_dx(hero), 0);
	}
	
		// Hitting the bottom of platform 2.
	if (sprites_collided(hero, plat2) && hero_y - HERO_HEIGHT < sprite_y(plat2)) {
		sprite_move(hero, 0, 1);
		sprite_turn_to(hero, sprite_dx(hero), 0);
	}
	
		// Landing on top of platform 2.
	if (sprites_collided(hero, plat2) && hero_y + HERO_HEIGHT > sprite_y(plat2) - 1) {
		sprite_move(hero, 0, -2);
		sprite_turn_to(hero, sprite_dx(hero), 0);
	}
	
	// Exit door collision.
	
	sprite_draw(exitd);
	if (sprites_collided(hero, exitd)) {
		monstercol = false;
		sprite_hide(hero);
		sprite_hide(hjump);
		sprite_turn_to(hero, 0, 0);
		sprite_draw(hexit);
		sprite_step(hexit);
		sprite_turn_to(hexit, 0.05, 0);
		if (sprite_x(hexit) + 3 > sprite_x(exitd) + 3) {
			score += 100;
			level++;
			monstercol = true;
			treasure = true;
			restart_level();
		}
		
	}  
	
	if (time % 2 == 0) {
		sprite_draw(mons);
	} else {
		sprite_draw(mons1);
	}
	
}

void level3( void ) {
	
	int hero_x, hero_y;
	hero_x = sprite_x(hero);
	hero_y = sprite_y(hero);
	
	// Create the platforms.
	// Lower platform.
	int plat_x;
	int plat_y;
	
	plat_x = (screen_width() + 2) * 0.25;
	plat_y = (screen_height() - 1) - (HERO_HEIGHT * 3.5);
	
	plat1 = sprite_create(plat_x, plat_y, plat_x * 2, 1, plat_image);
	plat3 = sprite_create(0, 0, 1, 1, pit_image);
	
	// Upper platform.
	int plat_x2;
	int plat_y2;
	
	plat_x2 = plat_x + plat_x * 0.66;
	plat_y2 = plat_y - HERO_HEIGHT * 3.5;
	
	plat2 = sprite_create(plat_x2, plat_y2, (plat_x * 2) * 0.33, 1, plat_image);
	
	// Create the pit.
	int pit_x;
	int pit_y;
	
	pit_x = plat_x;
	pit_y = screen_height() - 1;
	
	pit = sprite_create(pit_x, pit_y - 1, pit_x * 2, 1, pit_image);
	
	draw_line(pit_x, pit_y, pit_x * 3, pit_y, ' ');

	if (hero_x > plat_x && hero_x < plat_x * 3 && hero_y > screen_height() - 1 - (HERO_HEIGHT * 3.5)) {
		nopit = false;
		sprite_turn_to(hero, sprite_dx(hero), 0.2);
		if (hero_y > sprite_y(plat)) {
			nopit = true;
			lives--;
			restart_level();
		}
	}
	
	// Create the barrier.
	int wall_x;
	int wall_y;
	
	wall_x = (screen_width() - 1) / 2;
	wall_y = plat_y2;
	
	wall = sprite_create(wall_x, wall_y + 1, 1, HERO_HEIGHT * 3.5, wall_image);
	
	// Setup treasure position.
	int treas_x;
	int treas_y;
	
	treas_x = (screen_width() - 1) / 2;
	treas_y = plat_y2 - (HERO_HEIGHT * 3.5);
	
	treas = sprite_create(treas_x, treas_y, 1, 1, treas_image);
	
	sparkle = sprite_create(treas_x - 2, treas_y - 1, 5, 3, tsparkle_image);
	sparkle2 = sprite_create(treas_x - 2, treas_y - 1, 5, 3, tsparkle2_image);
	
	if (treasure) {
		sprite_draw(treas);
		
		if (time < 50) {
		sprite_draw(sparkle);
		} else {
			sprite_draw(sparkle2);
		}
		
		if (sprites_collided(hero, treas)) {
			score += 50;
			sprite_hide(treas);
			sprite_hide(sparkle);
			sprite_hide(sparkle2);
			treasure = false;
		}
	}
	
	// Initiate monster motion.	
		
	sprite_step(bat);
		
	int bat_x;
	//int bat_y;
		
	bat_x = round(sprite_x(bat));
	//bat_y = round(sprite_y(bat));
	
	double zdx;
	//double zdy;
		
	zdx = sprite_dx(bat);
	//zdy = sprite_dy(bat);	
	
	
	if (bat_x <= 1) 
	{
		zdx = fabs(zdx);
	} 
	else if (bat_x >= screen_width() - MONSTER_WIDTH - 1)
	{
		zdx = -fabs(zdx);
	}
	
	
	if (zdx != sprite_dx(bat)) {
		sprite_back(bat);
		sprite_turn_to(bat, zdx, 0);
	}

	sprite_step(bat1);
	
	int bat_x1;
	//int bat_y1;
	
	bat_x1 = round(sprite_x(bat1));
	//bat_y1 = round(sprite_y(bat1));
	
	double zdx1;
	//double zdy1;
	
	zdx1 = sprite_dx(bat1);
	//zdy1 = sprite_dy(bat1);	
	
	if (bat_x1 <= 1) 
	{
		zdx1 = fabs(zdx1);
	} 
	else if (bat_x1 >= screen_width() - MONSTER_WIDTH - 1)
	{
		zdx1 = -fabs(zdx1);
	}
	
	
	if (zdx1 != sprite_dx(bat1)) {
		sprite_back(bat1);
		sprite_turn_to(bat1, zdx1, 0);
	}

	// Monster collision.
	if (sprites_collided(hero, bat)) {
		if (monstercol) {
			lives--;
			restart_level();
		}
	}
	
	// Platform collision.
	
		// Hitting the bottom of platform 1.
	if (sprites_collided(hero, plat1) && hero_y - HERO_HEIGHT < sprite_y(plat1)) {
		sprite_move(hero, 0, 1);
		sprite_turn_to(hero, sprite_dx(hero), 0);
	}
	
		// Landing on top of platform 1.
	if (sprites_collided(hero, plat1) && hero_y + HERO_HEIGHT > sprite_y(plat1) - 1) {
		sprite_move(hero, 0, -2);
		sprite_turn_to(hero, sprite_dx(hero), 0);
	}
	
		// Hitting the bottom of platform 2.
	if (sprites_collided(hero, plat2) && hero_y - HERO_HEIGHT < sprite_y(plat2)) {
		sprite_move(hero, 0, 1);
		sprite_turn_to(hero, sprite_dx(hero), 0);
	}
	
		// Landing on top of platform 2.
	if (sprites_collided(hero, plat2) && hero_y + HERO_HEIGHT > sprite_y(plat2) - 1) {
		sprite_move(hero, 0, -2);
		sprite_turn_to(hero, sprite_dx(hero), 0);
	}
		
		// Hitting the wall from the left.
	// When the hero is not jumping.
	if (sprites_collided(hero, wall) && hero_x - HERO_WIDTH < sprite_x(wall) && sprite_dy(hero) == 0) {
		sprite_move(hero, -1, 0);
		sprite_turn_to(hero, 0, 0);
	}
	// Jumping up.
	if (sprites_collided(hero, wall) && hero_x - HERO_WIDTH < sprite_x(wall) && sprite_dy(hero) < 0) {
		sprite_move(hero, -1, 0);
		sprite_turn_to(hero, 0, sprite_dy(hero));
	}
	// Jumping down.
	if (sprites_collided(hero, wall) && hero_x - HERO_WIDTH < sprite_x(wall) && sprite_dy(hero) > 0) {
		sprite_move(hero, -1, 0);
		sprite_turn_to(hero, 0, sprite_dy(hero));
	}
	
		// Hitting the wall from the right.
	// When the hero is not jumping.
	if (sprites_collided(hero, wall) && hero_x + HERO_WIDTH > sprite_x(wall) && sprite_dy(hero) == 0) {
		sprite_move(hero, 2, 0);
		sprite_turn_to(hero, 0, 0);
	}
	// Jumping up.
	if (sprites_collided(hero, wall) && hero_x + HERO_WIDTH > sprite_x(wall) && sprite_dy(hero) < 0) {
		sprite_move(hero, 2, 0);
		sprite_turn_to(hero, 0, sprite_dy(hero));
	}
	// Jumping down.
	if (sprites_collided(hero, wall) && hero_x + HERO_WIDTH > sprite_x(wall) && sprite_dy(hero) > 0) {
		sprite_move(hero, 2, 0);
		sprite_turn_to(hero, 0, sprite_dy(hero));
	}
	
	// Exit door collision.
	sprite_draw(exitd);
	if (sprites_collided(hero, exitd)) {
		monstercol = false;
		sprite_hide(hero);
		sprite_hide(hjump);
		sprite_turn_to(hero, 0, 0);
		sprite_draw(hexit);
		sprite_step(hexit);
		sprite_turn_to(hexit, 0.05, 0);
		if (sprite_x(hexit) + 3 > sprite_x(exitd) + 3) {
			score += 100;
			level++;
			monstercol = true;
			treasure = true;
			restart_level();
		}
		
	}  

	if (time % 2 == 0) {
		sprite_draw(bat);
	} else {
		sprite_draw(bat1);
	}
}

void level4( void ) {
	
	int hero_x, hero_y;
	hero_x = sprite_x(hero);
	hero_y = sprite_y(hero);
		
	// Create the platforms.
	//Lower platform.
	int plat_x;
	int plat_y;
	
	plat_x = (screen_width() - 1) * 0.33;
	plat_y = screen_height() - 1 - (HERO_HEIGHT * 3.5);
	
	plat1 = sprite_create(plat_x + 1, plat_y, screen_width() * 0.66, 1, plat_image);
	draw_string(screen_width() - 2, plat_y, singlep);
	
	//Middle platform.	
	int plat_x2;
	int plat_y2;
	
	plat_x2 = 1;
	plat_y2 = plat_y - (HERO_HEIGHT * 3.5);
	
	plat2 = sprite_create(plat_x2, plat_y2, plat_x * 2, 1, plat_image);
	
	// Upper platform.
	int plat_x3;
	int plat_y3;
	
	plat_x3 = plat_x;
	plat_y3 = plat_y2 - (HERO_HEIGHT * 3.5);
	
	plat3 = sprite_create(plat_x3 + 1, plat_y3, screen_width() * 0.66, 1, plat_image);
	draw_string(screen_width() - 2, plat_y3, singlep);
	
	// Create barrier.
	int bar_x;
	int bar_y;
	
	bar_x = (screen_width() - 1) * 0.75;
	bar_y = screen_height() - (HERO_HEIGHT * 3.5);
	
	barrier = sprite_create(bar_x, bar_y, 2, HERO_HEIGHT * 3.5, bar_image);

	// Setup key position.
	int key_x;
	int key_y;
	
	key_x = screen_width() - HERO_WIDTH * 4;
	key_y = plat_y3 - HERO_HEIGHT * 2;
	
	key = sprite_create(key_x, key_y, 3, 1, key_image);
	
	ksparkle = sprite_create(key_x - 3, key_y - 2, 9, 5, ksparkle_image);
	ksparkle2 = sprite_create(key_x - 3, key_y - 2, 9, 5, ksparkle2_image);
	
	if (nokey) {
		sprite_draw(key);
		
		if (time < 50) {
		sprite_draw(ksparkle);
		} else {
			sprite_draw(ksparkle2);
		}
		
		if (sprites_collided(hero, key)) {
			sprite_hide(key);
			sprite_hide(ksparkle);
			sprite_hide(ksparkle2);
			nokey = false;
		}
	}
	
	// Platform collision.
		// Hitting the bottom of platform 1.
	if (sprites_collided(hero, plat1) && hero_y - HERO_HEIGHT < sprite_y(plat1)) {
		sprite_move(hero, 0, 1);
		sprite_turn_to(hero, sprite_dx(hero), 0);
	}
	
		// Landing on top of platform 1.
	if (sprites_collided(hero, plat1) && hero_y + HERO_HEIGHT > sprite_y(plat1) - 1) {
		sprite_move(hero, 0, -2);
		sprite_turn_to(hero, sprite_dx(hero), 0);
	}
	
		// Hitting the bottom of platform 2.
	if (sprites_collided(hero, plat2) && hero_y - HERO_HEIGHT < sprite_y(plat2)) {
		sprite_move(hero, 0, 1);
		sprite_turn_to(hero, sprite_dx(hero), 0);
	}
	
		// Landing on top of platform 2.
	if (sprites_collided(hero, plat2) && hero_y + HERO_HEIGHT > sprite_y(plat2) - 1) {
		sprite_move(hero, 0, -2);
		sprite_turn_to(hero, sprite_dx(hero), 0);
	}
	
		// Hitting the bottom of platform 3.
	if (sprites_collided(hero, plat3) && hero_y - HERO_HEIGHT < sprite_y(plat3)) {
		sprite_move(hero, 0, 1);
		sprite_turn_to(hero, sprite_dx(hero), 0);
	}
	
		// Landing on top of platform 3.
	if (sprites_collided(hero, plat3) && hero_y + HERO_HEIGHT > sprite_y(plat3) - 1) {
		sprite_move(hero, 0, -2);
		sprite_turn_to(hero, sprite_dx(hero), 0);
	}
	
	if (nokey) {
			// Hitting the barrier from the left.
		// When the hero is not jumping.
		if (sprites_collided(hero, barrier) && hero_x - HERO_WIDTH < sprite_x(barrier) && sprite_dy(hero) == 0) {
			sprite_move(hero, -1, 0);
			sprite_turn_to(hero, 0, 0);
		}
		// Jumping up.
		if (sprites_collided(hero, barrier) && hero_x - HERO_WIDTH < sprite_x(barrier) && sprite_dy(hero) < 0) {
			sprite_move(hero, -1, 0);
			sprite_turn_to(hero, 0, sprite_dy(hero));
		}
		// Jumping down.
		if (sprites_collided(hero, barrier) && hero_x - HERO_WIDTH < sprite_x(barrier) && sprite_dy(hero) > 0) {
			sprite_move(hero, -1, 0);
			sprite_turn_to(hero, 0, sprite_dy(hero));
		}
		
			// Hitting the barrier from the right.
		// When the hero is not jumping.
		if (sprites_collided(hero, barrier) && hero_x + HERO_WIDTH > sprite_x(barrier) && sprite_dy(hero) == 0) {
			sprite_move(hero, 2, 0);
			sprite_turn_to(hero, 0, 0);
		}
		// Jumping up.
		if (sprites_collided(hero, barrier) && hero_x + HERO_WIDTH > sprite_x(barrier) && sprite_dy(hero) < 0) {
			sprite_move(hero, 2, 0);
			sprite_turn_to(hero, 0, sprite_dy(hero));
		}
		// Jumping down.
		if (sprites_collided(hero, barrier) && hero_x + HERO_WIDTH > sprite_x(barrier) && sprite_dy(hero) > 0) {
			sprite_move(hero, 2, 0);
			sprite_turn_to(hero, 0, sprite_dy(hero));
		}
	}
	
	if (!nokey) {
		sprite_hide(key);
		
		if (hero_x > sprite_x(barrier) && hero_y > screen_height() - (HERO_HEIGHT * 3.5)) {
			is_barrier = false;
		}
	}
	if (!is_barrier) {
		sprite_hide(barrier);
	}
	
	// Exit door collision.
	sprite_draw(exitd);
	if (sprites_collided(hero, exitd)) {
		sprite_hide(hero);
		sprite_hide(hjump);
		sprite_turn_to(hero, 0, 0);
		sprite_draw(hexit);
		sprite_step(hexit);
		sprite_turn_to(hexit, 0.05, 0);
		if (sprite_x(hexit) + 3 > sprite_x(exitd) + 3) {
			score += 100;
			level++;
			treasure = true;
			nokey = true;
			is_barrier = true;
			restart_level();
		}
		
	}  

	sprite_draw(key);
	
}

void level5( void ) {
	
	int hero_x, hero_y;
	hero_x = sprite_x(hero);
	hero_y = sprite_y(hero);
	
	// Create the platforms.
	//Lower platform.
	int plat_x;
	int plat_y;
	
	plat_x = (screen_width() - 1) * 0.33;
	plat_y = screen_height() - 1 - (HERO_HEIGHT * 3.5);
	
	plat1 = sprite_create(plat_x + 1, plat_y, screen_width() * 0.66, 1, plat_image);
	draw_string(screen_width() - 2, plat_y, singlep);
	
	 //Middle platform.	
	//int plat_x2;
	int plat_y2;
	
	//plat_x2 = 1;
	plat_y2 = plat_y - (HERO_HEIGHT * 3.5);
	
	sprite_step(plat2);
		
	int plat2_x1;
	//int plat2_y1;
	
	plat2_x1 = round(sprite_x(plat2));
	//plat2_y1 = round(sprite_y(plat2));
	
	double pdx;
	//double pdy;
	
	pdx = sprite_dx(plat2);
	//pdy = sprite_dy(plat2);	
	
	
	if (plat2_x1 <= 0) 
	{
		pdx = fabs(pdx);
	} 
	else if (plat2_x1 >= screen_width() - (screen_width() * 0.66))
	{
		pdx = -fabs(pdx);
	}
	
	
	if (pdx != sprite_dx(plat2)) {
		sprite_back(plat2);
		sprite_turn_to(plat2, pdx, 0);
	}
	
	// Upper platform.
	int plat_x3;
	int plat_y3;
	
	plat_x3 = plat_x;
	plat_y3 = plat_y2 - (HERO_HEIGHT * 3.5);
	
	plat3 = sprite_create(plat_x3 + 1, plat_y3, screen_width() * 0.66, 1, plat_image);
	draw_string(screen_width() - 2, plat_y3, singlep);
	
	// Create the pit.
	int pit_x;
	int pit_y;
	
	pit_x = screen_width() - (screen_width() * 0.2) - 7;
	pit_y = screen_height() - 1;
	
	
	draw_line(pit_x, pit_y, pit_x + 9, pit_y, ' ');

	pit = sprite_create(pit_x, pit_y - 1, 7, 1, pit_image);
	
	// Hero and pit collision.
	if (hero_x > pit_x && hero_x < pit_x + 6 && hero_y + HERO_HEIGHT == screen_height() - 2) {
		nopit = false;
		sprite_turn_to(hero, sprite_dx(hero), 0.2);
		
	}
	if (hero_y > sprite_y(plat)) {
			nopit = true;
			lives--;
			restart_level();
			sprite_turn_to(hero, sprite_dx(hero), 0.2);
	}
	
	// Boulder and pit collision.
	if (sprite_x(bould) > pit_x /*&& sprite_x(bould) < screen_width() */&& sprite_y(bould) < screen_height() - 2 && sprite_y(bould) > screen_height() - 1 - (HERO_HEIGHT * 3.5)) {
		nopitB = false;
		sprite_turn_to(bould, sprite_dx(bould), 0.2);
		
	}
	if (sprite_y(bould) > sprite_y(plat)) {
			nopitB = true;
			//lives--;
			//restart_level(); 
			level5_setup();
	}
	
	// Create the barrier. 
	int bar_x;
	int bar_y;
	
	bar_x = (screen_width() - 1) * 0.66;
	bar_y = screen_height() - (HERO_HEIGHT * 3.5);
	
	barrier = sprite_create(bar_x, bar_y, 2, HERO_HEIGHT * 3.5, bar_image);
	
	// Setup treasure position.
	int treas_x;
	int treas_y;
	
	treas_x = screen_width() / 2;
	treas_y = plat_y2 - HERO_HEIGHT * 1.5;
	
	treas = sprite_create(treas_x, treas_y, 1, 1, treas_image);
	
	sparkle = sprite_create(treas_x - 2, treas_y - 1, 5, 3, tsparkle_image);
	sparkle2 = sprite_create(treas_x - 2, treas_y - 1, 5, 3, tsparkle2_image);
	
	if (treasure) {
		sprite_draw(treas);
		
		if (time < 50) {
		sprite_draw(sparkle);
		} else {
			sprite_draw(sparkle2);
		}
		
		if (sprites_collided(hero, treas)) {
			score += 50;
			sprite_hide(treas);
			sprite_hide(sparkle);
			sprite_hide(sparkle2);
			treasure = false;
		}
	}
	
	// Setup key position.
	int key_x;
	int key_y;
	
	key_x = screen_width() - HERO_WIDTH * 3;
	key_y = plat_y3 - HERO_HEIGHT * 2;
	
	key = sprite_create(key_x, key_y, 3, 1, key_image);
	
	ksparkle = sprite_create(key_x - 3, key_y - 2, 9, 5, ksparkle_image);
	ksparkle2 = sprite_create(key_x - 3, key_y - 2, 9, 5, ksparkle2_image);
	
	if (nokey) {
		sprite_draw(key);
		
		if (time < 50) {
		sprite_draw(ksparkle);
		} else {
			sprite_draw(ksparkle2);
		}
		
		if (sprites_collided(hero, key)) {
			sprite_hide(key);
			sprite_hide(ksparkle);
			sprite_hide(ksparkle2);
			nokey = false;
		}
	}
	
	// Platform collision.
		// Hitting the bottom of platform 1.
	if (sprites_collided(hero, plat1) && hero_y - HERO_HEIGHT < sprite_y(plat1)) {
		sprite_move(hero, 0, 1);
		sprite_turn_to(hero, sprite_dx(hero), 0);
	}
	
		// Landing on top of platform 1.
	if (sprites_collided(hero, plat1) && hero_y + HERO_HEIGHT > sprite_y(plat1) - 1) {
		sprite_move(hero, 0, -2);
		sprite_turn_to(hero, sprite_dx(hero), 0);
	}
	
		// Hitting the bottom of platform 2.
	if (sprites_collided(hero, plat2) && hero_y - HERO_HEIGHT < sprite_y(plat2)) {
		sprite_move(hero, 0, 1);
		sprite_turn_to(hero, sprite_dx(hero), 0);
	}
	
		// Landing on top of platform 2.
	if (sprites_collided(hero, plat2) && hero_y + HERO_HEIGHT > sprite_y(plat2) - 1) {
		sprite_move(hero, 0, -2);
		sprite_turn_to(hero, sprite_dx(hero), 0);
	}
	
		// Hitting the bottom of platform 3.
	if (sprites_collided(hero, plat3) && hero_y - HERO_HEIGHT < sprite_y(plat3)) {
		sprite_move(hero, 0, 1);
		sprite_turn_to(hero, sprite_dx(hero), 0);
	}
	
		// Landing on top of platform 3.
	if (sprites_collided(hero, plat3) && hero_y + HERO_HEIGHT > sprite_y(plat3) - 1) {
		sprite_move(hero, 0, -2);
		sprite_turn_to(hero, sprite_dx(hero), 0);
	}
	
	if (nokey) {
			// Hitting the barrier from the left.
		// When the hero is not jumping.
		if (sprites_collided(hero, barrier) && hero_x - HERO_WIDTH < sprite_x(barrier) && sprite_dy(hero) == 0) {
			sprite_move(hero, -1, 0);
			sprite_turn_to(hero, 0, 0);
		}
		// Jumping up.
		if (sprites_collided(hero, barrier) && hero_x - HERO_WIDTH < sprite_x(barrier) && sprite_dy(hero) < 0) {
			sprite_move(hero, -1, 0);
			sprite_turn_to(hero, 0, sprite_dy(hero));
		}
		// Jumping down.
		if (sprites_collided(hero, barrier) && hero_x - HERO_WIDTH < sprite_x(barrier) && sprite_dy(hero) > 0) {
			sprite_move(hero, -1, 0);
			sprite_turn_to(hero, 0, sprite_dy(hero));
		}
		
			// Hitting the barrier from the right.
		// When the hero is not jumping.
		if (sprites_collided(hero, barrier) && hero_x + HERO_WIDTH > sprite_x(barrier) && sprite_dy(hero) == 0) {
			sprite_move(hero, 2, 0);
			sprite_turn_to(hero, 0, 0);
		}
		// Jumping up.
		if (sprites_collided(hero, barrier) && hero_x + HERO_WIDTH > sprite_x(barrier) && sprite_dy(hero) < 0) {
			sprite_move(hero, 2, 0);
			sprite_turn_to(hero, 0, sprite_dy(hero));
		}
		// Jumping down.
		if (sprites_collided(hero, barrier) && hero_x + HERO_WIDTH > sprite_x(barrier) && sprite_dy(hero) > 0) {
			sprite_move(hero, 2, 0);
			sprite_turn_to(hero, 0, sprite_dy(hero));
		}
	}
	
	if (!nokey) {
		sprite_hide(key);
		
		if (hero_x > sprite_x(barrier) && hero_y > screen_height() - (HERO_HEIGHT * 3.5)) {
			is_barrier = false;
		}
	}
	if (!is_barrier) {
		sprite_hide(barrier);
	}
	
	sprite_step(bould);
	
	int bould_x;
	//int bould_y;
	
	bould_x = round(sprite_x(bould));
	//bould_y = round(sprite_y(bould));
	
	double zdx;
	//double zdy;
	
	zdx = sprite_dx(bould);
	//zdy = sprite_dy(bould);	
	
	
	if (bould_x <= 2) 
	{
		zdx = fabs(zdx);
	} 
	else if (bould_x >= screen_width() - MONSTER_WIDTH - 2)
	{
		zdx = -fabs(zdx);
	}
	
	
	if (zdx != sprite_dx(bould)) {
		sprite_back(bould);
		sprite_turn_to(bould, zdx, 0);
	}
	
	// Boulder collision.
	if (sprites_collided(hero, bould)) {
		if (monstercol) {
			lives--;
			restart_level();
		}
	}
	
	// Boulder on platform collision.	
		// Landing on top of platform 1.
	if (sprites_collided(bould, plat1) && sprite_y(bould) + 2 > sprite_y(plat1) - 1) {
		sprite_move(bould, 0, -1);
		sprite_turn_to(bould, sprite_dx(bould), 0);
	}
	
		// Landing on top of platform 2.
	if (sprites_collided(bould, plat2) && sprite_y(bould) + 2 > sprite_y(plat2) - 1) {
		sprite_move(bould, 0, -1);
		sprite_turn_to(bould, sprite_dx(bould), 0);
	}
	
		// Landing on top of platform 3.
	if (sprites_collided(bould, plat3) && sprite_y(bould) + 2 > sprite_y(plat3) - 1) {
		sprite_move(bould, 0, -1);
		sprite_turn_to(bould, sprite_dx(bould), 0);
	}
	
	// Boulder landing on platform.
	if (nopitB) {
		if (sprites_collided(bould, plat)) {
				sprite_move(bould, 0, -1);
				sprite_turn_to(bould, sprite_dx(bould), 0);
		}
	}

		// Exit door collision.
	sprite_draw(exitd);
	if (sprites_collided(hero, exitd)) {
		monstercol = false;
		sprite_hide(hero);
		sprite_hide(hjump);
		sprite_turn_to(hero, 0, 0);
		sprite_draw(hexit);
		sprite_step(hexit);
		sprite_turn_to(hexit, 0.05, 0);
		if (sprite_x(hexit) + 3 > sprite_x(exitd) + 3) {
			score += 100;
			monstercol = true;
			finish_screen();
		}
		
	}  
	
	sprite_draw(key);
	sprite_draw(bould);
	
}
bool jumper = false;
void move_hero() {
	// Receive user input.
	int key;
	key = get_char();
	//int jumpkey;
	//jumpkey = get_char();
	
	// Skip to next level.
	if (key == 'l') {
		level++;
		restart_level();
		if (level == 6 && key == 'l') {
			finish_screen();
		}
		treasure = true;
		nokey = true;
	}
	
	// Boulder gravity.
	double bdy = sprite_dy(bould);
	
	if (sprite_y(bould) < sprite_y(plat)) {
			bdy += 0.006;
			sprite_turn_to(bould, sprite_dx(bould), bdy);
	} 
	
	// Declaring necessary variables.
	int hero_x;
	int hero_y;
	
	hero_x = sprite_x(hero);
	hero_y = sprite_y(hero);
	
	sprite_step(hero);
	
	double hdx;
	hdx = 0.2;
	
	if (jump) {
		double hdy = sprite_dy(hero);
		
		if (jump) {
			sprite_step(hero);
			hdy += 0.02;
			sprite_turn_to(hero, sprite_dx(hero), hdy);
			
			if (sprites_collided(hero, plat) && hero_y < sprite_y(plat) - HERO_HEIGHT + 1) { 
				jump = false;
			}
			
			if (sprites_collided(hero, plat1) && hero_y < sprite_y(plat1) - HERO_HEIGHT + 1) { 
				jump = false;
			}
			
			if (hero_y < sprite_y(plat)) {
				jump = true;
			}
			
			if (sprites_collided(hero, plat)) {
				jump = false;
			}
			
			
			
		} 
		
	}

	
	if (key == KEY_UP) {
		
		jumper = true;		
		
		jump = true;
		sprite_turn_to(hero, sprite_dx(hero), -0.6);
		
		
	}
	
	if (jumper == true) {
		
		sprite_hide(hero);
		hjump = sprite_create(sprite_x(hero), sprite_y(hero), HERO_WIDTH, HERO_HEIGHT, hjump_image);
		sprite_step(hjump);
		//sprite_turn_to(hjump, sprite_dx(hero), sprite_dy(hero));
		//sprite_draw(hjump);
	}
		
	if (sprite_dy(hero) == 0) {
		jumper = false;
		//sprite_show(hjump);
		sprite_show(hero);
	} else if (sprites_collided(hero, plat1) || sprites_collided(hero, plat2) || sprites_collided(hero, plat3)) {
		jumper = false;
		//sprite_show(hjump);
		sprite_show(hero);
	} 

	double hdx_run;
	hdx_run = hdx * 2;
	
	// Initiate hero movements.
	
	// LEFT KEY movements. 
	if (key == KEY_LEFT && hero_x > 1) 
	{
		/*
		if (!jumper) {
			sprite_turn_to(hero, sprite_dx(hero), sprite_dy(hero));
		}*/
		
		if (sprite_dx(hero) == hdx_run) { // Walk right if running right
			sprite_turn_to(hero, hdx, 0); 
		} else if (sprite_dx(hero) == hdx) { // Stop walking if walking right
			sprite_turn_to(hero, 0, 0);
		} else if (sprite_dx(hero) == -hdx) { // Run if walking left
			sprite_turn_to(hero, -hdx_run, 0);
		} else if (sprite_dx(hero) == 0) { // Walk left if you're doing anything else
			sprite_turn_to(hero, -hdx, 0);
		} else {
			sprite_turn_to(hero, -hdx_run, 0);
		}
						
	}

	// RIGHT KEY movements.
	if (key == KEY_RIGHT && hero_x < screen_width() - HERO_WIDTH - 1) 
	{
		/*
		if (jump) {
			sprite_turn_to(hero, sprite_dx(hero), sprite_dy(hero));
		}*/
		
		if (sprite_dx(hero) == -hdx_run) { // Walk left when you are running left
			sprite_turn_to(hero, -hdx, 0);
		} else if (sprite_dx(hero) == -hdx) { // Stop walking if walking left
			sprite_turn_to(hero, 0, 0); 
		} else if (sprite_dx(hero) == hdx) { // Run if walking right
			sprite_turn_to(hero, hdx_run, 0);
		} else if (sprite_dx(hero) == 0){ // Walk right if you're doing anything else
			sprite_turn_to(hero, hdx, 0);
		} else {
			sprite_turn_to(hero, hdx_run, 0);
		}
		
	}
		
}

bool exit1 = true;

void process( void ) {	
	
	// Drawing all elements. 
	

	//sprite_draw(exitd);
	sprite_draw(hero);
	if (jumper) {
		sprite_draw(hjump);
	}
	
	/* // Exit door collision.
	if (sprites_collided(hero, exitd)) {
		exit1 = false;
		score += 100;
		sprite_hide(hero);
		sprite_draw(hexit);
		sprite_step(hexit);
		sprite_turn_to(hexit, 0.001, 0);
		if (sprite_x(hexit) + 1 == sprite_x(exitd)) {
			
			level++;
			restart_level();
		}
		
	} */




}

		
// Clean up game
void cleanup( void ) {
	// STATEMENTS
}	

int main( void ) {
	setup_screen();
	setup();
	level5_setup();
	
	while (!game_over)
	{
		// Clearing screen.
		clear_screen();
		
		// Starting the timer.
		timer();
		
		// Drawing the border.
		draw_border();
		
		// Displaying the status bar.
		display_status();
		
		//Start process.
		move_hero();
		
		//jump_time++;
		
		//Levels
		
		if (level == 1) {
			level1();
			sprite_draw(plat1);
		} else if (level == 2) {
			level2();
			sprite_draw(plat1);
			sprite_draw(plat2);
		} else if (level == 3) {
			level3();
			sprite_draw(plat1);
			sprite_draw(plat2);
			sprite_draw(wall);
			sprite_draw(pit);
		} else if (level == 4) {
			level4();
			sprite_draw(plat1);
			sprite_draw(plat2);
			sprite_draw(plat3);
			sprite_draw(barrier);
		} else {
			level5();
			sprite_draw(plat1);
			sprite_draw(plat2);
			sprite_draw(plat3);
			sprite_draw(barrier);
		}
		gravity();
		// Update screen.
		if (update_screen) {
			process();
			show_screen();
		}
		timer_pause(DELAY);
		
		if (lives == 0) {
			clear_screen();
			gameover_screen();
			
		}
	}
	
	cleanup();
	return 0;
}






