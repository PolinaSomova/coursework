#include <iostream>

#include "lab1.h"
#include "lab2.h"

using namespace std;

void Menu();

int main() {

    setlocale(LC_ALL, "Russian");

    srand(time (0));
    Menu();

    return 0;
}


void Menu () {

    system("cls");
    cout << "Главное меню: \n\n"
         << "Выберете раздел:\n"
         << "1) Лабораторная работа 1\n"
         << "2) Лабораторная работа 2\n"
         << "0) Выход из программы\n\n"
         << "Введите желаемый вариант: ";

    int choice;
    cin >> choice;
    cin.get();

    switch (choice)
    {
        case 0:
            return;
        case 1:
        {
            system ("cls");
            lab1 lab1;
            lab1.startLab();
            break;
        }
        case 2:
        {
            system ("cls");
            lab2 lab2;
            lab2.startLab();
            break;
        }

    }
    Menu();
}
