#include "GUI/FileChooser.h"


std::string FileChooser::getFileName(Gtk::FileChooserAction action)  
{
    FileChooser dialog("Select file", action);
    kit.run(dialog);
    std::string ret = dialog.chosenFile;
    return ret;
}


FileChooser::FileChooser(const Glib::ustring& title, Gtk::FileChooserAction action) :
    Gtk::FileChooserDialog(title, action) 
{
    chosenFile = std::string("");
    add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
    if (action == Gtk::FILE_CHOOSER_ACTION_SAVE)
        add_button(Gtk::Stock::SAVE, Gtk::RESPONSE_OK);
    else
        add_button(Gtk::Stock::OPEN, Gtk::RESPONSE_OK);

    //Add filters, so that only certain file types can be selected:
    auto filter_any = Gtk::FileFilter::create();
    filter_any->set_name("Any files");
    filter_any->add_pattern("*");
    add_filter(filter_any);

    signal_response().connect(sigc::mem_fun(*this,
            &FileChooser::on_my_response));
}

void FileChooser::on_my_response(int response_id) 
{
    chosenFile = get_filename();
    hide();
}


Gtk::Main FileChooser::kit(false);

