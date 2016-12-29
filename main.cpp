#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_primitives.h>	
#include <allegro5\allegro_ttf.h>
#include <allegro5\file.h>
#include <allegro5\allegro_native_dialog.h>
#include <math.h>
#include <stdio.h>
#define FILE_EXIT_ID 1
#define FILE_LOAD_ID 2
#define FILE_SAVE_ID 3
#define FILE_NEW_ID 4

ALLEGRO_BITMAP *image = NULL;
ALLEGRO_BITMAP *image1 = NULL;
ALLEGRO_BITMAP *pencil = NULL;
ALLEGRO_BITMAP *icon = NULL;
ALLEGRO_DISPLAY *display = NULL;
ALLEGRO_KEYBOARD_STATE *keyState = NULL;
ALLEGRO_FONT* font = NULL;
ALLEGRO_FILECHOOSER *filechooser;
ALLEGRO_FILECHOOSER *filesave;

ALLEGRO_COLOR color1, color2,color3,color4;
int tool = 0;
void create_manu();
void save_image();
void load_image();
int main(void)
{
	
	


	al_set_app_name("Paint");
	
	//variables
	int width = 640;
	int height = 480;
	int thick = 1;
	bool done = false;
	bool draw = false;
	bool line = true;
	bool rect = true;
	bool rectfill = true;
	bool circle = true;
	bool circlefill = true;
	bool tri = true;
	bool tri1 = true;
	bool tri2 = true;
	bool fileCho = false;
	bool trifill = true;
	int imageWidth = 0;
	int imageHeight = 0;
	int pos_x = 0;
	int pos_y = 0;
	int Cpos_x = 0;
	int Cpos_y = 0;
	int Cpos_x2 = 0;
	int Cpos_y2 = 0;
	int Cpos_x3 = 0;
	int Cpos_y3 = 0;

	//allegro variable

	ALLEGRO_EVENT_QUEUE *event_queue = NULL;

	//program init
	if (!al_init())										
		return -1;

	display = al_create_display(width, height);			

	if (!display)										
		return -1;
	
	
	//addon init
	al_init_image_addon();
	al_init_primitives_addon();
	al_init_native_dialog_addon();
	al_init_font_addon();
	al_install_mouse();
	al_init_ttf_addon();
	al_install_keyboard();



	// image
	icon = al_load_bitmap("icon.jpg");
	image = al_load_bitmap("image.png");
	pencil = al_load_bitmap("pencil.png");
	al_set_display_icon(display, icon);
	imageWidth = al_get_bitmap_width(image);
	imageHeight = al_get_bitmap_height(image);

	
	event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_mouse_event_source());
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	

	al_clear_to_color(al_map_rgb(255, 255, 255));
	while (!done)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);
		




	f (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			int button = al_show_native_message_box(
				display,
				"UYARI",
				"Cikmak istediginize eminmisiniz?",
				"Harbimi ?",
				NULL,
				ALLEGRO_MESSAGEBOX_YES_NO
				);
			if (button)
			{
				done = true;
			}
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_UP)
		{
			if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
			{
				int button = al_show_native_message_box(
					display,
					"UYARI",
					"Cikmak istediginize eminmisiniz?",
					"Harbimi ?",
					NULL,
					ALLEGRO_MESSAGEBOX_YES_NO
					);
				if (button)
				{
					done = true;
				}
			}
				
		}
		else if (ev.type == ALLEGRO_EVENT_MOUSE_AXES)
		{
			if (ev.mouse.x > 100)
			{
				pos_x = ev.mouse.x;
				pos_y = ev.mouse.y;
			}
			
		}
		else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{
			if(Cpos_x2>100)
			Cpos_x3 = Cpos_x2;
			Cpos_y3 = Cpos_y2;
			if (Cpos_x>100)
			Cpos_x2 = Cpos_x;
			Cpos_y2 = Cpos_y;
			Cpos_x = ev.mouse.x;
			Cpos_y = ev.mouse.y;
			if (ev.mouse.button & 1) {
				if (Cpos_x > 100)
					draw = !draw;
			}
		}

		// COLOR CONTROL
		if(!done)
		{ 
		color4 = al_get_pixel(image, Cpos_x, Cpos_y);
		if (Cpos_x > 0 &&Cpos_x < 100)
		{
			if (Cpos_y > 0 && Cpos_y < 120)
			{
				unsigned char r, g, b;
				al_unmap_rgb(color4, &r, &g, &b);
				bool isColor = (r == 200 && g == 200 && b == 200);
				if (!isColor)
				{
					color2 = color1;
					color1 = al_get_pixel(image, Cpos_x, Cpos_y);
				}

			}
		}
		}
		// TOOL SELECT
		if(!done) {
		if (Cpos_y > 130 && Cpos_y < 200&& Cpos_x > 10 && Cpos_x < 20)
		{
				tool = 1;
		}
		else if (Cpos_y > 130 && Cpos_y < 200&& Cpos_x > 25 && Cpos_x < 35)
		{
				tool = 2;
				Cpos_x2 = 0;
				Cpos_y2 = 0;
							
		}
		else if (Cpos_x > 40 && Cpos_x < 60 && Cpos_y>130 && Cpos_y < 150)
		{
			tool = 3;
			Cpos_x2 = 0;
			Cpos_y2 = 0;
		}
		else if (Cpos_x > 70 && Cpos_x < 90 && Cpos_y>130 && Cpos_y < 150)
		{
			tool = 4;
			Cpos_x2 = 0;
			Cpos_y2 = 0;

		}
		else if (Cpos_x > 40 && Cpos_x < 60 && Cpos_y>160 && Cpos_y < 180)
		{
			tool = 5;
			Cpos_x2 = 0;
			Cpos_y2 = 0;
		}
		else if (Cpos_x > 70 && Cpos_x < 90 && Cpos_y>160 && Cpos_y < 180)
		{
			tool = 6;
			Cpos_x2 = 0;
			Cpos_y2 = 0;
		}
		else if (Cpos_x > 40 && Cpos_x < 60 && Cpos_y>190 && Cpos_y < 210)
		{
			tool = 7;
			Cpos_x2 = 0;
			Cpos_y2 = 0;
			Cpos_x3 = 0;
			Cpos_y3 = 0;
		}
		else if (Cpos_x > 70 && Cpos_x < 90 && Cpos_y>190 && Cpos_y < 210)
		{
			tool = 8;
			Cpos_x2 = 0;
			Cpos_y2 = 0;
			Cpos_x3 = 0;
			Cpos_y3 = 0;
		}
		}
		// KALINLIK
		if(!done){
		if (Cpos_x > 10 && Cpos_x < 50 && Cpos_y>210 && Cpos_y < 230)
		{
			thick = 2;
		}
		else if (Cpos_x > 10 && Cpos_x < 50 && Cpos_y>235 && Cpos_y < 265)
		{
			thick = 3; 
		}
		else if (Cpos_x > 10 && Cpos_x < 50 && Cpos_y>260 && Cpos_y < 300)
		{
			thick = 4;
		}
		}

		// DRAW
		if (draw==true&&pos_x>100)
		{
		if(tool==1){

			if (thick == 1)
			{
				al_draw_pixel(pos_x, pos_y, color1);
			}
			else if(thick==2)
			{
				al_draw_pixel(pos_x, pos_y, color1);
				al_draw_pixel(pos_x + 1, pos_y, color1);

				al_draw_pixel(pos_x, pos_y + 1, color1);
				al_draw_pixel(pos_x + 1, pos_y + 1, color1);
			}
			else if (thick == 3)
			{
				al_draw_pixel(pos_x + 1, pos_y, color1);
				al_draw_pixel(pos_x, pos_y, color1);
				al_draw_pixel(pos_x - 1, pos_y, color1);

				al_draw_pixel(pos_x + 1, pos_y+1, color1);
				al_draw_pixel(pos_x, pos_y+1, color1);
				al_draw_pixel(pos_x - 1, pos_y+1, color1);

				al_draw_pixel(pos_x + 1, pos_y-1, color1);
				al_draw_pixel(pos_x, pos_y-1, color1);
				al_draw_pixel(pos_x - 1, pos_y-1, color1);
				
			}
			else
			{
				

				al_draw_pixel(pos_x + 2, pos_y, color1);
				al_draw_pixel(pos_x + 1, pos_y, color1);
				al_draw_pixel(pos_x,     pos_y, color1);
				al_draw_pixel(pos_x - 1, pos_y, color1);
				al_draw_pixel(pos_x - 2, pos_y, color1);

				al_draw_pixel(pos_x - 2, pos_y + 1, color1);
				al_draw_pixel(pos_x - 1, pos_y + 1, color1);
				al_draw_pixel(pos_x    , pos_y + 1, color1);
				al_draw_pixel(pos_x + 1, pos_y + 1, color1);
				al_draw_pixel(pos_x + 2, pos_y + 1, color1);

				al_draw_pixel(pos_x - 2, pos_y - 1, color1);
				al_draw_pixel(pos_x - 1, pos_y - 1, color1);
				al_draw_pixel(pos_x, pos_y - 1, color1);
				al_draw_pixel(pos_x + 1, pos_y - 1, color1);
				al_draw_pixel(pos_x + 2, pos_y - 1, color1);

				al_draw_pixel(pos_x - 2, pos_y + 2, color1);
				al_draw_pixel(pos_x - 1, pos_y + 2, color1);
				al_draw_pixel(pos_x, pos_y + 2, color1);
				al_draw_pixel(pos_x + 1, pos_y + 2, color1);
				al_draw_pixel(pos_x + 2, pos_y + 2, color1);

				al_draw_pixel(pos_x - 2, pos_y - 2, color1);
				al_draw_pixel(pos_x - 1, pos_y - 2, color1);
				al_draw_pixel(pos_x, pos_y - 2, color1);
				al_draw_pixel(pos_x + 1, pos_y - 2, color1);
				al_draw_pixel(pos_x + 2, pos_y - 2, color1);
			}
				
				}
		if (tool == 2 && Cpos_x2 != 0 && Cpos_y2 != 0&& Cpos_x > 100 && Cpos_x2>100)
		{
				if (line == true)
				{
					al_draw_line(Cpos_x2, Cpos_y2, Cpos_x, Cpos_y, color1, thick);
					Cpos_x2 = 0;
					Cpos_y2 = 0;
					line = false;
				}
				else
				{
					line = true;
				}}
		if (tool == 3 && Cpos_x2 != 0 && Cpos_y2 != 0 && Cpos_x > 100 && Cpos_x2 > 100)
		{
			if (rect == true)
			{
				al_draw_rectangle(Cpos_x, Cpos_y, Cpos_x2, Cpos_y2, color1, thick);
				Cpos_x2 = 0;
				Cpos_y2 = 0;
				rect = false;
			}
			else
			{
				rect = true;
			}
		}
		if (tool == 4 && Cpos_x2 != 0 && Cpos_y2 != 0 && Cpos_x > 100 && Cpos_x2 > 100)
		{
			if (rectfill == true)
			{
				al_draw_filled_rectangle(Cpos_x, Cpos_y, Cpos_x2, Cpos_y2, color1);
				Cpos_x2 = 0;
				Cpos_y2 = 0;
				rectfill = false;
			}
			else
			{
				rectfill = true;
			}
		}
		if (tool == 5 && Cpos_x2 != 0 && Cpos_y2 != 0 && Cpos_x > 100 && Cpos_x2 > 100)
		{
			if (circle == true)
			{
				float capX = fabs(Cpos_x - Cpos_x2);
				float capY = fabs(Cpos_y - Cpos_y2);
				float cap = sqrt(capX*capX + capY*capY);
				
				al_draw_ellipse(Cpos_x2, Cpos_y2,capX,capY, color1, thick);
				
				//al_draw_circle(Cpos_x2, Cpos_y2, cap, color1, 1);
				Cpos_x2 = 0;
				Cpos_y2 = 0;
				circle = false;
			}
			else
			{
				circle = true;
			}
			{

			}
		}
		if (tool == 6 && Cpos_x2 != 0 && Cpos_y2 != 0 && Cpos_x > 100 && Cpos_x2 > 100)
		{
			if (circlefill == true)
			{
				float capX = fabs(Cpos_x - Cpos_x2);
				float capY = fabs(Cpos_y - Cpos_y2);
				float cap = sqrt(capX*capX + capY*capY);
				al_draw_filled_ellipse(Cpos_x2, Cpos_y2, capX*2, capY*2, color1);
				Cpos_x2 = 0;
				Cpos_y2 = 0;
				circlefill = false;
			}
			else
			{
				circlefill = true;
			}
		}
		if (tool == 7 && Cpos_x2 != 0 && Cpos_y2 != 0 && Cpos_x3!=0&&Cpos_y3!=0&&Cpos_x > 100 && Cpos_x2 > 100&&Cpos_x3>100)
		{
			
			
			if (tri == true)
			{
				
				al_draw_triangle(Cpos_x3, Cpos_y3, Cpos_x2, Cpos_y2, Cpos_x, Cpos_y, color1, thick);
				Cpos_x3 = 0;
				Cpos_x2 = 0;
				Cpos_y2 = 0;
				Cpos_y3 = 0;
				Cpos_x = 0;
				Cpos_y = 0;
				tri = false;
			
			}
			else
			{	
				tri = true;
				
			}
				
				
			
		}
		if (tool == 8 && Cpos_x2 != 0 && Cpos_y2 != 0 && Cpos_x > 100 && Cpos_x2 > 100&&Cpos_x3>100)
		{

			if (trifill == true)
			{
				al_draw_filled_triangle(Cpos_x3, Cpos_y3, Cpos_x2, Cpos_y2, Cpos_x, Cpos_y, color1);

				Cpos_x3 = 0;
				Cpos_x2 = 0;
				Cpos_y2 = 0;
				Cpos_y3 = 0;
				Cpos_x = 0;
				Cpos_y = 0;
				trifill = false;
			}
			else
			{
				trifill = true;
			}
		}


		}
	
		create_manu();
		al_flip_display();
	}

	




	
	al_clear_to_color(al_map_rgb(0, 0, 0));	
	al_destroy_bitmap(icon);
	al_destroy_bitmap(pencil);
	al_destroy_bitmap(image);
	al_destroy_font(font);
	al_destroy_event_queue(event_queue);
	al_destroy_display(display);						//destroy our display object

	return 0;
}

void create_manu()
{

	

	font = al_load_font("arial.ttf", 18, 0);
	
	// MENÜ
	al_draw_filled_rectangle(0, 0, 100, 480, al_map_rgb(200, 200, 200));
	// RENKLER
	al_draw_filled_rectangle(10, 10, 40, 40, al_map_rgb(255, 255, 255));
	al_draw_filled_rectangle(50, 10, 80, 40, al_map_rgb(255, 0, 0));
	al_draw_filled_rectangle(10, 50, 40, 80, al_map_rgb(0, 255, 0));
	al_draw_filled_rectangle(50, 50, 80, 80, al_map_rgb(0, 0, 255));
	al_draw_filled_rectangle(10, 90, 40, 120, al_map_rgb(240, 240, 0));
	al_draw_filled_rectangle(50, 90, 80, 120, al_map_rgb(255, 0, 255));
	// ARAÇLAR
	al_draw_bitmap(pencil, 10, 130, 1);
	al_draw_line(30, 130, 30, 200, al_map_rgb(255, 255, 255),5);
	al_draw_rectangle(40, 130, 60, 150, al_map_rgb(255, 255, 255), 1);
	al_draw_filled_rectangle(70,130,90,150, al_map_rgb(255, 255, 255));
	al_draw_circle(50, 170, 10, al_map_rgb(255, 255, 255), 1);
	al_draw_filled_circle(80, 170, 10, al_map_rgb(255, 255, 255));
	al_draw_triangle(40, 210 , 60,210, 50, 190, al_map_rgb(255, 255, 255), 1);
	al_draw_filled_triangle(70, 210, 90, 210, 80, 190, al_map_rgb(255, 255, 255));
	// KALINLIK
	al_draw_line(10, 220, 50, 220, al_map_rgb(255, 255, 255), 10);
	al_draw_line(10, 250, 50, 250, al_map_rgb(255, 255, 255), 15);
	al_draw_line(10, 280, 50, 280, al_map_rgb(255, 255, 255), 20);
	
}

void save_image() 
{
	ALLEGRO_BITMAP *bmp = al_create_sub_bitmap(al_get_backbuffer(display), 100, 0, 540, 480);

	ALLEGRO_PATH *pSavePath = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
	filesave = al_create_native_file_dialog(al_path_cstr(pSavePath, ALLEGRO_NATIVE_PATH_SEP), "Save Game...", "*.png", ALLEGRO_FILECHOOSER_SAVE);
	if (al_show_native_file_dialog(display, filesave))
	{
		int counter = al_get_native_file_dialog_count(filesave);
		const char *filename = NULL;
		filename = al_get_native_file_dialog_path(filesave, 0);
		if (filename)
			al_save_bitmap(filename, bmp);
		if (!filename)
		{
			al_destroy_native_file_dialog(filesave);
		}
	}
}

void load_image()
{
	filechooser = al_create_native_file_dialog("C:", "Choose a file.", "*.*;*.png;", 1);
	if (filechooser)
	{
		al_show_native_file_dialog(display, filechooser);
		int counter = al_get_native_file_dialog_count(filechooser);
		const char* path = al_get_native_file_dialog_path(filechooser, 0);
		if (path)
		{
			image1 = al_load_bitmap(path);

			if (!image1) {
				al_destroy_bitmap(image1);
				al_destroy_native_file_dialog(filechooser);
			}
			al_draw_bitmap(image1, 100, 0, 1);
			al_destroy_bitmap(image1);
			al_destroy_native_file_dialog(filechooser);
			
		}

	}
}
