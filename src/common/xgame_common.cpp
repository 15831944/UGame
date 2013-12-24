#include "StdAfx.h"
#include "xgame_common.hpp"

//CSpeedKernel interface
CSpeedKernel& kernel_ = CSpeedKernel::GetInstance();

#ifdef ASMRAND
  DWORD randbuf[34];
  DWORD p1, p2;
#else
  DWORD randbuf[17][2];
  int p1, p2;
#endif

COMMAND_TASK::COMMAND_TASK()
{
  timer.Init(0);
  cycle = 0;
  is_go = false;
  star  = 0;
  index = 0;
  fuel = 0.0;

  //fleet
  SItem item;
  for(int i = 0 ; i < BOAT_MAX ; ++i)
  {
    item.Type = ITEM_TYPE(i);
    item.Num = 0;
    fleet.push_back(item);
  }
  //resource
  res.crystal_ = res.metal_ = res.diplogen_ = 0;
  loss_res.crystal_ = loss_res.metal_ = loss_res.diplogen_ = 0;

  is_can_back = true;
}

// inits random number generator
void InitRand() {
  int seed = time(NULL);
#ifdef ASMRAND
  __asm {
    mov eax, seed
      xor ecx, ecx
R80:
    imul eax, 2891336453
      inc eax
      mov randbuf[ecx*4], eax
      inc ecx
      cmp ecx, 34
      jb R80
      mov p1, 0         // initialize buffer pointers
      mov p2, 80
  }
#else 
  int i, j;
  
  for(i = 0; i < 17; i++) {
    for(j = 0; j < 2; j++) {
      seed = seed * 2891336453UL + 1;
      randbuf[i][j] = seed;
    }
  }
  // initialize pointers to circular buffer
  p1 = 0;
  p2 = 10;
#endif
}

#pragma warning(disable: 4035)
ULONG RandomNumber(ULONG Max)
{
#ifdef ASMRAND
  __asm {
    mov ebx, p1       // ring buffer pointers
      mov ecx, p2       // ring buffer pointer
      mov edx, randbuf[ebx]
      mov eax, randbuf[ebx]
      rol edx, 19       // rotate bits
      rol eax, 27
      add edx, randbuf[ecx]   // add two dwords
      add eax, randbuf[ecx+4]
      mov randbuf[ebx], eax   // save in swapped order
      mov randbuf[ebx+4], edx
      sub ebx, 8        // decrement p1
      jnc R30
      mov ebx, 128      // wrap around p1
R30:
    sub ecx, 8        // decrement p2
      jnc R40
      mov ecx, 128      // wrap around p2
R40:
    mov p1, ebx       // save updated pointers
      mov p2, ecx
      
      mov ebx, Max
      mov ecx, edx      // high bits of random number
      mul ebx           // multiply low 32 bits
      mov eax, ecx
      mov ecx, edx
      mul ebx           // multiply high 32 bits
      mov eax, edx
  }
#else
  DWORD y, z;
  // generate next number
  z = _lrotl(randbuf[p1][0], 19) + randbuf[p2][0];
  y = _lrotl(randbuf[p1][1], 27) + randbuf[p2][1];
  randbuf[p1][0] = y;
  randbuf[p1][1] = z;
  // rotate list pointers
  if (--p1 < 0)
    p1 = 16;
  if (--p2 < 0)
    p2 = 16;
  return y % Max;
#endif
}

LPTSTR AddPointsToNumber(__int64 value, LPTSTR out) {
  bool neg = false;
  if(value < INT_MAX && value > INT_MIN)
    _stprintf(out, _T("%d"), value);
  else {
    if((value % 1000 == 0) && (value / 1000 < INT_MAX) && ((value / 1000 > INT_MIN))) {
      value /= 1000;
      _stprintf(out, _T("%d"), value);
      _tcscat(out, _T("000"));
    }
    else
      _stprintf(out, _T("%I64d"), value);
  }
  genstring c = out;
  
  div_t res;
  if(value < 0) {
    c.erase(0, 1);
    neg = true;
  }
  res = div(c.length(), 3);
  if(res.rem == 0)
    res.quot--;
  for(int i = 1; i <= res.quot; i++) {
    c.insert(c.length() - i * 4 + 1, _T("."));
  }
  if(neg)
    c.insert(0, _T("-"));
  _tcscpy(out, c.data());
  return out;
}

bool  CheckPosValid(const PlaniPos& pos )
{
  if(pos.Gala < 1 || pos.Gala > MAX_GALAXY_GALA)
    return false;
  if(pos.Sys <  1 || pos.Sys > MAX_GALAXY_SYS)
    return false;
  if(pos.Pos <  1 || pos.Pos > MAX_GALAXY_POS)
    return false;

  return true;
}

PlaniPos Index2Pos(ulong index)
{
  assert(index < MAX_GALAXY_GALA * MAX_GALAXY_SYS * MAX_GALAXY_POS);
  PlaniPos pos;
  pos.Gala = index / (MAX_GALAXY_SYS * MAX_GALAXY_POS) + 1;
  pos.Sys  = ((index - (pos.Gala - 1) * MAX_GALAXY_SYS * MAX_GALAXY_POS) / MAX_GALAXY_POS) + 1;
  pos.Pos  = (index - (pos.Gala - 1) * MAX_GALAXY_SYS * MAX_GALAXY_POS - (pos.Sys - 1) * MAX_GALAXY_POS ) + 1;
  return pos;
}

ulong Pos2Index(const PlaniPos& pos)
{
  return (pos.Pos - 1) + (pos.Sys - 1) * MAX_GALAXY_POS + (pos.Gala - 1) * MAX_GALAXY_SYS * MAX_GALAXY_POS;
}

char RandomHighTemp(uchar pos)
{
  if(pos <= 3)
  {
    return 110 + RandomNumber(15);
  }
  if(pos <= 6)
  {
    return 65 + RandomNumber(15);
  }
  if(pos <= 9)
  {
    return 35 + RandomNumber(15);
  }
  if(pos <= 12)
  {
    return 5 + RandomNumber(15);
  }
  if(pos <= 15)
  {
    return -50 + RandomNumber(15);
  }
  return 0;
}

ushort RandomStarSize(uchar pos)
{
  if(pos <= 3)
  {
    return 150 + RandomNumber(50);
  }
  if(pos <= 6)
  {
    return 400 + RandomNumber(100);
  }
  if(pos <= 9)
  {
    return 300 + RandomNumber(100);
  }
  if(pos <= 12)
  {
    return 200 + RandomNumber(100);
  }
  if(pos <= 15)
  {
    return 150 + RandomNumber(100);
  }
  return 0;
}