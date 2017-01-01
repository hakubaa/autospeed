#ifndef FILECHOOSER_H
#define FILECHOOSER_H

#include <gtkmm.h>

class FileChooser : public Gtk::FileChooserDialog 
{
public:

    static std::string getFileName(Gtk::FileChooserAction action);

protected:
    static Gtk::Main kit;
    std::string chosenFile;

    FileChooser(const Glib::ustring& title, Gtk::FileChooserAction action = Gtk::FILE_CHOOSER_ACTION_OPEN);

    void on_my_response(int response_id);
};


#endif