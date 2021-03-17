/* File: main.cpp
 * --------------
 * The main function calls the investing.cpp
 * by calling it summarizing conclusion() function.
 */
#include <iostream>
#include "console.h"
#include "investing.h"
#include "testing/SimpleTest.h"
using namespace std;

static string dbfile = "res/52weeksData.txt";
static string dbByMonth = "res/dataByMonth.txt";



int main() {
    if (runSimpleTests(SELECTED_TESTS)) {
        return 0;
    }

    conclusion(dbfile, dbByMonth);

    cout << endl;
    cout << "All done, exiting!" << endl;
    return 0;
}
