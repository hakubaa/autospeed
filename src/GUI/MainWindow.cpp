
#include "GUI/MainWindow.h"


MainWindow::MainWindow(const Glib::RefPtr<Gtk::Application>& app) :
    m_simc(this),
    m_VBox_Main(Gtk::ORIENTATION_VERTICAL),
    m_VBox_Sub(Gtk::ORIENTATION_VERTICAL),
    m_HPaned(Gtk::ORIENTATION_HORIZONTAL),
    m_Label_Blind("Space for some buttons"),
    m_Label_Blind2("Space for some buttons"),
    m_Label_Blind3("Space for some buttons"),
    m_InfoWindow(),
    m_agentsModel(),
    m_agentsView(),
    m_modesBook(),
    m_BMNeat("res/NEATsettings"),
    m_BMTrack(),
    m_BMLearnMode(),
    m_simThread(nullptr),
    m_dFactory(nullptr),
    m_learnSim(nullptr),
    m_car(nullptr),
    m_driver(nullptr)
{
    set_title (m_title);
    set_border_width(5);
    set_default_size(m_initWidth, m_initHeight);

    m_modesBook.set_border_width(5);

    m_ScrolledWindow.add(m_agentsView);
    m_ScrolledWindow.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);

    m_modesBook.append_page(m_ScrolledWindow, "Learn Mode");
    m_modesBook.append_page(m_Label_Blind3, "Race Mode");

    m_modesBook.signal_switch_page().connect(sigc::mem_fun(*this, &MainWindow::modeChanged));

    m_VBox_Sub.pack_start(m_modesBook);
    m_VBox_Sub.pack_start(m_InfoWindow);

    m_HPaned.pack1(m_VBox_Sub, Gtk::EXPAND);

    
    m_configBook.append_page(m_BMNeat, "NEAT");
    m_configBook.append_page(m_BMDriver, "Driver/Car");
    m_configBook.append_page(m_BMTrack, "Track");
    m_configBook.append_page(m_BMLearnMode, "Learn Mode");
    m_configBook.signal_switch_page().connect(sigc::mem_fun(*this, &MainWindow::bookmarkChanged));

    m_HPaned.pack2(m_configBook);

    add(m_VBox_Main);

    //Define the actions:
    m_refActionGroup = Gio::SimpleActionGroup::create();

    m_refActionGroup->add_action("new",
        sigc::mem_fun(*this, &MainWindow::on_action_sim_new) );
    m_refActionGroup->add_action("save",
        sigc::mem_fun(*this, &MainWindow::on_action_sim_save) );
    m_refActionGroup->add_action("open",
        sigc::mem_fun(*this, &MainWindow::on_action_sim_open) );
    m_refActionGroup->add_action("quit",
        sigc::mem_fun(*this, &MainWindow::on_action_sim_quit) );

    m_refActionGroup->add_action("run",
        sigc::mem_fun(*this, &MainWindow::on_action_sim_run) );
    m_refActionGroup->add_action("stop",
        sigc::mem_fun(*this, &MainWindow::on_action_sim_stop) );
    m_refActionGroup->add_action("visu",
        sigc::mem_fun(*this, &MainWindow::on_action_sim_visu) );

    insert_action_group("actions", m_refActionGroup);

    m_refBuilder = Gtk::Builder::create();
    try {
        // m_refBuilder->add_from_string(ui_info);
        m_refBuilder->add_from_file("res/menubar.glade");
        m_refBuilder->add_from_file("res/toolbar.glade");
    } catch(const Glib::Error& ex) {
        std::cerr << "Building menus and toolbar failed: " <<  ex.what();
    }

    auto object = m_refBuilder->get_object("menubar");
    auto gmenu = Glib::RefPtr<Gio::Menu>::cast_dynamic(object);
    if (!gmenu)
        g_warning("GMenu not found");
    else {
        auto pMenuBar = Gtk::manage(new Gtk::MenuBar(gmenu));
        m_VBox_Main.pack_start(*pMenuBar, Gtk::PACK_SHRINK);
    }

    Gtk::Toolbar* toolbar = nullptr;
    m_refBuilder->get_widget("toolbar", toolbar);
    if (!toolbar)
        g_warning("GtkToolbar not found");
    else
        m_VBox_Main.pack_start(*toolbar, Gtk::PACK_SHRINK);

    m_VBox_Main.pack_start(m_HPaned);

    // m_LMController.setInfoWindow(&m_InfoWindow);
    // m_LMController.signal_new_generation().connect(
        // sigc::mem_fun(m_InfoWindow, &InfoWindow::update_on_signal));

    // Signales connection

    m_BMLearnMode.m_button_start.signal_clicked().connect(
        sigc::mem_fun(*this, &MainWindow::on_action_start));

    m_BMLearnMode.m_button_stop.signal_clicked().connect(
        sigc::mem_fun(*this, &MainWindow::on_action_stop));

    m_BMLearnMode.m_button_resume.signal_clicked().connect(
        sigc::mem_fun(*this, &MainWindow::on_action_resume));

    m_BMLearnMode.m_button_pause.signal_clicked().connect(
        sigc::mem_fun(*this, &MainWindow::on_action_pause));

    m_BMLearnMode.m_button_newgenr.signal_clicked().connect(
        sigc::mem_fun(*this, &MainWindow::on_action_newgenr));

     m_BMLearnMode.m_button_visu.signal_clicked().connect(
        sigc::mem_fun(*this, &MainWindow::on_action_visu));   

     m_BMTrack.m_button_apply.signal_clicked().connect(
        sigc::mem_fun(*this, &MainWindow::on_action_track_apply));  

    m_Dispatcher.connect(
        sigc::mem_fun(*this, &MainWindow::on_notification));


    show_all_children();
}

MainWindow::~MainWindow()
{
    if (m_dFactory != nullptr)
        delete m_dFactory; 
    if (m_learnSim != nullptr)
        delete m_learnSim; 
    if (m_car != nullptr)
        delete m_car;
    if (m_driver != nullptr)
        delete m_driver;
}


void MainWindow::on_action_sim_new() {}
void MainWindow::on_action_sim_save() {}
void MainWindow::on_action_sim_open() {}
void MainWindow::on_action_sim_quit() {} 
void MainWindow::on_action_sim_run() {}
void MainWindow::on_action_sim_stop() {}
void MainWindow::on_action_sim_visu() {}



void MainWindow::modeChanged(Gtk::Widget* page, guint page_number)
/*
page    The new current page.
page_number The index of the page. 
*/
{
}

void MainWindow::bookmarkChanged(Gtk::Widget* page, guint page_number)
{
}

void MainWindow::update_widgets()
{

}

void MainWindow::on_action_start()
{
    std::cout << "MainWindow::on_action_start() BEGIN" << std::endl;
    // Create LearnMode model

    NEAT::set_neat_params(m_BMNeat.getNEATconfig(), true);

    if (m_dFactory != nullptr)
        delete m_dFactory;

    TrackSpec tspec = m_BMTrack.getTrackSpec();
    StartPosSpec* spos = tspec.getStartPos(m_BMTrack.getStartPosNo());
    m_dFactory = new ASpeedFactory(m_BMDriver.getCarSpec(), spos->pos, 
        spos->angle - 90.0f * DEGTORAD); 

    // Experience Time
    std::stringstream s1;
    s1 << m_BMLearnMode.m_entry_exptime.get_text().raw();
    float expTime;
    s1 >> expTime;

    if (m_learnSim != nullptr)
        delete m_learnSim;
    m_learnSim = new LearnMode(m_BMLearnMode.getGenomeFile(), m_dFactory, sf::seconds(expTime));
    m_learnSim->setTrack(tspec);

    // Set Human Driver
    if (m_car != nullptr)
        delete m_car;
    CarSpec cspec = m_BMDriver.getCarSpec();
    cspec.rayVision.showRays = true;
    cspec.rayVision.dynamicRays = true;
    m_car = new Car(cspec, m_learnSim->getb2World());
    m_car->setTransform(spos->pos, spos->angle - 90.0f * DEGTORAD);
    
    if (m_driver != nullptr)
        delete m_driver;
    m_driver = new HumanDriver(m_car);
    m_driver->setKeyController(m_simc.getKeyController());
    m_driver->setActive(true);

    m_learnSim->setExtraDriver(m_driver);

    // Configure simulation controller
    m_simc.setSim(m_learnSim);

    // RTS
    m_simc.setRTS(m_BMLearnMode.m_button_rts.get_active());
    
    //Time Step
    std::stringstream s2;
    s2 << m_BMLearnMode.m_entry_timestep.get_text().raw();
    float timeStep;
    s2 >> timeStep;
    m_simc.setTimeStep(timeStep);

   // Start simulation
    m_simThread = Glib::Threads::Thread::create(
        sigc::mem_fun(m_simc, &SimController::start));

    std::cout << "MainWindow::on_action_start() END" << std::endl;
}

void MainWindow::on_action_stop()
{
    m_simc.stop();
}

void MainWindow::on_action_pause()
{
    m_simc.pause();
}

void MainWindow::on_action_resume()
{
    m_simc.resume();
}

void MainWindow::on_action_newgenr()
{
    m_learnSim->startNewGenr();
}

void MainWindow::on_action_visu()
{
    // m_simc.getMsgQueue().push(MainWindow::Msg::show_window());
    // m_simc.notify();
    m_simc.showWindow();
}

void MainWindow::on_notification()
{
    while (!m_eventsq.empty())
    {
        SimMode::event_t event = m_eventsq.front();
        m_eventsq.pop();

        if (event == LearnMode::Event::new_generation())
        {
            std::cout << "MainWindow::on_notification() - new generation BEGIN" << std::endl;
            m_InfoWindow.insert(m_learnSim->getPopMsgQueue());
            
            //RTS
            m_simc.setRTS(m_BMLearnMode.m_button_rts.get_active());
            
            // Experience Time
            std::stringstream s1;
            s1 << m_BMLearnMode.m_entry_exptime.get_text().raw();
            float expTime;
            s1 >> expTime;
            m_learnSim->setExpTime(expTime);

            //Time Step
            std::stringstream s2;
            s2 << m_BMLearnMode.m_entry_timestep.get_text().raw();
            float timeStep;
            s2 >> timeStep;

            m_simc. setTimeStep(timeStep);


            std::cout << "MainWindow::on_notification() - new generation END" << std::endl;
        }
    }
}

void MainWindow::on_action_track_apply()
{
    if (m_simc.isRunning())
    {
        TrackSpec tspec = m_BMTrack.getTrackSpec();
        StartPosSpec* spos = tspec.getStartPos(m_BMTrack.getStartPosNo());

        // update factory and track
        m_dFactory->setStartPos(spos->pos, spos->angle - 90.0f * DEGTORAD); 
        m_learnSim->setTrack(tspec);
    }
}