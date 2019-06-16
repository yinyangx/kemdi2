// Written by Yoon-Su Ra on June 26, 2018 to guess a 3 digit code (no repeats)
// using hints of right numbers (circles) and right locations (triangle).

#include <iostream>
#include <vector>
#include <algorithm>


using namespace std;

// Puts all possible codes in a vector of ints.
vector<int> initializer()
{ 
  vector<int> list = {};
  for (int a = 1; a < 10; a++)
  {
    for (int b = 1; b < 10; b++)
    {
      for (int c = 1; c < 10; c++)
      {
        if (a != b && a != c && b != c)
        {
          list.push_back(100*a + 10*b + c);
        }
      }
    }
  }
  return list;
}

// Returns all combinations that can have only a 2 circle response.
vector<int> twoCircles(vector<int> list, int digit1, int digit2, int digit3,
                                         int check1, int check2, int check3)
{
  for (int d = 0; d < list.size(); d++)
  {
    check1 = list[d]/100;
    check2 = (list[d]%100)/10;
    check3 = list[d]%10;
    if (!((check1 == digit1 && check2 == digit2) ||
          (check1 == digit1 && check3 == digit3) ||
          (check2 == digit2 && check3 == digit3)))
    {
      list.erase(list.begin()+d);
      d--;
    }     
  }
  return list;
}

// Returns all combinations that can have only a 1 circle response.
vector<int> oneCircles(vector<int> list, int digit1, int digit2, int digit3,
                                         int check1, int check2, int check3)
{
  for (int d = 0; d < list.size(); d++)
  {
    check1 = list[d]/100;
    check2 = (list[d]%100)/10;
    check3 = list[d]%10;
    if (!(check1 == digit1 || check2 == digit2 || check3 == digit3))
    {
      list.erase(list.begin()+d);
      d--;
    }      
  }
  vector<int> list2 = twoCircles(list, digit1, digit2, digit3, check1, check2, check3);
  vector<int> difference;
  set_difference(list.begin(), list.end(), list2.begin(), list2.end(), back_inserter(difference));
  return difference;
}

// Returns all combinations that can have only a 0 circle response.
vector<int> zeroCircles(vector<int> list, int digit1, int digit2, int digit3,
                                          int check1, int check2, int check3)
{
  for (int d = 0; d < list.size(); d++)
  {
    check1 = list[d]/100;
    check2 = (list[d]%100)/10;
    check3 = list[d]%10;
    if (check1 == digit1 || check2 == digit2 || check3 == digit3)
    {
      list.erase(list.begin()+d);
      d--;
    }      
  }
  return list;
}

// Returns all combinations that can have only a 3 triangle response.
vector<int> threeTriangles(vector<int> list, int digit1, int digit2, int digit3,
                                          int check1, int check2, int check3)
{                                          
  for (int e = 0; e < list.size(); e++)
  {
    check1 = list[e]/100;
    check2 = (list[e]%100)/10;
    check3 = list[e]%10;
    if (!((check1 == digit2 || check1 == digit3) && (check2 == digit1 || check2 == digit3) &&
          (check3 == digit1 || check3 == digit2)))
    {
      list.erase(list.begin()+e);
      e--;
    }      
  }
  return list;
}

// Returns all combinations that can have only a 2 triangle response.
vector<int> twoTriangles(vector<int> list, int digit1, int digit2, int digit3,
                                          int check1, int check2, int check3)
{                                          
  for (int e = 0; e < list.size(); e++)
  {
    check1 = list[e]/100;
    check2 = (list[e]%100)/10;
    check3 = list[e]%10;
    if (!((check1 == digit2 && check2 == digit1) || (check1 == digit2 && check2 == digit3) ||
          (check1 == digit2 && check3 == digit1) || (check1 == digit3 && check2 == digit1) ||
          (check1 == digit3 && check3 == digit1) || (check1 == digit3 && check3 == digit2) ||
          (check2 == digit1 && check3 == digit2) || (check2 == digit3 && check3 == digit1) ||
          (check2 == digit3 && check3 == digit2)))
    {
      list.erase(list.begin()+e);
      e--;
    }      
  }
  vector<int> list2 = threeTriangles(list, digit1, digit2, digit3, check1, check2, check3);
  vector<int> difference;
  set_difference(list.begin(), list.end(), list2.begin(), list2.end(), back_inserter(difference));
  return difference;
}

// Returns all combinations that can have only a 1 triangle response.
vector<int> oneTriangles(vector<int> list, int digit1, int digit2, int digit3,
                                          int check1, int check2, int check3)
{                                          
  for (int e = 0; e < list.size(); e++)
  {
    check1 = list[e]/100;
    check2 = (list[e]%100)/10;
    check3 = list[e]%10;
    if (!((check1 == digit2 || check1 == digit3) || (check2 == digit1 || check2 == digit3) ||
          (check3 == digit1 || check3 == digit2)))
    {
      list.erase(list.begin()+e);
      e--;
    }
  
  }
  vector<int> list2 = threeTriangles(list, digit1, digit2, digit3, check1, check2, check3);
  vector<int> difference;
  set_difference(list.begin(), list.end(), list2.begin(), list2.end(), back_inserter(difference));
  list = difference;
  vector<int> list3 = twoTriangles(list, digit1, digit2, digit3, check1, check2, check3);
  vector<int> difference2;
  set_difference(list.begin(), list.end(), list3.begin(), list3.end(), back_inserter(difference2));
  return difference2;
}

// Returns all combinations that can have only a 0 triangle response.
vector<int> zeroTriangles(vector<int> list, int digit1, int digit2, int digit3,
                                          int check1, int check2, int check3)
{                                          
  for (int e = 0; e < list.size(); e++)
  {
    check1 = list[e]/100;
    check2 = (list[e]%100)/10;
    check3 = list[e]%10;
    if ((check1 == digit2 || check1 == digit3) ||
        (check2 == digit1 || check2 == digit3) ||
        (check3 == digit1 || check3 == digit2))
    {
      list.erase(list.begin()+e);
      e--;
    }      
  }
  return list;
} 

void solver()
{
  // Initialization.
  vector<int> list = initializer();
  
  // Variables for checking response.
  int response;
  int circle;
  int triangle;
  int digit1;
  int digit2;
  int digit3;
  int check1;
  int check2;
  int check3;
  int count = 1;
  int number;
  
  while (true)
  {
    if (count == 2)
    {
      number = 456;
    }
    else
    {
      number = list[0];
    }
    cout << number << endl;
    digit1 = number/100;
    digit2 = (number%100)/10;
    digit3 = number%10;
    cout << "Enter response: ";
    cin >> response;
    circle = response/10;
    triangle = response%10;
  
    
    if (response != 30)
    {
      list.erase(remove(list.begin(), list.end(), number), list.end());
    }
  
    switch (response)
    {
      case 01: list = zeroCircles(list, digit1, digit2, digit3, check1, check2, check3);
               list = oneTriangles(list, digit1, digit2, digit3, check1, check2, check3);
               break;
      case 02: list = zeroCircles(list, digit1, digit2, digit3, check1, check2, check3);
               list = twoTriangles(list, digit1, digit2, digit3, check1, check2, check3);
               break;
      case 03: list = zeroCircles(list, digit1, digit2, digit3, check1, check2, check3);
               list = threeTriangles(list, digit1, digit2, digit3, check1, check2, check3); 
               break;
      case 10: list = oneCircles(list, digit1, digit2, digit3, check1, check2, check3);
               list = zeroTriangles(list, digit1, digit2, digit3, check1, check2, check3);
               break;
      case 11: list = oneCircles(list, digit1, digit2, digit3, check1, check2, check3);
               list = oneTriangles(list, digit1, digit2, digit3, check1, check2, check3);
               break;
      case 12: list = oneCircles(list, digit1, digit2, digit3, check1, check2, check3);
               list = twoTriangles(list, digit1, digit2, digit3, check1, check2, check3);
               break;
      case 20: list = twoCircles(list, digit1, digit2, digit3, check1, check2, check3);
               list = zeroTriangles(list, digit1, digit2, digit3, check1, check2, check3);
               break;
      case 30: return;      
      default: list = zeroCircles(list, digit1, digit2, digit3, check1, check2, check3);
               list = zeroTriangles(list, digit1, digit2, digit3, check1, check2, check3);
               break;
    }
    count++;
  }
}

int main()
{
  int round = 0;
  while(round < 4)
  {
    solver();
    round++;
  }
}