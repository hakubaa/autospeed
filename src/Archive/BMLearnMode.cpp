#include "GUI/Bookmark/BMLearnMode.h"

BMLearnMode::BMLearnMode(LMController* controller, BMDriver* driver, 
                            BMTrack* track, BMNeat* neat) :
    m_BMDriver(driver),
    m_BMTrack(track),
    m_BMNeat(neat),
    m_controller(controller)
{

    m_grid.set_column_spacing(5);
    m_grid.set_row_spacing(5);

    m_button_start.set_label("Start");
    m_button_start.set_hexpand(true);
    m_button_start.signal_clicked().connect(
        sigc::mem_fun(*this, &BMLearnMode::on_button_start));
    m_grid.attach(m_button_start, 0, 0, 1, 1);

    m_button_stop.set_label("Stop");
    m_button_stop.set_hexpand(true);
    m_button_stop.signal_clicked().connect(
        sigc::mem_fun(*this, &BMLearnMode::on_button_stop));
    m_grid.attach(m_button_stop, 1, 0, 1, 1);

    m_button_pause.set_label("Pause");
    m_button_pause.set_hexpand(true);
    m_button_pause.signal_clicked().connect(
        sigc::mem_fun(*this, &BMLearnMode::on_button_pause));
    m_grid.attach(m_button_pause, 0, 1, 1, 1);

    m_button_resume.set_label("Resume");
    m_button_resume.set_hexpand(true);
    m_button_resume.signal_clicked().connect(
        sigc::mem_fun(*this, &BMLearnMode::on_button_resume));
    m_grid.attach(m_button_resume, 1, 1, 1, 1);    

    m_button_visu.set_label("Show visualisation");
    m_button_visu.set_hexpand(true);
    m_button_visu.signal_clicked().connect(
        sigc::mem_fun(*this, &BMLearnMode::on_button_visu));
    m_grid.attach(m_button_visu, 0, 2, 1, 1);  

    m_button_newgenr.set_label("Start new generation");
    m_button_newgenr.set_hexpand(true);
    m_button_newgenr.signal_clicked().connect(
        sigc::mem_fun(*this, &BMLearnMode::on_button_newgenr));
    m_grid.attach(m_button_newgenr, 0, 3, 1, 1);     

    m_label_timestep.set_text("Time step (s)");
    m_grid.attach(m_label_timestep, 0, 4, 1, 1);

    m_entry_timestep.set_alignment(Gtk::ALIGN_CENTER);
    m_entry_timestep.set_text("0.01");
    m_grid.attach(m_entry_timestep, 1, 4, 1, 1);

    m_label_exptime.set_text("Exp. time (s)");
    m_grid.attach(m_label_exptime, 0, 5, 1, 1);

    m_entry_exptime.set_alignment(Gtk::ALIGN_CENTER);
    m_entry_exptime.set_text("0.01");
    m_grid.attach(m_entry_exptime, 1, 5, 1, 1);

    m_button_rts.set_label("RTS (real time simulation)");
    m_button_rts.set_active(true);
    m_grid.attach(m_button_rts, 0, 6, 2, 1);

    // Intitial Genome

    m_grid_genome.set_column_spacing(5);
    m_grid_genome.set_row_spacing(5);

    m_button_load_genome.set_label("Load");
    m_button_load_genome.signal_clicked().connect(
        sigc::mem_fun(*this, &BMLearnMode::on_button_load));
    m_grid_genome.attach(m_button_load_genome, 0, 0, 1, 1);

    m_button_create_genome.set_label("Create");
    m_grid_genome.attach(m_button_create_genome, 1, 0, 1, 1);

    m_label_genome.set_text("Genome File Path");
    m_label_genome.set_hexpand(true);
    m_grid_genome.attach(m_label_genome, 0, 1, 2, 1);

    m_entry_genome.set_hexpand(true);
    m_entry_genome.set_editable(false);
    m_grid_genome.attach(m_entry_genome, 0, 2, 2, 1);

    m_button_edit_genome.set_label("Edit");
    m_grid_genome.attach(m_button_edit_genome, 0, 3, 1, 1);

    m_button_save_genome.set_label("Save");
    m_grid_genome.attach(m_button_save_genome, 1, 3, 1, 1);

    m_frame_genome.set_label("Initial genome");
    m_frame_genome.set_shadow_type(Gtk::SHADOW_ETCHED_OUT);
    m_frame_genome.add(m_grid_genome);

    m_grid.attach(m_frame_genome, 0, 7, 2, 1);

    // Track

    m_grid_track.set_column_spacing(5);
    m_grid_track.set_row_spacing(5);

    m_entry_track.set_alignment(Gtk::ALIGN_CENTER);
    m_entry_track.set_text("");
    m_entry_track.set_hexpand(true);
    m_entry_track.set_editable(false);
    m_grid_track.attach(m_entry_track, 0, 0, 2, 1);

    // m_refModel = Gtk::ListStore::create(m_spm);
    // m_combo_startpos.set_model(m_refModel);

    m_combo_startpos.set_hexpand(true);
    m_combo_startpos.pack_start(m_spm.m_id);
    m_combo_startpos.pack_start(m_spm.m_pos);

    m_label_track.set_text("Start Pos.");
    m_label_track.set_hexpand(true);
    m_grid_track.attach(m_label_track, 0, 1, 1, 1);

    m_grid_track.attach(m_combo_startpos, 1, 1, 1, 1);

    m_frame_track.set_label("Track");
    m_frame_track.set_shadow_type(Gtk::SHADOW_ETCHED_OUT);
    m_frame_track.add(m_grid_track);

    m_grid.attach(m_frame_track, 0, 8, 2, 1);

    add(m_grid);
}

BMLearnMode::~BMLearnMode()
{
    
}

void BMLearnMode::on_button_start()
{
    NEAT::set_neat_params(m_BMNeat->getNEATconfig(), true);
    m_controller->loadGenome(m_entry_genome.get_text());
    m_controller->setTrack(m_BMTrack->getTrackSpec());
    m_controller->setCarSpec(m_BMDriver->getCarSpec());

    int posNo = m_combo_startpos.get_active_row_number();
    if (posNo >= 0)
    {
        StartPosSpec* spos = m_BMTrack->getTrackSpec().getStartPos(posNo);  
        ASpeedFactory* dFactory = new ASpeedFactory(m_BMDriver->getCarSpec(), 
            spos->pos, spos->angle - 90.0f * DEGTORAD);
        m_controller->setDriverFactory(dFactory);   
    }
    
    std::thread vtThread(&LMController::start, m_controller);
    vtThread.detach();
}

void BMLearnMode::on_button_stop()
{
}

void BMLearnMode::on_button_pause()
{
    m_controller->pause();
}

void BMLearnMode::on_button_resume()
{
    m_controller->resume();
}

void BMLearnMode::on_button_visu()
{
    m_controller->showVisu();
}

void BMLearnMode::on_button_newgenr()
{
    m_controller->startNewGenr();
}

void BMLearnMode::update_trackinfo()
{
    m_entry_track.set_text(m_BMTrack->getTrackFile());
    const TrackSpec& trackSpec = m_BMTrack->getTrackSpec();

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


void BMLearnMode::on_button_load()
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
            std::string filename = dialog.get_filename();
            m_entry_genome.set_text(filename);
            break;
        } case Gtk::RESPONSE_CANCEL: 
            break;
        default: 
            break;  
    }

}

void BMLearnMode::on_button_create()
{

}

void BMLearnMode::on_button_save()
{

}

void BMLearnMode::on_button_edit()
{

}