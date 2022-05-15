#include <iostream>
#include <vector>        //vectors used just for the parser
#include <string>

using namespace std;
class GameAVLNode;
class GameTree;

class AVLlistsNode              //These lists would be present in all avl nodes
{
public:
	GameAVLNode* addressOfGame;    //stores tha game address
	AVLlistsNode* next;            //points to the next game address in list
};

class AVLlists            //this is  a general list to back connect games when they are to be refered by other attributes
{
public:
	AVLlistsNode* start;
	AVLlistsNode* last;
	AVLlistsNode* ploc;
	AVLlistsNode* loc;
	int total;
	AVLlists()
	{
		start = NULL;
		last = NULL;
		ploc = NULL;
		loc = NULL;
		total = 0;
	}

	bool IsEmpty();
	void Insert(GameAVLNode* game);       //inserts the game address in the list
	void print();

};

class SalesAVLNode                  //basic node class (class used for sales and price attributes)
{
public:
	float data;
	SalesAVLNode* left;         //left child pointer
	SalesAVLNode* right;        //right child pointer
	int height;                 //height of each node
	AVLlists list;              //stores the list of all those games that has the same sales or price 
};

static SalesAVLNode* temporary;

class SalesTree                   //avl class
{
public:                     //root of tree
	SalesAVLNode* root;             //constructor sets root to null
	SalesTree()
	{
		root = NULL;
	}

	int height(SalesAVLNode*);               //height of a node calculator
	int getBalance(SalesAVLNode*);           //gets balance factor
	SalesAVLNode* rrotation(SalesAVLNode*);          //right rotation
	SalesAVLNode* lrotation(SalesAVLNode*);          //left rotation
	SalesAVLNode* rlrotation(SalesAVLNode*);         //right left rotation
	SalesAVLNode* lrrotation(SalesAVLNode*);         //left right rotation
	SalesAVLNode* Findmin(SalesAVLNode*);            //left most node in tree
	SalesAVLNode* Findmax(SalesAVLNode*);            //right most node in tree
	SalesAVLNode* insert(float, SalesAVLNode*);  //insert value in tree
	void InOrder(SalesAVLNode*);               //prints inorder
	void PreOrder(SalesAVLNode*);              //pre order printing
	SalesAVLNode* SalesAddress(float);         //returns the address of the sale node. This will be stored in the main game class sales attribute
};

class ScoreAVLNode                  //basic node class
{
public:
	int score;
	ScoreAVLNode* left;         //left child pointer
	ScoreAVLNode* right;        //right child pointer
	int height;         //height of each node
	AVLlists gamesScore;
};

static ScoreAVLNode* p;

class ReviewScoreTree                   //avl class
{
public:                     //root of tree
	ScoreAVLNode* root;             //constructor sets root to null
	ReviewScoreTree()
	{
		root = NULL;
	}

	int height(ScoreAVLNode*);               //height of a node calculator
	int getBalance(ScoreAVLNode*);           //gets balance factor
	ScoreAVLNode* rrotation(ScoreAVLNode*);          //right rotation
	ScoreAVLNode* lrotation(ScoreAVLNode*);          //left rotation
	ScoreAVLNode* rlrotation(ScoreAVLNode*);         //right left rotation
	ScoreAVLNode* lrrotation(ScoreAVLNode*);         //left right rotation
	ScoreAVLNode* Findmin(ScoreAVLNode*);            //left most node in tree
	ScoreAVLNode* Findmax(ScoreAVLNode*);            //right most node in tree
	ScoreAVLNode* insert(int, ScoreAVLNode*);  //insert value in tree
	void InOrder(ScoreAVLNode*);               //prints inorder
	void PreOrder(ScoreAVLNode*);              //pre order printing
	ScoreAVLNode* ScoreAddress(int);
	void getbestgame();
	void getworstgame();
	void InOrderlimit(ScoreAVLNode* node, float val, int type);
	void lowerlimit(float val);
	void upperlimit(float val);
	void withinrange(ScoreAVLNode* node, float val1, float val2);
	void printScoreGames(int);
};

class PublisherNode {
public:
	string name;
	AVLlists  games;
	PublisherNode* next;
};

class PublisherList {
public:
	PublisherNode* pstart;
	PublisherNode* plast;
	PublisherNode* loc_P;
	PublisherNode* ploc_P;

	PublisherList()
	{
		pstart = NULL;
		plast = NULL;
		loc_P = NULL;
		ploc_P = NULL;
	}

	bool P_IsEmpty()
	{
		return (pstart == NULL);
	}
	bool PublisherSearch(string);
	void printing();
	PublisherNode* PublisherAddress(string a);
	void PrintRecord(string);
	float avgcost(string pub);       //newlyadded
	float avgrating(string pub);
	int countpublishers();
	void bestpublisher();
};

class GenreNode {    //this node will be store in adj matrix in GenreGraph
public:
	AVLlists game;    //list that stores the gameAVLnode address with same genre as the one in the node of adjmatrix
	GameAVLNode* addressofgame;
	GenreNode* lower;
	GenreNode() {
		lower = NULL;
		addressofgame = NULL;
	}

};

class GenreGraph {     //Graph that stores edges on basis of genre(same or not)
public:
	int nodes;
	GenreNode* adjmatrix;

	GenreGraph() {
		nodes = 0;
		adjmatrix = NULL;
	}

	void addgame(GameAVLNode* game);                   //add game in adjmatrix node
	GenreNode* matrixtraverse(GameAVLNode* node);     //function to traverse adj matrix     
	void checkgenre(GameAVLNode* game, GameAVLNode* root);   //function to check new games genre with all previously maintained games
	void printadj();                                     //simple function to print all nodes in the adjacency matrix
	void printsimilar(string g);                        //print all games with same genre as input 
	void isgenresame(string, string, GameTree*);      


};

class Genre {   //this object will store pointer of genrelist IN the GameTree AVL 
public:
	string data;
	Genre* next;
};

class Genrelist {   //this list is maintained
public:

	Genre* head;
	Genre* tail;
	int length;

	Genrelist() {
		head = NULL;
		tail = NULL;
	}

	void insert(string val) {   //simple insert function to add genre of game(read from csv) to the list maintained in GameAVLNode
		Genre* temp = new Genre;
		temp->data = val;
		if (head == NULL) {
			head = temp;
			tail = temp;
			length++;
		}
		else {
			tail->next = temp;
			tail = temp;
			length++;
		}
	}

};

class Game {
public:
	string title;
	int maxplayers;
	Genre* genre;
	PublisherNode* publisher;
	ScoreAVLNode* review_score;
	SalesAVLNode* sales;    //assumed in millions
	SalesAVLNode* price;
	string console;
	char rating;
	int release_year;
	float playtime_average;
	float playtime_leisure;
	float playtime_median;
	float playtime_rushed;
	float playtime_comp_avg;   //comp = completionist
	float playtime_comp_leisure;
	float playtime_comp_median;
	float playtime_comp_rushed;
	float playtime_total_avg;    //total = main + extras
	float playtime_total_leisure;
	float playtime_total_median;
	float playtime_total_rushed;
	float playtime_main_avg;    //main = main story just
	float playtime_main_leisure;
	float playtime_main_median;
	float playtime_main_rushed;
};

class GameAVLNode {
public:
	Game data;                    //data value of type game
	GameAVLNode* left;
	GameAVLNode* right;
	int height;                   //height of each node

	GameAVLNode() {
		left = NULL;
		right = NULL;
		height = 0;
	}
	void printNode()                             //prints all data values of the node
	{
		cout << endl << endl;
		cout << "\x1b[31mTitle: " << data.title << endl;
		cout << "Max players: " << data.maxplayers << endl;
		cout << "Genre: " << data.genre->data<< endl;
		cout << "Publisher: " << data.publisher->name << endl;
		cout << "Review Score: " << data.review_score->score << endl;
		cout << "Sales: " << data.sales->data << endl;
		cout << "Price: " << data.price->data << endl;
		cout << "Console: " << data.console << endl;
		cout << "Rating: " << data.rating << endl;
		cout << "Release Year: " << data.release_year << endl;
		cout << "Playtime Average: " << data.playtime_average << endl;
		cout << "Playtime Leisure: " << data.playtime_leisure << endl;
		cout << "Playtime Median: " << data.playtime_median << endl;
		cout << "Playtime Rushed: " << data.playtime_rushed << endl;
		cout << "Playtime Completionist Average: " << data.playtime_comp_avg << endl;
		cout << "Playtime Completionist Leisure: " << data.playtime_comp_leisure << endl;
		cout << "Playtime Completionist Median: " << data.playtime_comp_median << endl;
		cout << "Playtime Completionist Rushed: " << data.playtime_comp_rushed << endl;
		cout << "Playtime Total Average: " << data.playtime_total_avg << endl;
		cout << "Playtime Total Leisure: " << data.playtime_total_leisure << endl;
		cout << "Playtime Total Median: " << data.playtime_total_median << endl;
		cout << "Playtime Total Rushed: " << data.playtime_total_rushed << endl;
		cout << "Playtime Main Average: " << data.playtime_main_avg << endl;
		cout << "Playtime Main Leisure: " << data.playtime_main_leisure << endl;
		cout << "Playtime Main Median: " << data.playtime_main_median << endl;
		cout << "Playtime Main Rushed: " << data.playtime_main_rushed <<"\x1b[0m\n";
	}

};

class GameTree {  //inherit SLL functions
public:
	GameAVLNode* root;
	GameAVLNode* loc;
	GameAVLNode* ploc;
	GameTree() {
		root = NULL;
		loc = NULL;
		ploc = NULL;
	}


	bool IsEmpty();
	int height(GameAVLNode*);               //height of a node calculator
	int getBalance(GameAVLNode*);           //gets balance factor
	GameAVLNode* rrotation(GameAVLNode*);          //right rotation
	GameAVLNode* lrotation(GameAVLNode*);          //left rotation
	GameAVLNode* rlrotation(GameAVLNode*);         //right left rotation
	GameAVLNode* lrrotation(GameAVLNode*);         //left right rotation
	GameAVLNode* insert(Game*, GameAVLNode*);
	void InOrder(GameAVLNode*);

	void parser(PublisherList&, ReviewScoreTree&, SalesTree&, SalesTree&, GenreGraph&);
	GameAVLNode* search(string);
	void traversal(GameAVLNode*, float &, GameAVLNode*&, int);
	void mostWorthGame(GameAVLNode*);
	void leastWorthGame(GameAVLNode*);
};
