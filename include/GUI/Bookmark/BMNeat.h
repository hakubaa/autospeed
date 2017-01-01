#ifndef BMNEAT_H
#define BMNEAT_H

#include <gtkmm.h>
#include <map>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

#include <NEAT/neat.h>

// class BMLearnMode;
class MainWindow;

class BMNeat : public Gtk::ScrolledWindow
{
    // friend class BMLearnMode;
    friend class MainWindow;

    Gtk::Grid m_grid;
    Gtk::Button m_load;
    Gtk::Button m_save;
    Gtk::Label m_label;
    std::vector<std::string> m_paramsList;
    std::map<std::string, Gtk::Label*> m_labelsNEAT;
    std::map<std::string, Gtk::Entry*> m_entriesNEAT;

    void on_button_loadNEAT_clicked();
    void on_button_saveNEAT_clicked();

public:
    BMNeat(std::string fileName);
    ~BMNeat();

    std::map<std::string, double> getNEATconfig();
};

#endif