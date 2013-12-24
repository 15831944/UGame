#if !defined(GAME_LOGGER_H)
#define GAME_LOGGER_H

class CGameLogger  
{
public:
	~CGameLogger();
  void Log(const CString& info);
  void Init(const CString& account_name);
  static CGameLogger& Instance();

private:
  CGameLogger();
  CGameLogger(const CGameLogger&);
  CGameLogger& operator=(const CGameLogger&);

private:
  CStdioFile logger_;
  CString account_name_;
};

#endif // !defined(GAME_LOGGER_H)
