#include <iostream>
#include <random>
#include <cmath>
#include <algorithm>

using namespace std;

struct Circle {
    double x, y, r;
    bool contains(double qx, double qy) const {
        double dx = x - qx, dy = y - qy;
        return dx * dx + dy * dy <= r * r;
    }
};

int main() {
    Circle c1, c2, c3;
    cin >> c1.x >> c1.y >> c1.r;
    cin >> c2.x >> c2.y >> c2.r;
    cin >> c3.x >> c3.y >> c3.r;

    double minX = std::min(c1.x - c1.r, std::min(c2.x - c2.r, c3.x - c3.r));
    double maxX = std::max(c1.x + c1.r, std::max(c2.x + c2.r, c3.x + c3.r));
    double minY = std::min(c1.y - c1.r, std::min(c2.y - c2.r, c3.y - c3.r));
    double maxY = std::max(c1.y + c1.r, std::max(c2.y + c2.r, c3.y + c3.r));

    const int N = 1000000;
    int count = 0;
    mt19937 gen(random_device{}());
    uniform_real_distribution<> disX(minX, maxX);
    uniform_real_distribution<> disY(minY, maxY);

    double boxArea = (maxX - minX) * (maxY - minY);

    for (int i = 0; i < N; ++i) {
        double x = disX(gen);
        double y = disY(gen);
        if (c1.contains(x, y) && c2.contains(x, y) && c3.contains(x, y))
            ++count;
    }

    double area = (double(count) / N) * boxArea;

    cout.precision(10);
    cout << fixed << area << endl;

    return 0;
}
