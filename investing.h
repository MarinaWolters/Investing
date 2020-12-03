#pragma once

#include <iostream>
#include "vector.h"
#include "set.h"
#include "map.h"
#include "math.h"
#include "error.h"
#include "filelib.h"
#include <string>
#include "strlib.h"
#include "testing/SimpleTest.h"



void conclusion(std::string dbfile, std::string dbByMonth);
double weeklyInvesting(std::string dbfile);
double investingOnce(std::string dbByMonth);

void buildPriceMap(std::string dbByMonth, Map<double, double> &priceMap);

Vector<std::string> readFile(std::string dbfile);


// The alternative implementation of buildMap function
//Map<double, Vector<double>> buildMap(std::string dbByMonth);


