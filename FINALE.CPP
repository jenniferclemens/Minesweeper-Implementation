#include<iostream.h>
#include<conio.h>
#include<process.h>
#include<string.h>
#include<fstream.h>
#include<stdlib.h>
#include<stdio.h>

int a, b;

class Minesweeper
{
	public:
		int mineBoard[9][9], playBoard[9][9];
		int adjacentmines, score;
		char playerName[50];
		void makeMove();
		void countAdjacentMines();
		void scores();
		void game();
		void instructions();
		void initializeBoards();
		void loseGame();
		void displayMineBoard();
}O, d;

void Minesweeper::instructions()
{
	clrscr();
	cout<<"******************************************************************************"
		<<"\n\t\t\t\tINSTRUCTIONS"
		<<"\n******************************************************************************";
	cout<<"\n\nA board filled with boxes will appear on the screen along with"
		<<" the positions of  each box. There are 'mines' placed in random "
		<<"boxes unknown to the player.\n The   user enters the position of a "
		<<"box they wish to select.\n If the selected box contains one of those "
		<<"randomly placed 'mines', then the    player loses.\n If the    player selects"
		<<" a box without a mine, a number will appear in that box signifying "
		<<"how many of its adjacent boxes have mines.\n The  game goes "
		<<" on as long as the player does not select a box containing a    mine."
		<<"\nThe player gains 5 points for every move made."
		<<"\n\n Press any key to go back to the menu";
	getch();
}

void Minesweeper::makeMove()
{
	cout<<"\n\t\t\t";
	for(int i=0;i<9;i++)
	{
		for(int j=0;j<9;j++)
		{
			if(O.playBoard[i][j]=='-')
				cout<<" "<<char(O.playBoard[i][j]);
			else
				cout<<" "<<O.playBoard[i][j];
		}
		cout<<"\n\t\t\t";
	}
	cout<<"\n\t\tEnter the following and press enter:"<<"\n\t\tROW:";
	cin>>a;
	cout<<"\t\tCOLUMN:";
	cin>>b;
	if(O.mineBoard[a][b]=='*')
	{
		O.loseGame();
		O.scores();
		O.game();
	}
	else
	{
		if(a<9 && b<9 && a>0 && b>0)
		{
			O.score+=5;
			O.countAdjacentMines();
		}
		O.makeMove();
	}
}

void Minesweeper::countAdjacentMines()
{
	O.adjacentmines=0;
	for(int i=(a-1);i<=(a+1);i++)
	{
		for(int j=(b-1);j<=(b+1);j++)
		{
			if(O.mineBoard[i][j]=='*')
				O.adjacentmines++;
		}
	}
	O.playBoard[a][b]=O.adjacentmines;
}

void Minesweeper::loseGame()
{
	cout<<"\n\n\t\t\t\tYOU LOSE\n";
	O.displayMineBoard();
	cout<<"\n\n\t\t\tBetter luck next time!";
	getch();
}

void Minesweeper::scores()
{
	clrscr();
	cout<<"********************************************************************************"
		<<"\t\t\t\tSCORES"
		<<"\n********************************************************************************";
	cout<<"\n\t\tYour score from the recently played game:"<<O.score<<"\n\n\t\t\t\tHigh Scores:\n";
	fstream fi("SCORES.TXT",ios::in|ios::binary);
	fstream fo("TEMP.TXT",ios::out|ios::binary);
	char last='y';
	while(!fi.eof())
	{
		fi.read((char*)&d,sizeof(d));                        //gets a value from scores.txt
		if(d.score<=O.score && O.score!=0)
		{
			fo.write((char*)&O,sizeof(O));   //if the score current score is greater, it is copied first into temp.txt
			fo.write((char*)&d,sizeof(d));
			last='n';
			break;
		}
		else
			fo.write((char*)&d,sizeof(d));
	}
	if(last=='y' && O.score!=0)
		fo.write((char*)&O,sizeof(O));               //inserts the current score into the file
	else if(!fi.eof())
	{
		while(!fi.eof())
		{                         //to copy the rest of the scores stored in the file after the current game store to maintain the sorted order
			fi.read((char*)&d,sizeof(d));
			fo.write((char*)&d,sizeof(d));
		}
	}
	fi.close();
	fo.close();
	remove("SCORES.TXT");
	rename("TEMP.TXT","SCORES.TXT");
	fo.open("SCORES.TXT",ios::in|ios::binary);
	int i=0;
	while(!fo.eof() && i<5)
	{                                 //to display the first 5 scores in the sorted file as high scores
		i++;
		fo.read((char*)&d,sizeof(d));
		cout<<"\t\t\t"<<i<<". "<<d.score<<"\t scored by ";
		puts(d.playerName);
	}
	fo.close();
	getch();
	O.score=0;
}

void Minesweeper::game()
{
	int x;
	clrscr();
	cout<<"********************************************************************************"
		<<"\t\t\t\tMINESWEEPER"
		<<"\n********************************************************************************"
		<<"\n\n\t\t\t\t  Menu:"
		<<"\n\t\t\t1.Play Game"
		<<"\n\t\t\t2.Instructions"
		<<"\n\t\t\t3.Scores"
		<<"\n\t\t\t4.Exit"
		<<"\n\n\t\tEnter your choice and press enter:";
	cin>>x;
	switch(x)
	{
		case 1: cout<<"\n\n\t\tEnter your name(player's name):";
			gets(playerName);
			clrscr();
			O.initializeBoards();
			O.score=0;
			O.makeMove();
			break;
		case 2: O.instructions();
			break;
		case 3: clrscr();
			O.scores();
			break;
		case 4: exit(0);
			break;
		default:O.game();
	}
	O.game();
}

void Minesweeper::initializeBoards()
{
	int a,b;
	randomize();
	for(int k=0;k<9;k++)
	{
		for(int l=0;l<9;l++)
			O.mineBoard[k][l]=0;
	}
	for(int i=0;i<25;i++)
	{
		a=random(8);
		b=random(8);
		O.mineBoard[++a][++b]='*';
	}
	for(i=0;i<9;i++)
	{
		for(int j=0;j<9;j++)
		{
			if(i==0)
			{
				O.playBoard[i][j]=j;
				O.mineBoard[i][j]=j;
			}
			else if(j==0)
			{
				O.playBoard[i][j]=i;
				O.mineBoard[i][j]=i;
			}
			else
				O.playBoard[i][j]='-';
		}
	}
}

void Minesweeper::displayMineBoard()
{
	cout<<"\t\t\t";
	for(int i=0;i<9;i++)
	{
		for(int j=0;j<9;j++)
		{
			if(i==0)
				cout<<" "<<j;
			else if(j==0)
				cout<<" "<<i;
			else if(O.mineBoard[i][j]!='*')
				cout<<" -";
			else
				cout<<" *";
		}
		cout<<"\n\t\t\t";
	}
}
void main()
{
	clrscr();
	O.initializeBoards();
	O.game();
	getch();
}


