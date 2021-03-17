/* File: investing.cpp
 * -------------------
 * Marina Wolters, CS106B
 *
 * This program helps the user to decide which strategy to following while
 * investing in bitcoin. It compares two different strategies: buying bitcoin
 * weekly and buying it all at once and draws the conclusion about the likely
 * winning strategy and its potential gains.
 */
#include <iostream>
#include <cctype>
#include <string>
#include <fstream>
#include "vector.h"
#include "math.h"
#include "error.h"
#include "filelib.h"
#include "map.h"
#include "investing.h"
#include "set.h"
#include "strlib.h"
#include "simpio.h"
#include "testing/SimpleTest.h"
using namespace std;

static const int weekly = 100;
static const int once = 5200;
static double bitcoinLatestPrice = 56740.32;


/* The function helps the user to draw the conclusion about the best
 * strategy to follow. It also supports this conclusion by providing
 * the information about how much more the user gained using the weekly
 * or all-at-once strategy as well as posts user total gains.
 */
void conclusion(string dbfile, string dbByMonth){
    double purchasedWeekly = weeklyInvesting(dbfile);
    double purchasedOnce = investingOnce(dbByMonth);

    if (purchasedWeekly > purchasedOnce){
        cout << endl;
        cout << "You are better off buying Bitcoin weekly!" << endl;
        cout << "You gained: $" << purchasedWeekly - purchasedOnce << " extra." << endl;
        cout << "Total gains: $" << purchasedWeekly - once << endl;
        cout << "Today's value: $" << purchasedWeekly << endl;
    }
    else{
        cout << endl;
        cout << "You are better off buying Bitcoin all at once!" << endl;
        cout << "You gained: $" << purchasedOnce - purchasedWeekly << " extra." << endl;
        cout << "Total gains: $" << purchasedOnce - once << endl;
        cout << "Today's value: $" << purchasedOnce << endl;
    }

    cout << endl;
    string trials = getLine("Do you want to do 100 tests to compare the odds? (yes/no): ");
    if (trials[0] == 'y' || trials[0] == 'Y') {
        int count = 0;
        int weeklyOdds = 0, onceOdds = 0;

        while (count < 100){
            purchasedWeekly = weeklyInvesting(dbfile);
            purchasedOnce = investingOnce(dbByMonth);

            if (purchasedWeekly > purchasedOnce) weeklyOdds += 1;
            else onceOdds += 1;
            count++;
        }

        cout << "You will be better off " << weeklyOdds*1 << "% of the times buying weekly vs "
             << onceOdds*1 << "% buying all at once." << endl;
    }

}

/* This function explores the weekly strategy and "buys" $100 worth
 * of bitcoin every week. It then calculates the accumulated amount
 * of bitcoin and weighs this investment in today's bitcoin price.
 */
double weeklyInvesting(string dbfile){

    double totalDollars = 0.00;
    double bitcoin, totalBitcoin = 0.00000000;

    Vector<string> lines = readFile(dbfile);
    for (int i = 0; i < lines.size(); i++){
        double price = stringToDouble(lines[i]);
        bitcoin = weekly / price;
        totalBitcoin += bitcoin;
    }
    totalDollars = totalBitcoin * bitcoinLatestPrice;
    return totalDollars;
}


/* This function explores the all-at-once strategy and "buys" $5,200 worth
 * of bitcoin one time. To do so, the function randomly chooses the month
 * and makes the transaction based on its lowest price. This strategy supports
 * the idea that the majority of users would be able to identify and act on the
 * "relative deep" - the lowest price of bitcoin every given month.
 */
double investingOnce(string dbByMonth){

    Map<double, double> priceMap;
    buildPriceMap(dbByMonth, priceMap);

    double key = randomInteger(1, 12);
    double price = priceMap[key];
    double bitcoin = once / price;
    double totalDollars = bitcoin * bitcoinLatestPrice;

    return totalDollars;
}


/* Given the data file, this function builds the price map by
 * identifying the lowest price of bitcoin at every given month.
*/
void buildPriceMap(string dbByMonth, Map<double, double> &priceMap){
    double price = 0.00;
    double key = 0;
    Vector<string> lines = readFile(dbByMonth);

    for (int i = 0; i < lines.size(); i++){
        if (i % 5 == 0){
            key = stringToDouble(lines[i]);
        }
        else{
            price = stringToDouble(lines[i]);
            if (!priceMap.containsKey(key)){
                priceMap[key] = price;
            } else {
                if (price < priceMap[key]){
                    priceMap[key] = price;
                }
            }
        }
    }
}


/* This function reads the entire file and places
 * its contents in the Vector<sting> lines.
 */
Vector<string> readFile(string dbfile){
    Vector<string> lines;
    ifstream in;
    if (!openFile(in, dbfile)){
        error("Cannot open file named" + dbfile);
    }

    readEntireFile(in, lines);
    return lines;
}


/** Here are the alternative implementations of investingOnce() and
 *  buildMap() functions.
 *  Printing functions of randomly chosen key, matching lowest price,
 *  and priceMap itself left here for the testing purposes.
 */
//double investingOnce(string dbByMonth){
//    double totalDollars = 0.00;
//    double bitcoin = 0.000000;
//    Map<double, Vector<double>> priceMap;
//    priceMap = buildMap(dbByMonth);

//    int key = randomInteger(1, 12);
//    cout << endl;
//    cout << "Key: " << key << endl;

//    priceMap[key].sort();
//    double price = priceMap[key][0];
//    cout << "Price: " << price << endl;

//    bitcoin = once / price;
//    totalDollars = bitcoin * bitcoinLatestPrice;

//    return totalDollars;
//}

/** The alternative implementation of buildMap function.
 * It creates the map in the function itself and populates it
 * with the data from dbByMonth file.
 */
//Map<double, Vector<double>> buildMap(string dbByMonth){
//    Map<double, Vector<double>> priceMap;
//    Vector<string> lines = readFile(dbByMonth);
//    double key = 0;
//    Vector<double> prices;

//    for (string line : lines){
//        double l = stringToDouble(line);
//        if (l >= 1 && l <= 12){
//            key = l;
//        }
//        else{
//            double price = l;
//            priceMap[key].add(price);
//            if (prices.size() >= 4){
//                priceMap[key] = prices;
//                prices.clear();
//            }
//        }
//    }
//    cout << priceMap << endl;
//    return priceMap;
//}



/* * * * * * * Test Cases * * * * * * */

/** For the testing strategy feel free to use the printing function to confirm
 *  that your map captures all the data as you intended and that you can identify
 *  the lowest price point correctly.
*/


PROVIDED_TEST("Tests weeklyInvesting function") {
    string dbfile = "res/52weeksData.txt";
    double todaysValue = 0.595163 * bitcoinLatestPrice;
    // Your investment is worth $33,186 in today's dollars
    EXPECT_EQUAL(int(weeklyInvesting(dbfile)), (int)todaysValue);
}


PROVIDED_TEST("Tests buildPriceMap, map is not empty"){
    string dbByMonth = "res/dataByMonth.txt";
    Map<double, double> priceMap;
    buildPriceMap(dbByMonth, priceMap);

    EXPECT(!priceMap.isEmpty());
}

PROVIDED_TEST("Tests buildPriceMap, map contains the keys"){
    string dbByMonth = "res/dataByMonth.txt";
    Map<double, double> priceMap;
    buildPriceMap(dbByMonth, priceMap);

    EXPECT(priceMap.containsKey(1));
    EXPECT(priceMap.containsKey(12));
    EXPECT(!priceMap.containsKey(0));
    EXPECT(!priceMap.containsKey(10673.58));
}

PROVIDED_TEST("buildPriceMap, key and value match th lowest price"){
    string dbByMonth = "res/dataByMonth.txt";
    Map<double, double> priceMap;
    buildPriceMap(dbByMonth, priceMap);

    EXPECT_EQUAL(priceMap[1], 7351.53);
    EXPECT_EQUAL(priceMap[5], 8728.88);
    EXPECT_EQUAL(priceMap[10], 10673.58);
}
