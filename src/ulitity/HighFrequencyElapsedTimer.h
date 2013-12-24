// HighFrequencyElapsedTimer.h: interface for the HighFrequencyElapsedTimer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(HIGH_FRQUENCY_TIMER)
#define HIGH_FRQUENCY_TIMER


class HighFrequencyElapsedTimer  
{
private:
  unsigned long hours_;
  unsigned char minute_;
  unsigned char second_;
  unsigned short millsecond_;
  double        leftmillSecond_;
  double        elapsedmillSecond_;

public:
	HighFrequencyElapsedTimer();
  HighFrequencyElapsedTimer(double total_ms);

  double GetLeftMSecond() const    {return leftmillSecond_;}
  double GetElapseMSecond() const  {return elapsedmillSecond_;}

  void Init(double total_ms);
  void Go(unsigned long elapsed_msecond = 1);
  bool IsZero() {return __int64(leftmillSecond_) == 0L;}
  CString ToCString()
  {
    CString temp;
    temp.Format("%d:%02d:%02d.%d" , hours_ , minute_ , second_ , millsecond_);
    return temp;
  }

  unsigned long GetHour() const {return hours_;}
  unsigned char GetMinute() const {return minute_;}
  unsigned char GetSecond() const {return second_;}
  unsigned short GetMSecond() const {return millsecond_;}

private:
  void MSecond2Timer();
};

inline
void HighFrequencyElapsedTimer::MSecond2Timer()
{
  hours_ = (leftmillSecond_ / 1000) / 3600;
  minute_ = (__int64(leftmillSecond_ / 1000) % 3600)  / 60;
  second_ = ((__int64(leftmillSecond_ / 1000) % 3600) % 60) % 60;
  millsecond_ = leftmillSecond_ - (hours_ * 3600 * 1000 + minute_ * 60 * 1000 + second_ * 1000);
}

#endif // !defined(HIGH_FRQUENCY_TIMER)
