
#include "stdafx.h"
#include "xgame.h"
#include "HighFrequencyElapsedTimer.h"

HighFrequencyElapsedTimer::HighFrequencyElapsedTimer()
:hours_(0L) , minute_(0) , second_(0) , leftmillSecond_(0.0) , elapsedmillSecond_(0.0)
{
}

HighFrequencyElapsedTimer::HighFrequencyElapsedTimer(double total_ms)
{
  leftmillSecond_ = total_ms;
  elapsedmillSecond_ = 0;
  MSecond2Timer();
}

void HighFrequencyElapsedTimer::Init(double total_ms)
{
  leftmillSecond_ = total_ms;
  elapsedmillSecond_ = 0L;
  MSecond2Timer();
}

void HighFrequencyElapsedTimer::Go(unsigned long elapsed_msecond )
{
  if(__int64(leftmillSecond_ - elapsed_msecond) <= 0)
  {
    leftmillSecond_ = 0.0;
  }
  else
  {
    leftmillSecond_ -= elapsed_msecond;
  }
  elapsedmillSecond_ += elapsed_msecond;
  MSecond2Timer();
}

