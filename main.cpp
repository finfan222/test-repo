﻿#include <vector>
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

void initTests()
{
    tests.push_back(test_body_contains1);
    tests.push_back(test_body_contains2);
    tests.push_back(test_body_contains3);
    tests.push_back(test_contains1);
    tests.push_back(test_contains2);
    tests.push_back(test_contains3);
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
