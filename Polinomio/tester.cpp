/*
 * tester.cpp
 *
 *  Created on: 25 dic 2020
 *      Author: vcapo
 */

#include <iostream>
#include "Polinomio.h"
using namespace std;

int main(){

	vector<double> s;
	s.push_back(2);
	s.push_back(3);
	s.push_back(4.4);

	Polinomio P(s);
	cout << P;

	vector<double> t;
	t.push_back(5);
	t.push_back(4);
	t.push_back(1);
	t.push_back(7);
	t.push_back(11);

	Polinomio T(t);
	cout << T;

	P.somma(T);
	cout << "Somma: " << P;
	double ris = P.valore(1);
	cout << "P(2): " <<  ris;

	system("PAUSE");
	return 0;
}
