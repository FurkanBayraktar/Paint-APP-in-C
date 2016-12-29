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
ALLEGRO_BITMAP *pencil = NULL;
ALLEGRO_BITMAP *icon = NULL;
ALLEGRO_BITMAP *menu = NULL;
ALLEGRO_DISPLAY *display = NULL;
ALLEGRO_KEYBOARD_STATE *keyState = NULL;
ALLEGRO_FILECHOOSER *filechooser;
ALLEGRO_FILECHOOSER *filesave;

ALLEGRO_COLOR color1=al_map_rgb(0,0,0);
ALLEGRO_COLOR color2, color3, color4;
int tool = 1;
int selectTool = 0;
ALLEGRO_COLOR selectColor;


void save_image();
void load_image();
bool done = false;
int main(void)
{



	al_set_app_name("Paint");

	//variables
	int width = 640;
	int height = 560;
	int thick = 1;

	bool draw = false;
	bool line = true;
	bool rect = true;
	bool drawPix = false;
	bool drawEras = false;
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
	al_init_ttf_addon();
	al_install_mouse();
	al_install_keyboard();

	al_init();




	// image
	icon = al_load_bitmap("icon.jpg");
	image = al_load_bitmap("image.png");
	pencil = al_load_bitmap("pencil.png");
	al_set_display_icon(display, icon);
	imageWidth = al_get_bitmap_width(image);
	imageHeight = al_get_bitmap_height(image);

	ALLEGRO_BITMAP *mouse = al_load_bitmap("kalem.png");
	ALLEGRO_BITMAP *erraser = al_load_bitmap("eraser1.png");
	



	ALLEGRO_MOUSE_CURSOR *mouseCursor = al_create_mouse_cursor(mouse, 0, 32);
	ALLEGRO_MOUSE_CURSOR *mouseCursor2 = al_create_mouse_cursor(erraser,0,15);
	event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_mouse_event_source());
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_keyboard_event_source());

	al_clear_to_color(al_map_rgb(255, 255, 255));
	color1=al_map_rgb(0,0,0);

	while (!done)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);





		if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			int button = al_show_native_message_box(
				display,
				"UYARI",
					"",
					"Cikmak istediginize eminmisiniz?",
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
					"",
					"Cikmak istediginize eminmisiniz?",
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
		
				pos_x = ev.mouse.x;
				pos_y = ev.mouse.y;
			

		}
		else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{
			if (Cpos_x2>125)
				Cpos_x3 = Cpos_x2;
			Cpos_y3 = Cpos_y2;
			if (Cpos_x>125)
			Cpos_x2 = Cpos_x;
			Cpos_y2 = Cpos_y;
			
			Cpos_x = ev.mouse.x;
			Cpos_y = ev.mouse.y;
			
			if (ev.mouse.button & 1) {
				if (Cpos_x > 125)
				{
					draw = !draw;
					drawPix = true;
					drawEras = true;
				}
		// COLOR CONTROL		
		if(Cpos_x>=34&&Cpos_x<=58&&Cpos_y>=4&&Cpos_y<=28)
		{
			color2=color1;
			color1=al_map_rgb(0,0,0);
		}
		else if(Cpos_x>=61&&Cpos_x<=85&&Cpos_y>=4&&Cpos_y<=28)
		{
			color2=color1;
			color1=al_map_rgb(127,127,127);
		}
		else if(Cpos_x>=88&&Cpos_x<=112&&Cpos_y>=4&&Cpos_y<=28)
		{
			color2 = color1;
			color1 = al_map_rgb(255,255,255);
		}
		else if(Cpos_x>=34&&Cpos_x<=58&&Cpos_y>=31&&Cpos_y<=55)
		{
			color2= color1;
			color1 = al_map_rgb(136,0,21);
		}
		else if(Cpos_x>=61&&Cpos_x<=85&&Cpos_y>=31&&Cpos_y<=55){
			color2=color1;
			color1 = al_map_rgb(237,28,36);
		}
		else if(Cpos_x>=88&&Cpos_x<=112&&Cpos_y>=31&&Cpos_y<=55)
		{
			color2=color1;
			color1=al_map_rgb(255,127,39);
		}
		else if(Cpos_x>=34&&Cpos_x<=58&&Cpos_y>=58&&Cpos_y<=82) 
		{
			color2=color1;
			color1=al_map_rgb(255,242,0);
		}
		else if(Cpos_x>=61&&Cpos_x<=85&&Cpos_y>=58&&Cpos_y<=82)
		{
			color2=color1;
			color1=al_map_rgb(34,177,76);
		}
		else if(Cpos_x>=88&&Cpos_x<=112&&Cpos_y>=58&&Cpos_y<=82)
		{
			color2=color1;
			color1=al_map_rgb(0,162,232);
		}
		else if(Cpos_x>=34&&Cpos_x<=58&&Cpos_y>=85&&Cpos_y<=109)
		{
			color2=color1;
			color1=al_map_rgb(63,72,204);
		}
		else if(Cpos_x>=61&&Cpos_x<=85&&Cpos_y>=85&&Cpos_y<=109)
		{
			color2=color1;
			color1=al_map_rgb(163,73,164);
		}
		else if(Cpos_x>=88&&Cpos_x<=112&&Cpos_y>=85&&Cpos_y<=109)
		{
			color2=color1;
			color1=al_map_rgb(234,11,252);
		}
		else if(Cpos_x>=83&&Cpos_y>=395&&Cpos_x<=106&&Cpos_y<=418)
		{
			
			color3=color1;
			color1=color2;
			color2=color3;
			
		}
			}
		}
		else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
		{
			if (ev.mouse.button & 1) {
				if (Cpos_x > 125)
				{
					drawPix = false;
					drawEras = false;
					
				}
			}
		}

	
	

	
		
		if (!done) {
		// TOOL SELECT
			if (Cpos_x>=34&&Cpos_y>=135&&Cpos_x<=58&&Cpos_y<=159)
			{
				tool = 1;
			}
			else if (Cpos_x>=61&&Cpos_y>=135&&Cpos_x<=85&&Cpos_y<=159)
			{
				tool = 2;
				Cpos_x2 = 0;
				Cpos_y2 = 0;
				draw = false;

			}
			else if (Cpos_x>=34&&Cpos_y>=162&&Cpos_x<=58&&Cpos_y<=186)
			{

				tool = 3;
				Cpos_x2 = 0;
				Cpos_y2 = 0;
				draw = false;
			}
			else if (Cpos_x>=34&&Cpos_y>=189&&Cpos_x<=58&&Cpos_y<=213)
			{
				tool = 4;
				Cpos_x2 = 0;
				Cpos_y2 = 0;

			}
			else if (Cpos_x>=61&&Cpos_y>=162&&Cpos_x<=85&&Cpos_y<=186)
			{
				tool = 5;
				Cpos_x2 = 0;
				Cpos_y2 = 0;
			}
			else if (Cpos_x>=61&&Cpos_y>=189&&Cpos_x<=85&&Cpos_y<=213)
			{
				tool = 6;
				Cpos_x2 = 0;
				Cpos_y2 = 0;
			}
			else if (Cpos_x>=88&&Cpos_y>=162&&Cpos_x<=112&&Cpos_y<=186)
			{
				tool = 7;
				Cpos_x2 = 0;
				Cpos_y2 = 0;
				Cpos_x3 = 0;
				Cpos_y3 = 0;
			}
			else if (Cpos_x>=88&&Cpos_y>=189&&Cpos_x<=112&&Cpos_y<=213)
			{
				tool = 8;
				Cpos_x2 = 0;
				Cpos_y2 = 0;
				Cpos_x3 = 0;
				Cpos_y3 = 0;
			}
			else if(Cpos_x>=88&&Cpos_y>=135&&Cpos_x<=112&&Cpos_y<=159)// SÝLGÝ
			{
				tool=9;
				Cpos_x2=0;
				Cpos_y2=0;
				drawEras=false;
			}
		}
		

		// SELECT 
		selectColor = color1;
		selectTool = tool;
		// KALINLIK

		if (Cpos_x>=36&&Cpos_y>=248&&Cpos_x<=108&&Cpos_y<=272)
		{
			thick = 1;
		}
		else if (Cpos_x>=36&&Cpos_y>=279&&Cpos_x<=108&&Cpos_y<=303)
		{
			thick = 4;
		}
		else if (Cpos_x>=36&&Cpos_y>=311&&Cpos_x<=108&&Cpos_y<=335)
		{
			thick = 6;
		}

		if (drawPix == true && pos_x>120)
		{
			if (tool == 1) {

				if (thick == 1)
				{
					al_draw_pixel(pos_x, pos_y, color1);
				}
				else if (thick == 4)
				{
					al_draw_pixel(pos_x + 1, pos_y, color1);
					al_draw_pixel(pos_x, pos_y, color1);
					al_draw_pixel(pos_x - 1, pos_y, color1);

					al_draw_pixel(pos_x + 1, pos_y + 1, color1);
					al_draw_pixel(pos_x, pos_y + 1, color1);
					al_draw_pixel(pos_x - 1, pos_y + 1, color1);

					al_draw_pixel(pos_x + 1, pos_y - 1, color1);
					al_draw_pixel(pos_x, pos_y - 1, color1);
					al_draw_pixel(pos_x - 1, pos_y - 1, color1);

				}
				else
				{


					al_draw_pixel(pos_x + 2, pos_y, color1);
					al_draw_pixel(pos_x + 1, pos_y, color1);
					al_draw_pixel(pos_x, pos_y, color1);
					al_draw_pixel(pos_x - 1, pos_y, color1);
					al_draw_pixel(pos_x - 2, pos_y, color1);

					al_draw_pixel(pos_x - 2, pos_y + 1, color1);
					al_draw_pixel(pos_x - 1, pos_y + 1, color1);
					al_draw_pixel(pos_x, pos_y + 1, color1);
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
				
		}
		if(drawEras==true&&pos_x>120)
		{
				if(tool==9)
			{
				if(thick==1)
				al_draw_filled_rectangle(pos_x-3,pos_y-3,pos_x+3,pos_y+3,al_map_rgb(255,255,255));
				if(thick==4)
				al_draw_filled_rectangle(pos_x-7,pos_y-7,pos_x+7,pos_y+7,al_map_rgb(255,255,255));
				if(thick==6)
				al_draw_filled_rectangle(pos_x-15,pos_y-15,pos_x+15,pos_y+15,al_map_rgb(255,255,255));
			}
		}
		if(tool==1&&pos_x>125)
		{
			al_set_mouse_cursor(display, mouseCursor);
		}
		else if (tool!=1&&tool!=9)
		{
			al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT);
		}
		else if(tool==9&&pos_x>125)
		{
			al_set_mouse_cursor(display, mouseCursor2);
		}
		else if (pos_x<=125)
		{
			al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT);
		}

		// DRAW
		if (draw == true && pos_x>125)
		{

			if (tool == 2 && Cpos_x2 != 0 && Cpos_y2 != 0 && Cpos_x > 125 && Cpos_x2>125)
			{
				al_draw_line(Cpos_x2, Cpos_y2, Cpos_x, Cpos_y, color1, thick);
				Cpos_x2 = 0;
				Cpos_y2 = 0;
				Cpos_x = 0;
				Cpos_y = 0;

			}
			if (tool == 3 && Cpos_x2 != 0 && Cpos_y2 != 0 && Cpos_x > 125 && Cpos_x2 > 125)
			{
				al_draw_rectangle(Cpos_x, Cpos_y, Cpos_x2, Cpos_y2, color1, thick);
				Cpos_x2 = 0;
				Cpos_y2 = 0;
				Cpos_x = 0;
				Cpos_y = 0;
			}
			if (tool == 4 && Cpos_x2 != 0 && Cpos_y2 != 0 && Cpos_x > 125 && Cpos_x2 > 125)
			{
				al_draw_filled_rectangle(Cpos_x, Cpos_y, Cpos_x2, Cpos_y2, color1);
				Cpos_x2 = 0;
				Cpos_y2 = 0;
				Cpos_x = 0;
				Cpos_y = 0;

			}
			if (tool == 5 && Cpos_x2 != 0 && Cpos_y2 != 0 && Cpos_x > 125 && Cpos_x2 > 125)
			{

				float capX = fabs(Cpos_x - Cpos_x2);
				float capY = fabs(Cpos_y - Cpos_y2);
				float cap = sqrt(capX*capX + capY*capY);

				al_draw_ellipse(Cpos_x2, Cpos_y2, capX, capY, color1, thick);

				//al_draw_circle(Cpos_x2, Cpos_y2, cap, color1, 1);
				Cpos_x2 = 0;
				Cpos_y2 = 0;
				Cpos_x = 0;
				Cpos_y = 0;

			}
			if (tool == 6 && Cpos_x2 != 0 && Cpos_y2 != 0 && Cpos_x > 125 && Cpos_x2 > 125)
			{

				float capX = fabs(Cpos_x - Cpos_x2);
				float capY = fabs(Cpos_y - Cpos_y2);
				al_draw_filled_ellipse(Cpos_x2, Cpos_y2, capX * 2, capY * 2, color1);
				Cpos_x2 = 0;
				Cpos_y2 = 0;
				Cpos_x = 0;
				Cpos_y = 0;

			}
			if (tool == 7 && Cpos_x2 != 0 && Cpos_y2 != 0 && Cpos_x3 != 0 && Cpos_y3 != 0 && Cpos_x > 125 && Cpos_x2 > 125 && Cpos_x3>125)
			{

				al_draw_triangle(Cpos_x3, Cpos_y3, Cpos_x2, Cpos_y2, Cpos_x, Cpos_y, color1, thick);
				Cpos_x3 = 0;
				Cpos_x2 = 0;
				Cpos_y2 = 0;
				Cpos_y3 = 0;
				Cpos_x = 0;
				Cpos_y = 0;

			}
			if (tool == 8) {
				if (Cpos_x2 != 0 && Cpos_y2 != 0 && Cpos_x > 125 && Cpos_x2 > 125 && Cpos_x3>125)
				{
					al_draw_filled_triangle(Cpos_x3, Cpos_y3, Cpos_x2, Cpos_y2, Cpos_x, Cpos_y, color1);
					Cpos_x3 = 0;
					Cpos_x2 = 0;
					Cpos_y2 = 0;
					Cpos_y3 = 0;
					Cpos_x = 0;
					Cpos_y = 0;
				}
			}
			if (tool != 1)
			{
				draw = false;
			}

		}
		
		// BUTTON KONTROL 
		if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
	{
		if(ev.mouse.x>=9&&ev.mouse.y>=450&&ev.mouse.x<=57&&ev.mouse.y<=500) // NEW FILE 
			{
				al_clear_to_color(al_map_rgb(255, 255, 255));
			}	
		else if(ev.mouse.x>=68&&ev.mouse.y>=450&&ev.mouse.x<=116&&ev.mouse.y<=500) // SAVE FILE 
			{
				save_image();
			}
		else if(ev.mouse.x>=9&&ev.mouse.y>=504&&ev.mouse.x<=57&&ev.mouse.y<=554) // LOAD FILE 
			{
				al_clear_to_color(al_map_rgb(255, 255, 255));
				load_image();
			}
		else if(ev.mouse.x>=68&&ev.mouse.y>=504&&ev.mouse.x<=116&&ev.mouse.y<=554) // CLOSE FILE 
			{
				
				int button = al_show_native_message_box(
					display,
					"UYARI",
					"",
					"Cikmak istediginize eminmisiniz?",
					NULL,
					ALLEGRO_MESSAGEBOX_YES_NO
					);
				if (button)
				{
					done = true;
				}
			}	
	}
		// MENUNUN ÇÝZDÝRÝLMESÝ 
		al_draw_bitmap(image,0,0,0);
		// 1nd 2nd COLOR 
		al_draw_filled_rectangle(14, 387, 57, 428, color1);
		al_draw_filled_rectangle(83, 395, 106, 418, color2);
		// SEÇÝLÝ TOOL'UN GÖSTERÝLMESÝ 
		if(tool==1)
		{
			al_draw_rectangle(33, 134, 59, 160, al_map_rgb(255,0,0), 3);
		}
		else if (tool ==2)
		{
			al_draw_rectangle(60, 134, 86, 160, al_map_rgb(255,0,0), 3);
		}
		else if(tool ==3)
		{
			al_draw_rectangle(33, 161, 59, 187, al_map_rgb(255,0,0), 3);
		}
		else if(tool==4)
		{
			al_draw_rectangle(33, 188, 59, 214, al_map_rgb(255,0,0), 3);
		}
		else if(tool==5)
		{
			al_draw_rectangle(60, 161, 86, 187, al_map_rgb(255,0,0), 3);
		}
		else if(tool==6)
		{
			al_draw_rectangle(60, 188, 86, 214, al_map_rgb(255,0,0), 3);
		}
		else if(tool==7)
		{
			al_draw_rectangle(87, 161, 113, 187, al_map_rgb(255,0,0), 3);
		}
		else if(tool==8)
		{
			al_draw_rectangle(87, 188, 113, 214, al_map_rgb(255,0,0), 3);
		}
		else if(tool ==9)
		{
			al_draw_rectangle(87, 134, 113, 160, al_map_rgb(255,0,0), 3);
		}
		
		if(thick==1)
		{
			al_draw_rectangle(35, 247, 109, 273, al_map_rgb(255,0,0), 3);
		}
		else if(thick==4)
		{
			al_draw_rectangle(35, 278, 109, 304, al_map_rgb(255,0,0), 3);
		}
		else if(thick==6)
		{
			al_draw_rectangle(35, 310, 109, 336, al_map_rgb(255,0,0), 3);
		}
		
		al_flip_display();

	}







	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_destroy_bitmap(icon);
	al_destroy_bitmap(pencil);
	al_destroy_bitmap(image);
	al_destroy_event_queue(event_queue);
	al_destroy_display(display);						//destroy our display object

	return 0;
}


void save_image()
{
	bool save;
	ALLEGRO_BITMAP *bmp = NULL;
	bmp = al_create_sub_bitmap(al_get_backbuffer(display), 125, 0, 515, 560);

	ALLEGRO_PATH *pSavePath = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
	filesave = al_create_native_file_dialog(al_path_cstr(pSavePath, ALLEGRO_NATIVE_PATH_SEP), "Save File...", "*.png", ALLEGRO_FILECHOOSER_SAVE);
	if (al_show_native_file_dialog(display, filesave))
	{
		int counter = al_get_native_file_dialog_count(filesave);
		const char *filename = NULL;
		filename = al_get_native_file_dialog_path(filesave, 0);

		save = al_save_bitmap(filename, bmp);

		if (!save)
		{
			int button = al_show_native_message_box(
				display,
				"UYARI",
				"Kayit edilmedi",
				"bak",
				NULL,
				ALLEGRO_MESSAGEBOX_WARN
				);
		}


		al_destroy_bitmap(bmp);

	}

}

void load_image()
{

	ALLEGRO_BITMAP *image1 = NULL;

	filechooser = al_create_native_file_dialog("C:/Users/furka/Desktop/Proje", "Choose a file.", "*.*;*.png;", 1);
	if (filechooser)
	{
		al_show_native_file_dialog(display, filechooser);
		int counter = al_get_native_file_dialog_count(filechooser);
		const char* path = al_get_native_file_dialog_path(filechooser, 0);
		if (path)
		{
			bool load = image1 = al_load_bitmap(path);

			if (!load) {
				int button = al_show_native_message_box(
					display,
					"UYARI",
					"Yuklenmedi.",
					"bak",
					NULL,
					ALLEGRO_MESSAGEBOX_WARN
					);

			}
			else
			{
				al_draw_bitmap(image1, 125, 0, 0);
			}


		}

		al_destroy_bitmap(image1);
		al_destroy_native_file_dialog(filechooser);

	}
}
