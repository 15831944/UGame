#ifndef _ECFILE_HPP_
#define _ECFILE_HPP_

//get password
inline
__int64 epass()
{
	DWORD plen;
	const char *ppass = "XGAME2006.CPH";
	__int64 mc= 8757735233305;
	plen = strlen(ppass);
	for(int i=0; i<(int)plen; i++)
	{
		mc ^= ppass[i]|128;
	}
	return mc;
}

//ecfile
inline
bool ecfile(LPCTSTR fpath)
{
	CFile file;
	__int64 m_password = epass();

	if ( !file.Open(fpath, CFile::shareDenyNone|CFile::modeReadWrite))
	{
		return false;
	}

	DWORD flen = file.GetLength();
	char *data = new char[(int)flen];

	file.SeekToBegin();
	file.Read(data, flen);

	for(int i=0; i<(int)flen; i++)
	{
		data[i] ^= m_password;
		data[i] ^= flen;
	}

	file.SeekToBegin();
	file.Write(data, flen);
	delete[] data;

	char cpass[5] = "Game";
	for(int j=0; j<5; j++)
	{
		cpass[j] ^= m_password;
	}
	file.SeekToEnd();
	file.Write(&cpass, 5);
	file.Close();
	return true;
}

//dcfile
inline
bool dcfile(LPCTSTR fpath)
{
	CFile file;
	char identy[5];
	if( !file.Open(fpath, CFile::shareDenyNone|CFile::modeReadWrite))
	{
		return false;
	}

	DWORD flen = file.GetLength();
	char *data = new char[(int)flen];

	file.Seek(-5, CFile::end);
	file.Read(&identy, 5);
	__int64 m_password = epass();

	for(int i=0; i<5; i++)
	{
		identy[i] ^= m_password;
	}

	if(strcmp(identy, "Game")!=0)
	{
		return FALSE;
	}

	file.SeekToBegin();
	file.Read(data, flen);

	for(int j=0; j<(int)flen; j++)
	{
		data[j] ^= m_password;
		data[j] ^= (flen-5);
	}
	file.SeekToBegin();
	file.Write(data, flen);
	file.SetLength(flen-5);
	file.Close();

	delete[] data;
	return true;
}


#endif//_ECFILE_HPP_