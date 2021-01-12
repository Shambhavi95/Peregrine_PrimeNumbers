//*************************************************************************
// Code: Generator of Prime Numbers using algorithm "Seive of Eratosthenes"
// Author: Shambhavi K.
// Date: 03.01.2021 (Last updated: 10.01.2021)
//*************************************************************************

#include <iostream>
#include <math.h>
#include <vector>
#include <chrono>
#include <omp.h>

using namespace std;
using namespace std::chrono;

//*************************************************************************
// Function: findPrimeNumbers()
// Description: Takes the value 'N' entered by the user and generates
//              & displays prime numbers upto Nth value.
//*************************************************************************

vector<bool> findPrimeNumbers(int N)
{
  vector<bool> vectorPrimes(N, false);
  vectorPrimes[0] = 0;
  vectorPrimes[1] = 0;
  for (int i = 2; i <= sqrt(N); ++i)
  {
    for (int j = i; (i * j) < N; ++j)
    {
      vectorPrimes[i * j] = true;
    }
  }

  // for (int k = 0; k < vectorPrimes.size(); k++)
  // {
  //   if (vectorPrimes[k])
  //     cout << k << " ";
  // }
  return vectorPrimes;
}

//*************************************************************************
// Function: validInput()
// Description: Checks validity of the user-entered input. If anything
//              apart from numeric is entered, the function ignores the
//              data and prompts the user to enter postive integer value.
//*************************************************************************

int validInput()
{
  int input;
  cin >> input;
  while (cin.fail())
  {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Incorrect entry. Please enter a positive integer: ";
    cin >> input;
  }
  return input;
}

//*************************************************************************
// Function: main()
// Description: Accepts data from the user and processes generation of
//              prime numbers. Addition of benchmark conditions (clocks) to
//              observe timing behaviour of algorithm (in microseconds).
//*************************************************************************

int main()
{
  unsigned int N = 0;

  cout << "Enter a positive integer =";
  N = validInput();

  //precaution
  if (N == 1)
    cout << "1 is neither prime nor composite";
  if (N <= 0)
    cout << "Please enter a positive integer";

  // vector<int> vectorPrimes(N, 1);
  // vectorPrimes[0] = 0;
  // vectorPrimes[1] = 0;

  auto start = steady_clock::now();
  vector<bool> vectorPrimes = findPrimeNumbers(N);
  auto stop = steady_clock::now();

  auto duration = duration_cast<microseconds>(stop - start);
  cout << "\nTime taken by function: " << duration.count() << " microseconds" << endl;

  // cout << "\n";
  // for (int k = 0; k < vectorPrimes.size(); k++)
  // {
  //   if (vectorPrimes[k])
  //     cout << k << " ";
  // }
  // cout << "\n";
}
