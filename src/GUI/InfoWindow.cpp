#include "GUI/InfoWindow.h"

InfoWindow::InfoWindow() :
    m_TextView(),
    m_buffer(m_TextView.get_buffer())
{
    set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
    set_shadow_type(Gtk::SHADOW_ETCHED_OUT);

    m_TextView.set_editable(false);
    m_TextView.set_cursor_visible(false);
    add(m_TextView);

    show_all_children();
}

InfoWindow::~InfoWindow() {
}

void InfoWindow::insert(const Glib::ustring& text)
{
    Gtk::TextBuffer::iterator m_iter = m_buffer->end();
    m_buffer->insert(m_iter, text);
}

void InfoWindow::insert(std::queue<std::string>* qmsg)
{
    while (!qmsg->empty())
    {
        std::string text = qmsg->front();
        insert(text);
        qmsg->pop();
    }
    insert("--------------------------------------------------------------------------------\n");
    Glib::RefPtr<Gtk::TextBuffer::Mark> mark = m_buffer->get_insert();
    m_buffer->move_mark(mark, m_buffer->end());
    m_TextView.scroll_to(mark);
}
