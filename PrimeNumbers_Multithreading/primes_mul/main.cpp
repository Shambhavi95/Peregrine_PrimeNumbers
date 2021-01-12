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

vector<unsigned int> vectPrime;		//global vector
mutex mutexLock;

//*************************************************************************
// Function: calculatePrimeNumbers()
// Description: calculation of prime numbers using Trial Division method
//*************************************************************************

void calculatePrimeNumbers(unsigned int firstNumber, unsigned int lastNumber) {
	for(unsigned int i=firstNumber; i<=lastNumber; i+=2) {
				for(unsigned int j=2; j<i; j++) {
					if((i%j) == 0) { break; }
					else if((j+1)==i) {
						mutexLock.lock();
						vectPrime.push_back(i);
						mutexLock.unlock();
					}
				}
			}
} 

//*************************************************************************
// Function: primeNumbersWithThreads()
// Description: implementing a callable using function pointer to calculate
//              prime numbers upto N.
//*************************************************************************

void primeNumbersWithThreads(unsigned int firstNumber, 
						unsigned int lastNumber, unsigned int totalThreads) 
{
	unsigned int threadSpread = lastNumber / totalThreads;
	unsigned int newLastNumber = firstNumber + threadSpread - 1;
	
			//create different thread object 
			thread thread1(calculatePrimeNumbers, firstNumber, newLastNumber); //thread object
			firstNumber = firstNumber + threadSpread;
			newLastNumber = newLastNumber + threadSpread;
			
			thread thread2(calculatePrimeNumbers, firstNumber, newLastNumber); //thread object
			firstNumber = firstNumber + threadSpread;
			newLastNumber = newLastNumber + threadSpread;
			
			thread thread3(calculatePrimeNumbers, firstNumber, newLastNumber); //thread object
	
	thread1.join();
	thread2.join();
	thread3.join();
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
    while(cin.fail())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
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

int main() {
	unsigned int N = 0;
	
	cout << "Enter a positive integer =";
	N = validInput();
	
	if(N==1) cout << "1 is neither prime nor composite"; 
	
	//vector<unsigned int> vectPrime(N,1);
	
	auto start = high_resolution_clock::now();
		primeNumbersWithThreads(1, N, 3);
	auto stop = high_resolution_clock::now();

	cout << "2 ";	//hardcoded value of 2
	
	for(auto i: vectPrime) {
		cout << i << " ";
	  }
	
	auto duration = duration_cast<microseconds>(stop - start);
	cout << "\nTotal Time taken = " << duration.count() 
					<< " microseconds" << endl;
}