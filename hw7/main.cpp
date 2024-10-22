//
//  main.cpp
//  hw7
//
//  Created by Valeria Dudinova on 22.10.2024.
//

#include <iostream>
#include <string>
using namespace std;

class Bankomat
{
private:
    int id;  // Ідентифікаційний номер банкомату
    int cash100;  // Кількість купюр номіналом 100
    int cash200;  // Кількість купюр номіналом 200
    int cash500;  // Кількість купюр номіналом 500
    int cash1000; // Кількість купюр номіналом 1000
    int minWithdrawal; // Мінімальна сума для зняття
    int maxWithdrawal; // Максимальна сума для зняття

public:
    // Конструктор ініціалізації банкомату
    Bankomat(int id, int minW, int maxW) : id(id), cash100(0), cash200(0), cash500(0), cash1000(0), minWithdrawal(minW), maxWithdrawal(maxW) {}

    // Метод для завантаження купюр у банкомат
    void loadCash(int c100, int c200, int c500, int c1000)
    {
        cash100 += c100;
        cash200 += c200;
        cash500 += c500;
        cash1000 += c1000;
        cout << "Banknotes are successfully vandalized.\n";
    }

    // Метод для зняття грошей з банкомату
    void withdraw(int amount)
    {
        if (amount < minWithdrawal)
        {
            cout << "The amount is less than the minimum allowable for withdrawal.\n";
            return;
        }
        if (amount > maxWithdrawal)
        {
            cout << "The amount exceeds the maximum allowable for withdrawal.\n";
            return;
        }

        // Перевірка наявної суми грошей в банкоматі
        int total = cash100 * 100 + cash200 * 200 + cash500 * 500 + cash1000 * 1000;
        if (amount > total)
        {
            cout << "Not enough money at the ATM to withdraw this amount.\n";
            return;
        }

        // Алгоритм видачі купюр
        int remaining = amount;

        int take1000 = min(remaining / 1000, cash1000);
        remaining -= take1000 * 1000;

        int take500 = min(remaining / 500, cash500);
        remaining -= take500 * 500;

        int take200 = min(remaining / 200, cash200);
        remaining -= take200 * 200;

        int take100 = min(remaining / 100, cash100);
        remaining -= take100 * 100;

        // Якщо залишилася сума, яку не можна видати, відміняємо операцію
        if (remaining != 0)
        {
            cout << "It is impossible to see the exact amount from actual banknotes. Operation canceled.\n";
            return;
        }

        // Видаємо купюри
        cash1000 -= take1000;
        cash500 -= take500;
        cash200 -= take200;
        cash100 -= take100;

        cout << "issued: " << take1000 << " bills for 1000, "
             << take500 << " bills for 500, "
             << take200 << " bills for 200, "
             << take100 << " bills for 100.\n";
    }

    // Метод для виведення залишку грошей у банкоматі
    string toString() const
    {
        int total = cash100 * 100 + cash200 * 200 + cash500 * 500 + cash1000 * 1000;
        return "The total amount in the ATM: " + to_string(total) + " GRN.";
    }
};

int main()
{
    // Ініціалізуємо банкомат
    Bankomat atm(1, 100, 5000);

    // Завантажуємо купюри
    atm.loadCash(10, 5, 3, 2);

    // Виводимо загальну суму
    cout << atm.toString() << endl;

    // Спробуємо зняти гроші
    atm.withdraw(3700);

    // Виводимо залишок
    cout << atm.toString() << endl;

    return 0;
}
