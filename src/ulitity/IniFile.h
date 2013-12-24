#if !defined(AFX_INIFILE_H__33CAF5C6_7820_43EB_8D84_42CC1856C35C__INCLUDED_)
#define AFX_INIFILE_H__33CAF5C6_7820_43EB_8D84_42CC1856C35C__INCLUDED_

class MyIniFile 
{
public:
  MyIniFile();
	~MyIniFile();

	void    SetFileName(const CString& FileName);
  CString GetString(const CString&  Section, const CString& Item , CString def_Value = "");
	int     GetInt(const CString&  Section, const CString& Item, int def_Value = 0);
  double  GetDouble(const CString&  Section, const CString& Item, double def_Value = 0);
	void    SetString(const CString&  Section, const CString& Item, const CString& Value);
	void    SetInt(const CString&  Section, const CString& Item, int Value);
  void    SetDouble(const CString&  Section, const CString& Item, double Value);

private:
	void    WriteFileString(const CString&  Section, const CString& Item, const CString& Value);
	CString GetFileString(const CString&  Section, const CString& Item, CString def_Value);
	BOOL WriteIniFile();
	BOOL ReadIniFile();

private:
	CString m_sFileName;
	CStdioFile IniFile;
	BOOL  bFileExist;
	CStringArray FileContainer;
};

#endif // !defined(AFX_INIFILE_H__33CAF5C6_7820_43EB_8D84_42CC1856C35C__INCLUDED_)
