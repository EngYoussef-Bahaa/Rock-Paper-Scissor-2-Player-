#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <ctime> 
#include <string>
#include <windows.h>  
#include<conio.h>
using namespace std;
enum enWinnerP1P2 { Player1 = 1, Player2 = 2, NoWinner = 3 };
enum enChoice { Stone = 1, Paper = 2, Scissor = 3 };
struct stRoundinfo
{
    short NumOfRoundNow = 0;
    enChoice Player1Choice;
    enChoice Player2Choice;
    enWinnerP1P2 WinnerofRound;
    string WinnerName;
};
struct stGameinfo
{
    short Rounds;
    short Player1Wintimes;
    short Player2Wintimes;
    short DrawTimes;
    enWinnerP1P2 ThefinalWinner;
    string ThefinalWinnerName;
    stRoundinfo Roundinfo;
};
void RestSetting()
{
    cout << "\033[2J\033[H";
    system("color 0F");
}
int ReadhowManyRounds()
{
    int Round;
    do
    {
        cout << "Enter How Many Rounds 1 To 10 ?\n";
        cin >> Round;
    } while (Round > 10 || Round < 1);
    return Round;
}
enChoice ReadUserChoiceP1()
{
    char ch;
    do {
    cout << "\n\n [Player 1 Green Team] Enter Your Choice :[1]stone ,[2]Paper ,[3] Scissors ?";
    ch = _getch();
    } while (ch<'1'||ch>'3');
    cout << "*\n";
    return (enChoice)(ch-'0');
}
enChoice ReadUserChoiceP2()
{
    char ch;
    do {
        cout << "\n\n [Player 2 Red Team] Enter Your Choice :[1]stone ,[2]Paper ,[3] Scissors ?";
        ch = _getch();
    } while (ch < '1' || ch>'3');
    cout << "*\n";
    return (enChoice)(ch - '0');
}
string Taab(int x)
{
    string tab = "  ";
    for (int i = 1; i <= x; i++)
    {
        tab += "\t";
    }
    return tab;
}
string ChoiceName(enChoice Choice)
{
    int X = (int)Choice;
    string WinnerName[3] = { "Stone","Paper","Scissor" };
    return WinnerName[X - 1];
}
enWinnerP1P2 WinneratRound(enChoice Player1Choice, enChoice Player2Choice)
{
    if (Player2Choice == Player1Choice)
    {
        return enWinnerP1P2::NoWinner;
    }
    else
    {
        switch (Player1Choice)
        {
        case enChoice::Stone:
            if (Player2Choice == enChoice::Paper)
            {
                return enWinnerP1P2::Player2;
            }
            break;
        case enChoice::Paper:

            if (Player2Choice == enChoice::Scissor)
            {
                return enWinnerP1P2::Player2;
            }
            break;
        case enChoice::Scissor:

            if (Player2Choice == enChoice::Stone)
            {
                return enWinnerP1P2::Player2;
            }
            break;
        }
        return enWinnerP1P2::Player1;

    }
}
string WinnerName(enWinnerP1P2 Winner)
{
    string WinnerName[3] = { "Player1","Player2","NoWinner"};
    int X = (int)Winner;
    return WinnerName[X - 1];
}
enWinnerP1P2 FinalWinner(short Player1Wintimes, short Player2Wintimes)
{
    if (Player2Wintimes > Player1Wintimes)
    {
        return enWinnerP1P2::Player2;
    }
    else if (Player2Wintimes < Player1Wintimes)
    {

        return enWinnerP1P2::Player1;
    }
    else {

        return enWinnerP1P2::NoWinner;
    }
}
void TheResultattheRound(int Round, stRoundinfo Roundinfo)
{
    cout << "______________Round [" << Round << "] __________\n";
    cout << "Player 1 Choise : " << ChoiceName(Roundinfo.Player1Choice) << endl;
    cout << "Computer Choise : " << ChoiceName(Roundinfo.Player2Choice) << endl;
    cout << "Round winner    : " << "[" << Roundinfo.WinnerName << "]" << endl;
    cout << "________________________________________________\n";
}
void ScreenWinnerColor(enWinnerP1P2 Winner)
{
    switch (Winner)
    {
    case enWinnerP1P2::Player2:
        cout << "\a";
        system("color 4F");
        break;
    case enWinnerP1P2::Player1:
        Beep(1000, 500);
        system("color 2F");
        break;
    case enWinnerP1P2::NoWinner:
        system("color 6F");
        break;
    }
}
void GameOverscreen()
{
    cout << Taab(2) << "-----------------------------------------------------\n\n";
    cout << Taab(2) << "             +++  G a m e   O v e r   +++            \n";
    cout << Taab(2) << "-----------------------------------------------------\n\n";
}
void GameResult(stGameinfo Gameinfo)
{
    ScreenWinnerColor(Gameinfo.ThefinalWinner);
    cout << Taab(2) << "-------------------- [ Game Results ] ---------------\n\n";
    cout << Taab(2) << "Game Rounds             : " << Gameinfo.Rounds << endl;
    cout << Taab(2) << "Player1 Win Times[Green]: " << Gameinfo.Player1Wintimes << endl;
    cout << Taab(2) << "Player2 Win times[Red]  : " << Gameinfo.Player2Wintimes << endl;
    cout << Taab(2) << "Draw Times              : " << Gameinfo.DrawTimes << endl;
    cout << Taab(2) << "Final Winner            : " << Gameinfo.ThefinalWinnerName << endl;
    cout << Taab(2) << "-----------------------------------------------------\n\n";
}
void PlayRounds(int Rounds, stGameinfo& Gameinfo)
{
    Gameinfo.Player2Wintimes = 0;
    Gameinfo.Player1Wintimes = 0;
    Gameinfo.DrawTimes = 0;
    Gameinfo.Rounds = Rounds;
    for (int i = 1; i <= Gameinfo.Rounds; i++)
    {
        Gameinfo.Roundinfo.NumOfRoundNow = i;
        cout << "Round [" << Gameinfo.Roundinfo.NumOfRoundNow << "] begins \n";
        Gameinfo.Roundinfo.Player1Choice = ReadUserChoiceP1();
        Gameinfo.Roundinfo.Player2Choice = ReadUserChoiceP2();
        Gameinfo.Roundinfo.WinnerofRound = WinneratRound(Gameinfo.Roundinfo.Player1Choice, Gameinfo.Roundinfo.Player2Choice);
        Gameinfo.Roundinfo.WinnerName = WinnerName(Gameinfo.Roundinfo.WinnerofRound);
        ScreenWinnerColor(Gameinfo.Roundinfo.WinnerofRound);
        TheResultattheRound(i, Gameinfo.Roundinfo);
        if (Gameinfo.Roundinfo.WinnerofRound == enWinnerP1P2::Player2)
        {
            Gameinfo.Player2Wintimes++;
        }
        else if (Gameinfo.Roundinfo.WinnerofRound == enWinnerP1P2::Player1)
        {
            Gameinfo.Player1Wintimes++;
        }
        else {
            Gameinfo.DrawTimes++;
        }
    }
}
void StartGame()
{
    char Playagain = 'Y';
    stGameinfo Gameinfo;
    do
    {
        RestSetting();
        PlayRounds(ReadhowManyRounds(), Gameinfo);
        Gameinfo.ThefinalWinner = FinalWinner(Gameinfo.Player1Wintimes, Gameinfo.Player2Wintimes);
        Gameinfo.ThefinalWinnerName = WinnerName(Gameinfo.ThefinalWinner);
        GameOverscreen();
        GameResult(Gameinfo);
        cout << Taab(2) << "Do you Want to Play again? Y/N?\n";
        cin >> Playagain;
    } while (Playagain == 'Y' || Playagain == 'y');
}
int main()
{
    srand((unsigned)time(NULL));
    StartGame();
    return 0;
}