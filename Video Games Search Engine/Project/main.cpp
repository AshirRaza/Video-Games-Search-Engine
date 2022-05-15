#include"custom.h"
#include<string>
#include <iostream>
void menu()                   //main menu 
{
	cout << "\x1b[33mPlease select from the following functions:\n\n";
	cout << "\n\t 1 - Print all the games in alphabetical order.";
	cout << "\n\t 2 - Find the game which is most worth it (based on price, reviews and playing time.";
	cout << "\n\t 3 - Find the game which is least worth it (based on price, reviews and playing time. ";
	cout << "\n\t 4 - Search for a publisher profile.";
	cout << "\n\t 5 - Print Average cost of games for a particular publisher. ";
	cout << "\n\t 6 - Print Average rating of games for a particular publisher.";
	cout << "\n\t 7 - Find out the best publisher (rating wise).";
	cout << "\n\t 8 - Find out the best game rating wise.";
	cout << "\n\t 9 - Find out the worst game rating wise.";
	cout << "\n\t 10 - Find out all those games that have scores between your specified range. ";
	cout << "\n\t 11 - Find out all games of a particular score.";
	cout << "\n\t 12 - FInd games similar to the one you want.";
	cout << "\n\t 13 - Check if 2 games have same genre or not. \x1b[0m";
}

int main()								//main function
{
	PublisherList p1;            //creation of a publisher list
	GameTree g1;                 // creation of the main Data tree where the complete row will be stored.
	ReviewScoreTree score1;      // Tree that stores the reviews score. If a duplicate score is passed, it will not add a new node. 
	SalesTree sales;             // A tree that stores the sales nodes.
	SalesTree prices;            //Tree for prices nodes
	GenreGraph genre;
	string g;
	int choice=0;
	cout << "Parsing File.....\n\n";
	g1.parser(p1, score1, sales, prices, genre);
	menu();
	while (choice!=-1)
	{
		cout<<"\n\nEnter your choice: ";
		cin>>choice;
		if (choice == 1)
			g1.InOrder(g1.root);
		else if (choice == 2)
			g1.mostWorthGame(g1.root);
		else if (choice == 3)
			g1.leastWorthGame(g1.root);
		else if (choice == 4)
		{
			string pub;
			cout << "\x1b[32mEnter the name of the publisher whose profile you want to look for. The dataset contains the following publishers: \x1b[0m\n\n";
			p1.printing();
			cout << "\n\nName: ";
			cin >> pub;
			cout << endl;
			p1.PrintRecord(pub);
		}
		else if (choice == 5)
		{
			string pub;
			cout << "\x1b[32mEnter the name of the publisher whose average cost you want to find out. The dataset contains the following publishers: \x1b[0m\n\n";
			p1.printing();
			cout << "\n\nName: ";
			cin >> pub;
			cout << endl;
			p1.avgcost(pub);
		}
		else if (choice == 6)
		{
			string pub;
			cout << "\x1b[32mEnter the name of the publisher whose average rating you want to find out. The dataset contains the following publishers: \x1b[0m\n\n";
			p1.printing();
			cout << "\n\nName: ";
			cin >> pub;
			cout << endl;
			p1.avgrating(pub);
		}
		else if (choice == 7)
		{
			p1.bestpublisher();
		}
		else if (choice == 8)
		{
			score1.getbestgame();
		}
		else if (choice == 9)
			score1.getworstgame();
		else if (choice == 10)
		{
			float lower, upper;
			cout << "\x1b[32mEnter the range of scores. The program will print all those games that are within those scores (excluding the bounds)\x1b[0m\n\n";
			cout << "Upper Bound: ";cin >> upper;
			cout << "Lower bound: ";cin >> lower;
			cout<<endl<<endl;
			score1.withinrange(score1.root, lower, upper);
		}
		else if (choice == 11)
		{
			int val;
			cout << "\x1b[32mEnter the score. The program will print the titles of all those games of that score\nScore: \x1b[0m";
			cin >> val;
			score1.printScoreGames(val);
		}
		else if (choice == 12) {
			cout << "\x1b[32mEnter the name of the game for which you want similar games: \x1b[0m";
			cin.ignore();
			getline(cin, g);

			genre.printsimilar(g);
		}
		else if (choice == 13) {
			string ga1;
			string ga2;
			cout << "\x1b[32mEnter name of game 1: \x1b[0m";
			cin.ignore();
			getline(cin, ga1);

			cout << "\x1b[32mEnter name of game 2: \x1b[0m";
			getline(cin, ga2);
			genre.isgenresame(ga1, ga2, &g1);
		}
		cout<<endl<<endl;
		menu();
	}
}