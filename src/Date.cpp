#include "Date.h"
#include <QObject>

// Converts from QString to this object format "day.month.year hour:minute:second".

bool Date::operator==(const Date& val)
{
    return (year == val.year) && (month == val.month) && (day == val.day) && (hour == val.hour) && (minute == val.minute) && (second == val.second);
    
}

bool Date::operator!=(const Date& val)
{
    return !(*this == val);
}

bool Date::fromQString(const QString& str)
{
    QString tmp;
    int i = 0;
    bool hasPrew = 0;

    // Day parsing.
    for (; i < str.length(); i++)
    {
        if (str[i] == '.')
        {
            i++;
            break;
        }
        if (!str[i].isDigit())
        {
            return 0;
        }
        tmp.push_back(str[i]);
        hasPrew = 1;
    }
    day = tmp.toInt();

    // Month parsing.
    if (!hasPrew)
        return 0;
    hasPrew = 0;
    tmp = "";
    for (; i < str.length(); i++)
    {
        if (str[i] == '.')
        {
            i++;
            break;
        }
        if (!str[i].isDigit())
        {
            return 0;
        }
        tmp.push_back(str[i]);
        hasPrew = 1;
    }
    month = tmp.toInt();

    // Year parsing.
    if (!hasPrew)
        return 0;
    hasPrew = 0;
    tmp = "";
    for (; i < str.length(); i++)
    {
        if (str[i] == ' ')
        {
            i++;
            break;
        }
        if (!str[i].isDigit())
        {
            return 0;
        }
        tmp.push_back(str[i]);
        hasPrew = 1;
    }
    year = tmp.toInt();

    // Hour parsing.
    if (!hasPrew)
        return 0;
    hasPrew = 0;
    tmp = "";
    for (; i < str.length(); i++)
    {
        if (str[i] == ':')
        {
            i++;
            break;
        }
        if (!str[i].isDigit())
        {
            return 0;
        }
        tmp.push_back(str[i]);
        hasPrew = 1;
    }
    hour = tmp.toInt();

    // Minute parsing.
    if (!hasPrew)
        return 0;
    hasPrew = 0;
    tmp = "";
    for (; i < str.length(); i++)
    {
        if (str[i] == ':')
        {
            i++;
            break;
        }
        if (!str[i].isDigit())
        {
            return 0;
        }
        tmp.push_back(str[i]);
        hasPrew = 1;
    }
    minute = tmp.toInt();

    // Second parsing.
    if (!hasPrew)
        return 0;
    hasPrew = 0;
    tmp = "";
    for (; i < str.length(); i++)
    {
        if (!str[i].isDigit())
        {
            return 0;
        }
        tmp.push_back(str[i]);
        hasPrew = 1;
    }
    second = tmp.toInt();

    return 1;
}

// Converts from QDateTime data to this object.

void Date::fromQDateTime(const QDateTime& date)
{
    year = date.date().year();
    month = date.date().month();
    day = date.date().day();

    hour = date.time().hour();
    minute = date.time().minute();
    second = date.time().second();
}

// Represent date in string, format "day.month.year hour:minute:second"

QString Date::toQString() const
{
    QString res;
    res += QString::number(day);
    res += ".";
    res += QString::number(month);
    res += ".";
    res += QString::number(year);
    res += " ";

    res += QString::number(hour);
    res += ":";
    res += QString::number(minute);
    res += ":";
    res += QString::number(second);

    return res;
}
