#include <iostream>
#include <array>
#include <random>
#include <cmath>
#include <iomanip>

struct Circle {
    double x;
    double y;
    double r;
};

struct Box {
    double xmin;
    double xmax;
    double ymin;
    double ymax;

    double area() const {
        return (xmax - xmin) * (ymax - ymin);
    }
};

bool inside_all(double px, double py, const std::array<Circle, 3> &circles) {
    for (const auto &c : circles) {
        double dx = px - c.x;
        double dy = py - c.y;
        if (dx * dx + dy * dy > c.r * c.r) {
            return false;
        }
    }
    return true;
}

double monte_carlo_estimate(const std::array<Circle, 3> &circles,
                            const Box &box,
                            int N,
                            std::mt19937_64 &rng) {
    std::uniform_real_distribution<double> dist_x(box.xmin, box.xmax);
    std::uniform_real_distribution<double> dist_y(box.ymin, box.ymax);

    int hits = 0;
    for (int i = 0; i < N; ++i) {
        double x = dist_x(rng);
        double y = dist_y(rng);
        if (inside_all(x, y, circles)) {
            ++hits;
        }
    }

    double fraction = static_cast<double>(hits) / static_cast<double>(N);
    return fraction * box.area();
}

int main() {
    std::array<Circle, 3> circles = {
        Circle{1.0, 1.0, 1.0},
        Circle{1.5, 2.0, std::sqrt(5.0) / 2.0},
        Circle{2.0, 1.5, std::sqrt(5.0) / 2.0}
    };

    const double TRUE_AREA = 0.25 * M_PI + 1.25 * std::asin(0.8) - 1.0;

    Box wide_box{0.0, 3.0, 0.0, 3.0};

    double xmin = circles[0].x - circles[0].r;
    double xmax = circles[0].x + circles[0].r;
    double ymin = circles[0].y - circles[0].r;
    double ymax = circles[0].y + circles[0].r;
    for (int i = 1; i < 3; ++i) {
        xmin = std::min(xmin, circles[i].x - circles[i].r);
        xmax = std::max(xmax, circles[i].x + circles[i].r);
        ymin = std::min(ymin, circles[i].y - circles[i].r);
        ymax = std::max(ymax, circles[i].y + circles[i].r);
    }
    Box tight_box{xmin, xmax, ymin, ymax};

    std::random_device rd;
    std::mt19937_64 rng(rd());

    std::cout << std::fixed << std::setprecision(8);
    std::cout << "# N "
              << "wide_area wide_rel_err "
              << "tight_area tight_rel_err\n";

    for (int N = 100; N <= 100000; N += 500) {
        double est_wide  = monte_carlo_estimate(circles, wide_box,  N, rng);
        double est_tight = monte_carlo_estimate(circles, tight_box, N, rng);

        double rel_err_wide  = std::fabs(est_wide  - TRUE_AREA) / TRUE_AREA;
        double rel_err_tight = std::fabs(est_tight - TRUE_AREA) / TRUE_AREA;

        std::cout << N << ' '
                  << est_wide  << ' ' << rel_err_wide  << ' '
                  << est_tight << ' ' << rel_err_tight << '\n';
    }

    return 0;
}