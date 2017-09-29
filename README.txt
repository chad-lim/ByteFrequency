ByteFrequency

This program is designed to take in some input file and obtain the frequency of the 256 possible characters. It creates a table of pairs made up of a hexadecimal value from 0x00 to 0xff and their associated frequencies in the input file. So far this works with most .txt files and source-code files, but does not properly take executables.

----------------------------------------------------------------------------------------------------------------------------

Usage:
bfreq [-n | -c] -s -p [-L<n>]

-n: Omit the hexadecimal value and the spaces between the value and the frequency
-c: Use a comma instead of spaces
-s: Sort the output by frequency 
-p: Use percents to represent frequency instead of the exact counts

----------------------------------------------------------------------------------------------------------------------------

# THIS README DESCRIBES THE PROGRAM
# KNOWN FUNCTIONALITY / NON-FUNCTIONALITY, AND KNOWN BUGS

FUNCTIONALITY:
It is expected that:
	- The code can read in a text file as an input to be used by the program
	- The program can properly obtain and decipher input arguments, which
	determine if spaces are removed, commas are used, percents are used, or
	if the output needs to be sorted
	- The program is able to inspect the input file and determine if
	- The program is able to output the frequencies found in text files
	and source-code.
	- The user cannot select both "no spaces" and "use commas" at once.
	One must be picked over the other. If both are still selected, the one
	input last will be selected.
	- The user will only enter a maximum of FIVE input arguments, not including
	the program name. This allows the user to potentially try to do
	-n and -c at the same time, as well as use all the other input arguments
	- The program calculates the frequencies before doing any of the outputs
	- The program can properly calculate frequencies in terms of percent for
	all arguments, including no spaces, commas, and default behavior.
	- The program can properly sort frequencies in terms of both the frequency
	and the frequency when turned into a percent for no spaces, commas, and
	default behavior.
	- The sorting of a vector pair will result in a sorted frequency column, and
	the associated hexadecimal column will follow along but not be sorted itself.
	- There will be no space between a comma and a frequency if the maximum sizes
	are reached.
	- In standard / default behavior, two spaces exist between the hexadecimal
	value and the most significant digit of the frequency.
	- Percent values will be output to a maximum of one digit past the decimal
	point
	- If any input arguments are given that are not any of the expected ones,
	including -n, -c, -s, -p, -L<n>, then the program writes to std::err
	and define proper parameters
	- The code does not check the upper bound for numbers. For example,
	while the code does ensure that there are always two spaces between the
	frequency and the hex-value in the default behavior, it does not prevent the
	frequency values from exceeding 999, instead allowing higher numbers to extend
	to the right.

BUGS
	- The code does not function when certain files are input to it. I have not
	been able to pinpoint the exact reason for this. At first I thought that
	maybe the size of my text files was too big, having too much data input.
	However, I've given a file as many as 3,000 words and my bfreq program still
	functioned correctly. Despite this, when pasting a research paper into a
	text file, it did not work. I suspect this could be that I had no hit the
	maximum size during my own test, or something went wrong during the copy
	and paste.
	- Like the previous bug, the code also does not like being fed
	executables
