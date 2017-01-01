#ifndef AGENTSTREEMODEL_H
#define AGENTSTREEMODEL_H

#include <gtkmm.h>

class AgentsTreeModel : public Gtk::TreeModelColumnRecord {

public:
    AgentsTreeModel();

    Gtk::TreeModelColumn<int> m_id;
    Gtk::TreeModelColumn<int> m_generation;
    Gtk::TreeModelColumn<double> m_fitness;

};

#endif


/*

Glib::RefPtr<Gtk::TreeStore> refListStore =
    Gtk::TreeStore::create(m_Columns);

*/