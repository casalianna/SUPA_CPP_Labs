#include "CustomFunctions.h"

using namespace std;

void read_store(const string& filename, vector<pair<double, double>>& xy_data) {
    //function to read file and store data (x,y) into a vector<pair<double, double>>
    ifstream file(filename);

    if (file.fail()) {
        cout << "Couldn't open file" << endl;
        exit(1);
    }

    string line;
    getline(file, line); //read header columns (x, y)

    while (getline(file, line)) {
        stringstream s(line);
        double x, y;
        s >> x;
        s.ignore(); //comma ignored
        s >> y;
        xy_data.push_back(make_pair(x, y)); //fill xy_data with x, y pairs
    }

    file.close();
}

void print(const vector<pair<double, double>>& xy_data, int n) {
    if (n > xy_data.size()) {
        cout << "Warning: Only " << xy_data.size() << " lines available. Printing the first 5 lines instead." << endl;
        n = min(n, 5);
    }

    for (int i = 0; i < n; ++i) {
        cout << "x: " << xy_data[i].first << ", y: " << xy_data[i].second << endl;
    }
}

void print(const vector<double>& data, int n) {
    if (n > data.size()) {
        cout << "Warning: Only " << data.size() << " values available. Printing the first 5 values instead." << endl;
        n = min(n, 5);
    }

    for (int i = 0; i < n; ++i) {
        cout << "Value: " << data[i] << endl;
    }
}

void print(const pair<double, double>& params, double red_chi2) {
    cout << "Line fit parameters:" << endl;
    cout << "p (slope): " << params.first << endl;
    cout << "q (intercept): " << params.second << endl;
    cout << "Reduced chi-squared: " << red_chi2 << endl;
}


vector<double> getMagnitudes(const vector<pair<double, double>>& xy_data) {
    //function to calculate magnitudes
    vector<double> magnitudes;
    for (int i = 0; i < xy_data.size(); ++i) {
        double x = xy_data[i].first;
        double y = xy_data[i].second;
        double magnitude = sqrt(pow(x, 2) + pow(y, 2));
        magnitudes.push_back(magnitude);
    }
    return magnitudes;
}

LineFitResult LineFit(const vector<pair<double, double>>& xy_data, const vector<pair<double, double>>& xy_errs) {
    //function to calculate line fit params and reduced chi-squared
    int N = xy_data.size();

    double sum_x = 0, sum_y = 0, sum_xx = 0, sum_xy = 0; //required sums

    for (int i = 0; i < N; ++i) {
        double x = xy_data[i].first;
        double y = xy_data[i].second;

        sum_x += x;
        sum_y += y;
        sum_xx += pow(x, 2);
        sum_xy += x*y;
    }

    double den = (N*sum_xx - sum_x*sum_x);
    double p = (N*sum_xy - sum_x*sum_y)/den;
    double q = (sum_xx*sum_y - sum_x*sum_xy)/den;

    //calculate chi-squared
    double chi2 = 0;
    for (int i = 0; i < N; ++i) {
        double x = xy_data[i].first;
        double y_obs = xy_data[i].second;   
        double y_exp = p*x + q;           
        double sigma = xy_errs[i].second;  
        chi2 += pow((y_obs - y_exp)/sigma, 2);
    }

    int NDF = N - 2; 
    double red_chi2 = chi2/NDF; //reduced chi-squared

    return {make_pair(p, q), red_chi2};
}

vector<double> exponentiate(const vector<pair<double, double>>& xy_data) {
    if (xy_data.empty()) {
        return {};
    }

    double base = xy_data[0].first;
    int exp = round(xy_data[0].second);
    double result = (exp == 0) ? 1 : base*exponentiate({{base, exp - 1}})[0]; //first pair

    vector<double> results = exponentiate({xy_data.begin() + 1, xy_data.end()}); //rest of data recursively
    results.insert(results.begin(), result);

    return results;
}

void saveToFile(const vector<double>& data, const string& filename) {
    ofstream file(filename);
    if (!file) {
        cerr << "Error opening file: " << filename << endl;
        return;
    }
    for (double val : data) {
        file << val << endl;
    }
    file.close();
}

void saveToFile(const pair<double, double>& params, double red_chi2, const string& filename) {
    ofstream file(filename);
    if (!file) {
        cerr << "Error opening file: " << filename << endl;
        return;
    }
    file << "p: " << params.first << ", q: " << params.second << endl;
    file << "Reduced chi-squared: " << red_chi2 << endl;
    file.close();
}