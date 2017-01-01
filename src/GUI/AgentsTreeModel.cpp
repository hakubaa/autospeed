#include "GUI/AgentsTreeModel.h"

AgentsTreeModel::AgentsTreeModel() {
    add(m_id);
    add(m_generation);
    add(m_fitness);
}