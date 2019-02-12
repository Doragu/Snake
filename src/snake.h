#ifndef __SNAKE_H__
#define __SNAKE_H__

#include "screen.h"
#include "winsys.h"
#include <vector>

using namespace std;

class CSnake:public CFramedWindow
{
public:
  vector <CPoint> snake;
  int menu=1;
  int pause=0;
  int dead=0;
  int lastKey=KEY_RIGHT;
  int actKey;
  CPoint food;

  CSnake(CRect r, char _c = ' ');
  ~CSnake();
  void paint();
  void showMenu();
  void showGameOver();
  void paintFood();
  void paintSnake();
  void paintLevel();
  bool handleEvent(int key);
  void eatingTail();
  void eatingFood();
  void addTail();
  void newFood();
  void moveUp();
  void moveDown();
  void moveRight();
  void moveLeft();
};

#endif


/*
Brak wyświetlania wyniku po grze
Brak pola aktualnego poziomu
Brak zwiększania szybkości wraz z poziomem
*/