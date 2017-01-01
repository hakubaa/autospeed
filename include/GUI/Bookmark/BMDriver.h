#ifndef BMDRIVER_H
#define BMDRIVER_H

#include "Entity/Entity.h"
#include "Entity/Spec/CarSpec.h"
#include "Entity/Spec/CarTireSpec.h"
#include "Entity/Spec/RayVisionSpec.h"

#include <gtkmm.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

// class BMLearnMode;
class MainWindow;

class BMDriver : public Gtk::ScrolledWindow
{
    // friend class BMLearnMode;
    friend class MainWindow;

    Gtk::Grid m_grid;

    Gtk::Button m_load;
    Gtk::Button m_save;

    // Car Frame

    Gtk::Label m_label1;
    Gtk::Frame m_frame1;
    Gtk::Grid m_grid1;

    Gtk::Label m_label_n;
    Gtk::Scale m_scale_n;
    Gtk::Label m_label_length;
    Gtk::Scale m_scale_length;
    Gtk::Label m_label_angle;
    Gtk::Scale m_scale_angle;

    Gtk::CheckButton m_button_show;
    Gtk::CheckButton m_button_dynamic;

    Gtk::Label m_label_filter;
    Gtk::CheckButton m_button_ENT_TDCAR;
    Gtk::CheckButton m_button_ENT_TDTIRE;
    Gtk::CheckButton m_button_ENT_TRACKLINK;
    Gtk::CheckButton m_button_ENT_CUBE;

    Gtk::Label m_label_groupIndex;
    Gtk::Entry m_entry_groupIndex;

    // Driver Frame

    Gtk::Frame m_frame_driver;
    Gtk::Grid m_grid_driver;

    Gtk::RadioButton m_button_human;
    Gtk::RadioButton m_button_auto;

    // Driver Setting

    Gtk::Frame m_frame_ds;
    Gtk::Grid m_grid_human;
    Gtk::Grid m_grid_auto;

    Gtk::Button m_button_load_genome;
    Gtk::Button m_button_save_genome;
    Gtk::Button m_button_create_genome;
    Gtk::TextView m_text_genome;


    Gtk::Button m_button_addDriver;

    void on_button_load_clicked();
    void on_button_save_clicked();

    void on_button_load_genome();
    void on_button_save_genome();
    void on_button_create_genome();

public:
    BMDriver();

    CarSpec getCarSpec();
};

#endif