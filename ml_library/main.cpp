#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cmath>
#include <limits>

struct LinearRegression {
    double slope = 0, intercept = 0;
    void fit(const std::vector<double>& x, const std::vector<double>& y) {
        double n = x.size(), sx = 0, sy = 0, sxy = 0, sx2 = 0;
        for (size_t i = 0; i < n; ++i) {
            sx += x[i]; sy += y[i];
            sxy += x[i]*y[i]; sx2 += x[i]*x[i];
        }
        slope = (n*sxy - sx*sy)/(n*sx2 - sx*sx);
        intercept = (sy - slope*sx)/n;
    }
    double predict(double xval) { return slope*xval + intercept; }
};

struct KMeans {
    std::vector<double> centers;
    std::vector<int> labels;
    void fit(const std::vector<double>& data, int k, int iters = 100) {
        centers.assign(data.begin(), data.begin()+k);
        labels.assign(data.size(), 0);
        for (int iter = 0; iter < iters; ++iter) {
            for (size_t i = 0; i < data.size(); ++i) {
                double best = std::numeric_limits<double>::max();
                for (int j = 0; j < k; ++j) {
                    double dist = std::abs(data[i]-centers[j]);
                    if (dist < best) { best = dist; labels[i] = j; }
                }
            }
            std::vector<double> sums(k,0); std::vector<int> counts(k,0);
            for (size_t i = 0; i < data.size(); ++i) {
                sums[labels[i]] += data[i];
                counts[labels[i]]++;
            }
            for (int j = 0; j < k; ++j)
                if (counts[j]) centers[j] = sums[j]/counts[j];
        }
    }
};

int main() {
    std::cout << "1. Linear Regression\n2. K-means\nChoose: ";
    int op; std::cin >> op;
    if (op == 1) {
        std::ifstream in("data.csv");
        std::vector<double> x, y;
        std::string line;
        while (std::getline(in, line)) {
            std::istringstream iss(line);
            double a,b; char comma;
            if (iss >> a >> comma >> b) { x.push_back(a); y.push_back(b); }
        }
        LinearRegression lr;
        lr.fit(x, y);
        std::cout << "Model: y = " << lr.slope << " * x + " << lr.intercept << std::endl;
        std::cout << "Test x: ";
        double tx; std::cin >> tx;
        std::cout << "Predicted y: " << lr.predict(tx) << std::endl;
    } else {
        std::ifstream in("cluster.csv");
        std::vector<double> data;
        double v;
        while (in >> v) data.push_back(v);
        int k; std::cout << "k? "; std::cin >> k;
        KMeans km; km.fit(data, k);
        for (int i = 0; i < k; ++i)
            std::cout << "Cluster " << i << " center: " << km.centers[i] << std::endl;
    }
}