//============================================================================
// Name        : AllSetCombinationsCPP.cpp
// Author      : rs
// Version     : 0.9
// Copyright   : nmarinkovic
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
//using namespace std;
using MyTuple = std::tuple<int, std::string>;

void printMyTuple(MyTuple niz[], int n) {
	for(int i = 0; i < n; i++) {
		std::cout << std::get<1>(niz[i]) + " ";
	}
	std::cout << std::endl;
}

bool areArraysEqualMoe(MyTuple arr1[], MyTuple arr2[], int n) {
	int broj = 0;
	for(int i = 0; i < n; i++) {
		if(std::get<0>(arr1[i]) == std::get<0>(arr2[i])) {
			broj += 1;
		}
	}
	if(broj == n) return true;
	else return false;
}

int main() {

	std::cout << "Provide the number of elements your set has: " << std::endl;
	int n = 4;
	try {
		std::cin >> n;
	} catch (const std::invalid_argument& e) {
		n = 4;
	}

	if (n == 0) return 0;
	if (n < 0) n = n * -1;


	std::cout << "Insert names of all elements: " << std::endl;
	if(n == 1) {
		std::string str;
		std::cin >> str;
		std::cout << "List of all combinations:" << std::endl;
		std::cout << str << std::endl;
	}
	else {
		//std::array<MyTuple, n> jednakomb;
		MyTuple jednakomb[n];

		for (int i = 0; i < n; i++) {
			std::string str;
			std::cin >> str;
			jednakomb[i] = MyTuple(i + 1, str);
		}

		MyTuple prvobitnareorder[n];

		for(int i = 0; i < n; i++) {
			prvobitnareorder[i] = MyTuple(std::get<0>(jednakomb[n - i - 1]), std::get<1>(jednakomb[n - i - 1]));
		}

		std::cout << "List of all combinations:" << std::endl;

		printMyTuple(jednakomb, n);


		//for(int i = 0; i < facn; i++) {
		while(!areArraysEqualMoe(jednakomb, prvobitnareorder, n)) {
			for(int j = n - 2; j >= 0; j--) {
				// poredi onu na kojoj smo sa prethodnikom, i ako je prethodnik veci onda radi stvari
				if(std::get<0>(jednakomb[j]) < std::get<0>(jednakomb[j + 1])) {

					int najmanjieliza = n+1;
					int indeksnajmanjeg = j;

					// pronadje sledeci element sa kojime ce se zameniti
					 // (on je prvi najmanji ali nije manji od njega, bitan detalj, u suprotnom ce se vrteti iste vrednosti)

					for (int k = j + 1; k < n; k++) {
						if (std::get<0>(jednakomb[k]) > std::get<0>(jednakomb[j])) {
							if (najmanjieliza > std::get<0>(jednakomb[k])) {
								najmanjieliza = std::get<0>(jednakomb[k]);
								indeksnajmanjeg = k;
							}
						}
					}

					// razmena vrednosti na ta 2 indeksa

					MyTuple temp = MyTuple(std::get<0>(jednakomb[j]), std::get<1>(jednakomb[j]));
					//delete(jednakomb[j]);
					jednakomb[j] = MyTuple(std::get<0>(jednakomb[indeksnajmanjeg]), std::get<1>(jednakomb[indeksnajmanjeg]));
					//delete(jednakomb[indeksnajmanjeg]);
					jednakomb[indeksnajmanjeg] = MyTuple(std::get<0>(temp), std::get<1>(temp));;
					//delete(temp);


					// niz svih elemenata nakon onog na kom smo stali
					// trebace nam da ga okrenemo
					MyTuple niz_iza[n - j - 1];

					for (int k = 0; k < n - j - 1; k++) {
						niz_iza[k] = MyTuple(std::get<0>(jednakomb[k + j + 1]), std::get<1>(jednakomb[k + j + 1]));
					}

					// okrecemo ceo niz
					MyTuple niz_iza_reordered[n - j - 1];

					for(int k = 0; k < n - j - 1; k++) {
						niz_iza_reordered[k] = MyTuple(std::get<0>(niz_iza[n - j - 2 - k]), std::get<1>(niz_iza[n - j - 2 - k]));
					}

					// stavljamo okrenut niz
					for (int lj = 0; lj < n - j - 1; lj++) {
						//delete(jednakomb[lj+j+1]);
						jednakomb[lj+j+1] = MyTuple(std::get<0>(niz_iza_reordered[lj]), std::get<1>(niz_iza_reordered[lj]));
					}
					printMyTuple(jednakomb, n);
					break;
				}
			}
		}
	}





	std::cout << "Hello World" << std::endl;
	return 0;
}
