
#if !defined(_GAMEFILE_READER_HEADER_)
#define _GAMEFILE_READER_HEADER_

class AccountManager  
{
private:
  struct accout_t{
    CString name;
    CString pswd;
    CString starname;
  };
  std::vector<accout_t> entry_accounts_;
  int cur_login_index_;

public:
	AccountManager();
	~AccountManager();
  size_t AccountSize();
  CString AccountName(size_t index);
  CString AccountPassword(size_t index);
  bool CheckValidAccount(const CString& accout , const CString& pass , int& index);
  void Login(int index);
  bool ExistAccount(const CString& name);
  bool RegisterAccount(const CString& name , const CString& password , const CString& star_name , uchar com_r , int speed , uchar com_ai_r , CString npc_name , BOOL computer_attack_me , BOOL not_up_res);
  bool DeleteAccount(const CString& name);
  bool CanGetPassword(const CString& account , const CString& starname , CString& password);
  int  LoginedIndex(){return cur_login_index_;}
  
private:
  void InitAccountList();
  BOOL CheckFile(const CString& path , CString& name , CString& password , CString& starname);
};

#endif // !defined(_GAMEFILE_READER_HEADER_)
