//*************************************************************************
// Code: Generator of Prime Numbers with Multithreading
// Author: Shambhavi K.
// Date: 08.01.2021 (Last updated: 09.01.2021)
//*************************************************************************

#include <iostream>
#include <cstdlib>
#include <numeric>
#include <math.h>
#include <sstream>
#include <vector>
#include <chrono>
#include <thread>
#include <mutex>

using namespace std;
using namespace std::chrono;

bool isPrime(unsigned int i)
{
  for (unsigned int j = 2; j <= sqrt(i); j++)
  {
    bool isIMultipleOfJ = (i % j) == 0;
    if (isIMultipleOfJ)
    {
      return false;
    }
  }
  return true;
}

//*************************************************************************
// Function: calculatePrimeNumbers()
// Description: calculation of prime numbers using Trial Division method
//*************************************************************************

void calculatePrimeNumbers(vector<unsigned int> &vectPrime, unsigned int firstNumber, unsigned int lastNumber)
{
  for (unsigned int i = firstNumber; i <= lastNumber; i += 2)
  {
    if (isPrime(i))
    {
      vectPrime.push_back(i);
    }
  }
}

//*************************************************************************
// Function: primeNumbersWithThreads()
// Description: implementing a callable using function pointer to calculate
//              prime numbers upto N.
//*************************************************************************

std::vector<unsigned int> primeNumbersWithThreads(unsigned int firstNumber,
                                                  unsigned int lastNumber, unsigned int totalThreads)
{
  unsigned int threadSpread = lastNumber / totalThreads;
  unsigned int newLastNumber = firstNumber + threadSpread - 1;

  //create different thread object
  vector<unsigned int> vectPrime1;
  thread thread1(calculatePrimeNumbers, std::ref(vectPrime1), firstNumber, newLastNumber); //thread object
  firstNumber = firstNumber + threadSpread;
  newLastNumber = newLastNumber + threadSpread;

  vector<unsigned int> vectPrime2;
  thread thread2(calculatePrimeNumbers, std::ref(vectPrime2), firstNumber, newLastNumber); //thread object
  firstNumber = firstNumber + threadSpread;
  newLastNumber = newLastNumber + threadSpread;

  vector<unsigned int> vectPrime3;
  thread thread3(calculatePrimeNumbers, std::ref(vectPrime3), firstNumber, newLastNumber); //thread object

  thread1.join();
  thread2.join();
  thread3.join();

  vectPrime1.insert(vectPrime1.end(), vectPrime2.cbegin(), vectPrime2.cend());
  vectPrime1.insert(vectPrime1.end(), vectPrime3.cbegin(), vectPrime3.cend());

  return vectPrime1;
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
    cout << "Incorrect entry. Please enter a positive integer = ";
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
  cout << "Enter a positive integer =";
  // int: -1 = 0xffff
  // unsigned int: 0xffff = 2^32 - 1
  unsigned int N = validInput();
  cout << "N=" << N << endl;

  if (N == 1)
    cout << "1 is neither prime nor composite";

  //vector<unsigned int> vectPrime(N,1);

  auto start = steady_clock::now();
  // vectPrime.reserve(N);
  std::vector<unsigned int> vectPrime = primeNumbersWithThreads(1, N, 3);
  auto stop = steady_clock::now();

  // cout << "2 "; //hardcoded value of 2

  // for (auto i : vectPrime)
  // {
  //   cout << i << " ";
  // }

  auto duration = duration_cast<microseconds>(stop - start);
  cout << "\nTotal Time taken = " << duration.count()
       << " microseconds" << endl;
}
