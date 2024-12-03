#include <vector>
#include <functional>
#include <iostream>

#include "candle.h"

//массив всех тестов, который мы заполняем в функции initTests
static std::vector<std::function<bool()>> tests;

// для is_green (return price >= open && price <= close;) where close = max (close > open)
bool test_body_contains1() {
    Candle data(0.5, 0, 0, 1.0);
    // 0.99 >= 0.5 && 0.99 <= 1 
    return data.body_contains(0.99);
}

// для !is_green (return price >= close && price <= open;) where open = max
bool test_body_contains2() {
    Candle data(1, 0, 0, 0.5);
    // 0.99 >= 1 && 0.99 <= 0.5
    return data.body_contains(0.99);
}

// в случае если close = open
bool test_body_contains3() {
    Candle data(1.0, 0, 0, 1.0);
    return data.body_contains(1.0);
}

// проверка содержания цены в границах low/high
bool test_contains1() {
    // price >= low && price <= high
    Candle data(0.0, 1, 0, 0);
    return data.contains(0.5); // true если 0.5 between 1 & 0
}

// проверка выхода за нижюю границу low
bool test_contains2() {
    // price >= low && price <= high
    Candle data(0.0, 1, 0, 0);
    return !data.contains(-1.0); // true если !(price >= low)
}

// проверка выхода за высшую границу high
bool test_contains3() {
    // price >= low && price <= high
    Candle data(0.0, 1, 0, 0);
    return !data.contains(2.0); // true если !(price >= low && price !(price <= high))
}

// проверка негативного значения
bool test_full_size1() {
    Candle data(0.0, 0, 1, 0);
    double result = data.full_size();
    return result == 1;
}

// проверка позитивного значения
bool test_full_size2() {
    Candle data(0.0, 1, 0, 0);
    double result = data.full_size();
    return result == 1;
}

// проверка zero значения
bool test_full_size3() {
    Candle data(0.0, 0, 0, 0);
    double result = data.full_size();
    return result == 0;
}

// проверка негативного значения
bool test_body_size1() {
    Candle data(0, 0, 0, 1);
    double result = data.body_size();
    return result == 1;
}

// проверка позитивного значения
bool test_body_size2() {
    Candle data(1, 0, 0, 0);
    double result = data.body_size();
    return result == 1;
}

// проверка zero значения
bool test_body_size3() {
    Candle data(0, 0, 0, 0);
    double result = data.body_size();
    return result == 0;
}

// проверка true значения close < open
// на вход: close=0, open=1
// PASSED если close < open, т.к. оно == red
bool test_is_red1() {
    return Candle(1, 0, 0, 0).is_red();
}

// проверка false значения close < open
// на вход: close=1, open=0
// PASSED если close > open, т.к. оно != red
bool test_is_red2() {
    return !Candle(0, 0, 0, 1).is_red();
}

// проверка equals значения
// на вход: close=0, open=0
// PASSED если close == open, т.к. оно != red
bool test_is_red3() {
    return !Candle(0, 0, 0, 0).is_red();
}

// проверка true значения
// на вход: close=1, open=0
// PASSED если close > open, т.к. оно == green
bool test_is_green1() {
    return Candle(0, 0, 0, 1).is_green();
}

// проверка false значения
// на вход: close=0, open=1
// PASSED если close < open, т.к. оно != green
bool test_is_green2() {
    return !Candle(1, 0, 0, 0).is_green();
}

// проверка true значения
// на вход: close=0, open=0
// PASSED если close == open, т.к. оно != green
bool test_is_green3() {
    return !Candle(0, 0, 0, 0).is_green();
}

void initTests()
{
    tests.push_back(test_body_contains1);
    tests.push_back(test_body_contains2);
    tests.push_back(test_body_contains3);
    tests.push_back(test_contains1);
    tests.push_back(test_contains2);
    tests.push_back(test_contains3);
    tests.push_back(test_full_size1);
    tests.push_back(test_full_size2);
    tests.push_back(test_full_size3);
    tests.push_back(test_body_size1);
    tests.push_back(test_body_size2);
    tests.push_back(test_body_size3);
    tests.push_back(test_is_red1);
    tests.push_back(test_is_red2);
    tests.push_back(test_is_red3);
    tests.push_back(test_is_green1);
    tests.push_back(test_is_green2);
    tests.push_back(test_is_green3);
}

int launchTests()
{
  int total = 0;
  int passed = 0;

  for (const auto& test : tests)
  {
    std::cout << "test #" << (total + 1);
    if (test())
    {
      passed += 1;
      std::cout << " passed\n";
    }
    else
    {
      std::cout << " failed\n";
    }
    total += 1;
  }

  std::cout << "\ntests " << passed << "/" << total << " passed!" << std::endl;

  //0 = success
  return total - passed;
}

int main()
{
  initTests();
  return launchTests();
}
