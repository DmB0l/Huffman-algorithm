#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <map>
#include <string>
#include <list>
#include <vector>
#include <fstream>
#include <ctime>
#include <unordered_map>

using namespace std;

/**
\brief the nood class is intended for implementing a tree
*/

struct node
{
private:
	int val; 
	char symbol;
	node* left;
	node* right;
public:
	/**
	simple constructor
	*/
	node()
	{
		left = NULL;
		right = NULL;
	}

	/**
	constructor that accepts 2 nodes as input: left and right
	*/
	node(node* L, node* R)
	{
		left = L;
		right = R;
		val = L->val + R->val;
	}

	/**
	changes the symbol in the node
	accepts a character as input
	*/
	
	void set_symbol(char c)
	{
		symbol = c;
	}

	/**
	changes the val in the node
	accepts a integer value as input
	*/
	void set_val(int a)
	{
		val = a;
	}

	/**
	get the val from the node
	*/
	int get_val()
	{
		return val;
	}

	/**
	get the symbol from the node
	*/
	char get_symbol()
	{
		return symbol;
	}

	/**
	returns a reference to the left son
	*/
	node* get_left()
	{
		return left;
	}

	/**
	returns a reference to the right son
	*/
	node* get_right()
	{
		return right;
	}
};

/**
\brief structure for comparing elements of the node class
*/

struct MyCompare
{
/**
returns true if the val value in the right node is greater than in the left node
*/

	bool operator()(node* L, node* R) const
	{
		return L->get_val() < R->get_val();
	}
};

/**
\brief class that implements the Huffman algorithm
*/


class huffman
{
private:
	map<char, int> cymbol_val;
	map<char, vector<bool>> table;
	list<node*> tree;
	int counter_of_symbols;
	string name_file;
public:
	/**
	reading information about how many times a particular symbol was encountered
	creating a list of primary elements
	creating a tree
	creating a Huffman code associativity table with a symbol,
	@param1 takes the name of the input file as input
	*/

	huffman(string file_name);
	/**
	delete a tree
	*/

	~huffman();
	/**
	a recursive function that builds a symbol associativity table with Huffman code takes a search tree and a bool vector as input
	*/

	void create_table(node* head, vector<bool>& code); 

	/**
	the function encoding the file takes the input name of the input file and the name of the output file
	*/

	void code_f(string in_file_name, string out_file_name);
	/**
	the function that decodes the file takes the name of the input file and the name of the output file as input
	*/

	void decod_f(string in_file_name, string out_file_name);


};

