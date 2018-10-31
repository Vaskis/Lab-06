// Jeremiah Vaskis
// Oct. 29, 2018
// COSC 2030

// SortedDriver.cpp

// tom bailey   1445  25 mar 2014
// Construct sorted sequences and call functions that
//   process the sorted sequences.


#include "RandomUtilities.h"
#include "ContainerPrinting.h"
#include "winTimer.h"//CHANGE: this to unixTimer.h if on mac/linux
#include <list>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// post: a sorted vector of listSize random doubles from
//         the range minNum to maxNum has been returned.
vector<double>
getNums(size_t listSize, double minNum, double maxNum)
{
	vector<double> theList;
	for (size_t i = 0; i < listSize; ++i)
	{
		theList.push_back(randReal(minNum, maxNum));
	}

	sort(begin(theList), end(theList));

	return theList;
}


// post: a sorted list of numWords words of length
//         wordLength with characters chosen randomly from
//         alphabet has been returned.
list<string>
getWords(size_t numWords, size_t wordLength, string alphabet)
{
	list<string> theWords;
	for (size_t i = 0; i < numWords; ++i)
	{
		string word;
		for (size_t j = 0; j < wordLength; ++j)
		{
			word += alphabet.at(randInt(0, alphabet.size()));
		}
		theWords.push_back(word);
	}

	theWords.sort();

	return theWords;
}


// pre:  number is not empty;
//       number is sorted from smallest to largest
// post: The most isolated entry in number has been returned
double
mostIsolated(vector<double> & number)
{
	vector<double> Input = number;
	//sort(Input.begin(), Input.end());	// Already sorted, use this if not
	double diffBefore = -1;
	double diffAfter = -1;
	double isolation = -1;
	double value = -1;

	cout << "started" << endl;

	// When the array is empty
	if (Input.empty()) {
		cout << "Empty Executed" << endl;
	}

	// When the array's size is exactly 1
	else if (Input.size() == 1) {
		value = Input[0];
		cout << "Size is 1" << endl;
	}

	// When the array's size is > 2
	else if (Input.size() > 1) {
		
		for (int i = 0; (i < Input.size()); i++) {

			// First element (looking at only i=0 and i=1)
			if (i == 0) {
				diffBefore = abs(Input[i] - Input[i + 1]);
				value = Input[i];
			}

			// Middle Updates Check (looking at all i-1, i , i+1)
			if (i > 0 && (Input.size() > 2) && (i <= Input.size()-2)) {
				diffBefore = abs(Input[i - 1] - Input[i]);
				diffAfter = abs(Input[i] - Input[i + 1]);
				
				// Check if the current element is more isolated
				if (min(diffBefore, diffAfter) > isolation) {
					value = Input[i];
					isolation = min(diffBefore, diffAfter);
				}
			}

			// Final element check (looking at the final two elements)
			if (i == Input.size() - 1) {
				diffAfter = abs(Input[i - 1] - Input[i]);
				if (min(diffBefore, diffAfter) > isolation) {
					value = Input[i];
				}
			}
		}
	}

	return value;
}


// pre:  A and B are sorted.
// post: The number of strings in A that do not occur in B
//         has been returned.
int
unmatched(list<string> & A, list<string> & B)
{
	int TotalEqual = 0;
	int Asize = A.size();

	// Loop interation code came from http://www.cplusplus.com/reference/list/list/begin/

	for (list<string>::iterator itA =A.begin(), itB = B.begin(); itA != A.end() && itB != B.end(); ) {
		// Check if particular A NODE's value is < than particular B NODE's value
		if (*itA < *itB) {
				// Increment Total
			itA++;	// Go to next NODE in A list
		}
		else if (*itA == *itB) {
			TotalEqual++;
			itA++;	// Go to next NODE in A list
					
		}
		else if (*itA > *itB){
			itB++;	// Go to next NODE in B list
		}
		else {
			cout << "Else case executed" << endl;
		}
	}

	// Asize - TotalEqual = # of NOT-EQUAL strings
	return Asize-TotalEqual;
}


int
main()
{
	cout << "Find the most isolated number" << endl
		<< "-----------------------------" << endl << endl;
	while (true)
	{
		cout << "Enter size for numbers: ";
		int n = 0;
		cin >> n;
		if (n <= 0)
			break;
		cout << "Enter seed for rand: ";
		unsigned int seed;
		cin >> seed;
		srand(seed);

		// Construct a sorted list of numbers
		Timer get;
		get.start();
		vector<double> numbers = getNums(n, -n, n);
		get.stop();
		cout << "Constructed in " << get() << " seconds"
			<< endl;

		if (n < 10)
			cout << numbers << endl << endl;

		// Report a most isolated isolated number
		Timer time;
		time.start();
		double isolated = mostIsolated(numbers);
		time.stop();
		cout << "The most isolated number is "
			<< isolated << endl
			<< "calculated in " << time() << " seconds"
			<< endl << endl;
	}


	cout << endl << endl;
	cout << "Count the unmatched words" << endl
		<< "-------------------------" << endl << endl;
	while (true)
	{
		cout << "Enter size for words lists: ";
		int n = 0;
		cin >> n;
		if (n <= 0)
			break;
		cout << "Enter word length: ";
		int wordSize;
		cin >> wordSize;
		cout << "Enter alphabet: ";
		string alphabet;
		cin >> alphabet;

		cout << "Enter seed for rand: ";
		unsigned int seed;
		cin >> seed;
		srand(seed);

		// Construct two sorted vectors of words
		Timer get;
		get.start();
		list<string> A = getWords(n, wordSize, alphabet);
		list<string> B = getWords(n, wordSize, alphabet);
		get.stop();
		cout << "Constructed in " << get() << " seconds"
			<< endl;

		if (wordSize * n < 60)
		{
			cout << "A is: " << A << endl
				<< "B is: " << B << endl;
		}

		// Report the number of words in the first sorted list
		//   that are not in the second sorted list
		Timer time;
		time.start();
		int count = unmatched(A, B);
		time.stop();
		cout << count
			<< " words in A were not in B" << endl
			<< "calculated in " << time() << " seconds"
			<< endl << endl;
	}

	return 0;
}
