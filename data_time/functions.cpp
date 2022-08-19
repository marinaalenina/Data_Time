#define _CRT_SECURE_NO_WARNINGS
#include "Header.h"

DateTime::DateTime()  {
    time_t t_t;
    std::time(&t_t);
    struct tm* datetime = localtime(&t_t);

    t = { datetime->tm_sec, datetime->tm_min, datetime->tm_hour };
    d = { datetime->tm_year + 1900, datetime->tm_mon + 1, datetime->tm_mday };
}

DateTime::DateTime(int secs, Date date, Time time) {
    tm tm = { time.seconds, time.minutes, time.hours, date.day, date.month - 1, date.year - 1900 };
    time_t tt = mktime(&tm) + secs;

    struct tm* datetime = localtime(&tt);

    t = { datetime->tm_sec, datetime->tm_min, datetime->tm_hour };
    d = { datetime->tm_year + 1900, datetime->tm_mon + 1, datetime->tm_mday };
}

DateTime DateTime::fromString(DateTime dt, std::string format) {
    char temp[100];
    tm tm = { dt.getSecs(), dt.getMinutes(), dt.getHours(), dt.getDay(), dt.getMonth() - 1, dt.getYear() - 1900 };
    strftime(temp, 100, format.c_str(), &tm);
    std::string date = temp;

    int year = -1;
    int month = -1;
    int day = -1;
    int hours = -1;
    int minutes = -1;
    int seconds = -1;

    int i = 0;
    int j = 0;
    int ind = 0;

    while (format[i]) {
        if (ind == 1) {
            ind = 0;
            switch (format[i]){
            case 'y':
                year = stoi(date.substr(j, 2));
                j += 2;
                break;
            case 'Y':
                year = stoi(date.substr(j, 4));
                j += 4;
                break;
            case 'm':
                month = stoi(date.substr(j, 2));
                j += 2;
                break;
            case 'd':
                day = stoi(date.substr(j, 2));
                j += 2;
                break;
            case 'H':
                hours = stoi(date.substr(j, 2));
                j += 2;
                break;
            case 'M':
                minutes = stoi(date.substr(j, 2));
                j += 2;
                break;
            case 'S':
                seconds = stoi(date.substr(j, 2));
                j += 2;
                break;
            default:
                break;
            }
            i++;
        }
        else if (format[i] == '%') { 
            ind = 1;
            i++;
        }
        else {
            i++;
            j++;
        }
    }

    Date d = { year, month, day };
    Time t = { hours, minutes, seconds };

    if (isValidDate(year, month, day) && isValidTime(hours, minutes, seconds))
        return DateTime(0, d, t);

    return DateTime();
}

bool DateTime::isRange(int value, int min, int max) {
    if (value < min) return false;
    if (value > max) return false;
    return true;
}

bool DateTime::isValidDate(int year, int month, int day) {
    if (year < 0)
        return false;

    switch (month) {
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
        return isRange(day, 1, 31);
    case 2:
        if (year % 4 == 0 || (year % 100 == 0 && year % 400))
            return isRange(day, 1, 29);
        else
            return isRange(day, 1, 28);
    case 4:
    case 6:
    case 9:
    case 11:
        return isRange(day, 1, 30);
    default:
        return false;
    }
}

bool DateTime::isValidTime(int seconds, int minutes, int hours) {
    if (seconds < 0 || seconds > 59)
        return false;

    if (minutes < 0 || minutes > 59)
        return false;

    if (hours < 0 || hours > 23)
        return false;

    return true;
}

DateTime DateTime::getLocalTime() {
    return DateTime();
}

DateTime DateTime::addYears(int num) {
    Date tempd = d;
    tempd.year += num;

    return DateTime(0, tempd, t);
}

DateTime DateTime::addMonths(int num) {
    Date tempd = d;
    tempd.month += num;

    return DateTime(0, tempd, t);
}

DateTime DateTime::addDays(int num) {
    Date tempd = d;
    tempd.day += num;

    return DateTime(0, tempd, t);
}

DateTime DateTime::addHours(int num) {
    return DateTime(num * 3600, d, t);
}

DateTime DateTime::addMinutes(int num) {
    return DateTime(num * 60, d, t);
}

DateTime DateTime::addSecs(int num) {
    return DateTime(num, d, t);
}

int DateTime::daysTo(DateTime dt) {
    return secsTo(dt) / (24 * 3600);
}

int DateTime::secsTo(DateTime dt) {
    tm tmcur = { getSecs(), getMinutes(), getHours(), getDay(), getMonth() - 1, getYear() - 1900 };
    tm tmdt = { dt.getSecs(), dt.getMinutes(), dt.getHours(), dt.getDay(), dt.getMonth() - 1, dt.getYear() - 1900 };

    return difftime(mktime(&tmdt), mktime(&tmcur));
}

std::ostream& operator<<(std::ostream& strm, const DateTime& dt) {
    strm << dt.getHours() << ":" << dt.getMinutes() << ":" << dt.getSecs() << "\n" << dt.getDay() << "/" << dt.getMonth() << "/" << dt.getYear() << "\n";
    return strm;
}