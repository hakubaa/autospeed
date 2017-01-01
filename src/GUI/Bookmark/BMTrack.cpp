#include "GUI/Bookmark/BMTrack.h"


BMTrack::BMTrack() 
{
    m_grid.set_column_spacing(5);
    m_grid.set_row_spacing(5);

    // Load Frame

    m_button_load.set_label("Load Track");
    m_button_load.signal_clicked().connect(sigc::mem_fun(*this,
                                &BMTrack::on_button_load_track) );
    m_grid.attach(m_button_load, 0, 0, 1, 1);

    m_label_trackfile.set_text("Active Track");
    m_label_trackfile.set_hexpand(true);
    m_grid.attach(m_label_trackfile, 0, 1, 2, 1);

    m_entry_trackfile.set_editable(false);
    m_entry_trackfile.set_text("<no track>");
    m_entry_trackfile.set_hexpand(true);
    m_grid.attach(m_entry_trackfile, 0, 2, 2, 1);

    // Settings

    m_grid_track.set_column_spacing(5);
    m_grid_track.set_row_spacing(5);

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

    m_grid_track.attach(m_frame_enable, 0, 1, 2, 1);

    // Settings c.d.

    m_combo_startpos.set_hexpand(true);
    m_combo_startpos.pack_start(m_spm.m_id);
    m_combo_startpos.pack_start(m_spm.m_pos);
    m_grid_track.attach(m_combo_startpos, 1, 0, 1, 1);

    m_label_track.set_text("Start Pos.");
    m_label_track.set_hexpand(true);
    m_grid_track.attach(m_label_track, 0, 0, 1, 1);

    m_button_view.set_label("View track");
    // m_button_view.signal_clicked().connect(sigc::mem_fun(*this,
    //                             &BMTrack::on_button_view_track) );
    m_grid_track.attach(m_button_view, 0, 2, 1, 1);

    m_frame_track.set_label("Settings - simulations");
    m_frame_track.set_shadow_type(Gtk::SHADOW_ETCHED_OUT);
    m_frame_track.add(m_grid_track);

    m_grid.attach(m_frame_track, 0, 3, 2, 1);

    m_button_apply.set_label("Apply changes*");
    m_grid.attach(m_button_apply, 0, 4, 1, 1);

    m_label_apply.set_text("*enable to make changes during simulation");
    m_grid.attach(m_label_apply, 0, 5, 2, 1);

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
            {
               m_tspec.clear();
            }
            tinyxml2::XMLError eResult = m_tspec.load(m_trackfile);
            if (eResult == tinyxml2::XML_SUCCESS) 
            {
                update_trackinfo();
            }
            
            break;
        } case Gtk::RESPONSE_CANCEL: 
            break;
        default: 
            break;  
    }    
}

// void BMTrack::on_button_view_track()
// {
//     // std::thread vtThread(&VTController::start, m_controller, m_trackfile);
//     // vtThread.detach();
// }

// void BMTrack::on_button_stop()
// {
//     // m_controller->stop();
// }

std::string BMTrack::getTrackFile()
{
    return m_trackfile;
}

const TrackSpec& BMTrack::getTrackSpec() const
{
    return m_tspec;
}

int BMTrack::getStartPosNo() const {
    return m_combo_startpos.get_active_row_number();
}

void BMTrack::update_trackinfo()
{
    m_entry_trackfile.set_text(m_trackfile);
    const TrackSpec& trackSpec = getTrackSpec();

    if (m_combo_startpos.get_model())
        m_combo_startpos.unset_model();

    if (trackSpec.startPosCount() == 0)
        return;

    Glib::RefPtr<Gtk::ListStore> m_refModel = Gtk::ListStore::create(m_spm);
    m_combo_startpos.set_model(m_refModel);
    Gtk::TreeModel::Row row = *(m_refModel->append());

    for(int i = 0; i < trackSpec.startPosCount(); i++)
    {
        StartPosSpec* sp = trackSpec.getStartPos(i);
        if (i == 0)
        {
            row[m_spm.m_id] = i;
            row[m_spm.m_pos] = m_spm.pos2str(sp->pos.x, sp->pos.y);
            m_combo_startpos.set_active(row);
        }  
        else
        {
            row = *(m_refModel->append());
            row[m_spm.m_id] = i;
            row[m_spm.m_pos] = m_spm.pos2str(sp->pos.x, sp->pos.y);
        } 
    }
}