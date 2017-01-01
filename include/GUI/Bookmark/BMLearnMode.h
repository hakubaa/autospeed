#ifndef BMLEARNMODE_H
#define BMLEARNMODE_H

#include <gtkmm.h>
#include <thread>
#include <sstream>

class MainWindow;

class BMLearnMode : public Gtk::ScrolledWindow 
{
    friend class MainWindow;

    Gtk::Grid m_grid;

    Gtk::Button m_button_start;
    Gtk::Button m_button_stop;
    Gtk::Button m_button_pause;
    Gtk::Button m_button_resume;
    Gtk::Button m_button_visu;
    Gtk::Button m_button_newgenr;

    Gtk::Grid m_grid_settings;
    Gtk::Frame m_frame_settings;

    Gtk::Label m_label_timestep;
    Gtk::Entry m_entry_timestep;
    Gtk::Label m_label_exptime;
    Gtk::Entry m_entry_exptime;
    Gtk::CheckButton m_button_rts;
    Gtk::Label m_label_info;
    Gtk::Button m_button_update;

    Gtk::Frame m_frame_genome;
    Gtk::Grid m_grid_genome;
    Gtk::Entry m_entry_genome;
    Gtk::Label m_label_genome;
    Gtk::Button m_button_load_genome;
    Gtk::Button m_button_save_genome;
    Gtk::Button m_button_create_genome;
    Gtk::Button m_button_edit_genome;


public:
    BMLearnMode();
    ~BMLearnMode();

    // void on_button_start();
    // void on_button_stop();
    // void on_button_pause();
    // void on_button_resume();
    // void on_button_visu();
    // void on_button_newgenr();

    void on_button_load();
    void on_button_create();
    void on_button_save();
    void on_button_edit();

    std::string getGenomeFile();
};

#endif