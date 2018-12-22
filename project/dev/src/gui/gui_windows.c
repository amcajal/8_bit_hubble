/*******************************************************************************
*   Project: 8-Bit Hubble
*
*   File: gui_windows.c
*
*   Description: Source file of GUI module for WINDOWS. It implements
* 				the GTK source of the GUI and the ENTRY POINT for
* 				such version. This version is similar to the one
* 				of LINUX, but due to Windows OS limitations, certain
* 				capabilites are removed (like Filesystem browsers).
*
*   Notes: No header file (gui.h) for this module.
*
*   Contact: Alberto Martin Cajal, amartin.glimpse23<AT>gmail.com
*
*   URL: https://github.com/amcajal/8_bit_hubble
*
*   License: GNU GPL v3.0
*
*   Copyright (C) 2018 Alberto Martin Cajal
*
*   This file is part of 8-Bit Hubble.
*
*   8-Bit Hubble is free software: you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*   the Free Software Foundation, either version 3 of the License, or
*   (at your option) any later version.
*
*   8-Bit Hubble is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*******************************************************************************/
#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "8bH_logo.h"
#include "../status_reporter/status_reporter.h"
#include "../big_bang_core/big_bang_core.h"
#include "../user_config_checker/user_config_checker.h"
#include "../app_info/app_info.h"

/* Turn off warnings about Gtk v2 deprecated functions. */
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

struct gui_io_param {
	GtkEntry *img_name;
	GtkEntry *seed;
	GtkTextBuffer *status_console_message;
} user_io;

void close_window(GtkWidget *widget, gpointer window)
{
    gtk_widget_destroy(GTK_WIDGET(window));
}

static void
call_entry_point (gchar *text, struct gui_io_param *p_giop)
{
    int n_seed_digits = 10; /* By default, generated seed has 10 digits. */
    char *img_name = (char *)gtk_entry_get_text(p_giop->img_name);
    
	store_output_path("./");
    store_file_name(img_name);
	
	if (strcmp(gtk_entry_get_text(p_giop->seed), "") != 0) 
	{
        printf("Seed: %s\n", gtk_entry_get_text(p_giop->seed));
        n_seed_digits = strlen(gtk_entry_get_text(p_giop->seed));
		store_seed((char *)gtk_entry_get_text(p_giop->seed));
	}
	
	int app_return_code;  
	app_return_code = start_big_bang();
        
	if (app_return_code == NO_ERROR)
	{
		GtkWidget *result_window;
		GtkWidget *image;
        GtkWidget *box;
        GtkWidget *img_seed_label;
        
		result_window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
		gtk_window_set_title (GTK_WINDOW (result_window), "Result");
		gtk_window_set_default_size (GTK_WINDOW (result_window), 550, 550);
        g_signal_connect (result_window, "destroy", G_CALLBACK (close_window), result_window);

        /* Add 7 chars: two for the "./", four for ".png" and one for the \0 */
		char *full_path = malloc((strlen(img_name) + 7) * sizeof(char));
		full_path = strcpy(full_path, "./");
		full_path = strcat(full_path, img_name);
		full_path = strcat(full_path, ".png");
		image = gtk_image_new_from_file (full_path);
        
        /* Since the location of the seed is static and previously known, it can
            be accessed directly. */
        char *seed_label = malloc(n_seed_digits * sizeof(char));
        FILE *fp = fopen(full_path, "rb");
        fseek(fp, 0x19B, SEEK_SET);
        fread(seed_label, sizeof(char), n_seed_digits, fp);
        fclose(fp);
        
        /* 21 chars: 20 for the text and one for \0. */
        int chars_to_malloc = 21 + n_seed_digits;
        char *seed_message = malloc(chars_to_malloc * sizeof(char));
        sprintf(seed_message, "SEED OF THE GALAXY: %s", seed_label);
        img_seed_label = gtk_label_new(seed_message);
        gtk_label_set_selectable ((GtkLabel *)img_seed_label, TRUE);
        free(seed_label);
        free(seed_message);
	
        box = gtk_vbox_new(FALSE, 1);
        gtk_container_add (GTK_CONTAINER (result_window), box);
        gtk_container_add (GTK_CONTAINER (box), image);
        gtk_container_add (GTK_CONTAINER (box), img_seed_label);
		gtk_widget_show_all (result_window);
		free(full_path);

		gtk_text_buffer_set_text(p_giop->status_console_message, "Galaxy generated successfully!", -1);
	}
	else {
		gtk_text_buffer_set_text(p_giop->status_console_message, report_status(app_return_code), -1);
	}
}

static void
print_gui_help (void)
{	
	/* @TODO make text window global, so if it is open, does not open again. */
    GtkWidget *help_window;
    GtkTextView *text_field;
    GtkTextBuffer *help_buffer;
    GtkWidget *box;
    
    help_window = (GtkWidget*)gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title (GTK_WINDOW (help_window), "8-Bit Hubble Help");
	gtk_window_set_default_size (GTK_WINDOW (help_window), 300, 300);
	g_signal_connect (help_window, "destroy", G_CALLBACK (close_window), help_window);
	
	help_buffer = gtk_text_buffer_new(NULL);
	gtk_text_buffer_set_text(help_buffer, get_gui_help(), -1);
	text_field = (GtkTextView *)gtk_text_view_new();
	gtk_text_view_set_editable (text_field, 0);
	gtk_text_view_set_buffer(text_field, help_buffer);

    box = gtk_vbox_new(TRUE, 1);
    gtk_container_add (GTK_CONTAINER (box), (GtkWidget *)text_field);
    gtk_container_add (GTK_CONTAINER (help_window), box);
	
	gtk_widget_show_all (help_window); 
}

static void
print_about (void)
{
    GtkWidget *about_window;
    GtkTextView *text_field;
    GtkTextBuffer *about_buffer;
    GtkWidget *box;
    
    about_window = (GtkWidget*)gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title (GTK_WINDOW (about_window), "About 8-Bit Hubble Project");
	gtk_window_set_default_size (GTK_WINDOW (about_window), 300, 300);
	g_signal_connect (about_window, "destroy", G_CALLBACK (close_window), about_window);
	
	about_buffer = gtk_text_buffer_new(NULL);
	gtk_text_buffer_set_text(about_buffer, get_gui_about(), -1);
	text_field = (GtkTextView *)gtk_text_view_new();
	gtk_text_view_set_editable (text_field, 0);
	gtk_text_view_set_buffer(text_field, about_buffer);

	box = gtk_vbox_new(TRUE, 1);
    gtk_container_add (GTK_CONTAINER (box), (GtkWidget *)text_field);
    gtk_container_add (GTK_CONTAINER (about_window), box);

	gtk_widget_show_all (about_window);
}

static void
activate (GtkApplication *app,
          gpointer        user_data)
{
	GtkWidget *window;
    GtkWidget *grid;
	GdkPixbuf *pixbuf;
	GtkImage *logo;
	GtkWidget *gen_galaxy_button;
	GtkWidget *help_button;
	GtkWidget *about_button;
	GtkEntry *out_img_name;
	GtkEntry *seed_value;
	GtkTextView *status_console;
	GtkTextBuffer *result_buffer;
    GtkWidget *output_dir_label;
    GtkWidget *output_dir_fixed_value;
    GtkWidget *img_name_label;
    GtkWidget *seed_label;
    GtkWidget *status_console_label;
    GdkColor window_color, button_focused_color;
	
	/* Explicit casts are included to avoid compilation warnings. */
    
    /* Main window */
    window = gtk_application_window_new (app);
    gtk_window_set_resizable((GtkWindow*)window, FALSE);
    gtk_window_set_title (GTK_WINDOW (window), "8-Bit Hubble");
    gtk_window_set_default_size (GTK_WINDOW (window), 400, 400);
	g_signal_connect (window, "destroy", G_CALLBACK (gtk_main_quit), NULL);
    
    gdk_color_parse ("#BEBEBE", &window_color);
    gtk_widget_modify_bg ( GTK_WIDGET(window), GTK_STATE_NORMAL, &window_color);
    
    /* Logo */
    pixbuf = gdk_pixbuf_new_from_inline (-1, app_logo, FALSE, NULL);
    logo = (GtkImage*)gtk_image_new_from_pixbuf(pixbuf);
    
    /* User input fields */    
	out_img_name = (GtkEntry *)gtk_entry_new();
    seed_value = (GtkEntry *)gtk_entry_new();
    
    /* User output fields */
    result_buffer = gtk_text_buffer_new(NULL);
	status_console = (GtkTextView *)gtk_text_view_new();
    gtk_text_view_set_editable (status_console, FALSE);
	gtk_text_view_set_buffer(status_console, result_buffer);
    
    /* Parameter for Generate Galaxy function */
    user_io.img_name = out_img_name;
    user_io.seed = seed_value;
    user_io.status_console_message = result_buffer;
    
    /* Buttons */
    gen_galaxy_button = gtk_button_new_with_label ("Generate Galaxy!");
	g_signal_connect (gen_galaxy_button, "clicked", G_CALLBACK (call_entry_point), &user_io);
    
    help_button = gtk_button_new_with_label ("Help");
	g_signal_connect (help_button, "clicked", G_CALLBACK (print_gui_help), NULL);
    
    about_button = gtk_button_new_with_label ("About");
	g_signal_connect (about_button, "clicked", G_CALLBACK (print_about), NULL);
    
    gdk_color_parse ("4B6983", &button_focused_color);
    gtk_widget_modify_fg ( GTK_WIDGET(gen_galaxy_button), GTK_STATE_PRELIGHT, &button_focused_color);
    gtk_widget_modify_fg ( GTK_WIDGET(help_button), GTK_STATE_PRELIGHT, &button_focused_color);
    gtk_widget_modify_fg ( GTK_WIDGET(about_button), GTK_STATE_PRELIGHT, &button_focused_color);
    
    /* Labels */
    size_t size = 100 * sizeof(char);
    char *cwd = malloc (size);
    getcwd(cwd, size);
    output_dir_fixed_value = gtk_label_new (cwd);
    gtk_label_set_selectable ((GtkLabel *)output_dir_fixed_value, TRUE);
    free(cwd);

    output_dir_label = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(output_dir_label), "<b>Output image directory:</b>");

    img_name_label = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(img_name_label), "<b>Output image name:</b>");
    
    seed_label = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(seed_label), "<b>Seed value (optional):</b>");
    
    status_console_label = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(status_console_label), "<b>Status console:</b>");
    
    gtk_misc_set_alignment (GTK_MISC (output_dir_label), 0.0, 0.5);
    gtk_misc_set_alignment (GTK_MISC (output_dir_fixed_value), 0.0, 0.5);
    gtk_misc_set_alignment (GTK_MISC (img_name_label), 0.0, 0.5);
    gtk_misc_set_alignment (GTK_MISC (seed_label), 0.0, 0.5);
    gtk_misc_set_alignment (GTK_MISC (status_console_label), 0.0, 0.5);
    
    /* Grid */
    grid = gtk_grid_new();
    gtk_grid_set_row_spacing ((GtkGrid *)grid, 2);                        
    gtk_container_add (GTK_CONTAINER (window), grid);
    gtk_grid_attach (GTK_GRID (grid), (GtkWidget *)logo, 0, 0, 1, 1);
    gtk_grid_attach (GTK_GRID (grid), (GtkWidget *)output_dir_label, 0, 1, 1, 1);
    gtk_grid_attach (GTK_GRID (grid), (GtkWidget *)output_dir_fixed_value, 0, 2, 1, 1);
    gtk_grid_attach (GTK_GRID (grid), (GtkWidget *)img_name_label, 0, 3, 1, 1);
    gtk_grid_attach (GTK_GRID (grid), (GtkWidget *)out_img_name, 0, 4, 1, 1);
    gtk_grid_attach (GTK_GRID (grid), (GtkWidget *)seed_label, 0, 5, 1, 1);
    gtk_grid_attach (GTK_GRID (grid), (GtkWidget *)seed_value, 0, 6, 1, 1);
    gtk_grid_attach (GTK_GRID (grid), gen_galaxy_button, 0, 7, 1, 1);
    gtk_grid_attach (GTK_GRID (grid), status_console_label, 0, 8, 1, 1);
    gtk_grid_attach (GTK_GRID (grid), (GtkWidget *)status_console, 0, 9, 1, 1);
    gtk_grid_attach (GTK_GRID (grid), help_button, 0, 10, 1, 1);
    gtk_grid_attach (GTK_GRID (grid), about_button, 0, 11, 1, 1);
  
	gtk_widget_show_all (window);       
}

int
main (int    argc,
      char **argv)
{
  GtkApplication *app;
  int status;

  app = gtk_application_new ("App.EigthBitHubble", G_APPLICATION_FLAGS_NONE);
  g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
  status = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);

  return status;
}
