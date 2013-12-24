// ElapsedTimer.h: interface for the ElapsedTimer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ELAPSEDTIMER_H__4D27AE73_5C30_404A_8562_A936F4ED3AE6__INCLUDED_)
#define AFX_ELAPSEDTIMER_H__4D27AE73_5C30_404A_8562_A936F4ED3AE6__INCLUDED_


class ElapsedTimer  
{
private:
  unsigned long hours_;
  unsigned char minute_;
  unsigned char second_;
  double  leftSecond_;
  double  elapsedSecond_;

public:
	ElapsedTimer();
  ElapsedTimer(double total_s);
  ElapsedTimer(unsigned long h , unsigned char m , unsigned char s);
	~ElapsedTimer();

  unsigned long GetHour() const   {return hours_;}
  unsigned char GetMinute() const {return minute_;}
  unsigned char GetSecond() const {return second_;}
  double GetLeftSecond() const    {return leftSecond_;}
  double GetElapseSecond() const  {return elapsedSecond_;}

  void Init(unsigned long h , unsigned char m , unsigned char s);
  void Init(double total_s);
  void Go(unsigned long elapsed_second = 1);
  bool IsZero() {return __int64(leftSecond_) == 0L;}
  CString ToCString()
  {
    CString temp;
    temp.Format("%d:%02d:%02d" , hours_ , minute_ , second_);
    return temp;
  }

private:
  void Second2Timer();
};

inline
void ElapsedTimer::Second2Timer()
{
  hours_ = leftSecond_ / 3600;
  minute_ = (__int64(leftSecond_) % 3600) / 60;  
  second_ = leftSecond_ - (hours_ * 3600 + minute_ * 60);
}

#endif // !defined(AFX_ELAPSEDTIMER_H__4D27AE73_5C30_404A_8562_A936F4ED3AE6__INCLUDED_)
