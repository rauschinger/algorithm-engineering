#include <iostream>
#include <omp.h>
#include <random>

using namespace std;

int main() {
  int seed = 0;
  default_random_engine re{seed};
  uniform_real_distribution<double> zero_to_one{0.0, 1.0};

  int n = 100000000; // amount of points to generate
  int counter = 0; // counter for points in the first quarter of a unit circle
  auto start_time = omp_get_wtime(); // omp_get_wtime() is an OpenMP library routine
  omp_set_num_threads(4); // setting the desired number of threads in the parallel region

  #pragma omp parallel // parallel region starts here
  { // idea for parallelisation: split up loop iterations between threads
    int num_threads = omp_get_num_threads(); // used as increment in for loop
    int thread_id = omp_get_thread_num();
    //double sum_local = 0.0; // for summing up heights locally


  // compute n points and test if they lie within the first quadrant of a unit circle
  for (int i = thread_id; i < n; i += num_threads) {
    auto x = zero_to_one(re); // generate random number between 0.0 and 1.0
    auto y = zero_to_one(re); // generate random number between 0.0 and 1.0
    if (x * x + y * y <= 1.0) { // if the point lies in the first quadrant of a unit circle
      ++counter;
    }
  }

  auto run_time = omp_get_wtime() - start_time;
  auto pi = 4 * (double(counter) / n);

  cout << "pi: " << pi << endl;
  cout << "run_time: " << run_time << " s" << endl;
  cout << "n: " << n << endl; }
}
