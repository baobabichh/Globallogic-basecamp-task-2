#ifndef CHECKBOXCONTROLLER_H
#define CHECKBOXCONTROLLER_H

#include <QMainWindow>
#include <QLineEdit>
#include <QCheckBox>
#include <set>


// Sets QWidget enabled or not depending on QCheckBox.
class CheckBoxController
{
public:

    CheckBoxController() = default;

    CheckBoxController(const CheckBoxController&) = delete;

    CheckBoxController(CheckBoxController&&) = default;

    virtual ~CheckBoxController();

    // Add connection of QWidget and QCheckBox
    void add(QWidget& widget , QCheckBox& checkBox);

    // Remove connection of QWidget and QCheckBox
    void remove(QWidget& widget,QCheckBox& checkBox);

private:

    // QWidget* and QCheckBox* is a key, QMetaObject::Connection is a value.
    // QMetaObject::Connection is connection between QWidget* and QCheckBox*.
    std::map<std::pair<QWidget*,QCheckBox*>,QMetaObject::Connection> m_connections;

};

#endif // CHECKBOXCONTROLLER_H
