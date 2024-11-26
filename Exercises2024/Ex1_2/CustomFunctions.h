#ifndef CUSTOM_FUNCTIONS_H
#define CUSTOM_FUNCTIONS_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>

using namespace std;

void read_store(const string& filename, vector<pair<double, double>>& xy_data);


void print(const vector<pair<double, double>>& xy_data, int n); 
void print(const vector<double>& data, int n); 
void print(const pair<double, double>& params, double red_chi2); 

vector<double> getMagnitudes(const vector<pair<double, double>>& xy_data);

struct LineFitResult {
    pair<double, double> params; // p, q
    double red_chi2;             // reduced chi2
};

LineFitResult LineFit(const vector<pair<double, double>>& xy_data, const vector<pair<double, double>>& xy_errs);

vector<double> exponentiate(const vector<pair<double, double>>& xy_data);

void saveToFile(const vector<double>& data, const string& filename);
void saveToFile(const pair<double, double>& params, double red_chi2, const string& filename);


#endif
