#ifndef TIMEENTRY_H
#define TIMEENTRY_H
struct TimeEntry {
    TimeEntry(const int &days,
              const int &hours,
              const int &minutes,
              const int &seconds) :
        days(days),
        hours(hours),
        minutes(minutes),
        seconds(seconds)
    {

    }

    int days;
    int hours;
    int minutes;
    int seconds;
};

#endif // TIMEENTRY_H
