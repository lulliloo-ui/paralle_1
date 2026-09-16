#include "clicker.hpp"

Clicker::Clicker():
  start_(std::chrono::steady_clock::now())
{}

double Clicker::millisec() const
{
  using std::chrono::steady_clock;
  using std::chrono::duration_cast;
  using std::chrono::milliseconds;
  auto t = steady_clock::now();
  return duration_cast< milliseconds >(t - start_).count();
}
