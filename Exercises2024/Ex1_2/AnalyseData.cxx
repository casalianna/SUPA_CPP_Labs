#include <iostream>
#include "CustomFunctions.h"

using namespace std;

int main() {

    //reading input data and errors
    vector<pair<double, double>> xy_data;
    read_store("input2D_float.txt", xy_data);
    vector<pair<double, double>> xy_errs;
    read_store("error2D_float.txt", xy_errs);

    string option;
    int nlines = 0;

    do {
        //menu options
        cout << "Select an operation:" << endl;
        cout << "1. Print data (x,y)" << endl;
        cout << "2. Calculate magnitudes" << endl;
        cout << "3. Fit straight line to data and compute reduced chi2" << endl;
        cout << "4. Exponentiate data (x^y)" << endl;
        cout << "5. Exit" << endl;

        cout << "\nChoose an option and enter the corresponding number: ";
        cin >> option;

        switch (stoi(option)) {
            case 1: {
                //print data
                cout << "How many lines would you like to print (max 25) ";
                cin >> nlines;
                print(xy_data, nlines);
                break;
            }
            case 2: {
                //calculate and print magnitudes
                vector<double> magnitudes = getMagnitudes(xy_data);
                cout << "How many magnitudes would you like to print (max 25)? ";
                cin >> nlines;
                print(magnitudes, nlines);
                saveToFile(magnitudes, "magnitudes.txt");
                break;
            }
            case 3: {
                //perform line fitting and print results
                LineFitResult result = LineFit(xy_data, xy_errs);
                print(result.params, result.red_chi2);
                saveToFile(result.params, result.red_chi2, "linefit.txt");
                break;
            }
            case 4: {
                //exponentiate data and print results
                vector<double> results = exponentiate(xy_data);
                cout << "How many exponentiation results would you like to print (max 25)? ";
                cin >> nlines;
                print(results, nlines);
                saveToFile(results, "exponentiation.txt");
                break;
            }
            case 5: {
                //exit
                cout << "Goodbye." << endl;
                return 0;
            }
            default:
                cout << "Invalid choice. Please enter a number between 1 and 5." << endl;
                break;
        }

        //ask the user if they want to perform another operation
        cout << "\nWould you like to perform another operation? (y/n): ";
        char answer;
        cin >> answer;

        //exit the loop 
        if (answer != 'y') {
            cout << "Goodbye." << endl;
            break;
        }

    } while (true); 

    return 0;
}
