#include "GUI/AgentsTreeView.h"

AgentsTreeView::AgentsTreeView() {

    m_refAgentsModel = Gtk::TreeStore::create(m_agentsModel);
    set_model(m_refAgentsModel);
    append_column("Id", m_agentsModel.m_id);
    append_column("Generation", m_agentsModel.m_generation);
    append_column("Fitness", m_agentsModel.m_fitness);
    std::vector<Gtk::TreeViewColumn*> columns = get_columns();
    for(std::vector<Gtk::TreeViewColumn*>::iterator column = columns.begin(); 
        column != columns.end(); ++column) 
        (*column)->set_resizable(true);

    set_enable_tree_lines(true);
    set_headers_clickable(true);

    // Fill the three model, example
    for(int j = 0; j < 3; j++) {
            
        Gtk::TreeModel::Row row = *(m_refAgentsModel->append());
        row[m_agentsModel.m_id] = j;
        row[m_agentsModel.m_generation] = j;
        row[m_agentsModel.m_fitness] = (float)j * 00.44;

        for(int i = 0; i < 10; i++) {
            Gtk::TreeModel::Row row2 = *(m_refAgentsModel->append(row.children()));
            row2[m_agentsModel.m_id] = i;
            row2[m_agentsModel.m_generation] = j;
            row2[m_agentsModel.m_fitness] = (float)i * 00.44;
        }
    }

  //Fill popup menu:
  auto item = Gtk::manage(new Gtk::MenuItem("_Edit", true));
  item->signal_activate().connect(
    sigc::mem_fun(*this, &AgentsTreeView::on_menu_file_popup_generic) );
  m_Menu_Popup.append(*item);
    
  item = Gtk::manage(new Gtk::MenuItem("_Process", true));
  item->signal_activate().connect(
    sigc::mem_fun(*this, &AgentsTreeView::on_menu_file_popup_generic) );
  m_Menu_Popup.append(*item);
    
  item = Gtk::manage(new Gtk::MenuItem("_Remove", true));
  item->signal_activate().connect(
    sigc::mem_fun(*this, &AgentsTreeView::on_menu_file_popup_generic) );
  m_Menu_Popup.append(*item);

  m_Menu_Popup.accelerate(*this);
  m_Menu_Popup.show_all(); //Show all menu items when the menu pops up
}

AgentsTreeView::~AgentsTreeView() {

}

bool AgentsTreeView::on_button_press_event(GdkEventButton* button_event) {

  bool return_value = false;

  //Call base class, to allow normal handling,
  //such as allowing the row to be selected by the right-click:
  return_value = TreeView::on_button_press_event(button_event);

  //Then do our custom stuff:
  if( (button_event->type == GDK_BUTTON_PRESS) && (button_event->button == 3) )
  {
    m_Menu_Popup.popup(button_event->button, button_event->time);
  }

  return return_value;
}

void AgentsTreeView::on_menu_file_popup_generic() {

  std::cout << "A popup menu item was selected." << std::endl;

  auto refSelection = get_selection();
  if(refSelection)
  {
    Gtk::TreeModel::iterator iter = refSelection->get_selected();
    if(iter)
    {
      int id = (*iter)[m_agentsModel.m_id];
      std::cout << "  Selected ID=" << id << std::endl;
    }
  }
}