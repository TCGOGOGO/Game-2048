#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cstring>
#include <conio.h>
#include <cstdlib>
#include <windows.h>
#define Coord_x 15
#define Coord_y 15
#define Height  20
#define Width  16

using namespace std;

class Game
{
    public:
        int score;
        int num[5][5];

    public:
        Game(int s = 0);
        bool control(char ch);
        void init();
        void make();
}G;

class Console
{
    public:
        void gotoxy(HANDLE hOut, int x, int y);
        void enter_game();
        void window();
        void show();
        void start_game();
        void end_game();

    friend class Game;
}C;

Game::Game(int s)
{
    score = s;
    memset(num,0,sizeof(num));
}

void Console::gotoxy(HANDLE hOut, int x, int y)
{
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(hOut, pos);
}

void Console::enter_game()
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    system("title 2048 by Tc");
    gotoxy(hOut,Coord_x+Width-1,Coord_y-12);
    SetConsoleTextAttribute(handle,FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
    cout<<"  欢迎进入 2 0 4 8";
    SetConsoleTextAttribute(handle,FOREGROUND_INTENSITY | FOREGROUND_GREEN);
    gotoxy(hOut,Coord_x+Width-25,Coord_y-8);
    cout << "        *  *           *  *            *        *        *  *         " << endl;
    gotoxy(hOut,Coord_x+Width-25,Coord_y-7);
    cout << "     *        *     *        *        *        *       *      *            " << endl;
    gotoxy(hOut,Coord_x+Width-25,Coord_y-6);
    cout << "    *        *     *          *      *        *         *    *            " << endl;
    gotoxy(hOut,Coord_x+Width-25,Coord_y-5);
    cout << "           *       *          *     *        *             *                     " << endl;
    gotoxy(hOut,Coord_x+Width-25,Coord_y-4);
    cout << "         *         *          *    *  *  *  *  * *      *      *     " << endl;
    gotoxy(hOut,Coord_x+Width-25,Coord_y-3);
    cout << "       *           *          *            *          *          *                 " << endl;
    gotoxy(hOut,Coord_x+Width-25,Coord_y-2);
    cout << "     *              *        *            *            *        *               " << endl;
    gotoxy(hOut,Coord_x+Width-25,Coord_y-1);
    cout << "  *  *  *  *  *        *  *              *                *  *      " << endl;
    gotoxy(hOut,Coord_x+Width+1,Coord_y+3);
    SetConsoleTextAttribute(handle,FOREGROUND_INTENSITY | FOREGROUND_RED);
    cout << "按回车键进入游戏\n"<< endl;;
    while(1)
    {
        char c;
        if(kbhit())
        {
            c = getch();
            if(c == 13)
            {
                system("CLS");
                C.start_game();
            }
        }
    }
    if(getch() == 27)
    {
        C.end_game();
    }
}


void Console::end_game()
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    system("CLS");
    gotoxy(hOut,Coord_x+Width+5,Coord_y-10);
    SetConsoleTextAttribute(handle,FOREGROUND_INTENSITY | FOREGROUND_RED);
    cout << "游戏结束";
    gotoxy(hOut,Coord_x+Width+5,Coord_y-7);
    cout << "最终得分 : " << G.score << endl;
    SetConsoleTextAttribute(handle,FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
    exit(0);
}

void Console::window()
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    system("title 2 0 4 8 by Tc");
    system("color 0C");
    gotoxy(hOut,Coord_x+Width-2,Coord_y-13);
    cout << " *******";
    gotoxy(hOut,Coord_x+Width-2,Coord_y-12);
    cout << " 2 0 4 8";
    gotoxy(hOut,Coord_x+Width-2,Coord_y-11);
    cout << " *******";
    gotoxy(hOut,Coord_x+2*Width+3,Coord_y+6);
    SetConsoleTextAttribute(handle,FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
    gotoxy(hOut,Coord_x+2*Width+3 + 2,Coord_y - 8);
    cout << "w键 : 向上  " << "s键 : 向下";
    gotoxy(hOut,Coord_x+2*Width+3 + 2,Coord_y - 6);
    cout << "a键 : 向左  " << "d键 : 向右";
    gotoxy(hOut,Coord_x+2*Width+3 + 2,Coord_y - 4);
    cout << "Esc ：退出";
}

void Console :: show()
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(handle,FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_RED);
    gotoxy(hOut,Coord_x+2*Width+3 + 2,Coord_y - 10);
    cout << "                   ";
    gotoxy(hOut,Coord_x+2*Width+3 + 2,Coord_y - 10);
    cout << "分数 : " << G.score;
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            if(G.num[i][j] != 0)
            {
                cout << " ";
                SetConsoleTextAttribute(handle,FOREGROUND_INTENSITY | FOREGROUND_RED);
                gotoxy(hOut, Coord_x + 6 + j * 8,Coord_x - 8 + i * 4);
                cout << G.num[i][j];
            }
            else
            {
                cout << " ";
                SetConsoleTextAttribute(handle,FOREGROUND_INTENSITY | FOREGROUND_GREEN);
                gotoxy(hOut, Coord_x + 6 + j * 8,Coord_x - 8 + i * 4);
                cout << "■";
            }
        }
        cout << endl;
    }

}

bool Game::control(char dir)
{
    int num2[4][4];
    for(int n = 0; n < 4; n++)
        for(int m = 0; m < 4; m++)
            num2[n][m] = num[n][m];
    bool IsMove = false;
    if(dir == 'w' || dir == 'W')
    {
        for(int j = 0; j < 4; j++)
        {
            int ii = 0, temp = 5;
            for(int i = 0; i < 4; i++)
            {
                if(num[i][j] == 0)
                    continue;
                else
                {
                    temp = i;
                    break;
                }
            }
            if(temp == 5)
                continue;
            num[ii][j] = num[temp][j];
            for(int i = temp + 1; i < 4; i++)
            {
                if(num[i][j] == 0)
                    continue;
                else if(num[i][j] != 0 && num[i][j] == num[ii][j])
                {
                    num[ii][j] *= 2;
                    G.score += num[ii][j];
                    num[i][j] = 0;
                }
                else if(num[i][j] != 0 && num[i][j] != num[ii][j])
                    num[++ii][j] = num[i][j];
            }
            while(ii < 4)
                num[++ii][j] = 0;
            for(int n = 0; n < 4; n++)
            {
                for(int m = 0; m < 4; m++)
                {
                    if(num2[n][m] != num[n][m])
                    {
                        IsMove = true;
                        break;
                    }
                }
                if(IsMove)
                    break;
            }
        }
        return IsMove;
    }
    else if(dir == 's' || dir == 'S')
    {
        for(int j = 0; j < 4; j++)
        {
            int ii = 3, temp = 5;
            for(int i = 3; i >= 0; i--)
            {
                if(num[i][j] == 0)
                    continue;
                else
                {
                    temp = i;
                    break;
                }
            }
            if(temp == 5)
                continue;
            num[ii][j] = num[temp][j];
            for(int i = temp - 1; i >= 0; i--)
            {
                if(num[i][j] == 0)
                    continue;
                else if(num[i][j] != 0 && num[i][j] == num[ii][j])
                {
                    num[ii][j] *= 2;
                    G.score += num[ii][j];
                    num[i][j] = 0;
                }
                else if(num[i][j] != 0 && num[i][j] != num[ii][j])
                    num[--ii][j] = num[i][j];
            }
            while(ii >= 0)
                num[--ii][j] = 0;
            for(int n = 0; n < 4; n++)
            {
                for(int m = 0; m < 4; m++)
                {
                    if(num2[n][m] != num[n][m])
                    {
                        IsMove = true;
                        break;
                    }
                }
                if(IsMove)
                    break;
            }
        }
        return IsMove;
    }
    else if(dir == 'a' || dir == 'A')
    {
        for(int i = 0; i < 4; i++)
        {
            int jj = 0, temp = 5;
            for(int j = 0; j < 4; j++)
            {
                if(num[i][j] == 0)
                    continue;
                else
                {
                    temp = j;
                    break;
                }
            }
            if(temp == 5)
                continue;
            num[i][jj] = num[i][temp];
            for(int j = temp + 1; j < 4; j++)
            {
                if(num[i][j] == 0)
                    continue;
                else if(num[i][j] != 0 && num[i][j] == num[i][jj])
                {

                    num[i][jj] *= 2;
                    G.score += num[i][jj];
                    num[i][j] = 0;
                }
                else if(num[i][j] != 0 && num[i][j] != num[i][jj])
                {

                    num[i][++jj] = num[i][j];
                }
            }
            while(jj < 4)
            {
                num[i][++jj] = 0;
            }
            for(int n = 0; n < 4; n++)
            {
                for(int m = 0; m < 4; m++)
                {
                    if(num2[n][m] != num[n][m])
                    {
                        IsMove = true;
                        break;
                    }
                }
                if(IsMove)
                    break;
            }
        }
        return IsMove;
    }
    else if(dir == 'd' || dir == 'D')
    {
        for(int i = 0; i < 4; i++)
        {
            int jj = 3, temp = 5;
            for(int j = 3; j >= 0; j--)
            {
                if(num[i][j] == 0)
                    continue;
                else
                {
                    temp = j;
                    break;
                }
            }
            if(temp == 5)
                continue;
            num[i][jj] = num[i][temp];
            for(int j = temp - 1; j >= 0 && jj > 0; j--)
            {
                if(num[i][j] == 0)
                    continue;
                else if(num[i][j] != 0 && num[i][j] == num[i][jj])
                {
                    num[i][jj] *= 2;
                    G.score += num[i][jj];
                    num[i][j] = 0;
                }
                else if(num[i][j] != 0 && num[i][j] != num[i][jj])
                    num[i][--jj] = num[i][j];
            }
            while(jj > 0)
                num[i][--jj] = 0;
            for(int n = 0; n < 4; n++)
            {
                for(int m = 0; m < 4; m++)
                {
                    if(num2[n][m] != num[n][m])
                    {
                        IsMove = true;
                        break;
                    }
                }
                if(IsMove)
                    break;
            }
        }
        return IsMove;
    }
    return false;
}

void Game :: init()
{
    srand((unsigned int) time(NULL));
    int x = rand() % 4;
    int y = rand() % 4;
    G.num[x][y] = 2;
    int xx = rand() % 4;
    int yy = rand() % 4;
    while(1)
    {
        if(xx != x && yy != y)
        {
            G.num[xx][yy] = 2;
            break;
        }
        xx = rand() % 4;
        yy = rand() % 4;
    }
}

void Game :: make()
{
    int count = 0;
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            if(num[i][j])
                count ++;
        }
    }
    if(count == 16)
        C.end_game();
    int xx = rand() % 4;
    int yy = rand() % 4;
    while(1)
    {
        if(num[xx][yy] == 0)
        {
            num[xx][yy] = 2;
            break;
        }
        xx = rand() % 4;
        yy = rand() % 4;
    }
}

void Console :: start_game()
{
    G.init();
    window();
    show();
    char dir;
    while(true)
    {
        bool flag = false;
        dir = getch();
        if(dir == 27)
            end_game();
        if(dir == 'w' || dir == 'W' || dir == 'a' || dir == 'A' || dir == 's' || dir == 'S' || dir == 'D' || dir == 'd')
        {
            flag = G.control(dir);
            window();
            if(flag)
                G.make();
            show();
        }
    }
}

int main()
{
    C.enter_game();
}
