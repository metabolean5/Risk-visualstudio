#pragma once
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <fstream>
#include <iterator>
#include <algorithm> 
#include <cctype>
#include <locale>

using namespace std;

//Country class constructor, will be the nodes of the Risk_map graph below
class Country
{
private:
	vector<Country*> neighboors;
public:
	int id;
	string name;
	string continent;
	Country(int idc, string namec, string continentc) : id(idc), name(namec), continent(continentc) {};
	Country(string namec) : name(namec) {};
	void addNeighboor(Country* c);
	void printNeighboors();
};




//Map graph constructor, implemented as an adjency list
class Risk_map
{


private:
	vector<vector<Country>> adj;
	vector<vector<string>> adjC;
	vector<Country*> countriesList;

public:

	void addEdge(int u, int v, vector<Country>& C);
	void printGraph(vector<Country>& C, int length);
	void addEdgeC(int u, int v, vector<string>& continents);
	void printGraphContinent(vector<string>& continents, int length);
	Risk_map(int size, int sizeC) : adj(size), adjC(sizeC) {};
	void DFS(int v, vector<Country>& C, vector<string>& continents, int len, int contLen);
	void DFSUtil(int v, vector<int>& visited, vector<Country>& C, vector<string>& continents, int len, int contLen);
	Country accessGraph(int u, int v);
	void addCountry(int idc, string namec, string continentc);
	void printCountriesList();
	Country* getCountry(int u);


	int Connected = 0;
	int sizeOfMap = 1;


};



class Map_Loader
{

public:
	Risk_map loadMap(ifstream &infile);

};
