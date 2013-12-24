#include "stdafx.h"
#include "IniFile.h"

MyIniFile::MyIniFile()
{
  m_sFileName = _T("empty.acc");
}

MyIniFile::~MyIniFile()
{
  if(FileContainer.GetSize() > 0)
  {
    FileContainer.RemoveAll();
  }
}

void MyIniFile::SetFileName(const CString& FileName)
{
  m_sFileName = FileName;
}

void MyIniFile::SetInt(const CString&  Section, const CString& Item, int Value)
{
  CString strtemp;
  strtemp.Format("%d",Value);
  WriteFileString(Section, Item, strtemp);
  WriteIniFile();
}

void MyIniFile::SetString(const CString&  Section, const CString& Item, const CString& Value)
{
  WriteFileString(Section, Item, Value);
  WriteIniFile();
}

CString MyIniFile::GetString(const CString&  Section, const CString& Item , CString def_Value)
{
  return GetFileString(Section, Item , def_Value);
}

int MyIniFile::GetInt(const CString&  Section, const CString& Item, int def_Value)
{
  CString strtemp;
  strtemp.Format("%d",def_Value);
  return atoi(GetFileString(Section, Item, strtemp));
}

double  MyIniFile::GetDouble(const CString&  Section, const CString& Item, double def_Value)
{
  CString strtemp;
  strtemp.Format("%f",def_Value);
  return atof(GetFileString(Section, Item, strtemp));
}

void MyIniFile::SetDouble(const CString&  Section, const CString& Item, double Value)
{
  CString strtemp;
  strtemp.Format("%f",Value);
  WriteFileString(Section, Item, strtemp);
  WriteIniFile();
}

BOOL MyIniFile::ReadIniFile()
{
  bFileExist=IniFile.Open(m_sFileName, CFile::modeRead);
  
  if(!bFileExist)
  {
    return FALSE;
  }
  
  CString strline;
  FileContainer.RemoveAll();
  
  //��IniFile�ļ����ݶ���FileContainer
  while(IniFile.ReadString(strline))
  {
    FileContainer.Add(strline);
  }
  
  IniFile.Close();
  return TRUE;
}

BOOL MyIniFile::WriteIniFile()
{
  bFileExist=IniFile.Open(m_sFileName, CFile::modeCreate | CFile::modeWrite);
  if(!bFileExist)
    return FALSE;
  
  CString strline;
  
  //��FileContainerд��IniFile�ļ�
  for(int i = 0; i< FileContainer.GetSize(); i++)
  {
    strline = FileContainer[i];
    IniFile.WriteString(strline+"\n");
  }
  
  IniFile.Close();
  
  return bFileExist;
}

CString MyIniFile::GetFileString(const CString&  Section, const CString& Item , CString def_Value)
{
  ReadIniFile();
  
  if(bFileExist == FALSE || FileContainer.GetSize() < 0)
    return def_Value;
  
  int i = 0;
  int iFileLines = FileContainer.GetSize();
  CString strline,str;
  
  while(i<iFileLines)
  {
    strline = FileContainer.GetAt(i++);
    if(strline.IsEmpty())
      continue;
    
    strline.TrimLeft();
    if(strline.GetAt(0)=='[')//����Section����һ������Ϊ[
    {
      str=strline.Left(strline.Find("]"));//ȥ��]�ұ�
      str=str.Right(str.GetLength()-str.Find("[")-1);//ȥ��[���
      
      str.TrimLeft();
      str.TrimRight();
      
      if(Section == str)//�ҵ�Section
      {
        while(i<iFileLines)
        {
          strline = FileContainer.GetAt(i++);
          strline.TrimLeft();
          
          if(strline.GetAt(0)=='[')
            return def_Value;//���������һ��[]�����Ҳ���,����Ĭ��ֵ
          
          str = strline.Left(strline.Find("="));//ȥ��=�ұ�
          
          str.TrimLeft();
          str.TrimRight();
          
          if(Item == str)//�ҵ�Item
          {
            str=strline.Right(strline.GetLength()-strline.Find("=")-1);//ȥ��=���
            
            str.TrimLeft();
            str.TrimRight();
            
            return str;
          }
        }
        return def_Value;//�Ҳ���,����Ĭ��ֵ
      }
      
    }
    
  }
  return def_Value;//�Ҳ���,����Ĭ��ֵ
}

void MyIniFile::WriteFileString(const CString&  Section, const CString& Item, const CString& Value)
{
  int i = 0;
  int iFileLines = FileContainer.GetSize();
  CString strline,str;
  
  while(i<iFileLines)
  {
    strline = FileContainer.GetAt(i++);
    if(strline.IsEmpty())
      continue;
    
    strline.TrimLeft();
    if(strline.GetAt(0)=='[')//����Section����һ������Ϊ[
    {
      str=strline.Left(strline.Find("]"));//ȥ��]�ұ�
      str=str.Right(str.GetLength()-str.Find("[")-1);//ȥ��[���
      
      str.TrimLeft();
      str.TrimRight();
      
      if(Section == str)//�ҵ�Section
      {
        while(i<iFileLines)
        {
          strline = FileContainer.GetAt(i++);
          strline.TrimLeft();
          
          if(strline.GetAt(0)=='[')//���������һ��[]�����Ҳ���Item
          {
            break;
          }
          
          str = strline.Left(strline.Find("="));//ȥ��=�ұ�
          
          str.TrimLeft();
          str.TrimRight();
          
          if(Item == str)//�ҵ�Item
          {
            strline = Item + "=" + Value;
            FileContainer[i-1] = strline;
            return;
          }
        }
        //�Ҳ���Item
        strline = Item + "=" + Value;
        FileContainer.InsertAt(i-1, strline);
        return;
        
      }
      
    }
    
  }
  //�Ҳ���Section
  //ֱ����������Section��Item��Value
  FileContainer.Add("[" + Section + "]");
  FileContainer.Add(Item + "=" + Value);
  return;
}

