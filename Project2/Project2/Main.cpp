#include <vector>
#include <list>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <filesystem>
#include "lib1.h"
#include "player.h"
#include "cards.h"


using namespace std;
namespace fs = std::experimental::filesystem;


void Country::printNeighboors() {

	cout << "Neighboors of " << this->name << " :\n\n";
	for (size_t i = 0; i < neighboors.size(); ++i)
		cout << neighboors.at(i)->name << "\n";
}

void Country::addNeighboor(Country* c) {

	cout << "HERE" << "\n";
	bool alreadyIn = false;

	for (size_t i = 0; i < neighboors.size(); ++i) { // loop inside each vector value to check if new added country is already in list

		if (this->name.compare(c->name) == 0) {   //checks if country is already in

			alreadyIn = true;
			break;

		}

	}

	if (alreadyIn == false) {

		this->neighboors.push_back(c); //performs the actual adding

	}

}

//basic addEdge function, u becomes adjecent to v and v to u.
void Risk_map::addEdge(int u, int v, vector<Country>& C) {

	bool alreadyIn = false;

	for (auto x : adj[u]) { // loop inside each vector value to check if new added country is already in list

		if (x.name.compare(C.at(v).name) == 0) {   //checks if country is already in

			alreadyIn = true;
			break;

		}

	}

	if (alreadyIn == false) {

		adj[u].push_back(C.at(v)); //performs the actual adding
		adj[v].push_back(C.at(u));



	}


}

//same method but for continent graph
void Risk_map::addEdgeC(int u, int v, vector<string>& continents) {

	bool alreadyIn = false;

	for (auto x : adjC[u]) { // loop inside each vector value to check if new added continent is already in list

		if (x.compare(continents.at(v)) == 0) {

			alreadyIn = true;
			break;

		}

	}

	if (alreadyIn == false) {

		adjC[u].push_back(continents.at(v));
		adjC[v].push_back(continents.at(u));
	}

}



// prints all of the countries with their adjecent nodes.

void Risk_map::printGraph(vector<Country>& C, int length) {
	for (int v = 0; v < length; v++)  //loop over the adj vector
	{
		cout << "\n number is :" << v;
		cout << "\n Adjacency list of country "
			<< C.at(v).name << " continent is " << C.at(v).continent << "\n head ";
		for (auto x : adj[v]) {  // loop inside vector value (countries)
			cout << "-> " << x.name;
			countriesList.at(v)->addNeighboor(countriesList.at(x.id));
		}
	}
	printf("\n");

}



void Risk_map::printGraphContinent(vector<string>& continents, int length) {
	for (int v = 0; v< length; v++)  //loop over the adj vector
	{
		cout << "\n number is :" << v;
		cout << "\n Adjacency list of country "
			<< continents.at(v) << "\n head ";
		for (auto x : adjC[v])  // loop inside each vector value (countries)
			cout << "-> " << x;
		printf("\n");

	}
}


void Risk_map::DFSUtil(int v, vector<int>& visited, vector<Country>& C, vector<string>& continents, int len, int contLen) {


	visited.at(v) = 1;   // marks node as visted
	cout << C.at(v).name << " ->  ";



	cout << Connected << "   " << len - 1 << "  ";

	if (Connected == len - 1) {
		cout << " GRAPH IS CONNECTED  \n";              //checks if all countries have been traversed
	}
	else {
		cout << "GRAPH IS not CONNECTED  and map is invalid \n";
	}

	int  lineContinentNum = 0;

	for (int k = 0; k < contLen; k++) { // finds index of continent 

		if (continents.at(k).compare(C.at(v).continent) == 0) {

			lineContinentNum = k;

		}
	}




	int i = 0;
	for (auto x : adj[v]) {

		//loops inside node to look for new edges
		if (x.continent.compare(C.at(v).continent) != 0) {

			for (int l = 0; l < contLen; l++) {

				if (continents.at(l).compare(x.continent) == 0) {


					this->addEdgeC(lineContinentNum, l, continents);

				}
			}
		}

		i = x.id;
		if (visited.at(i) != 1) {
			Connected++;
			DFSUtil(i, visited, C, continents, len, contLen);

		}


	}

}


void Risk_map::DFS(int v, vector<Country>& C, vector<string>& continents, int len, int  contLen) {

	cout << "\nGOT HERE\n";
	vector<int> visited;             //creates an array of int [0,1] to check if node is visited
	for (int i = 0; i < len; i++) {
		visited.push_back(0);

	}


	DFSUtil(v, visited, C, continents, len, contLen);

	if (Connected != len - 1) {
		cerr << "MAP IS INVALID";
		exit(1);
	}
}

Country Risk_map::accessGraph(int u, int v) {
	return adj.at(u).at(v);
}

void Risk_map::addCountry(int idc, string namec, string continentc) {
	countriesList.push_back(new Country(idc, namec, continentc));
}

void Risk_map::printCountriesList() {
	for (size_t i = 0; i < countriesList.size(); ++i)
		cout << countriesList.at(i)->name << "\n";
}


Country* Risk_map::getCountry(int u) {
	return countriesList.at(u);
}


//THE LOADER FUNCTION
Risk_map Map_Loader::loadMap(ifstream &infile) {

	string line;

	if (!infile) {                   //checks if file exists
		cerr << "Unable to open file datafile.txt";
		exit(1);   // call system to stop
	}



	// GET NUMBER OF CONTINENTS O(n)
	int linecount = 0;
	int nbOfContinents = 0;
	int tempC = 0;
	int num = 0;
	bool b = false;

	//list of strings to look for 
	string s3 = "[Territories]";
	string s2 = "[Continents]";
	string delimiter = "=";
	string delimiter1 = ",";
	string snum = "";


	while (getline(infile, line)) {

		if (b == true) {

			snum = line.substr(line.find(delimiter) + 1);	 //looks for 


			try {  // exception if line becomes blank it means we reached the end of continents list

				num = stoi(snum);

			}
			catch (std::invalid_argument e) {

				break;

			}
			nbOfContinents = linecount - tempC;		// computes difference between lines to get nb of continents	
		}

		if (line.find(s2) != string::npos) {   //looks for key word at specific line to start counting

			tempC = linecount;
			b = true;

		}
		linecount++;
	}

	cout << "\n number of continents is =  " << nbOfContinents << "\n";

	if (nbOfContinents<1) {                   //checks if AP IS VALID
		cerr << "INVALID MAP";
		exit(1);   // call system to stop
	}

	if (num >0) {


	}

	// GET NUMBER OF COUNTRIES O(n)

	b = false;
	int nbOfCountries = 0;

	while (getline(infile, line)) {

		if (b == true) {

			snum = line.substr(line.find(delimiter1) + 1);

			try {

				num = stoi(snum);
				nbOfCountries++;

			}
			catch (std::invalid_argument e) {
			}
		}

		if (line.find(s3) != string::npos) {

			b = true; //look for country key word, then set to true, to keep track of the line count

		}
	}

	cout << "\n number of countries is =  " << nbOfCountries << "\n";


	if (nbOfCountries<1) {                   //checks if MAP IS VALID
		cerr << "INVALID MAP";
		exit(1);   // call system to stop
	}



	Risk_map mapload(nbOfCountries, nbOfContinents);




	infile.clear();
	infile.seekg(0, ios::beg);



	if (num >0) {


	}

	// LOAD THE MAP WITH ITS EDGES 
	//FIRST LOAD CONTINENTS AND CONTRIES INTO ARRAYS


	vector<Country> countriesList;
	vector<string> continentsList;

	b = false;
	bool b1 = false;
	int count = 0;



	while (getline(infile, line)) {


		if (b == true) {

			string nameOfcontinent = line.substr(0, line.find(delimiter)); //same thing as for for the continents but looking for country keyowrd
			snum = line.substr(line.find(delimiter) + 1);

			try {

				num = stoi(snum);
				continentsList.push_back(nameOfcontinent);
				count++;



			}
			catch (std::invalid_argument e) {
				b = false;
				cout << "\n\n";
				count = 0;


			}
		}

		if (b1 == true) {

			string nameOfcountry = line.substr(0, line.find(delimiter1));
			string snum = line.substr(line.find(delimiter1) + 1);

			try {


				num = stoi(snum);
				countriesList.emplace_back(count, nameOfcountry, " ");
				mapload.addCountry(count, nameOfcountry, " ");
				count++;



			}
			catch (std::invalid_argument e) {


				if (count >= nbOfCountries) {
					break;

				}


			}
		}

		if (line.find(s2) != string::npos) {

			b = true;

		}

		if (line.find(s3) != string::npos) {

			b1 = true;

		}
	}


	infile.clear();
	infile.seekg(0, ios::beg);



	b = false;
	b1 = false;
	count = 0;
	size_t pos = 0;

	while (getline(infile, line)) {

		size_t endpos = line.find_last_not_of(" \t\r\n");  //strips line of blank spaces to make it easier to parse
		if (string::npos != endpos)
			line = line.substr(0, endpos + 1);

		size_t startpos = line.find_first_not_of(" \t\r\n");
		if (string::npos != startpos)
			line = line.substr(startpos);


		if (b1 == true) {

			string snum = line.substr(line.find(delimiter1) + 1);

			try {

				num = stoi(snum);

				for (int i = 0; i<3; i++) {                          // deletes the 1st 3 elements in line
					line.erase(0, line.find(delimiter1) + 1);
				}


				countriesList.at(count).continent = line.substr(0, line.find(delimiter1));
				line.erase(0, line.find(delimiter1) + 1);

				while ((pos = line.find(delimiter1)) != string::npos) {  //loops over elements in line to add them as edges

					string token = line.substr(0, pos);
					line.erase(0, pos + 1);

					for (int i = 0; i < nbOfCountries; i++) { //maps the current sting to an actual country object

						if (countriesList.at(i).name.compare(token) == 0) {

							mapload.addEdge(count, i, countriesList);        //then adds it to the coutry graph

						}

						if (countriesList.at(i).name.compare(line) == 0) {

							mapload.addEdge(count, i, countriesList);  //makes sure it gets last element of line


						}

					}


					int  lineContinentNum = 0;

					for (int k = 0; k < nbOfContinents; k++) {

						if (continentsList.at(k).compare(countriesList.at(count).continent) == 0) {

							lineContinentNum = k;

						}
					}




					for (int i = 0; i < nbOfCountries; i++) { //Loads continets into adjency list or connected graph (not necessary as it is done in the traversal)

						if ((countriesList.at(i).name.compare(token) == 0 || countriesList.at(i).name.compare(token) == 0) && countriesList.at(i).continent.compare(countriesList.at(count).continent) != 0) {

							for (int l = 0; l < nbOfContinents; l++) {

								if (continentsList.at(l).compare(countriesList.at(i).continent) == 0) {


									mapload.addEdgeC(lineContinentNum, l, continentsList);

								}

							}

						}

					}

				}


				count++;



			}
			catch (std::invalid_argument e) {

				if (count >= 42) {
					break;
				}

			}
		}

		if (line.find(s3) != string::npos) {

			b1 = true;

		}

	}



	mapload.printGraph(countriesList, nbOfCountries);

	cout << "\n\n 4th PART DONE (LOADED COUNTRIES IN GRAPH ADT) O(n**2)  \n\n";

	mapload.printGraphContinent(continentsList, nbOfContinents);

	cout << "\n\n 4th PART DONE (LOADED CONTINENTS IN SUBGRAPH ADT) O(n**2)  \n\n";
	//		
	mapload.DFS(1, countriesList, continentsList, nbOfCountries, nbOfContinents);

	mapload.sizeOfMap = nbOfCountries;

	return mapload;

}

string selectMap() {




	string path = "C:\\Users\\mar_past\\source\\repos\\Project2\\Project2\\maps";
	for (auto & p : fs::directory_iterator(path)) {
		
		cout << p << "\n" ;
		string path_string = p.path().string();
	

	};


	cout << "SELECT MAP (enter name)\n"; //lets user choose what map files he wants to load
	string name;
	cin >> name;

	cout << "YOU HAVE SELECTED " << name  << "\n";

	stringstream ss;
	ss << "C:\\Users\\mar_past\\source\\repos\\Project2\\Project2\\maps\\" << name;    // builds a string containing the path
	string mapPath = ss.str();

	return mapPath;




}


vector<Player> selectPLayers() {


	vector<Player> playervec;

	cout << "\nSELECT NUMBER OF PLAYERS (enter number)\n"; //lets user choose what map files he wants to load
	int nb;
	cin >> nb;

	for (int i = 0; i< nb; i++)
		playervec.emplace_back();


	cout << "YOU HAVE SELECTED " << nb << " PLAYERS\n\n";

	return playervec;
}

// Driver code
int main()
{


	cout << "################################################## PART I GAME Initializer #######################################################\n";

	string filepath = selectMap(); // lets you select the map from specific dir

	
	ifstream dinfile(filepath); //opens an instream with our map we chose

	Map_Loader maploader1; // creates the maploader facility

	Risk_map risk_map = maploader1.loadMap(dinfile); //calls map loader which will initialize the map and print all its information

	vector<Player> playervec = selectPLayers(); //vectors of player is created
	Deck deck(risk_map.sizeOfMap);    // deck with the valid amount of cards is created

	int playervecSize = playervec.size();

	for (int i = 0; i < playervecSize; i++) {

		playervec.at(i).addCountry(risk_map.accessGraph(i, 0)); // assigns random country to player
		cout << "Name of main country of player nb " << i << " is " << playervec.at(i).get1stCountryName() << "\n";
	}
	cout << "\nNumber of cards in deck is " << deck.getSize() << "\n";


	cout << "\n\nPRINTING VECTOR OF COUNTRIES FROM MAP\n";
	risk_map.printCountriesList();


	cout << "\n\nPRINTING NEIGHBOORS OF RANDOM COUNTRY\n";
	risk_map.getCountry(10)->printNeighboors();
	system("pause");
	return 0;
}