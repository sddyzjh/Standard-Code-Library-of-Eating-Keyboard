#include <random>
#include <chrono>
using namespace std::chrono;

int rd(int l, int r)
{
    static default_random_engine gen(high_resolution_clock::now().time_since_epoch().count());
    return uniform_int_distribution<int>(l, r)(gen);
}

double rd(double l, double r)
{
    static default_random_engine gen(high_resolution_clock::now().time_since_epoch().count());
    return uniform_real_distribution<double>(l, r)(gen);
}
