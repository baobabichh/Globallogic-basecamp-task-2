#include "CheckBoxController.h"

CheckBoxController::~CheckBoxController()
{
    for (auto & it : m_connections)
    {
        QObject::disconnect(it.second);
    }
    m_connections.clear();
}

void CheckBoxController::add(QWidget& widget , QCheckBox& checkBox)
{
    auto it = m_connections.find(std::make_pair(&widget,&checkBox));
    if(it == std::end(m_connections))
    {
        QWidget* widget_ptr = &widget;
        QCheckBox* checkBox_ptr = &checkBox;

        widget_ptr->setEnabled(checkBox.isChecked());
        auto connection = QObject::connect(&checkBox,&QCheckBox::stateChanged,[widget_ptr,checkBox_ptr](int state)
        {
            if(state == Qt::CheckState::Checked)
            {
                widget_ptr->setEnabled(1);
            }
            else
            {
                widget_ptr->setEnabled(0);
            }
        });
        m_connections.insert(std::make_pair(std::make_pair(&widget,&checkBox),connection));
    }
}
void CheckBoxController::remove(QWidget& widget,QCheckBox& checkBox)
{
    auto it = m_connections.find(std::make_pair(&widget,&checkBox));
    if(it != std::end(m_connections))
    {
        it->first.first->setEnabled(1);
        QObject::disconnect(it->second);
        m_connections.erase(std::make_pair(&widget,&checkBox));
    }
}
