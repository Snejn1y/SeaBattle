#include "SeaBattle.h"

SeaBattle::SeaBattle() {
    /*
        Конструктор ініціалізує змінні класу, що містять інформацію про розмір поля та стан ігрових дошок гравців.
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
        Перевіряє, чи можна розмістити корабель заданої довжини на ігровому полі певного гравця по заданій позиції та орієнтації.
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
        розміщує корабель заданої довжини на ігровому полі певного гравця по заданій позиції та орієнтації.
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
        генерує випадкову розстановку кораблів на ігровому полі певного гравця.
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
        виводить на екран ігрове поле певного гравця.
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
        виводить на екран меню гри та повертає номер вибраного пункту меню.
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
        виконує постріл по певній клітинці на ігровому полі певного гравця і оновлює стан ігрових дошок і оцінку стану гри.
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
         функція, яка відповідає за хід комп'ютера. Функція вибирає випадкову клітину на дошці, яка ще не була атакована. 
         Якщо попередній постріл був удачним (тобто був попаданням у корабель), то функція продовжує атакувати клітини поряд з попереднім попаданням, 
         доки корабель не буде знищено або ж не буде визначено, що він не може бути знищений.
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
        функція, яка виводить на екран статистику гравця, а також запитує, чи бажає гравець зберегти свої результати у файлі. 
        Якщо гравець погоджується, то його ім'я та рахунок записуються у текстовий файл.
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
        функція, яка реалізує гру проти комп'ютера. Гравцю та комп'ютеру випадковим чином розставляються кораблі на дошці. 
        Гра триває доти, доки у когось з гравців не закінчаться життя кораблів.
        На кожному ході гравець вводить координати клітини на дошці супротивника, куди він хоче постріляти,
        і потім виконується хід комп'ютера, використовуючи функцію FireEom. 
        Після закінчення гри викликається функція Stats, яка виводить на екран статистику гравця.
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
        функція, яка виводить на екран десять кращих результатів збережених у текстовому файлі.
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
         ця функція відповідає за гру 1 на 1 між двома гравцями. 
         Функція починається з випадкового розміщення кораблів на дошці для двох гравців. 
         Гра триває, доки життя (po та pt) будь-якого з гравців не стане нулем.
         У кожному циклі гравці намагаються знищити кораблі противника,
         вводячи координати своїх вогнів (x, y) і використовуючи функцію Fire.
         Якщо життя одного з гравців досягає нуля, гра закінчується і 
         виводиться повідомлення про перемогу відповідного гравця.
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
        Ця функція представляє ігровий цикл для гри "Морський бій".

        Основна логіка гри виконується в switch-структурі, що базується на виборі користувача з головного меню.

        1. PlayVsEom(game) - це функція, яка дозволяє гравцю грати проти комп'ютера.
        2. Play1vs1(game) - ця функція дозволяє гравцям грати один проти одного.
        3. ShowStats() - ця функція відображає статистику про гру.
        4. Виводиться інформація про автора програми та можливість повернення до головного меню.
        5. exit(0) - використовується для виходу з програми.

        Після виконання будь-якої з цих функцій, користувачеві запитується, чи він хоче грати знову, 
        тоді відбувається перехід до відповідної функції або до головного меню. 
        Після кожного вибору меню відбувається очищення консольного вікна за допомогою system("cls").
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
