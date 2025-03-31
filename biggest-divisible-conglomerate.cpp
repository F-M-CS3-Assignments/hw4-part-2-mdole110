#include "bdc.h"

#include <vector>
#include <cassert>
#include <iostream>
#include <set>
#include <string>
#include <climits>
#include <algorithm>
#include <random>


#define NPOS UINT32_MAX

using namespace std;

/*
TIME COMPLEXITIES office hour notes
dynamic programming - table process 
input size = n 
METHOD APPROACH
if constant number of steps =  O(n^2)
ALGORITHM APPROACH
diff number of steps per number = n(n+1)/2

....

Answers:
Time complexity for this dp solution:

the outer for loop: 
"for(size_t curr_index = 1; curr_index<input.size(); curr_index++){" 
runs curr_index times (n times)
... O(n)

the inner loop: 
"for(int j = 0; j<curr_index; ++j)"
runs from 0 to curr_index, so for each number in the outer loop (or in the list) it runs curr_index times, or n times
...O(n)

so overall time complexity would be O(n+n) AKA O(n^2)
....

Time complexity for recursive solution:

the programs calls each subset of each list (could be exponential growth) and says "use" or "lose" to each (2 possibilities)
therefore, I believe the time complexity would be 

O(n^2)


*/


string vec_to_string(vector<int> v){
    //just for printing the output/input?
        string vec_as_string = "{";
        for(long unsigned int i=0; i<v.size(); i++){
            string char_to_append = to_string(v[i]); //to_string: convert int to string https://www.geeksforgeeks.org/converting-number-to-string-in-cpp/
            vec_as_string = vec_as_string + char_to_append;
            //vec_as_string = vec_as_string + ",";
            //set up output to look like the output on the hmwk directions
            //space between each number, [ before and after ]
            if(i!= v.size()-1){
                vec_as_string += ", ";
            }
            
        }   
        vec_as_string += "}";
    
        return vec_as_string;
    }
vector<int> longest_vector(vector<vector<int>>& candidates){
    vector<int> longest_vector;
    for(long unsigned int i=0; i<candidates.size(); i++){
        if(candidates[i].size() > longest_vector.size()){
            longest_vector = candidates[i];
        }

    }
    return longest_vector;
}


vector<int> biggest_divisible_conglomerate(vector<int> input){
//initialize a 2D array 
    vector<vector<int>> dp_storing_found_conglomerates(input.size());
    //base cases
    if(input.empty() == true || input.size() == 1){
        //cout << "based case reached" << endl;
        return input;
    }

    //sort the lists

    vector<int> curr_subset;
    //sort in ascending order 
        for(long unsigned int i=0; i<input.size()-1; i++){
        //find the smallest unsorted number, move to back
        long unsigned int smallestIndex = i;
        for(long unsigned int j=i+1; j<input.size(); j++){
            if(input[j] < input[smallestIndex]){ //want the list to start w/ largest and decrease 
                smallestIndex = j;
            }
        }
        //use a third vaiable to swap
        if(smallestIndex!=i){//aka if not alr sorted
            int temporaryIndex = input[i];
            input[i] = input[smallestIndex];
            input[smallestIndex] = temporaryIndex;
        }
        }

        //NOW find the largest conglomerate 
        //add the first element to the subset because it can be divided by itself
        //SORTED NOW 
        
        //shouldn't have helper function for dynamic programming, helper function = very recursive 
        
        
        //code
        //for every input check all of the rest of tghe inputs to see if the division works
        //if it works then update the vector 
        //vector<int> sub_vector;
        for(size_t curr_index =0; curr_index< input.size(); curr_index++){
            //start a subvector of the current element (i)
            dp_storing_found_conglomerates[curr_index] = {input[curr_index]};
        }
        for(size_t curr_index = 1; curr_index<input.size(); curr_index++){ //index is all of the elements in the input list...called current index 
            for(int j = 0; j<curr_index; ++j){ //j as the elements in input before i. because its sorted in an increasing order input[curr_index] % input[j] makes sure that the bigger numer % but numbers that are smalller
                if(input[curr_index]%input[j] == 0){ // if the current number in the list (input[curr_index]) is divisible by a smaller number in the list (input[j])
                    //now go thru the subvectors already stored in the dp_.... vector<vector<int>>
                    if(dp_storing_found_conglomerates[curr_index].size() < dp_storing_found_conglomerates[j].size() +1 ){ //if the subvector of divisible values for i (input[i), the current number in the vector being checked, is SMALLER than the subvector for input[j], number BEFORE it in the list
                        dp_storing_found_conglomerates[curr_index] = dp_storing_found_conglomerates[j]; //bring all of the numbers from j's (earlier number) list to input[curr index]'s list this way the subvector for [j] now is the same as [i] and is called dp[i] (building off of the previous answers)
                        dp_storing_found_conglomerates[curr_index].push_back(input[curr_index]); //append the number itself (not the vector) at input[curr_idx] so that the number is also a divisible by itself basically. like how 4%4== 0 in the same way that 4%2 ==0
                    }

                }

            }
    
    }
return longest_vector(dp_storing_found_conglomerates);
}



int main() {

	// Test 1 (example from assignment description)
	vector<int> values = {28, 22, 7, 2, 8, 14, 24, 56};
	vector<int> ans = biggest_divisible_conglomerate(values);
	cout << "input: " << vec_to_string(values) << endl;
	cout << "output: " << vec_to_string(ans) << endl << endl;
	set<int> answerSet(ans.begin(), ans.end());
	set<int> soln = {56, 14, 7, 28};
	bool first = (answerSet == soln);
	soln = {56, 28, 14, 2};
	bool second = (answerSet == soln);
	assert(first || second);

	// Test 2
	values = {10, 5, 3, 15, 20};
	ans = biggest_divisible_conglomerate(values);
	cout << "input: " << vec_to_string(values) << endl;
	cout << "output: " << vec_to_string(ans) << endl << endl;
	soln = {20, 5, 10};
	set<int> answerSet2(ans.begin(), ans.end());
	assert(answerSet2 == soln);
    //test empty
    values = {};
	ans = biggest_divisible_conglomerate(values);
	cout << "input: " << vec_to_string(values) << endl;
	cout << "output: " << vec_to_string(ans) << endl << endl;
	soln = {};
	set<int> answerSet3(ans.begin(), ans.end());
	assert(answerSet3 == soln);

    //test size of 1
    values = {1};
	ans = biggest_divisible_conglomerate(values);
	cout << "input: " << vec_to_string(values) << endl;
	cout << "output: " << vec_to_string(ans) << endl << endl;
	soln = {1};
	set<int> answerSet4(ans.begin(), ans.end());
	assert(answerSet4 == soln);


	// The random number test creates a massive 28,000 value input vector.  
	// Solving the problem with such a large input is not feasible using recursion, 
	// but with dynamic programming it should take just a few seconds.  
	
	vector<int> random_values;
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> dist(1, 40000);
	while (random_values.size() < 28000) {
		random_values.push_back(dist(gen));
	}

	cout << "\nCalculating answer for input of size: " << random_values.size() << "..." << endl;
	time_t start = time(0);
	ans = biggest_divisible_conglomerate(random_values);
	time_t end = time(0);
	cout << "\x1B[32m" << "\tDone!  The answer is: " << vec_to_string(ans) << "\033[0m" << endl;
	time_t duration = end - start;
	cout << "It took " << duration << " seconds.  Wow!" << endl;\
	
	
	return 0;
}


