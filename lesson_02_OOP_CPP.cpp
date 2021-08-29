//============================================================================
// Name        : lesson_02_OOP_CPP.cpp
// Author      : andry antonenko
// IDE         : Qt Creator 4.14.2 based on Qt 5.15.2
// Description : lesson 02 of the object-oriented programming on C++ course
//============================================================================
#include <QCoreApplication>
#include <iostream>
#include <random>
#include <stdlib.h>
#include <cmath>
#include <chrono>
#include <list>
#include <string>
#include <sstream>
using namespace std;
//----------------------------------------------------------------------------
//#define NDEBUG
#include <cassert>
//----------------------------------------------------------------------------
int getRandomNum(int min, int max)
{
  const static auto seed = std::chrono::system_clock::now().time_since_epoch().count();
  static std::mt19937_64 generator(seed);
  std::uniform_int_distribution<int> dis(min, max);
  return dis(generator);
}
//----------------------------------------------------------------------------
/*
1. Создать класс Person (человек) с полями: имя, возраст, пол и вес.
Определить методы переназначения имени, изменения возраста и веса.
Создать производный класс Student (студент), имеющий поле года обучения.
Определить методы переназначения и увеличения этого значения.
Создать счетчик количества созданных студентов.
В функции main() создать несколько студентов.
По запросу вывести определенного человека.
//*/

enum Status
{
  STATUS_OK,
  ERROR_NO,
  ERROR_LIM,
  STACK_EMPTY
};

enum Gender
{
  MAN,
  WOMAN,
};

class Person
{
  string name;
  int age;
  Gender gender;
  double weight;

public:
  Person(string aName = "", int aAge = 0, Gender aGender = Gender::MAN, double aWeight = 0)
    :name(aName),age(aAge),gender(aGender),weight(aWeight)
  {}

  Status setName(string aName)
  {
    if(aName != "")
    {
      name = aName;
      return STATUS_OK;
    }
    return ERROR_LIM;
  }
  string getName() const {return name;}

  Status setAge(int aAge)
  {
    if(aAge > 0)
    {
      age = aAge;
      return STATUS_OK;
    }
    return ERROR_LIM;
  }
  int getAge() const {return age;}

  Status setWeight(double aWeight)
  {
    if(aWeight > 0)
    {
      weight = aWeight;
      return STATUS_OK;
    }
    return ERROR_LIM;
  }
  double getWeight() const {return weight;}
  Gender getGender() const {return gender;}
};

class Student: public Person
{
  static int countStudents;
  int yearOfLearning;

public:
  Student(string aName = "", int aAge = 0, Gender aGender = Gender::MAN,
          double aWeight = 0,int aYearOfLearning = 0)
      : Person(aName,aAge,aGender,aWeight),yearOfLearning(aYearOfLearning)
  {
    Student::countStudents++;
  }
  ~Student()
  {
    Student::countStudents--;
  }
  Status setYearOfLearning(int aYearOfLearning)
  {
    if(aYearOfLearning > 0)
    {
      yearOfLearning = aYearOfLearning;
      return STATUS_OK;
    }
    return ERROR_LIM;
  }
  Status incYearOfLearning()
  {
    yearOfLearning++;
    return STATUS_OK;
  }
  int getYearOfLearning() const {return yearOfLearning;}
  static int getCountStudents()
  {
    return Student::countStudents;
  }
  void print() const
  {
    cout << getName() << " ";
    cout << getAge() << " ";
    cout << (getGender() == MAN ? "MAN " : "WOMAN ");
    cout << getWeight() << " ";
    cout << getYearOfLearning() << " ";
    cout << endl;
  }
};

int Student::countStudents = 0;

/*
2. Создать классы Apple (яблоко) и Banana (банан),
которые наследуют класс Fruit (фрукт).
У Fruit есть две переменные-члена: name (имя) и color (цвет).
Добавить новый класс GrannySmith, который наследует класс Apple.

int main()
{
    Apple a("red");
    Banana b;
    GrannySmith c;

    std::cout << "My " << a.getName() << " is " << a.getColor() << ".\n";
    std::cout << "My " << b.getName() << " is " << b.getColor() << ".\n";
    std::cout << "My " << c.getName() << " is " << c.getColor() << ".\n";

    return 0;
}

Код, приведенный выше, должен давать следующий результат:

My apple is red.
My banana is yellow.
My Granny Smith apple is green.
//*/

class Fruit
{
public:
  string color;
  string name;
  Fruit(string aColor = "", string aName = "")
    :color(aColor),name(aName) {};
  string getName() const {return name;}
  string getColor() const {return color;}
};

class Apple: public Fruit
{
public:
  Apple(string aColor = "",string aName = "apple")
    :Fruit(aColor,aName) {};
};

class Banana: public Fruit
{
public:
  Banana(string aColor = "yellow",string aName = "banana")
    :Fruit(aColor,aName) {};
};

class GrannySmith: public Apple
{
public:
  GrannySmith(string aColor = "green",string aName = "Granny Smith apple")
    :Apple(aColor,aName) {};
};

/*
3. Изучить правила игры в Blackjack.
Подумать, как написать данную игру на С++,
используя объектно-ориентированное программирование.
Сколько будет классов в программе?
Какие классы будут базовыми, а какие производными?
Продумать реализацию игры с помощью классов и записать результаты.
//*/

class Card
{

};

class DeckCard
{
  list<Card> lCards;
};

class Player: public Person
{
  list<Card> lCards;
};

class Croupier: public Player
{

};

class CardGameBlackJack
{
  Croupier croupier;
  list<Player> lPlayers;
};

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
void task_1()
{
  cout << "Task 1\n" << endl;

  //Test 1
  cout << "Test 1\n" << endl;

  list<Student*> lStudents;

  int AMOUND = 8;

  cout << "Add " << AMOUND << " of students:" << endl;
  for(int i = 0; i < AMOUND; i++)
  {
    stringstream ss;
    ss << "name_" << Student::getCountStudents();

    Student *pSudent = new Student(ss.str(),
                    getRandomNum(18,100),
                    getRandomNum(0,100)%2 == 0 ? MAN:WOMAN,
                    getRandomNum(50,100),
                    getRandomNum(1,5));
    pSudent->print();

    lStudents.push_back(pSudent);
  }

  if(Student::getCountStudents() == AMOUND)
  {
    cout << "CountStudents " << Student::getCountStudents() <<
            " equals AMOUND " << AMOUND << endl;
  }
  else
  {
    cout << "CountStudents " << Student::getCountStudents() <<
            " doesn't equal AMOUND " << AMOUND << endl;
  }

  //Test 2
  cout << "\nTest 2" << endl;

  string nameLookingFor = "name_2";//the name you are looking for

  for(Student* p: lStudents)
  {
    if(p->getName() == nameLookingFor)
    {
      cout << "Student " << p->getName() << " was found:" << endl;
      p->print();
    }
  }

  while(!lStudents.empty())
  {
    Student *p = lStudents.front();
    if(p != nullptr)
    {
      delete p;
    }
    lStudents.pop_front();
  }

  cout << endl;
}
//----------------------------------------------------------------------------
void task_2()
{
  cout << "Task 2\n" << endl;

  Apple a("red");
  Banana b;
  GrannySmith c;

  std::cout << "My " << a.getName() << " is " << a.getColor() << ".\n";
  std::cout << "My " << b.getName() << " is " << b.getColor() << ".\n";
  std::cout << "My " << c.getName() << " is " << c.getColor() << ".\n";

  cout << endl;
}
//----------------------------------------------------------------------------
int main(int argc, char *argv[])
{
  QCoreApplication a(argc, argv);
  //----------------------------------------------------------------------------
  // Task 1
  //*
  task_1();
  //*/
  //----------------------------------------------------------------------------
  // Task 2
  //*
  task_2();
  //*/
  //----------------------------------------------------------------------------
  return a.exec();
}
//----------------------------------------------------------------------------
