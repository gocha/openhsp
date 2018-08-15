#ifndef __custom_config
#define __custom_config
	void GetINIFullPath(LPTSTR inipath);
	int GetINIForceFont(void);
	BOOL GetINICustomColor(void);
	void SetINIForceFont(BOOL f);
	void SetINICustomColor(int f);
	void SetINICustomString(LPTSTR key, LPTSTR value);

	void SetINICustomInt(int f, LPTSTR s);
	void SetINICustomBOOL(BOOL f, LPTSTR s);
	int GetINICustomInt(LPTSTR s);
	BOOL GetINICustomBOOL(LPTSTR s);
	DWORD GetINICustomString(LPTSTR key, LPTSTR value, int maxLength);
#endif