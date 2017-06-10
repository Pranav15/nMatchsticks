#include<iostream>
#include<ctime>
#include<cstdlib>
#include<windows.h>

using namespace std;

int getRan();
int genDelayTime(int,int);
int playCPU();
void singlePlayer();
void mainMenu();
void showRules();
void changeGame();
void reset();

int flag=2,msticks=21,usrN,cpuN,check,minSt=1,maxSt=4;
/*
flag - check which player played the last turn. (Used to determine the winner)
msticks - number of matchsticks remaining in the game
usrN - number of matchsticks user removes
cpuN - number of matchsticks CPU removes
check - used to determine who plays first
*/

/*Generate Random Numbers belonging to [minSt,maxSt] interval*/
int getRan()
{
	int temp,check=1;
	srand(time(NULL));
	do
	{
		temp = ( rand() % 10 );
		if(temp>=minSt && temp<=maxSt)
			check=0;
	}
	while(check);	
	return temp;
}

/*Generate delay time for CPU's turn, in the time interval of [min,max] seconds*/
int genDelayTime(int min, int max)
{
	int Delaytime,check=1;
		srand(time(NULL));
	do
	{
		Delaytime = ( rand() % 10 );
		if(Delaytime>=min && Delaytime<=max)
			check=0;
	}
	while(check);	
	return (Delaytime*1000);
}

/*Calculate the number of matchsticks CPU takes*/
int playCPU()
{
	/*
	
	--ALGORITHM - for 21 Matchsticks--
	
	minSt - min number of matchsticks that can be removed i.e. 1
	maxSt - max number of matchsticks that can be removed i.e. 4
	
	(minSt + maxSt) = 5;
	
	Opponent looses if the number of matchsticks remaining at his turn are 16/11/6/1
	1 + i(minSt+maxSt) = 21 , i=4
					   = 16 , i=3
					   = 11 , i=2
					   = 6  , i=1
					   = 1  , i=0
	if [ mstiks - (1+i(minSt+maxSt)) ] is >=1 and <=4, it means that the number of matchsticks 
													   remaining belong to one of the following   
													   intervals : [15,20]
													   			   [12,15]
													   			   [7,10]
													   			   [2,5]
	So, [msticks - (1+i(minSt+maxSt))] gives us the number of matchsticks CPU has to remove to bring the 
	number of matchsticks remaining to 16/11/6/1 at opponent's turn, i.e. CPU wins.
	
	check - used to check if CPU can bring the number of matchsticks remaining to 16/11/6/1,
	if check==0, CPU generates a random number between [1,4]
	
	*/
	
	int i,temp,check=0;
	temp = msticks;
	for(i=3;i>=0;i--)
	{
		if( (temp - (1+ i*(minSt+maxSt) ) ) >= minSt && (temp - (1+ i*(minSt+maxSt) ) ) <= maxSt )
		{
			return ( temp - (1+ i*(minSt+maxSt)) );
			check++;
			break;		
		}
		
	}
	if(check==0)
	{
		return (getRan());
	}
}

void mainMenu()
{
	int choice;
	system("cls");
	cout<<endl<<"\t\t\t\t 21 MATCHSTICKS"<<endl;
	cout<<"\t\t\t\t -- Main Menu --"<<endl;
	cout<<"1.Single Player"<<endl<<"2.Rules"<<endl<<"3.Change Game"<<endl<<"4.Reset Game"<<endl<<"5.Exit";
	cout<<endl<<"Enter your chocie:";
	cin>>choice;
	switch(choice)
	{
		case 1: singlePlayer();
				break;
		case 2: showRules();
				break;
		case 3:
				changeGame();
				break;
		case 4:
				reset();
				break;
		case 5:
				break;
		default:
				cout<<endl<<"Invalid Choice!";
				Sleep(2000);
				mainMenu();
				break;
	}
}

void singlePlayer()
{
	int go;
	do
	{
		system("cls");
		cout<<endl<<"\t\t\t\t 21 MATCHSTICKS";
		cout<<endl<<endl<<"Who starts?(CPU/Player)(1/2):"; //Determine who plays first
		cin>>check;
		//if CPU has to start first		
		if(check==1)
		{
			cout<<endl<<"Number of matchsticks Remaining : "<<msticks;
			cout<<endl<<"CPU: ";
			cpuN = playCPU();
			if(msticks>5)
				Sleep( genDelayTime(2,3) ); //Delay CPU's answer by x seconds, where x belongs to [min,max] i.e. [2,3]
			else
				Sleep(1000); //Delay CPU's answer by 1 second, if the number of matchsticks is less than 5, i.e. the CPU has won.
			cout<<cpuN;
			msticks-=cpuN;
			flag=1;
		}
		
		do
		{
			cout<<endl<<endl<<"Number of matchsticks Remaining : "<<msticks;
			if(msticks>1)
			{
				player1:
				cout<<endl<<"Player 1: ";
				cin>>usrN;
				if(usrN<minSt || usrN>maxSt)
				{
					cout<<"Invalid Input!"<<endl;
					cout<<"Enter a number between 1 to 4"<<endl;
					goto player1;
				}
				else
				{
					msticks-=usrN;
					flag = 0; //Player played last
				}
			}
			
			if(msticks>1)
				cout<<endl<<endl<<"Number of matchsticks Remaining : "<<msticks;
			
			if(msticks>1)
			{
				cout<<endl<<"CPU: ";
				cpuN = playCPU(); //playCPU returns the CPU's choice of number of matchsticks to be removed0
				if(msticks>(minSt+maxSt))
					Sleep( genDelayTime(2,4) ); //Delay CPU's answer by x seconds, where x belongs to [min,max] i.e. [2,4]
				else
					Sleep(1000); //Delay CPU's answer by 1 second, if the number of matchsticks is less than 5, i.e. the CPU has won.
				cout<<cpuN;
				msticks-=cpuN;
				flag = 1; //CPU played last
			}
		}
		while(msticks>1); //The game ends if there is only 1 matchstick remaining	
		
		if(flag == 0)//Player played the last turn
			cout<<endl<<endl<<"Player 1 Wins!";
		else//CPU played the last turn
			cout<<endl<<endl<<"CPU Wins!";
			
		cout<<endl<<"Rematch?(1/0): ";
		cin>>go;
	}
	while(go==1);
	mainMenu();	
}

void showRules()
{
	getchar();
	char ch;
	system("cls");
	cout<<endl<<"\t\t\t\t 21 MATCHSTICKS"<<endl;
	cout<<"\t\t\t\t -- RULES --"<<endl;
	cout<<endl<<"1. 21 Matchsticks is a two player game.";
	cout<<endl<<"2. Initially, there are 21 matchsticks, out of which each player can choose minumum 1 and maximum 4 matchsticks in their turn.";
	cout<<endl<<"3. The player who is remaining with the final one matchstick looses.";
	cout<<endl<<endl<<"Press any key to go back to the Main Menu";
	getchar();
	mainMenu();
}

void changeGame()
{
	system("cls");
	cout<<endl<<"Enter number of matchsticks:";
	cin>>msticks;
	cout<<endl<<"Enter minimum number of matchsticks that can be removed:";
	cin>>minSt;
	cout<<endl<<"Enter maximum number of matchsticks that can be removed:";
	cin>>maxSt;
	mainMenu();
}

void reset()
{
	getchar();
	system("cls");
	msticks=21;
	minSt=1;
	maxSt=4;
	cout<<endl<<"Game Reset to 21 Matchsticks!";
	cout<<endl<<"Press any key to continue.";
	getchar();
	mainMenu();
}

int main(void)
{
	mainMenu();
	return 0;
}
