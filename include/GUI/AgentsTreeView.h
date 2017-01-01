#ifndef AGENTSTREEVIEW_H
#define AGENTSTREEVIEW_H

#include "GUI/AgentsTreeModel.h"

#include <gtkmm.h>
#include <iostream>
#include <vector>


class AgentsTreeView : public Gtk::TreeView {

public:
  AgentsTreeView();
  virtual ~AgentsTreeView();

protected:
  // Override Signal handler:
  // Alternatively, use signal_button_press_event().connect_notify()
  bool on_button_press_event(GdkEventButton* button_event) override;

  //Signal handler for popup menu items:
  void on_menu_file_popup_generic();

  AgentsTreeModel m_agentsModel;
  Glib::RefPtr<Gtk::TreeStore> m_refAgentsModel;

  Gtk::Menu m_Menu_Popup;

};

#endif 