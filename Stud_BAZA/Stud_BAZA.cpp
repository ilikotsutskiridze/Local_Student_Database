#include <clocale>
#include "INTERFACE.H"


int main()
{
    bool exit = 1;
    setlocale(LC_ALL, "Russian");

    cout << "Здравствуйте! Эта программа поможет вам в работе с базами данных!\n";
    cout << "Прошу, выведите число, для желаемого действия:\n\n";

    while (exit)
    {
        interface(exit);
        if (exit)
            cout << "Операция выполнена! Что дальше?\n\n";
        else
            cout << "Тогда на этом всё...\n\n\n";
    }
}