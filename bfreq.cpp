#include "bfreq.h"

int main(int args, char *argv[]){

	// Get input from file
	std::string inputs = "";

	while(std::cin){
		std::string temp;
		std::getline(std::cin, temp);
		inputs.append(temp);
		inputs.append(" ");
	}

	// Default values for command line arguments
	bool omitValue = false;
	bool useComma = false;
	bool sort = false;
	bool percent = false;
	int n = 1;

	//std::vector <std::string> arguments;
	std::vector <int> freq;

	// Gets the arguments if there are any, otherwise continue with all the
	// default processes
	if(argv[1] != NULL){
		getArguments(argv, omitValue, useComma, sort, percent, n);
	}

	// Initialize a vector of zeros
	for(int i = 0; i < 256; i++){
		freq.push_back(0);
	}

	// Get all of the frequencies
	calculateFrequency(inputs, freq);

	// Create a vector pair
	std::vector<std::pair<int, int> > pear;

	// Assembles the vector pair so that sorting becomes easier
	// I only need to sort the frequencies and the associated values will
	// follow as well
	forSort(pear ,freq);

	// Get the total size of the inputs.
	// -2 because the size was oddly two greater than it should be
	// when reading the txt file I used
	int denominator = inputs.size()-2;

	/*
		THE FOLLOWING CONSISTS OF ALL OF THE ALGORITHMS FOR OUTPUTS
		All of the values are output in hex
		Frequencies are either integers or some percentage
		Assumes you can only omit values or use a comma, not both
	*/

	// Do this if you're supposed to omit the values
	if(omitValue){

		// Do this if you need to sort by percent
		if(sort && percent){

			// Sort in reverse order
			std::sort(pear.rbegin(), pear.rend());

			// Temporary values to make it easier with the sorting algorithm
			int t1 = 0;
			int t2 = 0;

			// Iterate through all the values
			for(int i = 0; i < 256; i++){

				// If the loop can continue as normal when printing "n" per line
				if(i+n < freq.size()){

					// Print "n" times per line
					for(int k = i; k < i+n; k++){
						t1 = (int)pear.at(k).second; // LEFT COLUMN
						t2 = (int)pear.at(k).first;  // RIGHT COLUMN
						if(t1 == 32){
							t2 -=2;
						}
						printf("%11.1f; ", 100*((double)t2)/denominator);
					}
				}

				// If incrementing would seg-fault, instead increment by one
				// To ensure all values are gathered
				if(i+n >= freq.size()){
					while(i < freq.size()){
						t1 = (int)pear.at(i).second; // LEFT COLUMN
						t2 = (int)pear.at(i).first;  // RIGHT COLUMN
						if(t1 == 32){
							t2-=2;
						}
						printf("%11.1f; ", 100*((double)t2)/denominator);
						i++;
					}
				}
				putchar('\n');
			}
		}

		// SAME LOGIC AS BEFORE BUT NO PERCENT, still sorted
		else if(sort){

			// Sort in reverse like before
			std::sort(pear.rbegin(), pear.rend());

			// Temporary values to make it easier with the sorting algorithm
			int t1 = 0;
			int t2 = 0;

			for(int i = 0; i < 256; i+=n){

				if(i+n < freq.size()){
					for(int k = i; k < i+n; k++){
						t1 = (int)pear.at(k).second; // LEFT COLUMN
						t2 = (int)pear.at(k).first;  // RIGHT COLUMN
						if(t1 == 32){
							t2 -=2;
						}

						// Here we do not calculate the percent but instead use frequency
						printf("%9d; ", t2);
					}
				}
				if(i+n >= freq.size()){
					while(i < freq.size()){
						t1 = (int)pear.at(i).second; // LEFT COLUMN
						t2 = (int)pear.at(i).first;  // RIGHT COLUMN
						if(t1 == 32){
							t2-=2;
						}

						// Here we do not calculate the percent but instead use frequency
						printf("%9d; ", t2);
						i++;
					}
				}
				putchar('\n');
			}
		}

		// Not sorted, percents used
		else if(percent){

			// Iterate through all the values
			for(int i = 0; i < freq.size(); i++){

				int temp = 0;

				// Make sure you can still go up by "n"
				if(i+n < freq.size()){
					for(int k = i; k < i+n; k++){
						temp = (int)freq.at(k);
						if(k == 32){
							temp -=2;
						}
						printf("%11.1f; \n",100*((double)temp)/denominator);
					}
				}

				// If you can't go up by "n", increment instead by one
				if(i+n >= freq.size()){
					while(i < freq.size()){
						temp = (int)freq.at(i);
						if(i == 32){
							temp-=2;
						}
						printf("%11.1f; \n",100*((double)temp)/denominator);
						i++;
					}
				}
				putchar('\n');
			}
		}

		// SAME LOGIC AS BEFORE but frequency used instead of percent
		else{
			for(int i = 0; i < freq.size(); i+=n){
				int temp = 0;
				if(i+n < freq.size()){
					for(int k = i; k < i+n; k++){
						temp = (int)freq.at(k);
						if(k == 32){
							temp -=2;
						}
						printf("%9d; ", temp);
					}
				}
				if(i+n >= freq.size()){
					while(i < freq.size()){
						temp = (int)freq.at(i);
						if(i == 32){
							temp-=2;
						}
						printf("%9d; ", temp);
						i++;
					}
				}
				putchar('\n');
			}
		}
	}

	// Do this if we replace one of the spaces with a comma
	else if(useComma){

		// If we have to use a comma and sort by percent
		if(sort && percent){

			// Sort in reverse
			std::sort(pear.rbegin(), pear.rend());
			int t1 = 0;
			int t2 = 0;

			// Iterate
			for(int i = 0; i < 256; i++){

				// Make sure you can keep incrementing by "n"
				if(i+n < freq.size()){
					for(int k = i; k < i+n; k++){

						t1 = (int)pear.at(k).second; // LEFT COLUMN
						t2 = (int)pear.at(k).first;  // RIGHT COLUMN
						if(t1 == 32){
							t2 -=2;
						}

						// Print n times per line
						printf("%2x,%5.1f; ", t1, 100*((double)t2)/denominator);
					}
				}

				// If you can't increment by "n" anymore, increment by one
				if(i+n >= freq.size()){
					while(i < freq.size()){
						t1 = (int)pear.at(i).second; // LEFT COLUMN
						t2 = (int)pear.at(i).first;  // RIGHT COLUMN
						if(t1 == 32){
							t2-=2;
						}

						// Print the remaining times
						printf("%2x,%5.1f; ", t1, 100*((double)t2)/denominator);
						i++;
					}
				}
				putchar('\n');
			}
		}

		// If we have to use a comma and sort by frequency
		// SAME LOGIC AS BEFORE WITHOUT FREQUENCY
		else if(sort){
			std::sort(pear.rbegin(), pear.rend());
			int t1 = 0;
			int t2 = 0;
			for(int i = 0; i < 256; i+=n){

				if(i+n < freq.size()){
					for(int k = i; k < i+n; k++){
						t1 = (int)pear.at(k).second; // LEFT COLUMN
						t2 = (int)pear.at(k).first;  // RIGHT COLUMN
						if(t1 == 32){
							t2 -=2;
						}
						printf("%2x,%3d; ", t1, t2);
					}
				}
				if(i+n >= freq.size()){
					while(i < freq.size()){
						t1 = (int)pear.at(i).second; // LEFT COLUMN
						t2 = (int)pear.at(i).first;  // RIGHT COLUMN
						if(t1 == 32){
							t2-=2;
						}
						printf("%2x,%3d; ", t1, t2);
						i++;
					}
				}
				putchar('\n');
			}
		}

		// If we have to use a comma and use percents
		else if(percent){

			// Iterate
			for(int i = 0; i < freq.size(); i++){
				int temp = 0;

				// Make sure we can keep incrementing by n
				if(i+n < freq.size()){
					for(int k = i; k < i+n; k++){
						temp = (int)freq.at(k);
						if(k == 32){
							temp -=2;
						}

						// Print n times, calculating the percent
						printf("%2x,%5.1f; \n", k, 100*((double)temp)/denominator);
					}
				}

				// If we cannot iterate "n"-more times, increment by one instead
				if(i+n >= freq.size()){
					while(i < freq.size()){
						temp = (int)freq.at(i);
						if(i == 32){
							temp-=2;
						}

						// Print the remaining number of times
						printf("%2x,%5.1f; \n", i, 100*((double)temp)/denominator);
						i++;
					}
				}
				putchar('\n');
			}
		}

		// If we have to use a comma but nothing else
		else{

			// Iterate
			for(int i = 0; i < freq.size(); i+=n){
				int temp = 0;

				// Increment by n, check if still possible
				if(i+n < freq.size()){
					for(int k = i; k < i+n; k++){
						temp = (int)freq.at(k);
						if(k == 32){
							temp -=2;
						}

						// Print the frequency with a comma
						printf("%2x,%3d; ", k, temp);
					}
				}

				// If we cannot increment by n anymore, increment by one
				if(i+n >= freq.size()){
					while(i < freq.size()){
						temp = (int)freq.at(i);
						if(i == 32){
							temp-=2;
						}

						// Print the frequency with a comma the remaining
						// number of times
						printf("%2x,%3d; ", i, temp);
						i++;
					}
				}
				putchar('\n');
			}
		}

	}

	// Default behavior, two spaces after the left column and
	// three spaces for the frequency
	else{

		// Default bevhavior, sorted by percent
		if(sort && percent){

			// Sort in reverse order
			std::sort(pear.rbegin(), pear.rend());
			int t1 = 0;
			int t2 = 0;

			// Iterate
			for(int i = 0; i < 256; i++){

				// Check if we can increment n times
				if(i+n < freq.size()){

					for(int k = i; k < i+n; k++){
						t1 = (int)pear.at(k).second; // LEFT COLUMN
						t2 = (int)pear.at(k).first;  // RIGHT COLUMN
						if(t1 == 32){
							t2 -=2;
						}

						// Print n times, using percent and default spacing
						printf("%2x  %5.1f; ", t1, 100*((double)t2)/denominator);
					}
				}

				// If we cannot increment n times, increment by one instead
				if(i+n >= freq.size()){

					while(i < freq.size()){
						t1 = (int)pear.at(i).second; // LEFT COLUMN
						t2 = (int)pear.at(i).first;  // RIGHT COLUMN
						if(t1 == 32){
							t2-=2;
						}

						// Print the remaining number of times
						printf("%2x  %5.1f; ", t1, 100*((double)t2)/denominator);
						i++;
					}
				}
				putchar('\n');
			}
		}

		// Default behavior, sorted by frequency
		// SAME LOGIC AS BEFORE, JUST WITHOUT PERCENT
		else if(sort){

			std::sort(pear.rbegin(), pear.rend());
			int t1 = 0;
			int t2 = 0;
			for(int i = 0; i < 256; i+=n){

				if(i+n < freq.size()){

					for(int k = i; k < i+n; k++){
						t1 = (int)pear.at(k).second; // LEFT COLUMN
						t2 = (int)pear.at(k).first;  // RIGHT COLUMN
						if(t1 == 32){
							t2 -=2;
						}
						printf("%2x  %3d; ", t1, t2);
					}
				}

				if(i+n >= freq.size()){

					while(i < freq.size()){
						t1 = (int)pear.at(i).second; // LEFT COLUMN
						t2 = (int)pear.at(i).first;  // RIGHT COLUMN
						if(t1 == 32){
							t2-=2;
						}
						printf("%2x  %3d; ", t1, t2);
						i++;
					}
				}
				putchar('\n');
			}
		}

		// Default behvaior, with percent in place of frequency
		else if(percent){

			for(int i = 0; i < freq.size(); i++){
				int temp = 0;

				// If incrementing by n is still possible
				if(i+n < freq.size()){

					for(int k = i; k < i+n; k++){
						temp = (int)freq.at(k);
						if(k == 32){
							temp -=2;
						}

						// Print n times in a line
						printf("%2x  %5.1f; \n", k, 100*((double)temp)/denominator);
					}
				}

				// If we cannot increment by n, increment by one instead
				if(i+n >= freq.size()){

					while(i < freq.size()){
						temp = (int)freq.at(i);
						if(i == 32){
							temp-=2;
						}

						// Print the remaining number of times
						printf("%2x  %5.1f; \n", i, 100*((double)temp)/denominator);
						i++;
					}
				}
				putchar('\n');
			}
		}

		// Default behavior entirely
		else{

			// Iterate
			for(int i = 0; i < freq.size(); i+=n){
				int temp = 0;

				// Simply check to see if we can continue incrementing by n
				if(i+n < freq.size()){

					// Print n times per line
					for(int k = i; k < i+n; k++){
						temp = (int)freq.at(k);
						if(k == 32){
							temp -=2;
						}
						printf("%2x  %3d; ", k, temp);
					}
				}

				// If we cannot continue incrementing by n, increment by one
				if(i+n >= freq.size()){
					while(i < freq.size()){
						temp = (int)freq.at(i);
						if(i == 32){
							temp-=2;
						}

						// Print the remaining number of times in a line,
						// up to n-1 times
						printf("%2x  %3d; ", i, temp);
						i++;
					}
				}
				putchar('\n');
			}
		}
	}

	return 0;
}


// Function that is meant to help with the sorting algorithm
/*
I had issues figuring out how to sort the values since I was keeping the
frequencies and corresponding values separate, so I decided to make them
a pair when it came to doing the sorting
*/
void forSort(std::vector<std::pair<int, int> > &pear, std::vector<int> &freq){

	// Creates a vector of pairs, made up of the frequencies and indices
	// in base 10
	for(int i = 0; i < 256; i++){
		pear.push_back(std::make_pair((int)freq.at(i), i));
	}
}

// Function to calculate the frequency of each value
// Given the vector of frequencies and the input file
void calculateFrequency(std::string inputs, std::vector<int> &freq){

	// Iterate through string
	for(int i = 0; i < inputs.size(); i++){

		// At every character in the string, take the integer representation
		// of the character and go to that index of the frequencies vector
		int temp = inputs.at(i);

		// Increment the frequency of the found character
		// This should work because the vector is indexed in the same way as the
		// integer representation of the characters found in the input
		freq.at(temp)++;
	}
}

// Gets the input arguments, depending on how many there are, and passes them to the select function
void getArguments(char *argv[], bool &omitValue, bool &useComma, bool &sort, bool &percent, int &n){

	std::vector <std::string> arguments;

	// Pushes the first argument since there will always be one if it gets here
	arguments.push_back(argv[1]);
	select(arguments.at(0), omitValue, useComma, sort, percent, n);

	// Pushes the second argument if there is one, etc.
	if(argv[2] != NULL){
		arguments.push_back(argv[2]);
		select(arguments.at(1), omitValue, useComma, sort, percent, n);
		if(argv[3] != NULL){
			arguments.push_back(argv[3]);
			select(arguments.at(2), omitValue, useComma, sort, percent, n);
			if(argv[4] != NULL){
				arguments.push_back(argv[4]);
				select(arguments.at(3), omitValue, useComma, sort, percent, n);
				if(argv[5] != NULL){
					arguments.push_back(argv[5]);
					select(arguments.at(4), omitValue, useComma, sort, percent, n);
				}
			}
		}
	}
}

// Assumes a user will only do either -n or -c, not both
// If both are selected, the second one taxes precedence
void select(std::string arguments, bool &omitValue, bool &useComma, bool &sort, bool &percent, int &n){

	// If we're going to do no spaces and no values, we won't do no comma
	if (arguments == "-n"){
		omitValue = true;
		useComma = false;
	}

	// If we're going to do commas, we will not be spaceless and valueless
	else if(arguments == "-c"){
		omitValue = false;
		useComma = true;
	}

	// Use percents
	if(arguments == "-p"){
		percent = true;
	}

	// Sort frequencies from highest to lowest
	if(arguments == "-s"){
		sort = true;
	}

	// If the user gives a new value for n, take note of it
	// Assumes input in the form -L<n>, with no space between L and n
	if(arguments.at(1) == 'L'){
		std::string temp = arguments.substr(2, std::string::npos);
		n = std::stoi(temp);
	}

	// Program ends if given any invalid input argument
	if(arguments != "-n" && arguments != "-c" && arguments != "-p" && arguments != "-s" && arguments.at(1) != 'L'){
		fprintf(stderr, "Error: Non-valid input argument(s)\nUsage: bfreq [-n | -c] -s -c [-L<n>]\nTerminating\n");
		exit(EXIT_SUCCESS);
	}
}
