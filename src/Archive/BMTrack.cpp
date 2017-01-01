#include "GUI/Bookmark/BMTrack.h"


BMTrack::BMTrack(VTController* controller) :
    m_controller(controller)
{
    m_grid.set_column_spacing(5);
    m_grid.set_row_spacing(5);

    // Enable frame

    m_grid_enable.set_column_spacing(5);
    m_grid_enable.set_row_spacing(5);
    m_grid_enable.set_hexpand(true);

    m_button_ENT_TRACKLINK.set_label("ENT_TRACKLINK");
    m_button_ENT_TRACKLINK.set_active(true);
    m_grid_enable.attach(m_button_ENT_TRACKLINK, 0, 0, 1, 1);

    m_button_ENT_NODE.set_label("ENT_NODE");
    m_button_ENT_NODE.set_active(true);   
    m_grid_enable.attach(m_button_ENT_NODE, 1, 0, 1, 1);

    m_button_ENT_CUBE.set_label("ENT_CUBE");
    m_button_ENT_CUBE.set_active(true);
    m_grid_enable.attach(m_button_ENT_CUBE, 0, 1, 1, 1);

    m_frame_enable.set_label("Enable entities");
    m_frame_enable.set_shadow_type(Gtk::SHADOW_ETCHED_OUT);
    m_frame_enable.add(m_grid_enable);

    // Load Frame

    m_frame_load.set_label("Load Track");
    m_frame_load.set_shadow_type(Gtk::SHADOW_ETCHED_OUT);
    m_frame_load.add(m_grid_load);
    m_frame_load.set_hexpand(true);

    m_grid_load.set_column_spacing(5);
    m_grid_load.set_row_spacing(5);
    m_grid_load.set_hexpand(true);

    m_grid_load.attach(m_frame_enable, 0, 0, 2, 1);

    m_button_load.set_label("Load");
    m_button_load.signal_clicked().connect(sigc::mem_fun(*this,
                                &BMTrack::on_button_load_track) );
    m_grid_load.attach(m_button_load, 0, 1, 1, 1);

    m_grid.attach(m_frame_load, 0, 0, 2, 1);

    m_label_trackfile.set_text("Active track");
    m_grid.attach(m_label_trackfile, 0, 1, 2, 1);

    m_entry_trackfile.set_editable(false);
    m_entry_trackfile.set_text("<no track>");
    m_grid.attach(m_entry_trackfile, 0, 2, 2, 1);

    m_button_view.set_label("View track");
    m_button_view.signal_clicked().connect(sigc::mem_fun(*this,
                                &BMTrack::on_button_view_track) );
    m_grid.attach(m_button_view, 0, 3, 1, 1);

    m_button_stop.set_label("Stop");
    m_button_stop.signal_clicked().connect(sigc::mem_fun(*this,
                                &BMTrack::on_button_stop));
    m_grid.attach(m_button_stop, 1, 3, 1, 1);

 //   m_button_editor.set_label("Track editor");
 //   m_grid.attach(m_button_editor, 0, 1, 1, 1);


    add(m_grid);
}

void BMTrack::on_button_load_track()
{
    Gtk::FileChooserDialog dialog("Please choose a file",
        Gtk::FILE_CHOOSER_ACTION_OPEN);
    // dialog.set_transient_for(this->get_parent_window());

    //Add response buttons the the dialog:
    dialog.add_button("_Cancel", Gtk::RESPONSE_CANCEL);
    dialog.add_button("_Open", Gtk::RESPONSE_OK);

    //Add filters, so that only certain file types can be selected:
    auto filter_any = Gtk::FileFilter::create();
    filter_any->set_name("Any files");
    filter_any->add_pattern("*");
    dialog.add_filter(filter_any);

    //Show the dialog and wait for a user response:
    int result = dialog.run();

    //Handle the response:
    switch(result) {
        case Gtk::RESPONSE_OK: {
            m_trackfile = dialog.get_filename();

            if (m_tspec.size() > 0)
                m_tspec.clear();
            tinyxml2::XMLError eResult = m_tspec.load(m_trackfile);
            if (eResult == tinyxml2::XML_SUCCESS) 
            {
                m_entry_trackfile.set_text(m_trackfile.c_str());
            }
            else
            {
                m_entry_trackfile.set_text("<No Track>");
                m_trackfile = "";
            }

            break;
        } case Gtk::RESPONSE_CANCEL: 
            break;
        default: 
            break;  
    }    
}

void BMTrack::on_button_view_track()
{
    std::thread vtThread(&VTController::start, m_controller, m_trackfile);
    vtThread.detach();
}

void BMTrack::on_button_stop()
{
    m_controller->stop();
}

std::string BMTrack::getTrackFile()
{
    return m_trackfile;
}

const TrackSpec& BMTrack::getTrackSpec() const
{
    return m_tspec;
}