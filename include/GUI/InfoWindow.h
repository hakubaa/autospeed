#ifndef INFOWINDOW_H
#define INFOWINDOW_H

#include <gtkmm.h>
#include <string>
#include <queue>
#include <sigc++/sigc++.h>

class InfoWindow : public Gtk::ScrolledWindow 
{
public:
    InfoWindow();
    virtual ~InfoWindow();

    void insert(const Glib::ustring& text);
    void insert(std::queue<std::string>* qmsg);
protected:
    Gtk::TextView m_TextView;
    Glib::RefPtr<Gtk::TextBuffer> m_buffer;

};

#endif //INFOWINDOW_H