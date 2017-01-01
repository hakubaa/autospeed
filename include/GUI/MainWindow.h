#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "GUI/InfoWindow.h"
#include "GUI/AgentsTreeModel.h"
#include "GUI/AgentsTreeView.h"
#include "GUI/Bookmark/BMNeat.h"
#include "GUI/Bookmark/BMDriver.h"
#include "GUI/Bookmark/BMTrack.h"
#include "GUI/Bookmark/BMLearnMode.h"

#include "SimMode/SimMode.h"
#include "SimMode/LearnMode.h"

#include "Entity/Car.h"
#include "Entity/Spec/CarSpec.h"
#include "Entity/Spec/CarTireSpec.h"
#include "Entity/Spec/RayVisionSpec.h"
#include "Drivers/HumanDriver.h"

#include "Drivers/ASpeedFactory.h"
#include "SimMode/SimController.h"

#include "Util/tsqueue.h"

#include <gtkmm.h>
#include <sstream>
#include <sigc++/sigc++.h>


#define CREATE_MSG(MSG_NAME) \
    static __attribute__((always_inline)) MainWindow::msg_t MSG_NAME() { return __COUNTER__; }


class MainWindow : public Gtk::Window {

    constexpr static char* m_title = "AutoSpeed Learning Simulator";
    constexpr static int m_initWidth = 800;
    constexpr static int m_initHeight = 600;

public:
    
    MainWindow(const Glib::RefPtr<Gtk::Application>& app);
    ~MainWindow();

    typedef unsigned int msg_t;
    class Msg 
    {
    public:
        CREATE_MSG(show_window);
    };

    // Called from the simulation thread
    void notify();
    TSQueue<SimMode::event_t>& getEventsQueue();

private:

    // Dispatcher handler (multithreading)
    Glib::Dispatcher m_Dispatcher;

    // Only one worker thread possible (can changed in the future)
    Glib::Threads::Thread* m_simThread;
    
    // Thread-safe events queue
    TSQueue<SimMode::event_t> m_eventsq;

    // Simulation controller
    SimController m_simc;
    LearnMode* m_learnSim;
    ASpeedFactory* m_dFactory;
    Car* m_car;
    HumanDriver* m_driver;

    // Dispatcher handler.
    void on_notification();
    void update_widgets();

    Gtk::Box m_VBox_Main;
    Gtk::Box m_VBox_Sub;
    Gtk::Paned m_HPaned;
    InfoWindow m_InfoWindow;
    Gtk::Label m_Label_Blind;
    Gtk::Label m_Label_Blind2;
    Gtk::Label m_Label_Blind3;

    // Bookmarks
    BMNeat m_BMNeat;
    BMDriver m_BMDriver;
    BMTrack m_BMTrack;
    BMLearnMode m_BMLearnMode;

    Gtk::Notebook m_modesBook;
    Gtk::Notebook m_configBook;

    AgentsTreeModel m_agentsModel;
    Glib::RefPtr<Gtk::TreeStore> m_refAgentsModel;

    Gtk::ScrolledWindow m_ScrolledWindow;
    AgentsTreeView m_agentsView;

    // Menubar & toolbar
    Glib::RefPtr<Gtk::Builder> m_refBuilder;
    Glib::RefPtr<Gio::SimpleActionGroup> m_refActionGroup;
    Glib::RefPtr<Gio::SimpleAction> m_refActionRain;

    //Signal handlers:
    void on_action_sim_new();
    void on_action_sim_save();
    void on_action_sim_open();
    void on_action_sim_quit();  
    void on_action_sim_run();
    void on_action_sim_stop();
    void on_action_sim_visu();

    void modeChanged(Gtk::Widget* page, guint page_number);
    void bookmarkChanged(Gtk::Widget* page, guint page_number);

    void on_action_start();
    void on_action_stop();
    void on_action_pause();
    void on_action_resume();
    void on_action_newgenr();
    void on_action_visu();
    void on_action_track_apply();
};

inline void MainWindow::notify() 
{
    m_Dispatcher.emit();
}

inline TSQueue<SimMode::event_t>& MainWindow::getEventsQueue()
{
    return m_eventsq;
}

#endif