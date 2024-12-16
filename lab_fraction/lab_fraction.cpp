#include <iostream>
#include <locale>
using namespace std;

// Структура для представления обыкновенной дроби
struct drob {
    int chislitel;   // Числитель
    int znamenatel; // Знаменатель
};

// Функция для вычисления наибольшего общего делителя (НОД) по алгоритму Евклида
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Функция для упрощения дроби
void yproshenie(drob& drob1) {
    int rezGZD = gcd(abs(drob1.chislitel) ,abs(drob1.znamenatel));

    drob1.chislitel /= rezGZD;

    drob1.znamenatel /= rezGZD;
    // Обеспечиваем, чтобы знаменатель был положительным
    if (drob1.znamenatel < 0) {
        drob1.chislitel = -drob1.chislitel;
        drob1.znamenatel = -drob1.znamenatel;
    }
}

// Функция для сравнения дробей
bool FractionEq(const drob& a, const drob& b) {
    return a.chislitel == b.chislitel && a.znamenatel == b.znamenatel;
}

// Функция для вывода дроби на экран
void display(const drob& frac) {
    cout << frac.chislitel << "/" << frac.znamenatel << endl;
}

// Функция для вычисления целой части дроби
int tselaya(const drob& frac) {
    return frac.chislitel / frac.znamenatel;
}

// Функция для сложения дробей
drob closhenie(const drob& a, const drob& b) {
    drob result;
    result.chislitel = a.chislitel * b.znamenatel + b.chislitel * a.znamenatel;
    result.znamenatel = a.znamenatel * b.znamenatel;
    yproshenie(result);
    return result;
}

// Функция для вычитания дробей
drob vichitanie(const drob& a, const drob& b) {
    drob result;
    result.chislitel = a.chislitel * b.znamenatel - b.chislitel * a.znamenatel;
    result.znamenatel = a.znamenatel * b.znamenatel;
    yproshenie(result);
    return result;
}

// Функция для умножения дробей
drob ymnoshenie(const drob& a, const drob& b) {
    drob result;
    result.chislitel = a.chislitel * b.chislitel;
    result.znamenatel = a.znamenatel * b.znamenatel;
    yproshenie(result);
    return result;
}

// Функция для деления дробей
drob del(const drob& a, const drob& b) {
    if (b.chislitel == 0) {
        throw invalid_argument("Деление на ноль!");
    }
    drob result;
    result.chislitel = a.chislitel * b.znamenatel;
    result.znamenatel = a.znamenatel * b.chislitel;
    yproshenie(result);
    return result;
}

// Функция для работы с дробью и целым числом
drob dobcel(const drob& frac, int integer) {
    return closhenie(frac, { integer, 1 });
}


// Вспомогательные функции и макросы для тестирования
void Test(bool expr) {
    if (expr)
        cout << "passed" << endl;
    else
        cout << "error" << endl;
}

#define TEST(expr) \
    cout << "Test " << #expr << "... "; \
    Test((expr));


int main() {
    setlocale(LC_ALL, "Russian");

    drob frac1 = { 3, 4 }; // 3/4
    drob frac2 = { 5, 6 }; // 5/6

    cout << "Первая дробь: ";
    display(frac1);
    cout << "Вторая дробь: ";
    display(frac2);

    // Тестируем сумму дробей
    TEST(FractionEq(closhenie(frac1, frac2), { 19, 12 }));

    // Тестируем разность дробей
    TEST(FractionEq(vichitanie(frac1, frac2), { -1, 12 }));

    // Тестируем произведение дробей
    TEST(FractionEq(ymnoshenie(frac1, frac2), { 5, 8 }));

    // Тестируем деление дробей
    TEST(FractionEq(del(frac1, frac2), { 9, 10 }));

    // Тестируем целую часть дроби
    TEST(tselaya(frac1) == 0);

    // Тестируем сложение дроби с целым числом
    TEST(FractionEq(dobcel(frac1, 2), { 11, 4 }));

    return 0;

}

