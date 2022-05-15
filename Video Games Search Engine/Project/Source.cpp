#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include "custom.h"

class GameAVLNode;
static GameAVLNode* tempRoot = NULL;

using namespace std;

bool AVLlists::IsEmpty()
{
	return (start == NULL);
}

void AVLlists::Insert(GameAVLNode* node)
{
	AVLlistsNode* newnode = new AVLlistsNode();         //A pointer of type GameAVLNode created dynamically at run time
	newnode->addressOfGame = node;                      //Data value assigned
	if (IsEmpty() == true)
	{
		start = newnode;                            //start and end pointers updated
		last = newnode;
		total++;
	}
	else
	{
		last->next = newnode;
		last = newnode;
		total++;
	}
}

void AVLlists::print()      //function which prints the whole list
{
	if (IsEmpty() == false)       //Checks if the list is empty or not
	{
		AVLlistsNode* temp = start;   //Temporary pointer created which stores the address of the node to be printed
		while (temp != NULL)      //Checks if the temp pointer is not NULL. NULL indicates the end of the list
		{
			GameAVLNode* current = temp->addressOfGame;			//Prints data element
			cout << current->data.title << endl;
			temp = temp->next;                                //Advances temp pointer
		}
		cout << endl << endl;
	}
	else
		cout << "List is empty." << endl << endl;
}

int SalesTree::height(SalesAVLNode* node)   //dual, will be used for prices aswell.
{
	if (node == NULL)     //if node is a leaf node
		return -1;
	else
	{
		int lDepth = height(node->left);		//compute the height of each subtree
		int rDepth = height(node->right);

		if (lDepth > rDepth)                    //height of a tree is one more than max of its two subtrees
			return(lDepth + 1);
		else return(rDepth + 1);
	}
}

int SalesTree::getBalance(SalesAVLNode* node)
{
	if (node == NULL)
		return 0;
	else
		return height(node->left) - height(node->right);  //balance factor is the difference between two subtree heights
}

SalesAVLNode* SalesTree::rrotation(SalesAVLNode* node)
{
	SalesAVLNode* temp = node->left;                       //performing right rotation
	node->left = temp->right;
	temp->right = node;
	node->height = max(height(node->left), height(node->right)) + 1;  //updating height of node
	temp->height = max(height(node->left), node->height) + 1;
	return temp;
}

SalesAVLNode* SalesTree::lrotation(SalesAVLNode* node)
{
	SalesAVLNode* temp = node->right;                   //performing left rotation
	node->right = temp->left;
	temp->left = node;
	node->height = max(height(node->left), height(node->right)) + 1;  //updating height of node
	temp->height = max(height(node->right), node->height) + 1;
	return temp;
}

SalesAVLNode* SalesTree::lrrotation(SalesAVLNode* node)    //left right rotation
{
	node->left = lrotation(node->left);  //left rotation on subchild of unbalanced node
	return rrotation(node);              //right rotation unbalanced node
}

SalesAVLNode* SalesTree::rlrotation(SalesAVLNode* node)         //right left rotation
{
	node->right = rrotation(node->right);  //right rotation on subchild of unbalanced node
	return lrotation(node);					//left rotation unbalanced node
}

SalesAVLNode* SalesTree::Findmin(SalesAVLNode* node)        //traversing to the left most node
{                                     //left most node contains smallest node
	if (node == NULL)
		return NULL;
	else if (node->left == NULL)
		return node;
	else
		return Findmin(node->left);
}

SalesAVLNode* SalesTree::Findmax(SalesAVLNode* node)     //traversing to the right most node
{								   //right most node contains largest node
	if (node == NULL)
		return NULL;
	else if (node->right == NULL)
		return node;
	else
		return Findmax(node->right);
}

SalesAVLNode* SalesTree::insert(float a, SalesAVLNode* root)   //inserts value in the node
{
	if (root == NULL)                            //node always inserted as a leaf node
	{
		SalesAVLNode* newnode = new SalesAVLNode();         //creating a new node dynamically
		newnode->data = a;                          //setting values
		newnode->height = 0;
		newnode->left = NULL;
		newnode->right = NULL;
		root = newnode;
		temporary = newnode;
	}
	else if (a < root->data)            //if inserted id is greater than node id
	{
		root->left = insert(a, root->left);      //recursive call
		if (getBalance(root) == 2)                  //checking balance factor
		{
			if (a < root->left->data)
				root = rrotation(root);
			else
				root = lrrotation(root);
		}
	}
	else if (a > root->data)							//if inserted id is larger than node id
	{
		root->right = insert(a, root->right);     //recursive call
		if (getBalance(root) == -2)                  //getting balance factor
		{
			if (a > root->right->data)
				root = lrotation(root);
			else
				root = rlrotation(root);
		}
	}

	root->height = max(height(root->left), height(root->right)) + 1;  //updating height of the inserted node
	return root;
}

void SalesTree::InOrder(SalesAVLNode* root)
{
	if (root != NULL)
	{
		InOrder(root->left);
		cout << "\x1b[32mScore: " << root->data << endl;
		InOrder(root->right);
	}
}

void SalesTree::PreOrder(SalesAVLNode* root)
{
	if (root != NULL)
	{
		cout << "\x1b[32mScore: " << root->data << endl;
		PreOrder(root->left);
		PreOrder(root->right);
	}
}

SalesAVLNode* SalesTree::SalesAddress(float a)  //returns the address
{
	SalesAVLNode* loc = root;   //loc initialized to root
	SalesAVLNode* ploc = NULL;  //ploc initialized to null
	if (root != NULL)      //searches only if tree is not empty
	{
		while (loc != NULL && a != loc->data)
		{
			if (a < loc->data)   //if value is less than data of node
			{
				ploc = loc;          //ploc advanced to loc
				loc = loc->left;   //loc advancedd to the left child
			}
			else
			{
				ploc = loc;			//ploc advanced to loc
				loc = loc->right;  //loc advancedd to the right child
			}
		}
		if (loc == NULL)
		{
			root = insert(a, root);
			return temporary;
		}
		else
			return loc;
	}
	else
	{
		root = insert(a, root);
		return temporary;
	}
}

bool GameTree::IsEmpty()        //Checks if list is empty or not. Returns a boolean value
{
	if (root == NULL)            //If start pointer doesn't contain any address, returns true
		return true;              //True indicates that the list is empty
	else                          //Else return false meaning list is not empty
		return false;
}



void GameTree::parser(PublisherList& p1, ReviewScoreTree& score1, SalesTree& sales, SalesTree& prices, GenreGraph& graph)
{
	fstream data("E:/video_games.csv", ios::in);        //opening our main file
	string line;
	vector <string> result;
	vector<vector<string>> content;
	string cell;
	while (getline(data, line))                    //reads a row from a file at a time
	{
		result.clear();
		stringstream linestream(line);
		while (getline(linestream, cell, ','))
		{
			result.push_back(cell);
		}
		content.push_back(result);
	}
	for (int i = 1; i < content.size(); i++)
	{
		Genrelist* genrelist = new Genrelist;
		Game* data = new Game();
		data->title = content[i][0];
		data->maxplayers = stoi(content[i][1]);
		genrelist->insert(content[i][2]);
		data->genre = genrelist->head;
		data->publisher = p1.PublisherAddress(content[i][3]);           //stores the address of the publisher node present in publisher list
		data->review_score = score1.ScoreAddress(stoi(content[i][4]));  //stores the address of the node present in score avl tree. 
		data->sales = sales.SalesAddress(stof(content[i][5]));          //stores the address of the node present in sales tree
		data->price = prices.SalesAddress(stof(content[i][6]));			//stores the address of the node present in prices tree
		data->console = content[i][7];
		data->rating = (content[i][8])[0];
		data->release_year = stoi(content[i][9]);
		data->playtime_average = stof(content[i][10]);
		data->playtime_leisure = stof(content[i][11]);
		data->playtime_median = stof(content[i][12]);
		data->playtime_rushed = stof(content[i][13]);
		data->playtime_comp_avg = stof(content[i][14]);
		data->playtime_comp_leisure = stof(content[i][15]);
		data->playtime_comp_median = stof(content[i][16]);
		data->playtime_comp_rushed = stof(content[i][17]);
		data->playtime_total_avg = stof(content[i][18]);
		data->playtime_total_leisure = stof(content[i][19]);
		data->playtime_total_median = stof(content[i][20]);
		data->playtime_total_rushed = stof(content[i][21]);
		data->playtime_main_avg = stof(content[i][22]);
		data->playtime_main_leisure = stof(content[i][23]);
		data->playtime_main_median = stof(content[i][24]);
		data->playtime_main_rushed = stof(content[i][25]);
		root = insert(data, root);                             //insertion in our main Game AVL tree 
		GameAVLNode* pointer = tempRoot;                       //stores address of the node which is added in the AVL tree
		data->publisher->games.Insert(pointer);             
		(data->review_score)->gamesScore.Insert(pointer);
		(data->sales)->list.Insert(pointer);
		(data->price)->list.Insert(pointer);
		graph.addgame(pointer);        //adding node to graph.
		graph.checkgenre(pointer, root);
	}
}

int GameTree::height(GameAVLNode* node)
{
	if (node == NULL)     //if node is a leaf node
		return -1;
	else
	{
		int lDepth = height(node->left);		//compute the height of each subtree
		int rDepth = height(node->right);

		if (lDepth > rDepth)                    //height of a tree is one more than max of its two subtrees
			return(lDepth + 1);
		else return(rDepth + 1);
	}
}

int GameTree::getBalance(GameAVLNode* node)
{
	if (node == NULL)
		return 0;
	else
		return height(node->left) - height(node->right);
}

GameAVLNode* GameTree::rrotation(GameAVLNode* node)
{
	GameAVLNode* temp = node->left;                       //performing right rotation
	node->left = temp->right;
	temp->right = node;
	node->height = max(height(node->left), height(node->right)) + 1;  //updating height of node
	temp->height = max(height(node->left), node->height) + 1;
	return temp;
}

GameAVLNode* GameTree::lrotation(GameAVLNode* node)
{
	GameAVLNode* temp = node->right;                   //performing left rotation
	node->right = temp->left;
	temp->left = node;
	node->height = max(height(node->left), height(node->right)) + 1;  //updating height of node
	temp->height = max(height(node->right), node->height) + 1;
	return temp;
}

GameAVLNode* GameTree::lrrotation(GameAVLNode* node)    //left right rotation
{
	node->left = lrotation(node->left);  //left rotation on subchild of unbalanced node
	return rrotation(node);              //right rotation unbalanced node
}

GameAVLNode* GameTree::rlrotation(GameAVLNode* node)         //right left rotation
{
	node->right = rrotation(node->right);  //right rotation on subchild of unbalanced node
	return lrotation(node);					//left rotation unbalanced node
}

GameAVLNode* GameTree::insert(Game* d, GameAVLNode* root) { //inserts value in the node

	if (root == NULL)                            //node always inserted as a leaf node
	{
		GameAVLNode* newnode = new GameAVLNode();         //creating a new node dynamically
		newnode->data = *d;                   //setting values
		newnode->height = 0;
		newnode->left = NULL;
		newnode->right = NULL;
		root = newnode;
		tempRoot = root;
	}
	else if (d->title < root->data.title)            //if inserted id is greater than node id
	{
		root->left = insert(d, root->left);      //recursive call
		if (getBalance(root) == 2)                  //checking balance factor
		{
			if (d->title < root->left->data.title)
				root = rrotation(root);
			else
				root = lrrotation(root);
		}
	}
	else if (d->title > root->data.title)							//if inserted id is larger than node id
	{
		root->right = insert(d, root->right);     //recursive call
		if (getBalance(root) == -2)                  //getting balance factor
		{
			if (d->title > root->right->data.title)
				root = lrotation(root);
			else
				root = rlrotation(root);
		}
	}

	root->height = max(height(root->left), height(root->right)) + 1;  //updating height of the inserted node
	return root;
}

GameAVLNode* GameTree::search(string n) {    //simple search function to return address of game node if found, if not then null
	loc = root;
	ploc = NULL;
	if (!IsEmpty()) {
		while (loc != NULL && loc->data.title != n) {
			if (n < loc->data.title) {
				ploc = loc;
				loc = loc->left;
			}
			else if (n > loc->data.title) {
				ploc = loc;
				loc = loc->right;
			}
		}
		if (loc == NULL) {
			return NULL;
		}
		else return loc;
	}
}

void GameTree::InOrder(GameAVLNode* root)
{
	if (root != NULL)
	{
		InOrder(root->left);
		root->printNode();
		cout << endl;
		InOrder(root->right);
	}
}

bool PublisherList::PublisherSearch(string a)
{
	loc_P = pstart;                       //Assigning Loc pointer with the address of the starting node
	ploc_P = NULL;                    //Assigning PredLoc pointer with NULL
	if (P_IsEmpty() == true)              //Checking if the list is empty or not
		return false;
	else
	{
		while (loc_P != NULL && loc_P->name != a)    //Loop until the Loc pointer is not NULL and value not found
		{
			ploc_P = loc_P;                          //Assigning the address stored in Loc into PredLoc
			loc_P = loc_P->next;
		}

		if (loc_P == NULL)
			return false;
		else
			return true;
	}

}

PublisherNode* PublisherList::PublisherAddress(string a)               //returns the address of the publisher node. This is present in publisher list
{

	bool found;
	found = PublisherSearch(a);
	if (found == true)
	{
		return loc_P;
	}
	else
	{
		PublisherNode* newnode = new PublisherNode();     //A pinter of type ListNode created dynamically at run time
		newnode->name = a;								  //Data value assigned
		if (P_IsEmpty() == true)
		{
			pstart = newnode;                            //start and end pointers updated
			plast = newnode;
		}
		else
		{
			plast->next = newnode;
			plast = newnode;
		}
		return plast;
	}
}

void PublisherList::printing()      //function which prints the whole list
{
	if (P_IsEmpty() == false)       //Checks if the list is empty or not
	{
		PublisherNode* temp = pstart;   //Temporary pointer created which stores the address of the node to be printed
		while (temp != NULL)      //Checks if the temp pointer is not NULL. NULL indicates the end of the list
		{
			cout << temp->name << endl;   //Prints data element
			temp = temp->next;                                //Advances temp pointer
		}
		cout << endl << endl;
	}
	else
		cout << "List is empty" << endl << endl;
}

void PublisherList::PrintRecord(string name)                    //prints record of a particular publisher
{
	bool found = PublisherSearch(name);                        //searches a publisher publisher whether it exists or not. Returns address if exists
	if (found == false)
		cout << "Publisher not found\n\n";
	else
	{
		cout << "\n\nGames published by " << name << " are: \n\n";
		AVLlistsNode* temp = loc_P->games.start;
		int count = 0;
		while (temp != NULL) {
			count++;
			cout << count << ": " << temp->addressOfGame->data.title << endl;
			temp = temp->next;
		}
	}
	cout << endl << endl;
}

int PublisherList::countpublishers() {
	int count = 0;
	loc_P = pstart;
	while (loc_P != NULL) {
		count++;
		loc_P = loc_P->next;
	}
	return count;
}

float PublisherList::avgcost(string pub) {
	float total = 0;
	bool found = PublisherSearch(pub);
	if (found == true) {
		AVLlistsNode* temp = loc_P->games.start;
		GameAVLNode* temp2 = new GameAVLNode();
		while (temp != NULL) {
			temp2 = temp->addressOfGame;
			total += temp2->data.price->data;
			temp = temp->next;
		}
		total = total / loc_P->games.total;
		cout << "Average cost of games by this publisher is: " << total << endl;
		return total;
	}
	else {
		cout << "Publisher not found." << endl;
		return 0;
	}
}

float PublisherList::avgrating(string pub) {  //returns the average rating of all the games of said publisher. 
	float total = 0;
	bool found = PublisherSearch(pub);
	if (found == true) {
		AVLlistsNode* temp = loc_P->games.start;
		GameAVLNode* temp2 = new GameAVLNode();
		while (temp != NULL) {
			temp2 = temp->addressOfGame;
			total += temp2->data.review_score->score;
			temp = temp->next;
		}
		total = total / loc_P->games.total;
		cout << "Average rating of games by " << pub << " is: " << total << endl;
		return total;
	}
	else {
		cout << "Publisher not found. " << endl;
		return 0;
	}
}

void PublisherList::bestpublisher() {
	float highest = 0;
	float current = 0;
	PublisherNode* temp = pstart;
	PublisherNode* best = new PublisherNode();

	int count = countpublishers();
	for (int i = 0; i < count; i++) {
		current = avgrating(temp->name);
		if (current > highest) {
			highest = current;
			best = temp;
		}
		if (temp->next != NULL) {
			temp = temp->next;
		}
	}
	cout << "\n\n The best publisher is: " << temp->name << " With an average game rating of: " << highest << endl;

}

int ReviewScoreTree::height(ScoreAVLNode* node)
{
	if (node == NULL)     //if node is a leaf node
		return -1;
	else
	{
		int lDepth = height(node->left);		//compute the height of each subtree
		int rDepth = height(node->right);

		if (lDepth > rDepth)                    //height of a tree is one more than max of its two subtrees
			return(lDepth + 1);
		else return(rDepth + 1);
	}
}

int ReviewScoreTree::getBalance(ScoreAVLNode* node)
{
	if (node == NULL)
		return 0;
	else
		return height(node->left) - height(node->right);  //balance factor is the difference between two subtree heights
}

ScoreAVLNode* ReviewScoreTree::rrotation(ScoreAVLNode* node)
{
	ScoreAVLNode* temp = node->left;                       //performing right rotation
	node->left = temp->right;
	temp->right = node;
	node->height = max(height(node->left), height(node->right)) + 1;  //updating height of node
	temp->height = max(height(node->left), node->height) + 1;
	return temp;
}

ScoreAVLNode* ReviewScoreTree::lrotation(ScoreAVLNode* node)
{
	ScoreAVLNode* temp = node->right;                   //performing left rotation
	node->right = temp->left;
	temp->left = node;
	node->height = max(height(node->left), height(node->right)) + 1;  //updating height of node
	temp->height = max(height(node->right), node->height) + 1;
	return temp;
}

ScoreAVLNode* ReviewScoreTree::lrrotation(ScoreAVLNode* node)    //left right rotation
{
	node->left = lrotation(node->left);  //left rotation on subchild of unbalanced node
	return rrotation(node);              //right rotation unbalanced node
}

ScoreAVLNode* ReviewScoreTree::rlrotation(ScoreAVLNode* node)         //right left rotation
{
	node->right = rrotation(node->right);  //right rotation on subchild of unbalanced node
	return lrotation(node);					//left rotation unbalanced node
}

ScoreAVLNode* ReviewScoreTree::Findmin(ScoreAVLNode* node)        //traversing to the left most node
{                                     //left most node contains smallest node
	if (node == NULL)
		return NULL;
	else if (node->left == NULL)
		return node;
	else
		return Findmin(node->left);
}

ScoreAVLNode* ReviewScoreTree::Findmax(ScoreAVLNode* node)     //traversing to the right most node
{								   //right most node contains largest node
	if (node == NULL)
		return NULL;
	else if (node->right == NULL)
		return node;
	else
		return Findmax(node->right);
}

ScoreAVLNode* ReviewScoreTree::insert(int a, ScoreAVLNode* root)   //inserts value in the node
{
	if (root == NULL)                            //node always inserted as a leaf node
	{
		ScoreAVLNode* newnode = new ScoreAVLNode();         //creating a new node dynamically
		newnode->score = a;                   //setting values
		newnode->height = 0;
		newnode->left = NULL;
		newnode->right = NULL;
		root = newnode;
		p = newnode;
	}
	else if (a < root->score)            //if inserted id is greater than node id
	{
		root->left = insert(a, root->left);      //recursive call
		if (getBalance(root) == 2)                  //checking balance factor
		{
			if (a < root->left->score)
				root = rrotation(root);
			else
				root = lrrotation(root);
		}
	}
	else if (a > root->score)							//if inserted id is larger than node id
	{
		root->right = insert(a, root->right);     //recursive call
		if (getBalance(root) == -2)                  //getting balance factor
		{
			if (a > root->right->score)
				root = lrotation(root);
			else
				root = rlrotation(root);
		}
	}

	root->height = max(height(root->left), height(root->right)) + 1;  //updating height of the inserted node
	return root;
}

void ReviewScoreTree::getbestgame() {
	ScoreAVLNode* temp = Findmax(root);
	int count = temp->gamesScore.total;
	GameAVLNode* game = new GameAVLNode();
	AVLlistsNode* temp2 = temp->gamesScore.start;
	cout << "The Game(s) with best rating of " << temp->score << " are/is:" << endl;
	for (int i = 0; i < count; i++) {
		game = temp2->addressOfGame;
		cout << i + 1 << ": " << game->data.title << endl;
		temp2 = temp2->next;
	}
}

void ReviewScoreTree::getworstgame() {
	ScoreAVLNode* temp = Findmin(root);
	int count = temp->gamesScore.total;
	GameAVLNode* game = new GameAVLNode();
	AVLlistsNode* temp2 = temp->gamesScore.start;
	cout << "The Game(s) with worst rating of " << temp->score << " are/is:" << endl;
	for (int i = 0; i < count; i++) {
		game = temp2->addressOfGame;
		cout << i + 1 << ": " << game->data.title << endl;
		temp2 = temp2->next;
	}
}
   
void ReviewScoreTree::withinrange(ScoreAVLNode* root, float val1, float val2) { //note function returns games EXCLUSIVE of input values
	GameAVLNode* temp = new GameAVLNode();
	if (root != NULL && root->score > val1 && root->score < val2) {    //check if val within range
		AVLlistsNode* temp2 = root->gamesScore.start;
		withinrange(root->left, val1, val2);            //recur left call
		while (temp2 != NULL) {
			temp = temp2->addressOfGame;
			cout << temp->data.title << endl;
			temp2 = temp2->next;
		}
		withinrange(root->right, val1, val2);   //recur call right
	}
	else if (root != NULL && root->score >= val2) {            //go left if nodes values is higher than range
		withinrange(root->left, val1, val2);
	}
	else if (root != NULL && root->score <= val1) {    //go right if nodes value is lower than range. 
		withinrange(root->right, val1, val2);
	}
}

void ReviewScoreTree::InOrder(ScoreAVLNode* root)
{
	if (root != NULL)
	{
		InOrder(root->left);
		cout << "\x1b[32mScore: " << root->score << endl;
		InOrder(root->right);
	}
}

void ReviewScoreTree::PreOrder(ScoreAVLNode* root)
{
	if (root != NULL)
	{
		cout << "\x1b[32mScore: " << root->score << endl;
		PreOrder(root->left);
		PreOrder(root->right);
	}
}

ScoreAVLNode* ReviewScoreTree::ScoreAddress(int a)
{
	ScoreAVLNode* loc = root;   //loc initialized to root
	ScoreAVLNode* ploc = NULL;  //ploc initialized to null
	if (root != NULL)      //searches only if tree is not empty
	{
		while (loc != NULL && a != loc->score)
		{
			if (a < loc->score)   //if value is less than data of node
			{
				ploc = loc;          //ploc advanced to loc
				loc = loc->left;   //loc advancedd to the left child
			}
			else
			{
				ploc = loc;			//ploc advanced to loc
				loc = loc->right;  //loc advancedd to the right child
			}
		}
		if (loc == NULL)
		{
			root = insert(a, root);
			return p;
		}
		else
			return loc;
	}
	else
	{
		root = insert(a, root);
		return p;
	}
}

void ReviewScoreTree::printScoreGames(int a)
{
	ScoreAVLNode* loc = root;   //loc initialized to root
	ScoreAVLNode* ploc = NULL;  //ploc initialized to null

	if (root != NULL) //searches only if tree is not empty
	{
		while (loc != NULL && a != loc->score)
		{

			if (a < loc->score)   //if value is less than data of node
			{
				ploc = loc;          //ploc advanced to loc
				loc = loc->left;   //loc advancedd to the left child
			}
			else
			{
				ploc = loc;			//ploc advanced to loc
				loc = loc->right;  //loc advancedd to the right child
			}
		}
		if (loc == NULL)
			cout << "\x1b[31mStudent not found in database\x1b[0m\n";
		else
		{
			cout << "Games of score " << a << " are: " << endl;
			AVLlistsNode* temp = loc->gamesScore.start;
			while (temp != NULL)
			{
				GameAVLNode* temp2 = temp->addressOfGame;
				cout << temp2->data.title << endl;
				temp = temp->next;
			}
		}
	}
	else
	{
		cout << "\x1b[31mTree is empty\x1b[0m\n\n";
	}
}

void GameTree::traversal(GameAVLNode* root, float& bestIndex, GameAVLNode*& gameaddress, int type)
{
	if (root != NULL)
	{
		if (type == 0)
		{
			float index = ((root->data.review_score->score) + (root->data.playtime_average)) / root->data.price->data;
			if (index > bestIndex)
			{
				bestIndex = index;
				gameaddress = root;
			}

			traversal(root->left, bestIndex, gameaddress, 0);
			traversal(root->right, bestIndex, gameaddress, 0);
		}
		else
		{
			float index = ((root->data.review_score->score) + (root->data.playtime_average)) / root->data.price->data;
			if (index < bestIndex)
			{
				bestIndex = index;
				gameaddress = root;
			}
			traversal(root->left, bestIndex, gameaddress, 1);
			traversal(root->right, bestIndex, gameaddress, 1);
		}
	}
}

void GameTree::mostWorthGame(GameAVLNode* root)
{
	float bestIndex = -1;
	GameAVLNode* gameaddress = NULL;
	traversal(root, bestIndex, gameaddress, 0);
	cout << "\n\nThe most worth game is: " << gameaddress->data.title << " based on price, reviews and game play time\n\n";
}

void GameTree::leastWorthGame(GameAVLNode* root)
{
	float bestIndex = 10000;
	GameAVLNode* gameaddress = NULL;
	traversal(root, bestIndex, gameaddress, 1);
	cout << "\n\nThe least worth game is: " << gameaddress->data.title << " based on price, reviews and game play time\n\n";
}

void GenreGraph::addgame(GameAVLNode* game) {  //function used to add nodes of the graph
	GenreNode* temp = new GenreNode;    //used to store new node
	GenreNode* temp2 = new GenreNode;   //used to go down in adj matrix/list

	temp->addressofgame = game;
	if (adjmatrix == NULL) {        //case if matrix is empty
		adjmatrix = temp;
		nodes++;
	}
	else {
		temp2 = adjmatrix;
		while(temp2->lower != NULL) {
			temp2 = temp2->lower;      //keeep going down until list ends
		}
		temp2->lower = temp;          //adding new node to list.
	}
}

GenreNode* GenreGraph::matrixtraverse(GameAVLNode* node) {  //used to traverse the adjacency matrix list.
	GenreNode* temp = adjmatrix;                            //initial temp with adjmatrixes first node
	bool found = false;
	while (temp != NULL && found == false) {               //keep repeatinng until end of matrix has been reached
		if (temp->addressofgame == node) {                 //is node foound in adj matrix?
			found = true;
		}
		else {
			temp = temp->lower;                         //if not go to next lower node in matrix
		}
	}
	if (found == true) {
		return temp;
	}
	else {
		cout << "Matrix traversal didnot reveal node." << endl;
		return NULL;
	}

}

void GenreGraph::checkgenre(GameAVLNode* game, GameAVLNode* root) { //function to compare genres of input with all other games and add edges in graph if genre similar
	if (root != NULL && root != game) {                  

		if (root->data.genre->data == game->data.genre->data) {  //genre of new node compared with roots genre
			if (adjmatrix->addressofgame == game) {                   // game input is first game in adjmatrix
				adjmatrix->game.Insert(root);                        //node in graph found, insert root input at tree
				GenreNode* temp3 = matrixtraverse(root);            //traverse adj matrix w.r.t root to find its node.
				temp3->game.Insert(game);							//insert game input into roots game list in graph
																	//this is done as graph is undirected therefore edges need to be created at both nodes
			}
			else {
				GenreNode* temp = matrixtraverse(game);    
				GenreNode* temp2 = matrixtraverse(root);  //since graph will be undirected this pointer will be used to store address of root node for reverse node addition.

				if (temp == NULL) cout << "Node in graph not found." << endl;
				else temp->game.Insert(root);
				if (temp2 == NULL) cout << "Root node not found in graph." << endl;
				else temp2->game.Insert(game);
			}
		}
		checkgenre(game, root->left);   //recur call with updated root(whole tree has to be compared.)
		checkgenre(game, root->right);
	}
}

void GenreGraph::printadj() {   //simple function to print all nodes in graph(adjacencey matrix)
	GenreNode* temp = adjmatrix;
	while (temp != NULL) {
		cout << temp->addressofgame->data.title << endl;

		temp = temp->lower;
	}
}

void GenreGraph::printsimilar(string g) {   //print games similar to input based on genre
	if (adjmatrix != NULL) {              //check if graph empty
		GenreNode* temp = adjmatrix;       //initial temp to traverse
		bool found = false;
		while (temp != NULL && found == false) {
			if (temp->addressofgame->data.title == g) {   //compare title of input and game in graph 
				temp->game.print();                          //print game list at said graph node if title matches
				found = true;
			}
			else {
				temp = temp->lower;          //if title does not match move to lower node in adjacencey list.
			}
		}
		if (found == false) cout << "Game not found in graph." << endl;
	}
	else {
		cout << "Graph is empty" << endl;
	}
	
}

void GenreGraph::isgenresame(string g1,string g2, GameTree* t){  //function to check genre of 2 
	GameAVLNode* temp =  t->search(g1);    //finding addresses of inputs in main GameTree
	GameAVLNode* temp2 = t->search(g2);

	GenreNode* temp3 = matrixtraverse(temp);   //pasing address to graph function to find its adjmatrix node address
	AVLlistsNode* temp4 = temp3->game.start;    //get head node of list maintained at each adj matrix node
	bool found = false;
	while (temp4 != NULL && found == false) {
		if (temp4->addressOfGame == temp2) {    //address of second game exists in list or not
			cout << "Genres of both games are same." << endl;  //if same output this
			found = true;
		}
		else temp4 = temp4->next;  //else go to next node in list.
	}

	if (found == false) cout << "Genre of these games is NOT same." << endl;
}