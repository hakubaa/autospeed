#include "GUI/Bookmark/BMDriver.h"

BMDriver::BMDriver() 
{
    m_grid.set_column_spacing(5);
    m_grid.set_row_spacing(5);

    m_load.signal_clicked().connect(sigc::mem_fun(*this,
              &BMDriver::on_button_load_clicked) );

    m_save.signal_clicked().connect(sigc::mem_fun(*this,
              &BMDriver::on_button_save_clicked) );

    m_load.set_label("Load");
    m_grid.attach(m_load, 0, 0, 1, 1);

    m_save.set_label("Save");
    m_grid.attach(m_save, 1, 0, 1, 1);

    m_label1.set_text("Driver/Car configuration");
    m_grid.attach(m_label1, 0, 1, 2, 1);
    

    m_grid1.set_column_spacing(5);
    m_grid1.set_row_spacing(5);

    // n

    m_label_n.set_text("rays no");
    m_label_n.set_size_request(50, -1);
    m_grid1.attach(m_label_n, 0, 0, 1, 1);

    m_scale_n.set_hexpand(true);
    m_scale_n.set_range(1, 100);
    m_scale_n.set_value(16);
    m_scale_n.set_digits(0);
    //m_scale_n.set_size_request(150, -1);
    m_scale_n.set_value_pos(Gtk::POS_TOP);
    m_scale_n.set_draw_value();
    m_grid1.attach(m_scale_n, 1, 0, 2, 1);

    // length

    m_label_length.set_text("length (in m)");
    m_label_length.set_size_request(50, -1);
    m_grid1.attach(m_label_length, 0, 1, 1, 1);

    m_scale_length.set_hexpand(true);
    m_scale_length.set_range(20, 200);
    m_scale_length.set_value(80);
    m_scale_length.set_digits(0);
    m_scale_length.set_increments(5, 5);
    //m_scale_length.set_size_request(150, -1);
    m_scale_length.set_value_pos(Gtk::POS_TOP);
    m_scale_length.set_draw_value();
    m_grid1.attach(m_scale_length, 1, 1, 2, 1);    
    

    // angle

    m_label_angle.set_text("max angle");
    m_label_angle.set_size_request(50, -1);
    m_grid1.attach(m_label_angle, 0, 2, 1, 1);

    m_scale_angle.set_hexpand(true);
    m_scale_angle.set_range(0, 180);
    m_scale_angle.set_value(70);
    m_scale_angle.set_digits(0);
    m_scale_angle.set_increments(5, 5);
    //m_scale_angle.set_size_request(150, -1);
    m_scale_angle.set_value_pos(Gtk::POS_TOP);
    m_scale_angle.set_draw_value();
    m_grid1.attach(m_scale_angle, 1, 2, 2, 1);    


    // checkbox show rays

    m_button_show.set_label("show rays");
    m_button_show.set_active(false);
    m_grid1.attach(m_button_show, 0, 3, 2, 1);
    
    // checkbox dynamic rays

    m_button_dynamic.set_label("dynamic rays");
    m_button_dynamic.set_active(false);
    m_grid1.attach(m_button_dynamic, 0, 4, 2, 1);
       
    // filter

    m_label_filter.set_text("Entitis to filter");
    m_grid1.attach(m_label_filter, 0, 5, 2, 1);

    m_button_ENT_TDCAR.set_label("ENT_TDCAR");
    m_button_ENT_TDCAR.set_active(false);
    m_grid1.attach(m_button_ENT_TDCAR, 0, 6, 2, 1);

    m_button_ENT_TDTIRE.set_label("ENT_TDTIRE");
    m_button_ENT_TDTIRE.set_active(false);
    m_grid1.attach(m_button_ENT_TDTIRE, 0, 7, 2, 1);

    m_button_ENT_TRACKLINK.set_label("ENT_TRACKLINK");
    m_button_ENT_TRACKLINK.set_active(true);
    m_grid1.attach(m_button_ENT_TRACKLINK, 0, 8, 2, 1);

    m_button_ENT_CUBE.set_label("ENT_CUBE");
    m_button_ENT_CUBE.set_active(true);
    m_grid1.attach(m_button_ENT_CUBE, 0, 9, 2, 1);

    m_frame1.set_label("Car - Ray Vision");
    m_frame1.set_shadow_type(Gtk::SHADOW_ETCHED_OUT);
    m_frame1.add(m_grid1);

    m_grid.attach(m_frame1, 0, 2, 2, 1);

    // group index

    m_label_groupIndex.set_label("group index (Box2D)");
    m_grid.attach(m_label_groupIndex, 0, 3, 1, 1);

    m_entry_groupIndex.set_alignment(Gtk::ALIGN_CENTER);
    m_entry_groupIndex.set_text("-1");
    m_grid.attach(m_entry_groupIndex, 1, 3, 1, 1);
    

    m_grid_driver.set_column_spacing(5);
    m_grid_driver.set_row_spacing(5);

    Gtk::RadioButton::Group rgroup = m_button_human.get_group();

    m_button_human.set_label("Human Driver");
    m_button_human.set_active(false);
    m_grid_driver.attach(m_button_human, 0, 0, 2, 1);

    m_button_auto.set_group(rgroup);
    m_button_auto.set_label("Autonomous Driver");
    m_button_auto.set_active(true);
    m_grid_driver.attach(m_button_auto, 0, 1, 2, 1);

    m_frame_driver.set_label("Driver Type");
    m_frame_driver.set_shadow_type(Gtk::SHADOW_ETCHED_OUT);
    m_frame_driver.add(m_grid_driver);

    m_grid.attach(m_frame_driver, 0, 4, 2, 1);

    // Driver Settings Frame

    m_grid_auto.set_column_spacing(5);
    m_grid_auto.set_row_spacing(5);

    m_button_load_genome.set_label("Load");
    m_button_load_genome.signal_clicked().connect(sigc::mem_fun(*this,
                                &BMDriver::on_button_load_genome) );
    m_grid_auto.attach(m_button_load_genome, 0, 0, 1, 1);

    m_button_create_genome.set_label("Create");
    m_grid_auto.attach(m_button_create_genome, 1, 0, 1, 1);

    m_text_genome.set_hexpand(true);
    m_text_genome.set_vexpand(true);
    m_grid_auto.attach(m_text_genome, 0, 1, 2, 1);

    m_button_save_genome.set_label("Save");
    m_grid_auto.attach(m_button_save_genome, 1, 2, 1, 1);

    m_frame_ds.set_label("Driver settings");
    m_frame_ds.set_shadow_type(Gtk::SHADOW_ETCHED_OUT);
    m_frame_ds.add(m_grid_auto);

    m_grid.attach(m_frame_ds, 0, 5, 2, 1);

    m_button_addDriver.set_label("Add Driver (only RaceMode)");
    m_grid.attach(m_button_addDriver, 0, 6, 2, 1);

    add(m_grid);
}


void BMDriver::on_button_load_clicked() 
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
            std::ifstream inSettings(filename);
            std::string param, paramVal;
            while (inSettings >> param) {
                inSettings >> paramVal;

            }
            inSettings.close();
            break;
        } case Gtk::RESPONSE_CANCEL: 
            break;
        default: 
            break;  
    }
}

void BMDriver::on_button_save_clicked() {

    Gtk::FileChooserDialog dialog("Please choose a file",
        Gtk::FILE_CHOOSER_ACTION_SAVE);
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
            std::ofstream outSettings(filename);
            


            outSettings.close();
            break;
        } case Gtk::RESPONSE_CANCEL: 
            break;
        default: 
            break;  
    }

}


void BMDriver::on_button_load_genome()
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
            std::ifstream genomeFile(filename);
            std::string line;
            std::stringstream sgenome;

            while (getline(genomeFile, line)) {
                sgenome << line << std::endl;
            }
            genomeFile.close();


            Glib::RefPtr<Gtk::TextBuffer> refTextBuffer = m_text_genome.get_buffer();
            Gtk::TextBuffer::iterator iter = refTextBuffer->get_iter_at_offset(0);

            refTextBuffer->insert(iter, sgenome.str());

            break;
        } case Gtk::RESPONSE_CANCEL: 
            break;
        default: 
            break;  
    }
}

void BMDriver::on_button_save_genome()
{

}

void BMDriver::on_button_create_genome()
{

}

CarSpec BMDriver::getCarSpec()
{
    CarSpec carSpec;
    
    carSpec.frontLeftTire.maxForwardSpeed = 250;
    carSpec.frontLeftTire.maxBackwardSpeed = -40;
    carSpec.frontLeftTire.maxDriveForce = 500;
    carSpec.frontLeftTire.maxLateralImpulse = 7.5;
    carSpec.frontRightTire = carSpec.frontLeftTire;
    carSpec.backLeftTire.maxForwardSpeed = 250;
    carSpec.backLeftTire.maxBackwardSpeed = -40;
    carSpec.backLeftTire.maxDriveForce = 300;
    carSpec.backLeftTire.maxLateralImpulse = 8.5;
    carSpec.backRightTire = carSpec.backLeftTire;   

    //carSpec.pos = track.getStartPos(1)->getPosition();
    //carSpec.angle = track.getStartPos(1)->getAngle();

    std::stringstream s;
    s << m_entry_groupIndex.get_text().raw();
    s >> carSpec.groupIndex;
    s >> carSpec.frontLeftTire.groupIndex;
    s >> carSpec.frontRightTire.groupIndex;
    s >> carSpec.backLeftTire.groupIndex;
    s >> carSpec.backRightTire.groupIndex;

    carSpec.rayVision.n = (int)m_scale_n.get_value();
    carSpec.rayVision.length = (int)m_scale_length.get_value();
    carSpec.rayVision.showRays = m_button_show.get_active();
    carSpec.rayVision.dynamicRays = m_button_dynamic.get_active();
    carSpec.rayVision.maxRayAngle = (int)m_scale_angle.get_value();

    carSpec.rayVision.filter = 0;
    if (m_button_ENT_TDCAR.get_active())
        carSpec.rayVision.filter |= EntType::ENT_CAR;
    if (m_button_ENT_TDTIRE.get_active())
        carSpec.rayVision.filter |= EntType::ENT_CARTIRE;
    if (m_button_ENT_TRACKLINK.get_active())
        carSpec.rayVision.filter |= EntType::ENT_TRACKLINK;
    if (m_button_ENT_CUBE.get_active())
        carSpec.rayVision.filter |= EntType::ENT_CUBE;    
    
    return carSpec;
}