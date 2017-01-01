#ifndef BMTRACK_H
#define BMTRACK_H

#include "Entity/Spec/TrackSpec.h"
#include "SimMode/RaceMode.h"
#include "Controller/VTController.h"

#include "SFMLDebugDraw.h"

#include <Box2D/Box2D.h>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <gtkmm.h>
#include <string>
#include <fstream>
#include <thread>

// class BMLearnMode;
class MainWindow;

class BMTrack : public Gtk::ScrolledWindow 
{
    // friend class BMLearnMode;
    friend class MainWindow;

    Gtk::Grid m_grid;

    Gtk::Frame m_frame_load;
    Gtk::Grid m_grid_load;

    Gtk::Button m_button_load;
    Gtk::Button m_button_editor;

    Gtk::Frame m_frame_enable;
    Gtk::Grid m_grid_enable;
    Gtk::CheckButton m_button_ENT_TRACKLINK;
    Gtk::CheckButton m_button_ENT_NODE;
    Gtk::CheckButton m_button_ENT_CUBE;

    Gtk::Label m_label_trackfile;
    Gtk::Entry m_entry_trackfile;

    Gtk::Button m_button_view;
    Gtk::Button m_button_stop;

    std::string m_trackfile;
    TrackSpec m_tspec;

    void on_button_load_track();
    void on_button_view_track();
    void on_button_stop();

    VTController* m_controller;

public:
    BMTrack(VTController* controller);

    std::string getTrackFile();
    const TrackSpec& getTrackSpec() const;
};

#endif