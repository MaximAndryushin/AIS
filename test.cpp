#include "immune_system.h"

using namespace std;

double exponential_regression(double a, double b, double x) {
  return a * exp(b * x);
}

double goal_exponential_regression(double x) {
  return 1.2 * exp(-3.1 * x);
}

double hyperbolic_regression(double a, double b, double x) {
  return a + b / x;
}

double goal_hyperbolic_regression(double x) {
  return 9.45 + -10.7 / x;
}

double square_regression(double a, double b, double x) {
  return a + b * sqrt(x);
}

double goal_square_regression(double x) {
  return -12.12 + 6.66 * sqrt(x);
}

double power_regression(double a, double b, double x) {
  return a * pow(x, b);
}

double goal_power_regression(double x) {
  return -0.7 * pow(x, 2.4);
}

double semilogarithmic_regression(double a, double b, double x) {
  return a + b * log(x);
}

double goal_semilogarithmic_regression(double x) {
  return 1.448 + -3.22 * log(x);
}

int main() {
  for (const auto& [goal_func, func, name] : vector<tuple<function<double(double)>, function<double(double, double, double)>, string>>{
    //{goal_hyperbolic_regression, hyperbolic_regression, "hyperbolic_regression"},
    //{goal_square_regression, square_regression, "square_regression"},
    {goal_power_regression, power_regression, "power_regression"},
    {goal_exponential_regression, exponential_regression, "exponential_regression"},
    //{goal_semilogarithmic_regression, semilogarithmic_regression, "semilogarithmic_regression"}
  }) {

    vector<pair<double, double>> points(100);

    for (auto& [x, y]: points) {
      x = rand_in_range(0, 100);
      y = goal_func(x);
    }
    
    artificial_immune_system AIS(func, points);

    auto res = AIS.solve();

    cout << name << ':' << endl << res << endl << endl << endl;
  }
}