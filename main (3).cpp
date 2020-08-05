#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
using namespace std;
const int n = 3;

struct BestMove {
    int score;
    int x;
    int y;
};

char table[2 * n + 1][2 * n + 1];
bool win = false;
bool win1 = true;
bool win2 = true;
bool winX = false;
bool winO = false;
int cnt = 0;

void draw()
{
    for (int i = 0; i < 2 * n + 1; i++)
    {
        for (int j = 0; j < 2 * n + 1; j++)
        {
            if (i + j == 0 || i + j == 4 * n || (i == 2 * n && j == 0) || (j == 2 * n && i == 0))
            {
                table[0][0] = 201;
                table[2 * n][0] = 200;
                table[0][2 * n] = 187;
                table[2 * n][2 * n] = 188;
            }
            else if (i % 2 == 0 && j % 2 == 1)
            {
                table[i][j] = 205;
                continue;
            }
            else if (i % 2 == 1 && j % 2 == 0)
            {
                table[i][j] = 186;
            }
            else if (i == 0 && j != 0 && j != 2 * n)
            {
                table[i][j] = 203;
            }
            else if (i == 2 * n && j != 0 && j != 2 * n)
            {
                table[i][j] = 202;
            }
            else if (j == 2 * n && i != 0 && i != 2 * n)
            {
                table[i][j] = 185;
            }
            else if (j == 0 && i != 0 && i != 2 * n)
            {
                table[i][j] = 204;
            }
            else if (i % 2 == 0 && j % 2 == 0)
            {
                table[i][j] = 206;
            }
        }
    }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
        {
            table[2 * i - 1][2 * j - 1] = ' ';
        }
}

bool checkWin(char tableWin[2 * n + 1][2 * n + 1])
{
    for (int i = 0; i < n; i++)
    {
        if (tableWin[2 * (i + 1) - 1][2 * (i + 1) - 1] == ' ')
            continue;
        for (int j = 3; j < 2 * n + 1; j += 2)
        {
            if (tableWin[2 * (i + 1) - 1][j] != tableWin[2 * (i + 1) - 1][j - 2])
            {

                break;
            }
            //cout<<i<<' '<<j<<"did not break";
            if (j == 2 * n - 1)
            {
                //cout<<"***"<<'\n';
                win = true;
            }
        }
        for (int j = 3; j < 2 * n + 1; j += 2)
        {
            if (tableWin[j][2 * (i + 1) - 1] != tableWin[j - 2][2 * (i + 1) - 1])
                break;
            if (j == 2 * n - 1)
            {
                //cout<<"+++"<<'\n';
                win = true;
                if (tableWin[2 * (i + 1) - 1][2 * (i + 1) - 1] == 'x')
                    winX = true;
                else
                    winO = true;
            }
        }
    }
    if (tableWin[1][1] != ' ')
    {
        if (win1)
            for (int j = 3; j < 2 * n + 1; j += 2)
            {
                if (tableWin[j][j] != tableWin[j - 2][j - 2])
                {
                    win1 = false;
                    break;
                }
                if (j == 2 * n - 1)
                {
                    //cout<<"---"<<'\n';
                    win = true;
                    if (tableWin[j][j] == 'x')
                        winX = true;
                    else
                        winO = true;
                }
            }
        win1 = true;
    }
    if (tableWin[2 * n - 1][1] != ' ')
    {
        if (win2)
            for (int j = 3; j < 2 * n + 1; j += 2)
            {
                if (tableWin[2 * n - j][j] != tableWin[2 * n - j + 2][j - 2])
                {
                    win2 = false;
                    break;
                }
                if (j == 2 * n - 1)
                {
                    //cout<<"///"<<'\n';
                    win = true;
                    if (tableWin[2 * n - j][j] == 'x')
                        winX = true;
                    else
                        winO = true;
                }
            }
        win2 = true;
    }
    return win;
}

pair <char, char> chooseMode()
{
    pair <char, char> gameMode;
    cout << "Please choose a game mode(type 'P' for player, 'B' for bot). If you choose a bot for crosses, this will be bot vs. bot match" << '\n';
    cout << "X: ";
    cin >> gameMode.first;
    if (gameMode.first == 'B')
    {
        gameMode.second = 'B';
        return gameMode;
    }
    cout << "O: ";
    cin >> gameMode.second;
    return gameMode;
}

BestMove botStep(char tempTable[2*n+1][2*n+1], int count)
{
    int res = -1;
    bool gameFinished;
    BestMove whatToReturn;
    whatToReturn.score = -47;
    int score;
    int justToCheckOneThing;
    gameFinished = checkWin(tempTable) || (cnt == n * n);
    //cout<<gameFinished<<' '<<checkWin(tempTable)<<'\n';
    win=false;
    if (!gameFinished)
    {
        for (int i = 1; i < 2 * n; i += 2)
        {
            for (int j = 1; j < 2 * n; j += 2)
            {
                if (tempTable[i][j] == ' ')
                {
                    justToCheckOneThing = cnt % 2;
                    if (justToCheckOneThing == 0)
                        tempTable[i][j] = 'x';
                    else
                        tempTable[i][j] = 'o';
                    score = botStep(tempTable, count + 1).score;
                    tempTable[i][j] = ' ';
                    if (count % 2 == justToCheckOneThing)
                    {
                        if (score > res)
                        {
                            res = score;
                            whatToReturn.x = (i+1)/2;
                            whatToReturn.y = (j+1)/2;
                        }
                    }
                    else
                    {
                        if (score < res)
                        {
                            res = score;
                            whatToReturn.x = (i+1)/2;
                            whatToReturn.y = (j+1)/2;
                        }
                    }
                }
            }
        }
    }
    else
    {
        if (!checkWin(tempTable))
        {
            whatToReturn.score = 0;
        }
        else
        {
            if (winX && justToCheckOneThing == 0)
                whatToReturn.score = 1;
            else if (winX)
                whatToReturn.score = -1;
            else if (winO && justToCheckOneThing == 1)
                whatToReturn.score = 1;
            else
                whatToReturn.score = -1;
        }
    }
    win=false;
    if (whatToReturn.score = -47)
    {
        whatToReturn.score = res;
    }
    winX = false;
    winO = false;
    return whatToReturn;
}


int main()
{
    int x, y;
    int player1, player2;
    char cur;
    bool fin = false;
    pair <char, char> mode;
    mode = chooseMode();
    draw();
    if (mode.first == 'B')
    {
        player1 = 1;
        player2 = 1;
    }
    else if (mode.second == 'B')
    {
        player1 = 0;
        player2 = 1;
    }
    else
    {
        player1 = 0;
        player2 = 0;
    }
    BestMove step;
    while (!win)
    {
        if (cnt == n * n)
            break;
        if (cnt % 2 == 0)
        {
            cout << "x step: ";
            cur = 'x';
        }
        else
        {
            cout << "o step: ";
            cur = 'o';
        }
        while (!fin)
        {
            if (cur == 'x')
            {
                if (player1 == 0)
                    cin >> x >> y;
                else
                {
                    step = botStep(table, cnt);
                    x = step.x;
                    y = step.y;
                    cout << x << ' ' << y;
                }
            }
            else
            {
                if (player2 == 0)
                    cin >> x >> y;
                else
                {
                    step = botStep(table, cnt);
                    x = step.x;
                    y = step.y;
                    cout << x << ' ' << y;
                }
            }
            cout << '\n';
            if (x > n || y > n || x < 1 || y < 1 || table[2 * x - 1][2 * y - 1] != ' ')
            {
                cout << "bad coordinates, try again" << '\n';
                cout << cur << " step: ";
            }
            else
            {
                fin = true;
            }
        }
        fin = false;
        cout << '\n';
        table[2 * x - 1][2 * y - 1] = cur;
        system("cls");
        for (int i = 0; i <= 2 * n; i++)
        {
            for (int j = 0; j <= 2 * n; j++)
            {
                cout << table[i][j];
            }
            cout << '\n';
        }
        checkWin(table);
        winX = false;
        winO = false;
        cnt++;
    }
    if (win)
        cout << cur << " WINS!";
    else
        cout << "It's a draw";
    return 0;
}
