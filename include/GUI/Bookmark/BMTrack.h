#ifndef BMTRACK_H
#define BMTRACK_H

#include "Entity/Spec/TrackSpec.h"

// #include "SFMLDebugDraw.h"

#include <Box2D/Box2D.h>
// #include <SFML/Window.hpp>
// #include <SFML/Graphics.hpp>

#include <gtkmm.h>
#include <string>
#include <fstream>
#include <iomanip>
#include <sstream>

// class BMLearnMode;
class MainWindow;

class BMTrack : public Gtk::ScrolledWindow 
{
    // friend class BMLearnMode;
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

    Gtk::Frame m_frame_track;
    Gtk::Grid m_grid_track;
    Gtk::Label m_label_track;
    Gtk::ComboBox m_combo_startpos;
    StartPosModel m_spm;

    Gtk::Button m_button_apply;
    Gtk::Label m_label_apply;

    void on_button_load_track();
    // void on_button_view_track();
    // void on_button_stop();

    void update_trackinfo();

public:
    BMTrack();

    std::string getTrackFile();
    const TrackSpec& getTrackSpec() const;
    int getStartPosNo() const;
};

#endif