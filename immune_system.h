#ifndef __IMMUNE_SYSTEM_H_INCLUDED__
#define __IMMUNE_SYSTEM_H_INCLUDED__
#include <bits/stdc++.h>

using namespace std;

// Constants
constexpr int DEFAULT_NUMBER_OF_LYMPHOCYTES = (1 << 8);
constexpr int DEFAULT_NUMBER_OF_ITERATIONS = 10000;

double rand_in_range(double l, double r);

struct lymphocyte {
  double a; // first coef
  double b; // second coef

  double fitness_function; // store this value, because calculating takes long time O(number of existing points)

  lymphocyte();

  lymphocyte(double a, double b);

  void set_range_a(double mi, double ma);

  void set_range_b(double mi, double ma);

  void set_mutate_range(double val);

  lymphocyte mutate_a() const;

  lymphocyte mutate_b() const;

  void calc_fitness_function(const function<double (double, double, double)>& func, const vector<pair<double, double>>& points);

  private:
  inline static double MIN_A = -100;
  inline static double MIN_B = -100;
  inline static double MAX_A = 100;
  inline static double MAX_B = 100;
  inline static double MUTATE_RANGE = 5;

  double diff() const;
};

ostream& operator<<(ostream& out, const lymphocyte& l);

struct artificial_immune_system {
  artificial_immune_system() = delete;

  artificial_immune_system(
    const function<double (double, double, double)>& func, 
    const vector<pair<double, double>>& points, 
    int number_of_lymphocytes = DEFAULT_NUMBER_OF_LYMPHOCYTES,
    int number_of_iterations = DEFAULT_NUMBER_OF_ITERATIONS) :
      func(func),
      points(points), 
      number_of_lymphocytes(number_of_lymphocytes),
      number_of_iterations(number_of_iterations) {};

  lymphocyte solve();

  private:
  function<double (double, double, double)> func;
  vector<pair<double, double>> points;
  int number_of_lymphocytes;
  int number_of_iterations;
};

#endif