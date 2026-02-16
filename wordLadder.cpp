/*
 * Name: Stephen Samuelson
 * Date Submitted: 5/6/24
 * Lab Section: 4
 * Assignment Name: wordLadder.cpp
 */

#include <iostream>
#include <fstream>
#include <utility>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <cassert>
#include <algorithm>

#include <map>

using namespace std;

//State holds string data type
typedef string state;


vector<string> V; //words from wordlist05.txt

//Unordered_set stringSet for hashing
unordered_set<string> stringSet;

//Maps for breadth first search
map<state, bool> visited;
unordered_map<state, state> pred;
unordered_map<state, int> dist;
unordered_map<state, vector<state>> nbrs;

//Global variables for bfs distance, bfs predecessor, and neighboring nodes
//Should be unordered_map type

//Function populateVector reads from a file and populates vector V
void populateVector() {

	//String input stores the words from file wordlist05.txt
	string input;

	//Fstream file to open the file
	fstream file;
	file.open("wordlist05.txt");

	//If the file opened correctly, get each line and store it in vector V
	if (file.is_open()) {
		while (getline(file, input)) {
			V.push_back(input);
		}
	}

	//Add each string to stringSet
	for (auto i : V) {
		stringSet.insert(i);
	}
}

//Implement breadth-first search, refer to Lab 10
void search(state source_node) {
	queue<state> to_visit;
	to_visit.push(source_node);
	visited[source_node] = true;
	dist[source_node] = 0;

	while (!to_visit.empty()) {
		state curnode = to_visit.front();
		to_visit.pop();
		for (state n : nbrs[curnode])
			if (!visited[n]) {
				pred[n] = curnode;
				dist[n] = 1 + dist[curnode];
				visited[n] = true;
				to_visit.push(n);
			}
	}
}

void wordLadder(string s, string t, int &steps, vector<string> &p)
{
	//Call functions to populate the vector V and store each string at their hashed index in hashedV
	populateVector();

	//State key is initialized to parameter s
	state key = s;

	//State start stores the starting word
	state start = s;

	//Loop through size of vector
	for (int h = 0; h < V.size(); ++h) {

		//Key equals current string at h
		key = V[h];

		//Loop through each letter in key
		for (int i = 0; i < key.size(); ++i) {

			//Key equals current string at h
			key = V[h];

			//Loop through each letter in the alphabet
			for (char c = 'a'; c <= 'z'; ++c) {

				//Set the current letter in key to c
				key[i] = c;

				//If the key is found in stringSet and key does not equal current word at h
				if (stringSet.find(key) != stringSet.end() && key != V[h]) {

					//Add key to current string in V
					nbrs[V[h]].push_back(key);
				}
			}
		}
	}

	//Call function search passing start node
	search(s);

	//Set steps to the total distance
	steps = dist[t];

	//Clear vector p
	p.clear();

	//push target to p
	p.push_back(t);

	//Set key equal to target
	key = t;

	//While key does not equal start and steps is greater than 0
	while (key != s && steps > 0) {

		//Set key to pred
		key = pred[key];

		//Push back key into vector p
		p.push_back(key);
	}

	//Reverse vector p
	reverse(p.begin(), p.end());
}

/*
int main()
{

	int steps=0;
	vector<string> path;

	wordLadder("stale", "tales", steps, path);

	cout << steps;
	cout << "\n";

	for (int i = 0; i < path.size(); ++i) {
		cout << path[i] << "\n";
	}

	//ASSERT_EQ(steps,8);
	if (steps != 8)
	{
		std::cout << "stale->tales: expected/correct value for steps is 8, actual value when testing " << steps << ".\n";
		return 1;
	}

	std::cout << "Passed" << endl;
}*/
