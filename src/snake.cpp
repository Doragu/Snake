#include "snake.h"
#include "cpoint.h"
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string.h>

using namespace std;

CSnake::CSnake(CRect r, char _c /*=' '*/): CFramedWindow(r, _c)
{
  snake.push_back(CPoint(4, 2));
  snake.push_back(CPoint(3, 2));
  snake.push_back(CPoint(2, 2));
  food.y = geom.size.y/2;
  food.x = geom.size.x/2;
}

CSnake::~CSnake()
{
  snake.clear();
}

void CSnake::paint()
{
  CFramedWindow::paint();
  paintSnake();
  paintFood();
  paintLevel();
  if (menu==1)
    showMenu();
  if (dead==1)
    showGameOver();
}

void CSnake::paintSnake()
{
  gotoyx(snake[0].y + geom.topleft.y, snake[0].x + geom.topleft.x);
  printl("x");

  for (unsigned int i=1;i<snake.size();i++)
  {
    gotoyx(snake[i].y + geom.topleft.y, snake[i].x + geom.topleft.x);
    printl("o");
  }
}

void CSnake::paintFood()
{
  gotoyx(food.y + geom.topleft.y, food.x + geom.topleft.x);
  printl("@");
}

void CSnake::paintLevel()
{
  char text[15];
  sprintf (text, "| LEVEL: %lu |", (snake.size()-3)/2);

  gotoyx(geom.topleft.y-1, geom.topleft.x);
  printl(text);
}


bool CSnake::handleEvent(int key)
{
  if (key=='h')
  {
    actKey = 0;

    if (menu==1)
      menu=0;
    else 
        menu=1;  
    return true;
  }

  if (key=='p')
  {
    actKey = 0;

    if (pause==1)
        pause=0;
    else 
        pause=1;  
    return true;
  }

  if (key=='r')
  {
    snake.clear();
    snake.push_back(CPoint(4, 2));
    snake.push_back(CPoint(3, 2));
    snake.push_back(CPoint(2, 2));
    lastKey=KEY_RIGHT;
    menu = 1;
    pause = 0;
    dead = 0;
    return true;
  }

  if((menu==1 || pause==1) && CFramedWindow::handleEvent(key))
    return true;

  if (key!=ERR)
    actKey = key;

  eatingTail();  
  if (dead==1)
    return true;
    
  if (menu==0 && pause==0 && dead==0)
  {
    eatingFood();
    
    switch (actKey)
    {
      case KEY_UP:
        moveUp();
        return true;
      case KEY_DOWN:
        moveDown();
        return true;
      case KEY_RIGHT:
        moveRight();
        return true;
      case KEY_LEFT:
        moveLeft();
        return true;
      default:
        actKey = lastKey;
        return true;
    };
  } 
  return false;
}

void CSnake::eatingTail()
{
  for (unsigned int i=2;i<snake.size();i++)
    if (snake[0].y == snake[i].y && snake[0].x == snake[i].x)
    {
      dead = 1;
      break;
    }
}

void CSnake::eatingFood()
{
  if (snake[0].y == food.y && snake[0].x == food.x)
  {
    addTail();
    newFood();
  }
}

void CSnake::addTail()
{
  snake.push_back(CPoint(0, 0));
}

void CSnake::newFood()
{
  int checker = 0;
  
  do
  {
    checker = 0;
    food.y = rand()%(geom.size.y-2);
    food.x = rand()%(geom.size.x-2);
      
    for (unsigned int i=0;i<snake.size();i++)
      if (food.y == snake[i].y || food.x == snake[i].x || food.x == 0 || food.y == 0)
        checker = 1;

  }while (checker == 1);
}

void CSnake::moveUp()
{
  if (lastKey!=KEY_DOWN)
  {
    for (int i=snake.size()-1;i>0;i--)
    {
      snake[i].y = snake[i-1].y;
      snake[i].x = snake[i-1].x;
    }
    if (snake[0].y-1 <= 0)
      snake[0].y = geom.size.y-2;
    else 
      snake[0].y--;

    lastKey = actKey;
  }
  else
    actKey = lastKey;
  //paintSnake();
}

void CSnake::moveDown()
{
  if (lastKey!=KEY_UP)
  {
    for (int i=snake.size()-1;i>0;i--)
    {
      snake[i].y = snake[i-1].y;
      snake[i].x = snake[i-1].x;
    }
    if (snake[0].y >= geom.size.y-2)
      snake[0].y = 1;
    else 
      snake[0].y++;

    lastKey = actKey;
  }
  else
    actKey = lastKey;
  //paintSnake();
}

void CSnake::moveRight()
{
  if (lastKey!=KEY_LEFT)
  {
    for (int i=snake.size()-1;i>0;i--)
    {
      snake[i].y = snake[i-1].y;
      snake[i].x = snake[i-1].x;
    }
    if (snake[0].x >= geom.size.x-2)
      snake[0].x = 1;
    else 
      snake[0].x++;

    lastKey = actKey;
  }
  else
    actKey = lastKey;
  //paintSnake();
}

void CSnake::moveLeft()
{
  if (lastKey!=KEY_RIGHT)
  {
    for (int i=snake.size()-1;i>0;i--)
    {
      snake[i].y = snake[i-1].y;
      snake[i].x = snake[i-1].x;
    }
    if (snake[0].x-1 <= 0)
      snake[0].x = geom.size.x-2;
    else 
      snake[0].x--;

    lastKey = actKey;
  }
  else
    actKey = lastKey;
  //paintSnake();
}

void CSnake::showMenu()
{
  int y = geom.topleft.y + 4;
  int x = geom.topleft.x + 5;

  gotoyx(y, x);
  printl("h - toggle help information");

  gotoyx(y+1, x);
  printl("p - toggle pause/play mode");

  gotoyx(y+2, x);
  printl("r - restart game");

  gotoyx(y+3, x);
  printl("arrows - move snake (in play mode) or");
  
  gotoyx(y+4, x+8);
  printl("move window (in pause mode)");
}

void CSnake::showGameOver()
{
  char text[30];
  sprintf (text, "GAME OVER, result: %lu", snake.size()-3);

  gotoyx(geom.topleft.y+1, geom.topleft.x+1);
  printl(text);
}