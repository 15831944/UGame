
#include "stdafx.h"
#include "xgame.h"
#include "ElapsedTimer.h"

ElapsedTimer::ElapsedTimer()
:hours_(0L) , minute_(0) , second_(0) , leftSecond_(0L) , elapsedSecond_(0L)
{
}

ElapsedTimer::ElapsedTimer(unsigned long h , unsigned char m , unsigned char s)
:hours_(h) , minute_(m) , second_(s) , elapsedSecond_(0L)
{
  leftSecond_ = second_  + minute_ * 60 + hours_ * 3600;
}

ElapsedTimer::ElapsedTimer(double total_s)
{
  leftSecond_ = total_s;
  elapsedSecond_ = 0;
  Second2Timer();
}

ElapsedTimer::~ElapsedTimer()
{
}

void ElapsedTimer::Init(unsigned long h , unsigned char m , unsigned char s)
{
  if(s > 59){ s = 59; }
  if(m > 59){ m = 59; }
  hours_ = h; 
  minute_ = m; 
  second_ = s; 
  leftSecond_ = second_  + minute_ * 60 + hours_ * 3600; 
  elapsedSecond_ = 0L;
}
void ElapsedTimer::Init(double total_s)
{
  leftSecond_ = total_s;
  elapsedSecond_ = 0L;
  Second2Timer();
}

void ElapsedTimer::Go(unsigned long elapsed_second )
{
  if( __int64(leftSecond_ - elapsed_second) <= 0)
  {
    leftSecond_ = 0;
  }
  else
  {
    leftSecond_ -= elapsed_second;
  }
  elapsedSecond_ += elapsed_second;
  Second2Timer();
}

