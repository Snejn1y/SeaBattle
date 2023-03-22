#include <cstdlib>
#include <ctime>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

class SeaBattle {
private:
    char Pone[10][10];
    char Ptwo[10][10];
    char O[10][10];
    char T[10][10];
    int playerCount;
public:
    SeaBattle();
    bool CanPlace(char Pone[10][10], int x, int y, int dir, int len);
    void Place(char Pone[10][10], int x, int y, int dir, int len);
    void RandomBoard(char Pone[10][10]);
    void ShowBoard(char Pone[10][10]);
    void Game(SeaBattle& game);
    void PlayVsEom(SeaBattle& game);
    int Menu();
    void Fire(char board[10][10], char bboard[10][10], int x, int y, int& s, int& score);
    void FireEom(char board[10][10], int& s, bool& hit, int& hx, int& hy);
    void Stats(int score);
    void ShowStats();
    void Play1vs1(SeaBattle& game);
    ~SeaBattle() {};
};

