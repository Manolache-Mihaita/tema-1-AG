// tema1AG.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <math.h>
#include <string>
#include <time.h> 
#include <cstdlib>
#include <fstream>
#include <ctime>

/////////////////////
//#define nrOfV 10
#define MaxIterations 100
#define SetPrecison 3
#define PI 3.14159265359
#define NormalAmountOfNumbers 30


using namespace std;

vector<double> hcfirst;
vector<double> hcbest;
vector<double> annealing;


vector<double>interval(2);
bool minOrMax;/* 0-min 1-max*/
int nrOfB, function;
vector<double> maxFunction(3), minFunction(3);
unsigned int nrOfV;
int vectrCount;


double randDoubleVal(double rM, double lM) {
	double range = lM - rM;
	double randVal = (double)rand() / (double)RAND_MAX;
	return range + randVal + rM;
}


void initMaxs(vector<double> &maxFunction, vector<double> &minFunction) {
	for (int i = 0; i < 3; i++) {
		maxFunction[i] = LLONG_MIN;
		minFunction[i] = LLONG_MAX;
	}
}

vector<double> decodeBits(vector<bool>solution1) {
	vector<double> decodedBits(nrOfV);
	for (int i = 0; i < nrOfV; i++) {
		int power = 0;
		for (int j = 0; j < nrOfB; j++) {
			decodedBits[i] += solution1[i*nrOfB + j] * pow(2, power);
			power++;
			//cout << "pos in vector:" << i*nrOfB + j << endl;
		}
		//cout << decodedBits[i] << " ";
	}
	return decodedBits;
}

vector<double>realNumbers(vector<double> decoded) {
	vector<double>decRN;
	for (int i = 0; i < decoded.size(); i++) {
		decRN.push_back(interval[0] + decoded[i] * (interval[1] - interval[0]) / (pow(2, nrOfB) - 1));
	}
	return decRN;
}

void genRandBitString(vector<bool>&randbitstring) {
	for (auto i = 0; i <randbitstring.size(); i++) {
		randbitstring[i] = rand() % 2;
		//cout << best[i] << " ";
	}
}

double dejong(vector<double>vctr) {
	double fctRes = 0;
	for (int i = 0; i < vctr.size(); i++) {
		fctRes += vctr[i] * vctr[i];
	}
	return fctRes;
}



double Schwefel(vector<double>vctr) {
	double fctRes = 0;
	for (int i = 0; i < vctr.size(); i++) {
		fctRes += ((-vctr[i]) * sin(sqrt(abs(vctr[i]))));
	}
	return fctRes;
}




double Six_Hump(vector<double>vctr) {
	double fctRes = 0;
	fctRes = (4 - 2.1*pow(vctr[0], 2) + pow(vctr[0], 4 / 3))*pow(vctr[0], 2) + vctr[0] * vctr[1] + (-4 + 4 * pow(vctr[1], 2))*pow(vctr[1], 2);
	return fctRes;
}

double Rastrigin(vector<double>vctr) {
	double fctRes = 10 * nrOfV;
	for (int i = 0; i < vctr.size(); i++) {
		fctRes += pow(vctr[i], 2) - 10 * cos(2 * PI*vctr[i]);
	}
	return fctRes;
}


int getFunctions() {
	cout << "1.Six Hump Camel Back \n2.De Jong  \n3.Rastrigin \n4. Schwefel \nIntroduceti indicele functiei: ";
	int index_fct;

	cin >> index_fct;
	switch (index_fct)
	{
	case 1: {/*Six Hump*/
		interval[0] = -2;
		interval[1] = 2;
		nrOfV = 2;
		break;
	}
	case 2: {/*De J*/
		interval[0] = -5.12;
		interval[1] = 5.12;
		nrOfV = NormalAmountOfNumbers;
		break;
	}
	case 3: {/*Rastrigin*/
		interval[0] = -5.12;
		interval[1] = 5.12;
		nrOfV = NormalAmountOfNumbers;
		break;
	}
	case 4: {/*Schwefel*/
		interval[0] = -500;
		interval[1] = 500;
		nrOfV = NormalAmountOfNumbers;
		break;
	}
	default:
	{
		cout << "BAD ENTRY\nPROGRAM TERMINATED";
		exit(-1);
	}
	}
	return index_fct;
}


void maxInFct(double value) {
	if (value > maxFunction[vectrCount])maxFunction[vectrCount] = value;
	if (value < minFunction[vectrCount])minFunction[vectrCount] = value;
}

unsigned int getFirstNeighbor(vector<bool>currbitString) {
	double best;
	double curr;
	switch (function)
	{
	case 1: { /*Six Hump*/
		best = Six_Hump(realNumbers(decodeBits(currbitString)));
		for (unsigned int bit = 0; bit < currbitString.size(); bit++)
		{
			currbitString[bit] = !currbitString[bit];
			curr = Six_Hump(realNumbers(decodeBits(currbitString)));
			currbitString[bit] = !currbitString[bit];
			if (minOrMax == 0)
			{
				if (curr < best)return bit;
			}
			else
			{
				if (curr > best)return bit;
			}
		}

		break;
	}
	case 2: { /*De J*/

		best = dejong(realNumbers(decodeBits(currbitString)));
		for (unsigned int bit = 0; bit < currbitString.size(); bit++)
		{
			currbitString[bit] = !currbitString[bit];
			curr = dejong(realNumbers(decodeBits(currbitString)));
			currbitString[bit] = !currbitString[bit];
			if (minOrMax == 0)
			{
				if (curr < best)return bit;
			}
			else
			{
				if (curr > best)return bit;
			}
		}
		break;
	}
	case 3: { /*Ras*/
		best = Rastrigin(realNumbers(decodeBits(currbitString)));
		for (unsigned int bit = 0; bit < currbitString.size(); bit++)
		{
			currbitString[bit] = !currbitString[bit];
			curr = Rastrigin(realNumbers(decodeBits(currbitString)));
			currbitString[bit] = !currbitString[bit];
			if (minOrMax == 0)
			{
				if (curr < best)return bit;
			}
			else
			{
				if (curr > best)return bit;
			}
		}
		break;
	}
	case 4: { /*Sch*/
		best = Schwefel(realNumbers(decodeBits(currbitString)));
		for (unsigned int bit = 0; bit < currbitString.size(); bit++)
		{
			currbitString[bit] = !currbitString[bit];
			curr = Schwefel(realNumbers(decodeBits(currbitString)));
			currbitString[bit] = !currbitString[bit];
			if (minOrMax == 0)
			{
				if (curr < best)return bit;
			}
			else
			{
				if (curr > best)return bit;
			}
		}
		break;
	}

	}
	return 0;
}




unsigned int getBestNeighbor(vector<bool>currbitString) {
	double best;
	double curr;
	unsigned int bestBit = 0;

	switch (function)
	{
	case 1: { /*Six Hump*/
		best = Six_Hump(realNumbers(decodeBits(currbitString)));
		for (unsigned int bit = 0; bit < currbitString.size(); bit++)
		{
			currbitString[bit] = !currbitString[bit];
			curr = Six_Hump(realNumbers(decodeBits(currbitString)));
			currbitString[bit] = !currbitString[bit];

			if (minOrMax == 0)
			{
				if (curr < best) {
					best = curr;
					bestBit = bit;
				}
			}
			else
			{
				if (curr > best) {
					best = curr;
					bestBit = bit;
				}
			}


		}
		break;
	}
	case 2: { /*De J*/

		best = dejong(realNumbers(decodeBits(currbitString)));
		for (unsigned int bit = 0; bit < currbitString.size(); bit++)
		{
			currbitString[bit] = !currbitString[bit];
			curr = dejong(realNumbers(decodeBits(currbitString)));
			currbitString[bit] = !currbitString[bit];

			if (minOrMax == 0)
			{
				if (curr < best) {
					best = curr;
					bestBit = bit;
				}
			}
			else
			{
				if (curr > best) {
					best = curr;
					bestBit = bit;
				}
			}


		}
		break;
	}
	case 3: { /*Ras*/
		best = Rastrigin(realNumbers(decodeBits(currbitString)));
		for (unsigned int bit = 0; bit < currbitString.size(); bit++)
		{
			currbitString[bit] = !currbitString[bit];
			curr = Rastrigin(realNumbers(decodeBits(currbitString)));
			currbitString[bit] = !currbitString[bit];

			if (minOrMax == 0)
			{
				if (curr < best) {
					best = curr;
					bestBit = bit;
				}
			}
			else
			{
				if (curr > best) {
					best = curr;
					bestBit = bit;
				}
			}


		}
		break;
	}
	case 4: { /*Sch*/
		best = Schwefel(realNumbers(decodeBits(currbitString)));
		for (unsigned int bit = 0; bit < currbitString.size(); bit++)
		{
			currbitString[bit] = !currbitString[bit];
			curr = Schwefel(realNumbers(decodeBits(currbitString)));
			currbitString[bit] = !currbitString[bit];

			if (minOrMax == 0)
			{
				if (curr < best) {
					best = curr;
					bestBit = bit;
				}
			}
			else
			{
				if (curr > best) {
					best = curr;
					bestBit = bit;
				}
			}


		}
		break;
	}

	}


	return bestBit;
}





void Annealing() {
	srand(time(NULL));
	double currBestValInString;
	double alteredBestValInString;
	bool local;
	vector<bool> Vc(nrOfB*nrOfV);
	genRandBitString(Vc);
	unsigned int stuckCounter;
	unsigned int randBit;
	int tests = 0;
	unsigned int temp = 10000;
	do {
		stuckCounter = 0;
		genRandBitString(Vc);
		do {
			local = false;
			vector<bool>Vn;
			switch (function)
			{
			case 1: {/*six hump*/
				stuckCounter++;
				currBestValInString = Six_Hump(realNumbers(decodeBits(Vc)));
				randBit = rand() % Vc.size();
				Vc[randBit] = !Vc[randBit];
				alteredBestValInString = Six_Hump(realNumbers(decodeBits(Vc)));
				break;
			}
			case 2:/*De J*/
			{
				stuckCounter++;
				currBestValInString = dejong(realNumbers(decodeBits(Vc)));
				randBit = rand() % Vc.size();
				Vc[randBit] = !Vc[randBit];
				alteredBestValInString = dejong(realNumbers(decodeBits(Vc)));
				break;
			}
			case 3: {/*Rastrigin*/
				stuckCounter++;
				currBestValInString = Rastrigin(realNumbers(decodeBits(Vc)));
				randBit = rand() % Vc.size();
				Vc[randBit] = !Vc[randBit];
				alteredBestValInString = Rastrigin(realNumbers(decodeBits(Vc)));
				break;
			}
			case 4: {/*sche*/
				stuckCounter++;
				currBestValInString = Schwefel(realNumbers(decodeBits(Vc)));
				randBit = rand() % Vc.size();
				Vc[randBit] = !Vc[randBit];
				alteredBestValInString = Schwefel(realNumbers(decodeBits(Vc)));
				break;
			}
			}

			if (minOrMax == 0) {
				if (alteredBestValInString > currBestValInString) {
					Vc[randBit] = !Vc[randBit];
				}
				else {
					if (randDoubleVal(0.0, 1.0) > exp(-abs(alteredBestValInString - currBestValInString) / temp))
						Vc[randBit] = !Vc[randBit];
					else
						local = true;
				}
			}
			else
			{
				if (alteredBestValInString < currBestValInString) {
					Vc[randBit] = !Vc[randBit];
				}
				else {
					if (randDoubleVal(0.0, 1.0) > exp(-abs(alteredBestValInString - currBestValInString) / temp))
						Vc[randBit] = !Vc[randBit];
					else
						local = true;
				}
			}
			annealing.push_back(currBestValInString);
		} while (local&&stuckCounter <= 30);

		switch (function)
		{
		case 1: {
			currBestValInString = Six_Hump(realNumbers(decodeBits(Vc)));
			maxInFct(currBestValInString);
			break;
		}
		case 2:
		{
			currBestValInString = dejong(realNumbers(decodeBits(Vc)));
			maxInFct(currBestValInString);
			break;
		}
		case 3: {
			currBestValInString = Rastrigin(realNumbers(decodeBits(Vc)));
			maxInFct(currBestValInString);
			break;
		}
		case 4: {
			currBestValInString = Schwefel(realNumbers(decodeBits(Vc)));
			maxInFct(currBestValInString);
			break;
		}

		}

		//annealing.push_back(currBestValInString);
		--temp;
		tests++;
	} while (tests < MaxIterations);
	//	cout << (minOrMax == 1 ? maxFunction[2] : minFunction[2]) << endl;
}




void hcBest() {
	srand(time(NULL));
	vector<bool> Vc(nrOfB*nrOfV);
	unsigned short count = 1;
	unsigned short Bit;
	double currBestValInString;
	double alteredBestValInString;
	bool local;
	int tests = 0;
	do {


		genRandBitString(Vc);
		do {
			local = false;
			vector<bool>Vn;
			unsigned int testBit = getBestNeighbor(Vc);
			switch (function)
			{
			case 1: {
				currBestValInString = Six_Hump(realNumbers(decodeBits(Vc)));
				Vc[testBit] = !Vc[testBit];
				alteredBestValInString = Six_Hump(realNumbers(decodeBits(Vc)));
				break;
			}
			case 2:/*dej*/
			{
				currBestValInString = dejong(realNumbers(decodeBits(Vc)));
				Vc[testBit] = !Vc[testBit];
				alteredBestValInString = dejong(realNumbers(decodeBits(Vc)));
				break;
			}
			case 3: {
				currBestValInString = Rastrigin(realNumbers(decodeBits(Vc)));
				Vc[testBit] = !Vc[testBit];
				alteredBestValInString = Rastrigin(realNumbers(decodeBits(Vc)));
				break;
			}
			case 4: {
				currBestValInString = Schwefel(realNumbers(decodeBits(Vc)));
				Vc[testBit] = !Vc[testBit];
				alteredBestValInString = Schwefel(realNumbers(decodeBits(Vc)));
				break;
			}
			}

			if (minOrMax == 0)
			{
				if (alteredBestValInString > currBestValInString) {
					Vc[testBit] = !Vc[testBit];
					local = true;
				}
			}
			else
			{
				if (alteredBestValInString < currBestValInString)
				{
					Vc[testBit] = !Vc[testBit];
					local = true;
				}
			}
			hcbest.push_back(currBestValInString);
		} while (local);

		tests++;
		switch (function)
		{
		case 1: {
			currBestValInString = Six_Hump(realNumbers(decodeBits(Vc)));
			maxInFct(currBestValInString);
			break;
		}
		case 2:/*dej*/ {
			currBestValInString = dejong(realNumbers(decodeBits(Vc)));
			maxInFct(currBestValInString);
			break;
		}
		case 3: {
			currBestValInString = Rastrigin(realNumbers(decodeBits(Vc)));
			maxInFct(currBestValInString);
			break;
		}
		case 4: {
			currBestValInString = Schwefel(realNumbers(decodeBits(Vc)));
			maxInFct(currBestValInString);
			break;
		}
			



		}
		//cout << currBestValInString << " ";
		//hcbest.push_back(currBestValInString);
	} while (tests < MaxIterations);
	//	return (minOrMax == 1 ? maxFunction[1] : minFunction[1]);
}


void hcFirst() {
	double currBestValInString;
	double alteredBestValInString;
	bool local;
	vector<bool> Vc(nrOfB*nrOfV);
	unsigned int t = 0;
	do {


		genRandBitString(Vc);
		do {
			local = false;
			vector<bool>Vn;
			unsigned int testBit = getFirstNeighbor(Vc);
			switch (function)
			{
			case 1: {
				currBestValInString = Six_Hump(realNumbers(decodeBits(Vc)));
				Vc[testBit] = !Vc[testBit];
				alteredBestValInString = Six_Hump(realNumbers(decodeBits(Vc)));
				break;
			}
			case 2:/*dej*/
			{
				currBestValInString = dejong(realNumbers(decodeBits(Vc)));
				Vc[testBit] = !Vc[testBit];
				alteredBestValInString = dejong(realNumbers(decodeBits(Vc)));
				break;
			}
			case 3: {
				currBestValInString = Rastrigin(realNumbers(decodeBits(Vc)));
				Vc[testBit] = !Vc[testBit];
				alteredBestValInString = Rastrigin(realNumbers(decodeBits(Vc)));
				break;
			}
			case 4: {
				currBestValInString = Schwefel(realNumbers(decodeBits(Vc)));
				Vc[testBit] = !Vc[testBit];
				alteredBestValInString = Schwefel(realNumbers(decodeBits(Vc)));
				break;
			}

			}
			if (minOrMax == 0)
			{
				if (alteredBestValInString > currBestValInString) {
					Vc[testBit] = !Vc[testBit];
					local = true;
				}
			}
			else
			{
				if (alteredBestValInString < currBestValInString)
				{
					Vc[testBit] = !Vc[testBit];
					local = true;
				}
			}

			hcfirst.push_back(currBestValInString);
		} while (local);
		t++;
		switch (function)
		{
		case 1: {
			currBestValInString = Six_Hump(realNumbers(decodeBits(Vc)));
			maxInFct(currBestValInString);
			break;
		}
		case 2:/*dej*/ {
			currBestValInString = dejong(realNumbers(decodeBits(Vc)));
			maxInFct(currBestValInString);
			break;
		}
		case 3: {
			currBestValInString = Rastrigin(realNumbers(decodeBits(Vc)));
			maxInFct(currBestValInString);
			break;
		}
		case 4: {
			currBestValInString = Schwefel(realNumbers(decodeBits(Vc)));
			maxInFct(currBestValInString);
			break;
		}
		}
		//hcfirst.push_back(currBestValInString);
	} while (t < MaxIterations);
	//cout << currBestValInString << " ";
	//cout << (minOrMax == 1 ? maxFunction[0] : minFunction[0]) << endl;
}

int main()
{
	vector<double>time1(3);
	srand(time(NULL));
	clock_t startTime, endTime;
	function = getFunctions();
	nrOfB = ceil(log2((interval[1] - interval[0])*pow(10, SetPrecison)));
	//cin >> minOrMax;
	minOrMax = 0;
	initMaxs(maxFunction, minFunction);
	startTime = clock();
	hcFirst();
	endTime = clock();
	time1[0] = 1.0*(endTime - startTime) / CLOCKS_PER_SEC;
	vectrCount++;
	startTime = clock();
	hcBest();
	endTime = clock();
	time1[1] = 1.0*(endTime - startTime) / CLOCKS_PER_SEC;
	vectrCount++;
	startTime = clock();
	Annealing();
	endTime = clock();
	time1[2] = 1.0*(endTime - startTime) / CLOCKS_PER_SEC;
	vectrCount++;
	for (int i = 0; i < vectrCount; i++) {
		cout << "MAX:" << maxFunction[i] << " MIN:" << minFunction[i] << " TIME:" << time1[i] << endl;
	}

	cout << "\nHcFirst:\n";
	for (int i = 0; i < hcfirst.size(); i++) {
		cout << hcfirst[i] << " \n";
	}
	cout << "\nHcBest:\n";
	for (int i = 0; i < hcbest.size(); i++) {
		cout << hcbest[i] << " \n";
	}

	cout << "\nAnnealing:\n";
	for (int i = 0; i < annealing.size(); i++) {
		cout << annealing[i] << " \n";
	}

	return 0;
}
