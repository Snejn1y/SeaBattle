#include "SeaBattle.h"

SeaBattle::SeaBattle() {
    /*
        ����������� �������� ���� �����, �� ������ ���������� ��� ����� ���� �� ���� ������� ����� �������.
    */

    srand(time(NULL));
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            Pone[i][j] = '-';
            Ptwo[i][j] = '-';
            O[i][j] = '-';
            T[i][j] = '-';
        }
    }
}

bool SeaBattle::CanPlace(char board[10][10], int x, int y, int dir, int len) {
    /*
        ��������, �� ����� ��������� �������� ������ ������� �� �������� ��� ������� ������ �� ������ ������� �� ��������.
    */

    bool place = false;
    for (int i = 0; i < len; i++)
    {
        int px = x + (dir == 0 ? i : 0);
        int py = y + (dir == 1 ? i : 0);
        int xx = (dir == 1 ? 1 : 0);
        int yy = (dir == 0 ? 1 : 0);

        if (board[px][py] != '-' || px < 0 || py < 0 || px >= 10 || py >= 10) {
            return false;
        }
        if (i == 0) {
            if ((px - 1 >= 0 && board[px - 1][py] != '-') || (py - 1 >= 0 && board[px][py - 1] != '-') ||
                (py + 1 < (dir == 1 ? 10 - len + 1 : 10) && board[px][py + 1] != '-') ||
                (px + 1 < (dir == 0 ? 10 - len + 1 : 10) && board[px + 1][py] != '-')) {
                return false;
            }
        }
        else {
            if ((board[px + xx][py - yy] != '-') || (board[px - xx][py + yy] != '-') ||
                (board[px + yy][py + xx] != '-')) {
                return false;
            }
        }
        place = true;
    }
    return place;
}

void SeaBattle::Place(char board[10][10], int x, int y, int dir, int len) {
    /*
        ������ �������� ������ ������� �� �������� ��� ������� ������ �� ������ ������� �� ��������.
    */

    for (int i = 0; i < len; i++)
    {
        int px = x + (dir == 0 ? i : 0);
        int py = y + (dir == 1 ? i : 0);
        board[px][py] = 'S';
    }
}

void SeaBattle::RandomBoard(char board[10][10]) {
    /*
        ������ ��������� ����������� ������� �� �������� ��� ������� ������.
    */

    int ships[10] = { 4, 3, 3, 2, 2, 2, 1, 1, 1, 1};

    for (int i = 0; i < 10; i++)
    {
        int len = ships[i];
        int x, y, dir;
        x = rand() % 10;
        y = rand() % 10;
        dir = rand() % 2;
        while (!CanPlace(board, x, y, dir, len))
        {
            x = rand() % 10;
            y = rand() % 10;
        }
        Place(board, x, y, dir, len);
    }
}
void SeaBattle::ShowBoard(char board[10][10])
{
    /*
        �������� �� ����� ������ ���� ������� ������.
    */

    std::cout << "  0 1 2 3 4 5 6 7 8 9\n";
    for (int i = 0; i < 10; i++)
    {
        std::cout << i << " ";
        for (int j = 0; j < 10; j++)
        {
            std::cout << board[i][j] << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

int SeaBattle::Menu()
{
    /*
        �������� �� ����� ���� ��� �� ������� ����� ��������� ������ ����.
    */

    int v = 4;
    std::cout << std::setw(10) << "Menu\n\n"
        << "1. Playing with a computer;\n"
        << "2. Playing with a second player;\n"
        << "3. Show statistics;\n"
        << "4. Author;\n"
        << "5. Exit.\n\n"
        << ">>> ";
    std::cin >> v;
    system("cls");
    return v;
}

void SeaBattle::Fire(char board[10][10], char bboard[10][10], int x, int y, int& s, int& score)
{
    /*
        ������ ������ �� ����� ������� �� �������� ��� ������� ������ � ������� ���� ������� ����� � ������ ����� ���.
    */

    if (board[x][y] == 'S')
    {
        bboard[x][y] = 'X';
        score += 1;
        s--;
        std::cout << "You have hit the ship!\n";
        board[x][y] = 'X';
        if (board[x][y] != 'S' && board[x - 1][y] != 'S' && board[x][y - 1] != 'S' && board[x][y + 1] != 'S' && board[x + 1][y] != 'S')
        {
            score += 5;
            std::cout << "You destroyed the ship!\n";
        } 
    }
    else
    {
        board[x][y] = '~';
        std::cout << "You miss(\n";
        bboard[x][y] = '~';
    }
}

void SeaBattle::FireEom(char board[10][10], int& s, bool& hit, int& hx, int& hy)
{
    /*
         �������, ��� ������� �� ��� ����'�����. ������� ������ ��������� ������ �� �����, ��� �� �� ���� ���������. 
         ���� ��������� ������ ��� ������� (����� ��� ���������� � ��������), �� ������� �������� ��������� ������ ����� � ��������� ����������, 
         ���� �������� �� ���� ������� ��� � �� ���� ���������, �� �� �� ���� ���� ��������.
    */

    int x = rand() % 10;
    int y = rand() % 10;
    while (board[x][y] == '~' || board[x][y] == 'X')
    {
        x = rand() % 10;
        y = rand() % 10;
    }
    if (hit)
    {
        int i = rand() % 3;

        if(i == 0)
        {
            x = hx - 1;
            y = hy;
            if (board[x][y] == '~' || board[x][y] == 'X')
            {
                x = hx + 1;
                y = hy;
            }
        }
        if (i == 1)
        {
            x = hx + 1;
            y = hy;
            if (board[x][y] == '~' || board[x][y] == 'X')
            {
                x = hx - 1;
                y = hy;
            }
        }
        if (i == 2)
        {
            x = hx;
            y = hy - 1;
            if (board[x][y] == '~' || board[x][y] == 'X')
            {
                x = hx;
                y = hy + 1;
            }
        }
        if (i == 3)
        {
            x = hx;
            y = hy + 1;
            if (board[x][y] == '~' || board[x][y] == 'X')
            {
                x = hx;
                y = hy - 1;
            }
        }
    }
    if (board[x][y] == 'S')
    {
        board[x][y] = 'X';
        std::cout << "AI have hit the ship!\n";
        hit = true;
        hx = x;
        hy = y;
        if (board[x][y] != 'S' && board[x - 1][y] != 'S' && board[x][y - 1] != 'S' && board[x][y + 1] != 'S' && board[x + 1][y] != 'S')
        { 
            hit = false;
            std::cout << "AI destroy ship";
        }
            
    }
    else
    {
        board[x][y] = '~';
        std::cout << "AI miss(\n";
    }
}

void SeaBattle::Stats(int score)
{
    /*
        �������, ��� �������� �� ����� ���������� ������, � ����� ������, �� ���� ������� �������� ��� ���������� � ����. 
        ���� ������� �����������, �� ���� ��'� �� ������� ����������� � ��������� ����.
    */

    std::cout << "Your statistics: " << score;
    bool choose = 0;
    std::cout << "\nDo you want to save it?"
        << ">>> ";
    std::cin >> choose;
    if (choose)
    {
        std::string a;
        std::ofstream out("stats.txt");
        std::ifstream in("stats.txt");

        if (!out.is_open())
        {
            std::cout << "File open error\n";
            exit(0);
        }

        std::cout << "Please enter your nickname: ";
        std::cin >> a;
        in.seekg(0, std::ios_base::beg);
        out << a << " " << score;

        in.close();
        out.close();
    }
}


void SeaBattle::PlayVsEom(SeaBattle& game)
{
    /*
        �������, ��� ������ ��� ����� ����'�����. ������ �� ����'����� ���������� ����� �������������� ������ �� �����. 
        ��� ����� ����, ���� � ������ � ������� �� ���������� ����� �������.
        �� ������� ��� ������� ������� ���������� ������ �� ����� ������������, ���� �� ���� ���������,
        � ���� ���������� ��� ����'�����, �������������� ������� FireEom. 
        ϳ��� ��������� ��� ����������� ������� Stats, ��� �������� �� ����� ���������� ������.
    */

    RandomBoard(game.Pone);
    RandomBoard(game.Ptwo);

    int x, y, hx, hy;
    int po = 20, pt = 20;
    int score = 0;
    bool hit = false;
    while (po > 0 && pt > 0)
    {

        std::cout << std::setw(10) << "Your turn.\n"
            << "Your board: \n";
        ShowBoard(game.Pone);
        std::cout << "Enemy board: \n";
        ShowBoard(game.O);
        std::cout << "Enter X to fire: ";
        std::cin >> y;
        std::cout << "Enter Y to fire : ";
        std::cin >> x;
        system("cls");
        Fire(game.Ptwo, game.O, x, y, po, score);
        
        std::cout << std::setw(10) << "Enemy turn.\n";
        FireEom(game.Pone, pt, hit, hx, hy);

    }
    if (po == 0)
    {
        system("cls");
        std::cout << "Congratulations, you have won!\n";
    }
    if (pt == 0)
    {
        system("cls");
        std::cout << "You have lost(\n";
    }

    Stats(score);
    
}

void SeaBattle::ShowStats()
{
    /*
        �������, ��� �������� �� ����� ������ ������ ���������� ���������� � ���������� ����.
    */

    std::ifstream in("stats.txt");
    int i = 10;
    std::string name;
    int score;
    std::cout << "Nick\tScore\n";
    while (in >> name >> score && i > 0) 
    {
        std::cout << name << "\t" << score << '\n';
        i--;
    }
    while(i > 0)
    {
        std::cout << "-----\t---\n";
        i--;
    }
}

void SeaBattle::Play1vs1(SeaBattle& game)
{
    /*
         �� ������� ������� �� ��� 1 �� 1 �� ����� ��������. 
         ������� ���������� � ����������� ��������� ������� �� ����� ��� ���� �������. 
         ��� �����, ���� ����� (po �� pt) ����-����� � ������� �� ����� �����.
         � ������� ���� ������ ����������� ������� ������ ����������,
         ������� ���������� ���� ����� (x, y) � �������������� ������� Fire.
         ���� ����� ������ � ������� ������ ����, ��� ���������� � 
         ���������� ����������� ��� �������� ���������� ������.
    */

    RandomBoard(game.Pone);
    RandomBoard(game.Ptwo);

    int x, y;
    int po = 20, pt = 20;
    int score = 0;
    bool hit = false;
    while (po > 0 && pt > 0)
    {

        std::cout << std::setw(10) << "Player 1 turn.\n"
            << "Your board: \n";
        ShowBoard(game.Pone);
        std::cout << "Enemy board: \n";
        ShowBoard(game.O);
        std::cout << "Enter X to fire: ";
        std::cin >> y;
        std::cout << "Enter Y to fire : ";
        std::cin >> x;
        system("cls");
        Fire(game.Ptwo, game.O, x, y, po, score);

        std::cout << std::setw(10) << "Player 2 turn.\n"
            << "Your board: \n";
        ShowBoard(game.Ptwo);
        std::cout << "Enemy board: \n";
        ShowBoard(game.T);
        std::cout << "Enter X to fire: ";
        std::cin >> y;
        std::cout << "Enter Y to fire : ";
        std::cin >> x;
        system("cls");
        Fire(game.Pone, game.T, x, y, pt, score);
    }
    if (po == 0)
    {
        system("cls");
        std::cout << "Player 1 win!\n";
    }
    if (pt == 0)
    {
        system("cls");
        std::cout << "Player 2 win!\n";
    }
}

void SeaBattle::Game(SeaBattle& game)
{
    /*
        �� ������� ����������� ������� ���� ��� ��� "�������� ��".

        ������� ����� ��� ���������� � switch-��������, �� �������� �� ����� ����������� � ��������� ����.

        1. PlayVsEom(game) - �� �������, ��� �������� ������ ����� ����� ����'�����.
        2. Play1vs1(game) - �� ������� �������� ������� ����� ���� ����� ������.
        3. ShowStats() - �� ������� �������� ���������� ��� ���.
        4. ���������� ���������� ��� ������ �������� �� ��������� ���������� �� ��������� ����.
        5. exit(0) - ��������������� ��� ������ � ��������.

        ϳ��� ��������� ����-��� � ��� �������, ������������ ����������, �� �� ���� ����� �����, 
        ��� ���������� ������� �� �������� ������� ��� �� ��������� ����. 
        ϳ��� ������� ������ ���� ���������� �������� ����������� ���� �� ��������� system("cls").
    */
    int a;
    while(true)
        switch (Menu())
        {
            case 1:
                PlayVsEom(game);
                std::cout << "Do you want play again?\n"
                    << ">>> ";
                std::cin >> a;
                if (a)
                    Play1vs1(game);
                system("cls");
                break;
            case 2:
                Play1vs1(game);
                std::cout << "Do you want play again?\n"
                    << ">>> ";
                std::cin >> a;
                if(a)
                    Play1vs1(game);
                system("cls");
                break;
            case 3:
                ShowStats();
                std::cout << "Type 1 if you want to back a main menu\n"
                    << ">>> ";
                std::cin >> a;
                if (a)
                {
                    system("cls");
                }
                break;
            case 4:
                std::cout << std::setw(20) << "Author\n\n"
                    << "This program was made by Denis Lutsak\n"
                    << "Telegram: @Snejn1y\n"
                    << "Mail for feedback: dlutsak@knu.ua\n\n"
                    << "Type 1 if you want to back a main menu\n"
                    << ">>> ";
                std::cin >> a;
                if (a)
                {
                    system("cls");
                }
                break;
            case 5:
                std::cout << "Thank you for your time!\n";
                exit(0);
                break;
            default:
                std::cout << "You entered an incorrect value, please try again.\n\n";
                break;
        }

}
