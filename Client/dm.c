#include <gtk/gtk.h>
//GtkWidget *g_lbl_hello;
GtkWidget *g_tbf_mess;
 
int main(int argc, char *argv[])
{
    GtkBuilder      *builder; 
    GtkWidget       *window;
 
    gtk_init(&argc, &argv);
 
    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "chatui.glade", NULL);
 
    window = GTK_WIDGET(gtk_builder_get_object(builder, "window_main"));
    gtk_builder_connect_signals(builder, NULL);
    // get pointers
    g_tbf_mess = GTK_WIDGET(gtk_builder_get_object(builder, "tbf_mess"));

    g_object_unref(builder);
 
    gtk_widget_show(window);                
    gtk_main();
 
    return 0;
}

// called when button send is clicked sua tham so de truyen vao
void on_btn_send_clicked()
{    
    gtk_text_buffer_set_text(GTK_TEXT_BUFFER(g_tbf_mess), "Hello, world!",-1);
}

// called when window is closed
void on_window_main_destroy()
{
    gtk_main_quit();
}
