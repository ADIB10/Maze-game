#include <iostream>
#include <vector>
#include <windows.h>
#include <conio.h>
#include <random>
#include <ctime>
#include <cstdlib>
#include <algorithm>
using namespace std;

int HEIGHT=40,WIDTH=100,playerX,playerY,temp2=0;
vector<pair<int,int>> pai,pai2;
string s;
bool done=false;
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
void gotoxy(int x,int y)//positioning
{
    COORD coord={x,y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}
vector<vector<char>> grid(HEIGHT, vector<char>(WIDTH, char(219)));  // Fill with block char //inistial grid
void hideCursor() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hOut, &cursorInfo);
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(hOut, &cursorInfo);
}
void Grid(vector<vector<char>>& grid,int startx,int starty)// drawing the grid
{
    string output;gotoxy(startx,starty);
    for (int y = 0; y < HEIGHT; y++) {

        for (int x = 0; x < WIDTH; x++) {
                //cout<<grid[y][x];
            output+=grid[y][x];
        }output+='\n';
        //cout<<endl;
    }cout<<output;
}

void move() //creating the maze it-self
{
static vector<vector<bool>> visited(HEIGHT, vector<bool>(WIDTH, false));// new from gpt

    grid[playerY][playerX] = ' ';
    visited[playerY][playerX] = true;

    vector<pair<int, int>> directions = {{0, 2}, {0, -2}, {2, 0}, {-2, 0}};

    random_shuffle(directions.begin(), directions.end());

    bool moved = false;

    for (auto&p : directions) {
        int nx = playerX + p.first;
        int ny = playerY + p.second;

        if (ny > 0 && ny < HEIGHT - 1 && nx > 0 && nx < WIDTH - 1 && !visited[ny][nx]) {

            grid[playerY + (p.second / 2)][playerX + (p.first / 2)] = ' ';
            pai.push_back({playerX, playerY});
            pai2.push_back({playerX, playerY});
            playerX = nx;
            playerY = ny;
            moved = true;
            break;
        }
    }

    if (!moved && !pai.empty()) {//backtracking its way for a suitable spot
        playerX = pai.back().first;
        playerY = pai.back().second;
        pai.pop_back();

    }
    if(pai.size()==0){done=true;}
    cout<<pai.back().first<<' '<<pai.back().second;
    //grid[playerY][playerX] = '@';
}
void solver()// automatically solving it
{
    pai.clear();
    int temp=rand()%pai2.size();
    playerX=pai2[temp].first;
    playerY=pai2[temp].second;
    pai.push_back({playerX,playerY});
    bool solved=false;
    while(solved==false)
    {Grid(grid,0,0);
    while(grid[playerY][playerX+1]==' '&&!solved)
    {
        playerX++;grid[playerY][playerX]='.';pai.push_back({playerX,playerY});
        if(grid[playerY+1][playerX]=='O'||grid[playerY-1][playerX]=='O'||grid[playerY][playerX+1]=='O'||grid[playerY][playerX-1]=='O'){solved=true;break;}
    }
    while(grid[playerY][playerX-1]==' '&&!solved)
    {
        playerX--;grid[playerY][playerX]='.';pai.push_back({playerX,playerY});
        if(grid[playerY+1][playerX]=='O'||grid[playerY-1][playerX]=='O'||grid[playerY][playerX+1]=='O'||grid[playerY][playerX-1]=='O'){solved=true;break;}
    }
    while(grid[playerY+1][playerX]==' '&&!solved)
    {
        playerY++;grid[playerY][playerX]='.';pai.push_back({playerX,playerY});
        if(grid[playerY+1][playerX]=='O'||grid[playerY-1][playerX]=='O'||grid[playerY][playerX+1]=='O'||grid[playerY][playerX-1]=='O'){solved=true;break;}
    }
    while(grid[playerY-1][playerX]==' '&&!solved)
    {
        playerY--;grid[playerY][playerX]='.';pai.push_back({playerX,playerY});
        if(grid[playerY+1][playerX]=='O'||grid[playerY-1][playerX]=='O'||grid[playerY][playerX+1]=='O'||grid[playerY][playerX-1]=='O'){solved=true;break;}
    }
    if(grid[playerY][playerX+1]!=' '&&grid[playerY][playerX-1]!=' '&&grid[playerY+1][playerX]!=' '&&grid[playerY-1][playerX]!=' '&&!solved)
    {
        while(true)// backtracking its way to last passed junction point
        {
            int bx=pai.back().first,by=pai.back().second;
            if(grid[by+1][bx]==' '||grid[by-1][bx]==' '||grid[by][bx+1]==' '||grid[by][bx-1]==' ')
            {
                 playerY=by;
                 playerX=bx;
                 break;
            }pai.pop_back();
        }
    }cout<<playerY<<playerX;

    }
    if(solved)// final solution
    {
        for(auto&p:pai)
        {
            grid[p.second][p.first]='X';Grid(grid,0,0);
            Sleep(16);
        }
    }
    system("pause>nul");

}
void manually()
{
    int temp=rand()%pai2.size();
    playerX=pai2[temp].first;
    playerY=pai2[temp].second;
    int counter=0,minute=0,second=0;
    while(true)
    {
        if(GetAsyncKeyState('W')&&grid[playerY-1][playerX]==' '){grid[playerY][playerX] = ' '; playerY--;}
        if(GetAsyncKeyState('S')&&grid[playerY+1][playerX]==' '){grid[playerY][playerX] = ' '; playerY++;}
        if(GetAsyncKeyState('D')&&grid[playerY][playerX+1]==' '){grid[playerY][playerX] = ' '; playerX++;}
        if(GetAsyncKeyState('A')&&grid[playerY][playerX-1]==' '){grid[playerY][playerX] = ' '; playerX--;}
        grid[playerY][playerX]='@';

        Sleep(33);
        Grid(grid,0,0);
        counter++;
        cout<<"TIME :"<<(counter*33/1000)/60<<":"<<(counter*33/1000)%60;
        if(grid[playerY][playerX]=='O'){cout<<"SOLVED";done=true;break;}
    }
}
void reset()
{

    for(int i=0;i<WIDTH;i++)
    {
        for(int j=0;j<HEIGHT;j++)
        {
            grid[j][i]=char(219);
        }
    }
}

int main()
{srand(time(0));

int temp=rand();
playerX=temp%(WIDTH-2)+1;
playerY=temp%(HEIGHT-2)+1;
    int counter=0;
    hideCursor();

    while(done==false)
    {
        counter++;
        Grid(grid,0,0);
        move();
    }
    system("cls");
    //grid[1][1]=' ';
    Grid(grid,0,0);

    gotoxy(0,WIDTH+2);
    cout<<"DO YOU WANT SOLVE IT AUTOMETICALLY\nY-FOR YES\nN-FRO NO\n>>";
    char cha;
    cin>>cha;
    temp=rand()%pai2.size();
    grid[pai2[temp].second][pai2[temp].first]='O';
    if(cha=='Y'||cha=='y')
        {Sleep(1000);
        Grid(grid,0,0);
        solver();}

    else{done=false;
        while(!done)
        {Sleep(1000);
        Grid(grid,0,0);
            manually();
        }
    }
        return 0;
}

