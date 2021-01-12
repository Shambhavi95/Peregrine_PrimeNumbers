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
	std::vector<std::thread> threadVect;
	
	unsigned int threadSpread = lastNumber / totalThreads;
	unsigned int newLastNumber = firstNumber + threadSpread - 1;
	
	for(unsigned int i = 0; i<totalThreads; i++) {	
			//launch thread using function pointer as callable
			thread threadVect(calculatePrimeNumbers, firstNumber, newLastNumber);
		
			firstNumber = firstNumber + threadSpread;
			newLastNumber = newLastNumber + threadSpread;
		}
	
	//Wait for other threads to finish
	for(auto& thread : threadVect) {
			thread.join();
		}
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
	
	vector<unsigned int> vectPrime(N,1);
	
	auto start = high_resolution_clock::now();
		primeNumbersWithThreads(1, N, 3);
	auto stop = high_resolution_clock::now();
	
	for(int k=0; k<vectPrime.size(); k++) {
		if(vectPrime[k] == 1)	cout << k << " ";
	}
	
	auto duration = duration_cast<microseconds>(stop - start);
	cout << "\nTotal Time taken = " << duration.count() 
					<< " microseconds" << endl;
}