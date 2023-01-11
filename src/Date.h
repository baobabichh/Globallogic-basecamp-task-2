#ifndef DATE_H
#define DATE_H

#include <QDateTime>

// Light weight Date structure, includes time.
struct Date
{
    unsigned short year = 0;
    unsigned char month = 0, day = 0;
    unsigned char hour = 0, minute = 0, second = 0;

    bool operator==(const Date& val);

    bool operator!=(const Date& val);

    // Converts from QString to this object format "day.month.year hour:minute:second".
    bool fromQString(const QString& str);

    // Converts from QDateTime data to this object.
    void fromQDateTime(const QDateTime& date);

    // Represent date in string, format "day.month.year hour:minute:second"
    QString toQString() const;
};

#endif // DATE_H
