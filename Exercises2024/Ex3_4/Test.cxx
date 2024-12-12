#include "FiniteFunctions.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

std::vector<double> read_store(const std::string &filename) {
    //Function to read and store data from the file
    std::vector<double> data;
    std::ifstream file(filename);

    if (file.fail()) {
        std::cerr << "Couldn't open file" << std::endl;
        exit(1);
    }

    double value;
    while (file >> value) {
        data.push_back(value);
    }
    file.close();

    return data;
}

void process_functions(FiniteFunction &func, std::vector<double> &data, int n_sampled, int nbins) {
    //Function to process each distribution
    func.integral(10000);
    func.plotFunction();
    std::vector<double> sampled_data = func.sampling(n_sampled, 0.5);
    func.plotData(sampled_data, nbins, false);
    func.plotData(data, nbins, "Mystery Data");
}

int main() {
    std::string dataFile = "Outputs/data/MysteryData13000.txt";
    std::vector<double> mysteryData = read_store(dataFile);

    if (mysteryData.empty()) {
        std::cerr << "Error: No data read from file " << dataFile << std::endl;
        return 1;
    }

    do {
        std::cout << "Choose the distribution to plot:" << std::endl;
        std::cout << "0: Default Function" << std::endl;
        std::cout << "1: Normal Distribution" << std::endl;
        std::cout << "2: Cauchy-Lorentz Distribution" << std::endl;
        std::cout << "3: Negative Crystal Ball Function" << std::endl;

        std::cout << "\nEnter the number corresponding to your choice (0, 1, 2, or 3): ";

        int choice;
        std::cin >> choice;

        int nbins = 100;          
        unsigned int n_sampled = 70000; 

        switch (choice) {
            case 0: {
                FiniteFunction func(-5.0, 5.0, "default");
                process_functions(func, mysteryData, n_sampled, nbins);
                break;
            }
            case 1: {
                NormalDistribution norm(0, 0.5, -5, 5, "normal");
                process_functions(norm, mysteryData, n_sampled, nbins);
                break;
            }
            case 2: {
                CauchyLorentz cauchy(0, 0.5, -5, 5, "cauchy");
                process_functions(cauchy, mysteryData, n_sampled, nbins);
                break;
            }
            case 3: {
                NegCrystalBall crystal(0, -1, 2, 2, -5, 5, "negcrystal");
                process_functions(crystal, mysteryData, n_sampled, nbins);
                break;
            }
            default:
                std::cerr << "Error: invalid choice." << std::endl;
                return 1;
        }

        //ask the user if they want to perform another operation
        std::cout << "\nWould you like to perform another operation? (y/n): ";
        char answer;
        std::cin >> answer;
        
        //exit the loop 
        if (answer != 'y') {
            std::cout << "Goodbye." << std::endl;
            break;
        }
    } while (true); 

    return 0;
}