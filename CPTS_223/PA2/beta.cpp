//joshua luhrman 
//PA 2
//
//Note: beta was to make sure time worked and that i have it in miroseconds
//
//

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <array>
#include <list>
#include <math.h>
#include <algorithm>
#include <chrono>

using namespace std;

void openFileCheck(string filename, ifstream &file, vector<int> &in);
void buildVector(ifstream &file, vector<int> &in);


//the max sum functions
int maxSubSum1 (const vector<int> &a);
int maxSubSum2 (const vector<int> &a);
int maxSubSum3 (const vector<int> &a);
int maxSubSum4 (const vector<int> &a);
int maxSumRec  (const vector<int> &a, int left, int right);
int max3 (int left, int right, int border);




int main(int argc, char* argv[]){

	cout << "hello world" << endl;
	string fileName = argv[1];
	vector<int> ofInts;
	ifstream file;

	openFileCheck(fileName, file, ofInts);
	
	for(int i = 0; i < ofInts.size(); i++)
		cout << "[" << i << "] " << ofInts[i] << endl;


	for(int i = 0; i < *argv[2]; i++)  {
		std::chrono::time_point<std::chrono::system_clock> start, end;
		
		int max;

		// using as a source to find time for each function/method of finding max
		// https://www.geeksforgeeks.org/chrono-in-c/
		
		//method 1
		start = std::chrono::system_clock::now();
        	max = maxSubSum1(ofInts);
		end = std::chrono::system_clock::now();
	
		std::chrono::duration<double, std::micro> elapsed_microseconds = end - start;
		// dont think this is needed
		//std::time_t end_time = std::chrono::system_clock::to_time_t(end);
		cout << "time 1: " << elapsed_microseconds.count() << " ms." << endl;
		cout << "from 1: " << max << endl;

		
		//method 2
		start = std::chrono::system_clock::now();
		max = maxSubSum2(ofInts);
		end = std::chrono::system_clock::now();
	
		elapsed_microseconds = end - start;
		cout << "time 2: " << elapsed_microseconds.count() << " ms." << endl;
		cout << "from 2: " << max << endl;

		
		//method 3
		start = std::chrono::system_clock::now();
		max = maxSubSum3(ofInts);
		end = std::chrono::system_clock::now();
	
		elapsed_microseconds = end - start;
		cout << "time 3: " << elapsed_microseconds.count() << " ms." << endl;
		cout << "from 3: " << max << endl;

		
		//method 4
		start = std::chrono::system_clock::now();
		max = maxSubSum4(ofInts);
		end = std::chrono::system_clock::now();
	
		elapsed_microseconds = end - start;
		cout << "time 4: " << elapsed_microseconds.count() << " ms." << endl;
		cout << "from 4: " << max << endl;
	
	}

	return 0;
}


// used to open file, calles another fucnction
// to extrat the needed data
// then closes the file.
void openFileCheck(string fileName, ifstream &file, vector<int> &in)  {

	file.open(fileName);
	if(!file){
		cout << "error in opening file" << endl;
	}
	else  {
		if(!in.empty())
			in.clear();
		
		buildVector(file, in);

		if(file.is_open())
			file.close();
	}
}


//simple way of walking through a file and obtaining each intitiger
void buildVector(ifstream &file, vector<int> &in)  {
	int item;

	//https://stackoverflow.com/questions/19602407/read-integers-from-a-file-into-a-vector-in-c
	//found what looks like a simple way of reading integers from a file. think it acts like getline. 
	while(file >> item)  {
		in.push_back(item);
	}
}


// cubic maximum contiguous 
int maxSubSum1 ( const vector<int> & a)  {

	int maxSum = 0;
	for ( int i = 0; i < a.size(); i++) {
		for (int j = i; j < a.size(); ++j)  {
			
			int thisSum = 0;

			for (int k = i; k <= j; ++k) {
				thisSum += a[k];
			}

			if (thisSum > maxSum)  {
				maxSum = thisSum;
			}	
		}
	}
	return maxSum;
}



// Quadratic
int maxSubSum2 ( const vector<int> & a)  {

	int maxSum = 0;

	for( int i = 0; i < a.size(); ++i)  {
		int thisSum = 0;
		
		for ( int j = i; j < a.size(); ++j)  {
			thisSum += a[j];

			if (thisSum > maxSum)  {
				maxSum = thisSum;
			}
		}
	}
	return maxSum;
}

// recursive
int maxSumRec ( const vector<int> & a, int left, int right)  {

        if ( left == right)  { // base case
                if( a[left] > 0) {
                        return a[left];
                }
                else
                        return 0;
        }

        int center = ( left + right ) / 2;
        int maxLeftSum = maxSumRec( a, left, center );
        int maxRightSum = maxSumRec ( a, center + 1, right);

        int maxLeftBorderSum = 0, leftBorderSum = 0;
        for ( int i = center + 1; i >= left; --i)  {
                leftBorderSum += a[i];
                if( leftBorderSum > maxLeftSum)
                        maxLeftBorderSum = leftBorderSum;
        }


        int maxRightBorderSum = 0, rightBorderSum = 0;
        for ( int j = center + 1; j <= right; ++j )  {
                rightBorderSum += a[j];
                if( rightBorderSum > maxRightSum)
                        maxRightBorderSum = rightBorderSum;
        }
        return max3 (maxLeftSum, maxRightSum, maxLeftBorderSum + maxRightBorderSum);
}

//max3 method
int max3 (int left, int right, int border) {

        if (left >= right && left >= border)
                return left;
        else if (right >= left && right >= border)
                return right;
        else if (border >= right && border >= left)
                return border;
        else
                return 0;
}


//Driver
int maxSubSum3 (const vector<int> &a) {

        return maxSumRec (a, 0, a.size() - 1);
}



// Linear-time
int maxSubSum4 (const vector<int> & a)  {
	
	int maxSum = 0, thisSum = 0;

	for (int j = 0; j <a.size(); ++j)  {
		thisSum += a[j];

		if (thisSum > maxSum){
			maxSum = thisSum;
		}
		else if(thisSum < 0) {
			thisSum = 0;
		}
	}
	return maxSum;
}
