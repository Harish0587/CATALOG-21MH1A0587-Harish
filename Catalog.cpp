#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <cmath>
#include "json.hpp"

using json = nlohmann::json;
using namespace std;

// Function to convert a number from any base to decimal
long long convertToDecimal(const string& value, int base) {
    long long result = 0;
    for (char c : value) {
        result *= base;
        if (isdigit(c)) {
            result += c - '0';
        } else {
            result += c - 'a' + 10;
        }
    }
    return result;
}

// Function to perform Lagrange interpolation
long long lagrangeInterpolation(const vector<pair<int, long long>>& points) {
    int k = points.size();
    long long constant = 0;
    
    for (int i = 0; i < k; i++) {
        long long term = points[i].second; // Start with y_i
        long long denominator = 1;

        for (int j = 0; j < k; j++) {
            if (i != j) {
                term *= -points[j].first;
                denominator *= (points[i].first - points[j].first);
            }
        }
        constant += term / denominator;
    }
    return constant;
}

// Function to read and parse JSON input
vector<pair<int, long long>> parseJSON(const string& filename, int& k) {
    ifstream file(filename);
    json root;
    file >> root;

    vector<pair<int, long long>> points;
    k = root["keys"]["k"].get<int>();

    for (const auto& item : root.items()) {
        if (item.key() != "keys") {
            int x = stoi(item.key());
            int base = item.value()["base"].get<int>();
            string value = item.value()["value"].get<string>();
            long long y = convertToDecimal(value, base);
            points.emplace_back(x, y);
        }
    }
    return points;
}

int main() {
    int k1, k2;
    vector<pair<int, long long>> points1 = parseJSON("testcase1.json", k1);
    vector<pair<int, long long>> points2 = parseJSON("testcase2.json", k2);

    long long secret1 = lagrangeInterpolation(points1);
    long long secret2 = lagrangeInterpolation(points2);

    cout << "Secret 1: " << secret1 << endl;
    cout << "Secret 2: " << secret2 << endl;
    return 0;
}

