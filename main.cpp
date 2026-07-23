#include <iostream>
#include <cmath>
#include <algorithm>
#include <cstdlib>
using namespace std;

enum enGameChoice{ stone=1 , paper=2 , scissors=3 };
enum enWinner{ Player=1 , Computer=2 , Draw=3 };

struct stRoundInfo
{
  short RoundNumber=0;
  enGameChoice PlayerChoice;
  enGameChoice ComputerChoice;
  enWinner Winner;  // Who is win in this round (number)
  string WinnerName; // To Change this number to value (name)
};

struct stGameResult
{
  short GameRounds=0;
  short PlayerWinTimes=0;
  short ComputerWinTimes=0;
  short DrawTimes=0;
  enWinner Gamewinner;
  string WinnerName;
};

short HowManyRoundsToWant()
{
    short RoundNumber=0;

    cout<<"\n How Many Round To want Play (Enter number between 1:10) : ";
    cin>>RoundNumber;

    while(RoundNumber<1||RoundNumber>10)
    {
     cout<<" please Enter Correct answer : ";
     cin>>RoundNumber;
    }
    return RoundNumber;
}

int RandomNumber(int from , int to)// Computer Choice by This function
{
    int RandNum=0;
    RandNum = rand()%(to-from+1)+from;
    return RandNum;
}

enGameChoice ReadChoicePlayer()
{
    short choice;

    cout<<" Enter your choice from [ stone = 1 , paper = 2 , scissors = 3 ] : ";
    cin>>choice;

    while(choice<1||choice>3)
    {
     cout<<" please Enter Correct answer : ";
     cin>>choice;
    }
    return (enGameChoice) choice;

}

enGameChoice GetComputerChoice()
{
    return (enGameChoice) RandomNumber( 1 , 3 ) ;// The Computer Choice Randomly
}

string choiceName(enGameChoice choice) // Change choice from unknown number to know name
{
    string arrGameChoice[3] = {"stone" , "paper" , "scissors"};
    return arrGameChoice[choice-1]; //array starts from 0
}

string WinnerName(enWinner winner) // Change winner from unknown number to know name
{
    string arrWinnerName[3] = {"player" , "computer" , "No Winner"};
    return arrWinnerName[winner-1];
}

enWinner WhoWinInRound( stRoundInfo RoundInfo )
{
 if( RoundInfo.PlayerChoice == RoundInfo.ComputerChoice )// status : Draw
    {
     return enWinner :: Draw ;
    }
 // status : Computer is win *****
 switch (RoundInfo.ComputerChoice)
    {
        case enGameChoice::stone:
            if (RoundInfo.PlayerChoice == enGameChoice::scissors) return enWinner::Computer;
            break;
        case enGameChoice::paper:
            if (RoundInfo.PlayerChoice == enGameChoice::stone) return enWinner::Computer;
            break;
        case enGameChoice::scissors:
            if (RoundInfo.PlayerChoice == enGameChoice::paper) return enWinner::Computer;
            break;
    }
 // if Not computer is win , or status is Draw . so player is won
 return enWinner :: Player ;
}

void SetWinnerScreenColor(enWinner winner)
{

    switch(winner)
    {

    case enWinner::Computer :
    {
     system("color 4f") ;// Change Screen Color to Red
     cout<<"\a";        //  and Sound
     break;
    }

    case enWinner::Player :
    {
     system("color 2f") ; // Change Screen Color to Green
     break;
    }

    case enWinner::Draw :
    {
    system("color 6f") ; // Change Screen Color to yellow
    break;
    }

    }
}


void PrintResultInRound (stRoundInfo RoundInfo)
{
  cout<< "\n___________ Round ["<< RoundInfo.RoundNumber <<"] ___________\n\n" ;
  cout<<" Player Choice   : "<< choiceName(RoundInfo.PlayerChoice) <<endl;
  cout<<" Computer Choice : "<< choiceName(RoundInfo.ComputerChoice) <<endl;
  cout<<" The Winner      : { "<< RoundInfo.WinnerName <<" }"<<endl;
  cout<<"_________________________________\n\n";

  SetWinnerScreenColor(RoundInfo.Winner);
}


enWinner whoWinInGame( short playerWinTimes , short computerWinTimes )
{
    if( playerWinTimes > computerWinTimes )
        return enWinner :: Player ;

    else if ( playerWinTimes < computerWinTimes )
        return enWinner :: Computer ;

    else
        return enWinner::Draw;
}

stGameResult fillGameResult( short GameRound , short playerWinTimes , short computerWinTimes , short DrawTimes )
{
    stGameResult GameResult;

    GameResult.GameRounds=GameRound;
    GameResult.PlayerWinTimes=playerWinTimes;
    GameResult.ComputerWinTimes=computerWinTimes;
    GameResult.DrawTimes=DrawTimes;
    GameResult.Gamewinner=whoWinInGame(playerWinTimes,computerWinTimes);
    GameResult.WinnerName=WinnerName(GameResult.Gamewinner);

    return GameResult;
}

stGameResult playGame(short HowManyRound)
{
  stRoundInfo RoundInfo;
  short PlayerWinTimes=0 ,  ComputerWinTimes=0 ,DrawTimes=0 ;

  for(int i=1 ; i<=HowManyRound ; i++)
  {
   cout<<"\n Round ["<<i<<"] starts : \n";

   RoundInfo.RoundNumber = i ;
   RoundInfo.PlayerChoice = ReadChoicePlayer();
   RoundInfo.ComputerChoice = GetComputerChoice();
   RoundInfo.Winner=WhoWinInRound(RoundInfo);
   RoundInfo.WinnerName=WinnerName(RoundInfo.Winner);

   if(RoundInfo.Winner==enWinner::Player)
    PlayerWinTimes++;

   else if (RoundInfo.Winner==enWinner::Computer)
    ComputerWinTimes++;

   else
    DrawTimes++;

   PrintResultInRound(RoundInfo);
  }

  return fillGameResult( HowManyRound , PlayerWinTimes , ComputerWinTimes , DrawTimes );
}

void ResetScreen ()// This function To Clean Screen again
{
    system(" cls "); // Clean Screen
    system(" color 0f "); // reset screen to black
}

void ShowResultOfGame( stGameResult GameResult)
{
 cout<<"\t\t__**_________________________________________**____\n\n";
 cout<<"\t\t              *** G A M E O V E R ***          \n";
 cout<<"\t\t__**_________________________________________**____\n\n";

 cout<<"\t\t------------------[Game Results]-------------------\n\n";
 cout<<"\t\t Game Rounds        : "<<GameResult.GameRounds<<endl;
 cout<<"\t\t Player won times   : "<<GameResult.PlayerWinTimes<<endl;
 cout<<"\t\t Computer won times : "<<GameResult.ComputerWinTimes<<endl;
 cout<<"\t\t Draw Times         : "<<GameResult.DrawTimes<<endl;
 cout<<"\t\t Final Winner       : "<<GameResult.WinnerName<<endl;
 cout<<"\t\t---------------------------------------------------"<<endl;

  SetWinnerScreenColor(GameResult.Gamewinner);
}

void StartGame()
{
    char playAgain ='Y' ;

    do
    {
      ResetScreen();
      stGameResult GameResult = playGame(HowManyRoundsToWant());
      ShowResultOfGame(GameResult);

      cout<<"\n"<<"\t Do you want play again ? (answer by \" Y \" , \" N \") : ";
      cin>>playAgain;

    } while( playAgain == 'Y' || playAgain == 'y' );
}

int main()
{

 srand((unsigned)time(NULL));

  StartGame();


    return 0;

}













