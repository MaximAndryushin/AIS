#include "immune_system.h"
using namespace std;

// Object for generating random numbers
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

double rand_in_range(double l, double r) {
  return l + (double)rng() / (UINT32_MAX / (r - l));
}

// Lymphocyte methods

// Random initialization
lymphocyte::lymphocyte() {
  a = rand_in_range(MIN_A, MAX_A);
  b = rand_in_range(MIN_B, MAX_B);
}

lymphocyte::lymphocyte(double a, double b) : a(a), b(b) {};

void lymphocyte::set_range_a(double mi, double ma) {
  MIN_A = mi;
  MAX_A = ma;
}

void lymphocyte::set_range_b(double mi, double ma) {
  MIN_B = mi;
  MAX_B = ma;
}

void lymphocyte::set_mutate_range(double val) {
  MUTATE_RANGE = val;
}

lymphocyte lymphocyte::mutate_a() const {
  return lymphocyte(min(max(a + diff(), MIN_A), MAX_A), b);
}

lymphocyte lymphocyte::mutate_b() const {
  return lymphocyte(a, min(max(b + diff(), MIN_B), MAX_B));
}

double lymphocyte::diff() const {
  return rand_in_range(-MUTATE_RANGE, MUTATE_RANGE);
}

void lymphocyte::calc_fitness_function(const function<double (double, double, double)>& func, const vector<pair<double, double>>& points) {
  fitness_function = 0;
  for (const auto& [x, y]: points)
    fitness_function += (y - func(a, b, x)) * (y - func(a, b, x));
  fitness_function = sqrt(fitness_function);
}

ostream& operator<<(ostream& out, const lymphocyte& l) {
  cout << "Fitness function: " << l.fitness_function << endl;
  cout << "Coefficient a: " << l.a << endl;
  cout << "Coefficient b: " << l.b << endl;
}


// AIS methods
lymphocyte artificial_immune_system::solve() {

  // Random generation of initial set of lymphocytes
  vector<lymphocyte> lymphocytes(number_of_lymphocytes);

  for (auto& l: lymphocytes)
    l.calc_fitness_function(func, points);

  auto comp = [](const lymphocyte& a, const lymphocyte& b) {
    return a.fitness_function < b.fitness_function;
  };

  for (int i = 0; i < number_of_iterations; i++) {
    sort(lymphocytes.begin(), lymphocytes.end(), comp);

    // Best half generate mutated children
    for (int j = 0; j < number_of_lymphocytes / 2; j++) {
      lymphocytes[j + number_of_lymphocytes / 2] = rng() & 2 ? lymphocytes[j].mutate_a() : lymphocytes[j].mutate_b();
      lymphocytes[j + number_of_lymphocytes / 2].calc_fitness_function(func, points);
    }
  }

  return *min_element(lymphocytes.begin(), lymphocytes.end(), comp);
}

