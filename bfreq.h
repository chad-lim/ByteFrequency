#ifndef BFREQ_H
#define BFREQ_H


#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <string>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>

#define DEBUG 0
#define true 1
#define false 0
#define BYTE_MASK 0xFF
#define NYBBLE_MASK 0xFF
#define LAST_NEWLINE 0
#define MAXBYTES 16

void getArguments(char *argv[], bool &omitValue, bool &useComma, bool &percent, bool &sort, int &n);
void select(std::string arguments, bool &omitValue, bool &useComma, bool &percent, bool &sort, int &n);
void calculateFrequency(std::string inputs, std::vector<int> &freq);
void forSort(std::vector<std::pair<int, int> > &pear, std::vector<int> &freq); 

#endif
