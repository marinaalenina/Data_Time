#include "Header.h"
#include <iostream>

using namespace std;

int main()
{
    DateTime t;
    DateTime dt2(0, { 2000, 7, 20 }, { 12, 4, 14});

    cout << t;
    cout << dt2;

    cout << dt2.secsTo(t) << " secs" << endl;
    cout << dt2.daysTo(t) << " days" << endl;

    cout << dt2.fromString(dt2, "%Y%m%d%S%M%H");
}
