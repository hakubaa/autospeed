#ifndef BMLEARNMODE_H
#define BMLEARNMODE_H

#include "Controller/LMController.h"
#include "GUI/Bookmark/BMDriver.h"
#include "GUI/Bookmark/BMTrack.h"
#include "GUI/Bookmark/BMNeat.h"
#include "Drivers/ASpeedFactory.h"

#include "NEAT/neat.h"

#include <gtkmm.h>
#include <thread>
#include <sstream>
#include <iomanip>

class MainWindow;

class BMLearnMode : public Gtk::ScrolledWindow 
{
    friend class MainWindow;

    class StartPosModel : public Gtk::TreeModel::ColumnRecord
    {
    public:

        StartPosModel()
        { 
            add(m_id); 
            add(m_pos); 
        };

        Gtk::TreeModelColumn<int> m_id;
        Gtk::TreeModelColumn<std::string> m_pos;

        static std::string pos2str(float x, float y, int digits = 2)
        {
            std::stringstream s;
            s << std::fixed << std::setprecision(digits) << "(" << x << ", " << y << ")";
            return s.str();
        }
    };


    Gtk::Grid m_grid;

    Gtk::Button m_button_start;
    Gtk::Button m_button_stop;
    Gtk::Button m_button_pause;
    Gtk::Button m_button_resume;
    Gtk::Button m_button_visu;
    Gtk::Button m_button_newgenr;

    Gtk::Label m_label_timestep;
    Gtk::Entry m_entry_timestep;
    Gtk::Label m_label_exptime;
    Gtk::Entry m_entry_exptime;

    Gtk::CheckButton m_button_rts;

    Gtk::Frame m_frame_genome;
    Gtk::Grid m_grid_genome;
    Gtk::Entry m_entry_genome;
    Gtk::Label m_label_genome;
    Gtk::Button m_button_load_genome;
    Gtk::Button m_button_save_genome;
    Gtk::Button m_button_create_genome;
    Gtk::Button m_button_edit_genome;

    Gtk::Frame m_frame_track;
    Gtk::Grid m_grid_track;
    Gtk::Entry m_entry_track;
    Gtk::Label m_label_track;
    Gtk::ComboBox m_combo_startpos;
    StartPosModel m_spm;

    LMController* m_controller;
    BMDriver* m_BMDriver;
    BMTrack* m_BMTrack;
    BMNeat* m_BMNeat;

public:
    BMLearnMode(LMController* controller, BMDriver* driver, BMTrack* track, BMNeat* neat);
    ~BMLearnMode();

    void on_button_start();
    void on_button_stop();
    void on_button_pause();
    void on_button_resume();
    void on_button_visu();
    void on_button_newgenr();

    void on_button_load();
    void on_button_create();
    void on_button_save();
    void on_button_edit();

    void update_trackinfo();
};

#endif