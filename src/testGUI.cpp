#include "GUI/MainWindow.h"

#include <gtkmm/application.h> 

int main (int argc, char *argv[]) {
    
    Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv, "ASLS");

    MainWindow window(app);

    return app->run(window);      
} 