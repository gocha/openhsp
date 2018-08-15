#ifndef __pack_icon_resource
#define __pack_icon_resource
	int StrReplace(LPTSTR buf, LPTSTR mae, LPTSTR ato);
	int StrReplaceALL(LPTSTR buf, LPTSTR mae, LPTSTR ato);
	int GetIconResourcePath(LPTSTR exepath, LPTSTR iconpath, LPTSTR respath, LPTSTR manifestpath/*manifest by Tetr@pod*/, int _activeFootyID, int *upx, int *lang, LPTSTR extension);
	BOOL _PathFileExists(LPCTSTR pszPath);
	BOOL _PathRemoveFileSpec(LPTSTR pszPath);
	void RunIconChange(int activeFootyID);
#endif