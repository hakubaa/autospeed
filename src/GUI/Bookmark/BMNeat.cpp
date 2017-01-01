#include "GUI/Bookmark/BMNeat.h"

BMNeat::BMNeat(std::string fileName) :
    m_load("Load"), m_save("Save"),
    m_label("NEAT parameters") 
{
    m_grid.set_column_spacing(5);
    m_grid.set_row_spacing(5);

    // Add buttons and main label
    m_load.set_hexpand(true);
    m_grid.attach(m_load, 0, 0, 1, 1);
    m_save.set_hexpand(true);
    m_grid.attach(m_save, 1, 0, 1, 1);
    m_label.set_hexpand(true);
    m_grid.attach(m_label, 0, 1, 2, 1);
    // m_grid.attach_next_to(m_label, m_load, Gtk::POS_BOTTOM, 2, 1);

    // Ascribe actions to the buttons

    m_load.signal_clicked().connect(sigc::mem_fun(*this,
              &BMNeat::on_button_loadNEAT_clicked) );

     m_save.signal_clicked().connect(sigc::mem_fun(*this,
              &BMNeat::on_button_saveNEAT_clicked) );
   
    // Load settings' names from the file
    std::ifstream inNames(fileName);
    std::string sName;

    int index = 2;
    while (inNames >> sName) {
        m_paramsList.push_back(sName);

        Gtk::Label* sLabel = new Gtk::Label(sName);
        sLabel->set_hexpand(true);
        m_grid.attach(*sLabel, 0, index, 1, 1);

        Gtk::Entry* sEntry = new Gtk::Entry;
        sEntry->set_hexpand(true);
        sEntry->set_alignment(Gtk::ALIGN_CENTER);
        m_grid.attach(*sEntry, 1, index, 1, 1);

        m_labelsNEAT[sName] = sLabel;
        m_entriesNEAT[sName] = sEntry;

        index++;
    }
    inNames.close();
 
    add(m_grid);
}

BMNeat::~BMNeat() {
    for(std::map<std::string, Gtk::Label*>::iterator label = m_labelsNEAT.begin(); 
        label != m_labelsNEAT.end(); ++label) 
        delete label->second;

     for(std::map<std::string, Gtk::Entry*>::iterator entry = m_entriesNEAT.begin(); 
        entry != m_entriesNEAT.end(); ++entry) 
        delete entry->second;

    m_paramsList.clear();
}

void BMNeat::on_button_loadNEAT_clicked() {

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

                if (m_entriesNEAT.find(param) != m_entriesNEAT.end()) {
                    m_entriesNEAT[param]->set_text(paramVal);
                } else {
                    std::stringstream s;
                    s << "Unrecognized parametr '" << param << "'" << std::endl; 
                    Gtk::MessageDialog dialog(*dynamic_cast<Gtk::Window *>(this->get_toplevel()), 
                        s.str(), false, Gtk::MESSAGE_ERROR, Gtk::BUTTONS_OK_CANCEL);
                    dialog.set_secondary_text("Please make sure that the file with NEAT parameters is not corrupted. Proper selecton of the parameters can have significant impact on learning process.");
                    int result = dialog.run();
                    if (result == Gtk::RESPONSE_CANCEL)
                        break;
                }
            }
            inSettings.close();
            std::cout << "weight_mut_power = " << 
                m_entriesNEAT["weight_mut_power"]->get_text() << std::endl;
            getNEATconfig();
            break;
        } case Gtk::RESPONSE_CANCEL: 
            break;
        default: 
            break;  
    }

}

void BMNeat::on_button_saveNEAT_clicked() {

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
            for(std::vector<std::string>::iterator sName = m_paramsList.begin(); 
                sName != m_paramsList.end(); ++sName) {
                outSettings << *sName << " " << m_entriesNEAT[*sName]->get_text() << std::endl;
            }
            outSettings.close();
            break;
        } case Gtk::RESPONSE_CANCEL: 
            break;
        default: 
            break;  
    }

}


std::map<std::string, double> BMNeat::getNEATconfig()
{
    std::map<std::string, double> config;

    for(std::map<std::string, Gtk::Entry*>::iterator entry = m_entriesNEAT.begin(); 
            entry != m_entriesNEAT.end(); ++entry) 
    {
        std::stringstream s;
        double val;

        s << entry->second->get_text().raw();
        s >> val;

        config[entry->first] = val;
    }

    std::cout << "weight_mut_power = " << config["weight_mut_power"] << std::endl;

    return config;
}