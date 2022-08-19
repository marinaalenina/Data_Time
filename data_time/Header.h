#pragma once
#include <string>
#include <iostream>

typedef struct Date {
    int year;
    int month;
    int day;
} Date;

typedef struct Time {
    int seconds;
    int minutes;
    int hours;
} Time;

class DateTime {
private:
    Time t;
    Date d;
    static bool isRange(int value, int min, int max);
public:
    DateTime();
    DateTime(int secs, Date date, Time time);

    DateTime(DateTime& obj) = default;
    DateTime(DateTime&& obj) = default;

    inline Time getTime() const;
    inline void setTime(Time time);

    inline Date getDate() const;
    inline void setDate(Date date);

    static bool isValidDate(int year, int month, int day);
    static bool isValidTime(int seconds, int minutes, int hours);

    static DateTime getLocalTime();

    inline int getSecs() const;
    inline int getMinutes() const;
    inline int getHours() const;
    inline int getDay() const;
    inline int getMonth() const;
    inline int getYear() const;

    static DateTime fromString(/*std::string date*/DateTime dt, std::string format);

    DateTime addYears(int num);
    DateTime addMonths(int num);
    DateTime addDays(int num);
    DateTime addHours(int num);
    DateTime addMinutes(int num);
    DateTime addSecs(int num);

    int daysTo(DateTime dt);
    int secsTo(DateTime dt);
};

inline Time DateTime::getTime() const {
    return t;
}

inline void DateTime::setTime(Time time) {
    if (isValidTime(time.seconds, time.minutes, time.hours)) t = time;
}

inline Date DateTime::getDate() const {
    return d;
}

inline void DateTime::setDate(Date date) {
    if (isValidDate(date.year, date.month, date.day)) d = date;
}

inline int DateTime::getSecs() const {
    return t.seconds;
}

inline int DateTime::getMinutes() const {
    return t.minutes;
}

inline int DateTime::getHours() const {
    return t.hours;
}

inline int DateTime::getDay() const {
    return d.day;
}

inline int DateTime::getMonth() const {
    return d.month;
}

inline int DateTime::getYear() const {
    return d.year;
}

std::ostream& operator<<(std::ostream& strm, const DateTime& dt);

#pragma once