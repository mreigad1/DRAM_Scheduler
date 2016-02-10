#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#define LINESIZE 3
#define MAX(a,b) ((a > b)?(a):(b))
#define MIN(a,b) ((a < b)?(a):(b))
#define MAXBITS(a) ((1 << a) - 1)
#define INVALID (-1)
using namespace std;

enum action{
	A = 0,
	R = 1,
	W = 2,
	P = 3
};

//dMap[previousCommand][currentCommand]
int delayMap[4][4] = {	{ INVALID,      12,      12,      30 }, 
			{ INVALID,       1,       4,       3 },
			{ INVALID,       1,       1,       1 },
			{      20, INVALID, INVALID, INVALID } };

//takes cycles from map and prints any idles
void printIdles(int i){
	int k = i - 1;
	if(k > 0){
		cout << "I" << dec << k << endl;
	}
}

int main(){

	unsigned int consecutives = 0;
	int lineCount = 0;
	unsigned int prevRow = 0;
	unsigned int prevCol = 0;
	unsigned int rowBuff = 0;
	action prevAction = P;
	cout.fill('0');
	while(cin.good() && !cin.eof()){
		static bool first = true;
		action act;
		unsigned int row, column;
		char readStore;
		unsigned int address;
		int delay = 0;
		cin >> readStore;
		cin >> hex >> address;
		act = ((readStore == 'L' || readStore == 'l')?(R) : ( (readStore == 'S' || readStore == 's')?(W) : (A) ));
		if(act == A){
			cerr << "Invalid Action read in.  Now Exiting.\n";
			exit(0);
		}
		if(!cin.good() || cin.eof()){
			continue;
		}
		column = MAXBITS(12) & address;
		row = (address >> 12) & MAXBITS(20);
		if(row != rowBuff){//this row is not in buffer, must activate
			if(prevAction != P){	//if previous action was not precharge, must precharge
				delay = MAX(0, (19 - consecutives));
				if(prevAction == R){
					delay = MAX(delay, 3);
				}
				consecutives = 0;
				prevAction = P;
				printIdles(delay);
				cout << "P" << endl;
			}
			delay = delayMap[prevAction][A];	//current action in this if is 'Activate'
			prevAction = A;
			rowBuff = row;
			if(!first){
				printIdles(delay);
			}
			cout << "A";
			cout.width(5);
			cout << hex << uppercase << row << endl;
			cout.width(0);
			first = false;
		}
		delay = delayMap[prevAction][act];
		if(prevAction != A){
			consecutives += delay;
		}else{
			consecutives++;
		}
		prevAction = act;
		printIdles(delay);
		if(act == W){
			cout << "W";
		}else if (act == R){
			cout << "R";
		}
		cout.width(3);
		cout << hex << uppercase << column << endl;
		cout.width(0);
	}
}
