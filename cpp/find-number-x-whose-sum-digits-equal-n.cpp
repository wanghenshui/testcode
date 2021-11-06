// CPP program to find x such that 
// X + sumOfDigits(X) = N 
#include <cmath> 
#include <cstdlib> 
#include <iostream> 
#include <vector> 
using namespace std; 

// Computing the sum of digits of x 
int sumOfDigits(long int x) 
{ 
	int sum = 0; 
	while (x > 0) { 
		sum += x % 10; 
		x /= 10; 
	} 
	return sum; 
} 

// Checks for 100 numbers on both left 
// and right side of the given number to 
// find such numbers X such that X + 
// sumOfDigits(X) = N and updates the answer 
// vector accordingly 
void compute(vector<long int>& answer, long int n) 
{ 
	// Checking for all possibilities of 
	// the answer 
	for (int i = 0; i <= 100; i++) { 

		// Evaluating the value on the left 
		// side of the given number 
		long int valueOnLeft = abs(n - i) + 
					sumOfDigits(abs(n - i)); 

		// Evaluating the value on the right 
		// side of the given number 
		long int valueOnRight = n + i + sumOfDigits(n + i); 

		// Checking the condition of equality 
		// on both sides of the given number N 
		// and updating the answer vector 
		if (valueOnLeft == n) 
			answer.push_back(abs(n - i)); 
		if (valueOnRight == n) 
			answer.push_back(n + i); 
	} 
} 

// Driver Function 
int main() 
{	 
	long int N = 100000001; 
	cin>>N;
	vector<long int> answer; 
	compute(answer, N); 

	// If no solution exists, print -1 
	if (answer.size() == 0) 
		cout << -1; 
	else { 

		// If one or more solutions are possible, 
		// printing them! 
		for (vector<long int>::iterator it = answer.begin(); it != answer.end(); ++it) 
			cout <<  (*it) << endl; 
	} 
	return 0; 
} 
