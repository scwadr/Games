#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
const int n = 3;

char table[2 * n + 1][2 * n + 1];
bool win = false;
bool win1 = true;
bool win2 = true;

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

void checkWin()
{
    for (int i = 0; i < n; i++)
    {
        if (table[2 * (i + 1) - 1][2 * (i + 1) - 1] == ' ')
            continue;
        for (int j = 3; j <= 2 * n + 1; j += 2)
        {
            if (table[2 * (i + 1) - 1][j] != table[2 * (i + 1) - 1][j - 2])
                break;
            if (j + 2 > 2 * n + 1)
            {
                win = true;
            }
        }
        for (int j = 3; j < 2 * n + 1; j += 2)
        {
            if (table[j][2 * (i + 1) - 1] != table[j - 2][2 * (i + 1) - 1])
                break;
            if (j + 2 > 2 * n + 1)
            {
                win = true;

            }
        }
    }
    if (table[1][1] != ' ')
    {
        if (win1)
            for (int j = 3; j < 2 * n + 1; j += 2)
            {
                if (table[j][j] != table[j - 2][j - 2])
                {
                    win1 = false;
                    break;
                }
                if (j == 2 * n - 1)
                {
                    win = true;
                }
            }
        win1 = true;
    }
    if (table[2 * n - 1][1] != ' ')
    {
        if (win2)
            for (int j = 2 * n - 3; j < -1; j -= 2)
            {
                if (table[j][j] != table[j + 2][j + 2])
                {
                    win2 = false;
                    break;
                }
                if (j == 2 * n - 1)
                {
                    win = true;

                }
            }
        win2 = true;
    }
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

pair <int, int> botStep()
{
    pair <int, int> xy;
    xy.first = rand() % 3 + 1;
    xy.second = rand() % 3 + 1;
    return xy;
}

int main()
{
    cout << "hello";
    int cnt = 0;
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
        player2 = 1;
    }
    pair <int, int> step;
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
                    step = botStep();
                    x = step.first;
                    y = step.second;
                }
            }
            else
            {
                if (player2 == 0)
                    cin >> x >> y;
                else
                {
                    step = botStep();
                    x = step.first;
                    y = step.second;
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
        checkWin();
        cnt++;
    }
    if (win)
        cout << cur << " WINS!";
    else
        cout << "It's a draw";
    return 0;
}
