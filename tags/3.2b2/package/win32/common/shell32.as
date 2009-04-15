;(shell32.as)
#ifdef __hsp30__
#ifndef __SHELL32__
#define global __SHELL32__
#uselib "SHELL32.DLL"
	#func global CDefFolderMenu_Create2 "CDefFolderMenu_Create2" sptr,sptr,sptr,sptr,sptr,sptr,sptr,sptr,sptr
	#func global CDefFolderMenu_Create "CDefFolderMenu_Create" sptr,sptr,sptr,sptr,sptr,sptr,sptr,sptr,sptr
	#func global CallCPLEntry16 "CallCPLEntry16" sptr,sptr,sptr,sptr,sptr,sptr
	#define global CheckEscapes CheckEscapesA
	#func global CheckEscapesA "CheckEscapesA" sptr,sptr
	#func global CheckEscapesW "CheckEscapesW" wptr,wptr
	#func global CommandLineToArgvW "CommandLineToArgvW" wptr,wptr
	#func global DAD_AutoScroll "DAD_AutoScroll" sptr,sptr,sptr
	#func global DAD_DragEnterEx2 "DAD_DragEnterEx2" sptr,sptr,sptr,sptr
	#func global DAD_DragEnterEx "DAD_DragEnterEx" sptr,sptr,sptr
	#func global DAD_DragLeave "DAD_DragLeave"
	#func global DAD_DragMove "DAD_DragMove" sptr,sptr
	#func global DAD_SetDragImage "DAD_SetDragImage" sptr,sptr
	#func global DAD_ShowDragImage "DAD_ShowDragImage" sptr
	#define global DoEnvironmentSubst DoEnvironmentSubstA
	#func global DoEnvironmentSubstA "DoEnvironmentSubstA" sptr,sptr
	#func global DoEnvironmentSubstW "DoEnvironmentSubstW" wptr,wptr
	#func global DragAcceptFiles "DragAcceptFiles" sptr,sptr
	#func global DragFinish "DragFinish" sptr
	#func global DragQueryFile "DragQueryFile" sptr,sptr,sptr,sptr
	#func global DragQueryFileA "DragQueryFileA" sptr,sptr,sptr,sptr
	#func global DragQueryFileAorW "DragQueryFileAorW" wptr,wptr,wptr,wptr,wptr,wptr
	#func global DragQueryFileW "DragQueryFileW" wptr,wptr,wptr,wptr
	#func global DragQueryPoint "DragQueryPoint" sptr,sptr
	#func global DriveType "DriveType" sptr
	#func global DuplicateIcon "DuplicateIcon" sptr,sptr
	#define global ExtractAssociatedIcon ExtractAssociatedIconA
	#func global ExtractAssociatedIconA "ExtractAssociatedIconA" sptr,sptr,sptr
	#define global ExtractAssociatedIconEx ExtractAssociatedIconExA
	#func global ExtractAssociatedIconExA "ExtractAssociatedIconExA" sptr,sptr,sptr,sptr
	#func global ExtractAssociatedIconExW "ExtractAssociatedIconExW" wptr,wptr,wptr,wptr
	#func global ExtractAssociatedIconW "ExtractAssociatedIconW" wptr,wptr,wptr
	#define global ExtractIcon ExtractIconA
	#func global ExtractIconA "ExtractIconA" sptr,sptr,sptr
	#func global ExtractIconEx "ExtractIconEx" sptr,sptr,sptr,sptr,sptr
	#func global ExtractIconExA "ExtractIconExA" sptr,sptr,sptr,sptr,sptr
	#func global ExtractIconExW "ExtractIconExW" wptr,wptr,wptr,wptr,wptr
	#define global ExtractIconResInfo ExtractIconResInfoA
	#func global ExtractIconResInfoA "ExtractIconResInfoA" sptr,sptr,sptr,sptr,sptr
	#func global ExtractIconResInfoW "ExtractIconResInfoW" wptr,wptr,wptr,wptr,wptr
	#func global ExtractIconW "ExtractIconW" wptr,wptr,wptr
	#func global ExtractVersionResource16W "ExtractVersionResource16W" wptr,wptr
	#func global FindExeDlgProc "FindExeDlgProc" sptr,sptr,sptr,sptr
	#define global FindExecutable FindExecutableA
	#func global FindExecutableA "FindExecutableA" sptr,sptr,sptr
	#func global FindExecutableW "FindExecutableW" wptr,wptr,wptr
	#func global FreeIconList "FreeIconList" sptr,sptr
	#func global GetFileNameFromBrowse "GetFileNameFromBrowse" sptr,sptr,sptr,sptr,sptr,sptr,sptr
	#func global ILAppendID "ILAppendID" sptr,sptr,sptr
	#func global ILClone "ILClone" sptr
	#func global ILCloneFirst "ILCloneFirst" sptr
	#func global ILCombine "ILCombine" sptr,sptr
	#func global ILCreateFromPath "ILCreateFromPath" sptr
	#func global ILCreateFromPathA "ILCreateFromPathA" sptr
	#func global ILCreateFromPathW "ILCreateFromPathW" wptr
	#func global ILFindChild "ILFindChild" sptr,sptr
	#func global ILFindLastID "ILFindLastID" sptr
	#func global ILFree "ILFree" sptr
	#func global ILGetNext "ILGetNext" sptr
	#func global ILGetSize "ILGetSize" sptr
	#func global ILIsEqual "ILIsEqual" sptr,sptr
	#func global ILIsParent "ILIsParent" sptr,sptr,sptr
	#func global ILLoadFromStream "ILLoadFromStream" sptr,sptr
	#func global ILRemoveLastID "ILRemoveLastID" sptr
	#func global ILSaveToStream "ILSaveToStream" sptr,sptr
	#define global InternalExtractIconList InternalExtractIconListA
	#func global InternalExtractIconListA "InternalExtractIconListA" sptr,sptr,sptr
	#func global InternalExtractIconListW "InternalExtractIconListW" wptr,wptr,wptr
	#func global IsLFNDrive "IsLFNDrive" sptr
	#func global IsLFNDriveA "IsLFNDriveA" sptr
	#func global IsLFNDriveW "IsLFNDriveW" wptr
	#func global IsNetDrive "IsNetDrive" sptr
	#func global IsUserAnAdmin "IsUserAnAdmin"
	#func global OpenRegStream "OpenRegStream" sptr,sptr,sptr,sptr
	#func global PathCleanupSpec "PathCleanupSpec" sptr,sptr
	#func global PathGetShortPath "PathGetShortPath" sptr
	#func global PathIsExe "PathIsExe" sptr
	#define global PathIsSlow PathIsSlowA
	#func global PathIsSlowA "PathIsSlowA" sptr,sptr
	#func global PathIsSlowW "PathIsSlowW" wptr,wptr
	#func global PathMakeUniqueName "PathMakeUniqueName" sptr,sptr,sptr,sptr,sptr
	#func global PathProcessCommand "PathProcessCommand" sptr,sptr,sptr,sptr
	#func global PathQualify "PathQualify" sptr
	#func global PathResolve "PathResolve" sptr,sptr,sptr
	#func global PathYetAnotherMakeUniqueName "PathYetAnotherMakeUniqueName" sptr,sptr,sptr,sptr
	#func global PickIconDlg "PickIconDlg" sptr,sptr,sptr,sptr
	#func global PifMgr_CloseProperties "PifMgr_CloseProperties" sptr,sptr
	#func global PifMgr_GetProperties "PifMgr_GetProperties" sptr,sptr,sptr,sptr,sptr
	#func global PifMgr_OpenProperties "PifMgr_OpenProperties" sptr,sptr,sptr,sptr
	#func global PifMgr_SetProperties "PifMgr_SetProperties" sptr,sptr,sptr,sptr,sptr
	#func global ReadCabinetState "ReadCabinetState" sptr,sptr
	#func global RealDriveType "RealDriveType" sptr,sptr
	#define global RealShellExecute RealShellExecuteA
	#func global RealShellExecuteA "RealShellExecuteA" sptr,sptr,sptr,sptr,sptr,sptr,sptr,sptr,sptr,sptr
	#define global RealShellExecuteEx RealShellExecuteExA
	#func global RealShellExecuteExA "RealShellExecuteExA" sptr,sptr,sptr,sptr,sptr,sptr,sptr,sptr,sptr,sptr,sptr
	#func global RealShellExecuteExW "RealShellExecuteExW" wptr,wptr,wptr,wptr,wptr,wptr,wptr,wptr,wptr,wptr,wptr
	#func global RealShellExecuteW "RealShellExecuteW" wptr,wptr,wptr,wptr,wptr,wptr,wptr,wptr,wptr,wptr
	#func global RegenerateUserEnvironment "RegenerateUserEnvironment" sptr,sptr
	#func global RestartDialog "RestartDialog" sptr,sptr,sptr
	#func global RestartDialogEx "RestartDialogEx" sptr,sptr,sptr,sptr
	#func global SHAddFromPropSheetExtArray "SHAddFromPropSheetExtArray" sptr,sptr,sptr
	#func global SHAddToRecentDocs "SHAddToRecentDocs" sptr,sptr
	#func global SHAlloc "SHAlloc" sptr
	#func global SHAllocShared "SHAllocShared" sptr,sptr,sptr
	#func global SHAppBarMessage "SHAppBarMessage" sptr,sptr
	#func global SHBindToParent "SHBindToParent" sptr,sptr,sptr,sptr
	#func global SHBrowseForFolder "SHBrowseForFolder" sptr
	#func global SHBrowseForFolderA "SHBrowseForFolderA" sptr
	#func global SHBrowseForFolderW "SHBrowseForFolderW" wptr
	#func global SHCLSIDFromString "SHCLSIDFromString" sptr,sptr
	#func global SHChangeNotification_Lock "SHChangeNotification_Lock" sptr,sptr,sptr,sptr
	#func global SHChangeNotification_Unlock "SHChangeNotification_Unlock" sptr
	#func global SHChangeNotify "SHChangeNotify" sptr,sptr,sptr,sptr
	#func global SHChangeNotifyDeregister "SHChangeNotifyDeregister" sptr
	#func global SHChangeNotifyRegister "SHChangeNotifyRegister" sptr,sptr,sptr,sptr,sptr,sptr
	#func global SHCloneSpecialIDList "SHCloneSpecialIDList" sptr,sptr,sptr
	#func global SHCoCreateInstance "SHCoCreateInstance" sptr,sptr,sptr,sptr,sptr
	#func global SHCreateDirectory "SHCreateDirectory" sptr,sptr
	#define global SHCreateDirectoryEx SHCreateDirectoryExA
	#func global SHCreateDirectoryExA "SHCreateDirectoryExA" sptr,sptr,sptr
	#func global SHCreateDirectoryExW "SHCreateDirectoryExW" wptr,wptr,wptr
	#func global SHCreateFileExtractIconW "SHCreateFileExtractIconW" wptr,wptr,wptr,wptr
	#func global SHCreateProcessAsUserW "SHCreateProcessAsUserW" wptr
	#func global SHCreatePropSheetExtArray "SHCreatePropSheetExtArray" sptr,sptr,sptr
	#func global SHCreateQueryCancelAutoPlayMoniker "SHCreateQueryCancelAutoPlayMoniker" sptr
	#func global SHCreateShellFolderView "SHCreateShellFolderView" sptr,sptr
	#func global SHCreateShellFolderViewEx "SHCreateShellFolderViewEx" sptr,sptr
	#func global SHCreateShellItem "SHCreateShellItem" sptr,sptr,sptr,sptr
	#func global SHCreateStdEnumFmtEtc "SHCreateStdEnumFmtEtc" sptr,sptr,sptr
	#define global SHDefExtractIcon SHDefExtractIconA
	#func global SHDefExtractIconA "SHDefExtractIconA" sptr,sptr,sptr,sptr,sptr,sptr
	#func global SHDefExtractIconW "SHDefExtractIconW" wptr,wptr,wptr,wptr,wptr,wptr
	#func global SHDestroyPropSheetExtArray "SHDestroyPropSheetExtArray" sptr
	#func global SHDoDragDrop "SHDoDragDrop" sptr,sptr,sptr,sptr,sptr
	#define global SHEmptyRecycleBin SHEmptyRecycleBinA
	#func global SHEmptyRecycleBinA "SHEmptyRecycleBinA" sptr,sptr,sptr
	#func global SHEmptyRecycleBinW "SHEmptyRecycleBinW" wptr,wptr,wptr
	#func global SHEnumerateUnreadMailAccountsW "SHEnumerateUnreadMailAccountsW" wptr,wptr,wptr,wptr
	#func global SHExtractIconsW "SHExtractIconsW" wptr,wptr,wptr,wptr,wptr,wptr,wptr,wptr
	#func global SHFileOperation "SHFileOperation" sptr
	#func global SHFileOperationA "SHFileOperationA" sptr
	#func global SHFileOperationW "SHFileOperationW" wptr
	#func global SHFindFiles "SHFindFiles" sptr,sptr
	#func global SHFind_InitMenuPopup "SHFind_InitMenuPopup" sptr,sptr,sptr,sptr
	#func global SHFlushClipboard "SHFlushClipboard"
	#func global SHFlushSFCache "SHFlushSFCache"
	#func global SHFormatDrive "SHFormatDrive" sptr,sptr,sptr,sptr
	#func global SHFree "SHFree" sptr
	#func global SHFreeNameMappings "SHFreeNameMappings" sptr
	#func global SHFreeShared "SHFreeShared" sptr,sptr
	#func global SHGetAttributesFromDataObject "SHGetAttributesFromDataObject" sptr,sptr,sptr,sptr
	#define global SHGetDataFromIDList SHGetDataFromIDListA
	#func global SHGetDataFromIDListA "SHGetDataFromIDListA" sptr,sptr,sptr,sptr,sptr
	#func global SHGetDataFromIDListW "SHGetDataFromIDListW" wptr,wptr,wptr,wptr,wptr
	#func global SHGetDesktopFolder "SHGetDesktopFolder" sptr
	#define global SHGetDiskFreeSpace SHGetDiskFreeSpaceA
	#func global SHGetDiskFreeSpaceA "SHGetDiskFreeSpaceA" sptr,sptr,sptr,sptr
	#define global SHGetDiskFreeSpaceEx SHGetDiskFreeSpaceExA
	#func global SHGetDiskFreeSpaceExA "SHGetDiskFreeSpaceExA" sptr,sptr,sptr,sptr
	#func global SHGetDiskFreeSpaceExW "SHGetDiskFreeSpaceExW" wptr,wptr,wptr,wptr
	#func global SHGetFileInfo "SHGetFileInfo" sptr,sptr,sptr,sptr,sptr
	#func global SHGetFileInfoA "SHGetFileInfoA" sptr,sptr,sptr,sptr,sptr
	#func global SHGetFileInfoW "SHGetFileInfoW" wptr,wptr,wptr,wptr,wptr
	#func global SHGetFolderLocation "SHGetFolderLocation" sptr,sptr,sptr,sptr,sptr
	#define global SHGetFolderPath SHGetFolderPathA
	#func global SHGetFolderPathA "SHGetFolderPathA" sptr,sptr,sptr,sptr,sptr
	#define global SHGetFolderPathAndSubDir SHGetFolderPathAndSubDirA
	#func global SHGetFolderPathAndSubDirA "SHGetFolderPathAndSubDirA" sptr,sptr,sptr,sptr,sptr,sptr
	#func global SHGetFolderPathAndSubDirW "SHGetFolderPathAndSubDirW" wptr,wptr,wptr,wptr,wptr,wptr
	#func global SHGetFolderPathW "SHGetFolderPathW" wptr,wptr,wptr,wptr,wptr
	#define global SHGetIconOverlayIndex SHGetIconOverlayIndexA
	#func global SHGetIconOverlayIndexA "SHGetIconOverlayIndexA" sptr,sptr
	#func global SHGetIconOverlayIndexW "SHGetIconOverlayIndexW" wptr,wptr
	#func global SHGetInstanceExplorer "SHGetInstanceExplorer" sptr
	#func global SHGetMalloc "SHGetMalloc" sptr
	#func global SHGetNewLinkInfo "SHGetNewLinkInfo" sptr,sptr,sptr,sptr,sptr
	#func global SHGetNewLinkInfoA "SHGetNewLinkInfoA" sptr,sptr,sptr,sptr,sptr
	#func global SHGetNewLinkInfoW "SHGetNewLinkInfoW" wptr,wptr,wptr,wptr,wptr
	#func global SHGetPathFromIDList "SHGetPathFromIDList" sptr,sptr
	#func global SHGetPathFromIDListA "SHGetPathFromIDListA" sptr,sptr
	#func global SHGetPathFromIDListW "SHGetPathFromIDListW" wptr,wptr
	#func global SHGetRealIDL "SHGetRealIDL" sptr,sptr,sptr
	#func global SHGetSetFolderCustomSettingsW "SHGetSetFolderCustomSettingsW" wptr,wptr,wptr
	#func global SHGetSetSettings "SHGetSetSettings" sptr,sptr,sptr
	#func global SHGetSettings "SHGetSettings" sptr,sptr
	#func global SHGetShellStyleHInstance "SHGetShellStyleHInstance"
	#func global SHGetSpecialFolderLocation "SHGetSpecialFolderLocation" sptr,sptr,sptr
	#func global SHGetSpecialFolderPath "SHGetSpecialFolderPath" sptr,sptr,sptr,sptr
	#func global SHGetSpecialFolderPathA "SHGetSpecialFolderPathA" sptr,sptr,sptr,sptr
	#func global SHGetSpecialFolderPathW "SHGetSpecialFolderPathW" wptr,wptr,wptr,wptr
	#func global SHGetUnreadMailCountW "SHGetUnreadMailCountW" wptr,wptr,wptr,wptr,wptr,wptr
	#func global SHHandleUpdateImage "SHHandleUpdateImage" sptr
	#func global SHILCreateFromPath "SHILCreateFromPath" sptr,sptr,sptr
	#define global SHInvokePrinterCommand SHInvokePrinterCommandA
	#func global SHInvokePrinterCommandA "SHInvokePrinterCommandA" sptr,sptr,sptr,sptr,sptr
	#func global SHInvokePrinterCommandW "SHInvokePrinterCommandW" wptr,wptr,wptr,wptr,wptr
	#func global SHIsFileAvailableOffline "SHIsFileAvailableOffline" sptr,sptr
	#func global SHLimitInputEdit "SHLimitInputEdit" sptr,sptr
	#func global SHLoadInProc "SHLoadInProc" sptr
	#func global SHLoadNonloadedIconOverlayIdentifiers "SHLoadNonloadedIconOverlayIdentifiers"
	#func global SHLoadOLE "SHLoadOLE" sptr
	#func global SHLockShared "SHLockShared" sptr,sptr
	#func global SHMapIDListToImageListIndexAsync "SHMapIDListToImageListIndexAsync" sptr,sptr,sptr,sptr,sptr,sptr,sptr,sptr,sptr
	#func global SHMapPIDLToSystemImageListIndex "SHMapPIDLToSystemImageListIndex" sptr,sptr,sptr
	#func global SHMultiFileProperties "SHMultiFileProperties" sptr,sptr
	#func global SHObjectProperties "SHObjectProperties" sptr,sptr,sptr,sptr
	#func global SHOpenFolderAndSelectItems "SHOpenFolderAndSelectItems" sptr,sptr,sptr,sptr
	#func global SHOpenPropSheetW "SHOpenPropSheetW" wptr,wptr,wptr,wptr,wptr,wptr,wptr
	#func global SHParseDisplayName "SHParseDisplayName" sptr,sptr,sptr,sptr,sptr
	#define global SHPathPrepareForWrite SHPathPrepareForWriteA
	#func global SHPathPrepareForWriteA "SHPathPrepareForWriteA" sptr,sptr,sptr,sptr
	#func global SHPathPrepareForWriteW "SHPathPrepareForWriteW" wptr,wptr,wptr,wptr
	#func global SHPropStgCreate "SHPropStgCreate" sptr,sptr,sptr,sptr,sptr,sptr,sptr,sptr
	#func global SHPropStgReadMultiple "SHPropStgReadMultiple" sptr,sptr,sptr,sptr,sptr
	#func global SHPropStgWriteMultiple "SHPropStgWriteMultiple" sptr,sptr,sptr,sptr,sptr,sptr
	#define global SHQueryRecycleBin SHQueryRecycleBinA
	#func global SHQueryRecycleBinA "SHQueryRecycleBinA" sptr,sptr
	#func global SHQueryRecycleBinW "SHQueryRecycleBinW" wptr,wptr
	#func global SHReplaceFromPropSheetExtArray "SHReplaceFromPropSheetExtArray" sptr,sptr,sptr,sptr
	#func global SHRestricted "SHRestricted" sptr
	#func global SHRunControlPanel "SHRunControlPanel" sptr,sptr
	#func global SHSetInstanceExplorer "SHSetInstanceExplorer" sptr
	#func global SHSetLocalizedName "SHSetLocalizedName" sptr,sptr,sptr
	#func global SHSetUnreadMailCountW "SHSetUnreadMailCountW" wptr,wptr,wptr
	#func global SHShellFolderView_Message "SHShellFolderView_Message" sptr,sptr,sptr
	#func global SHSimpleIDListFromPath "SHSimpleIDListFromPath" sptr
	#func global SHStartNetConnectionDialogW "SHStartNetConnectionDialogW" wptr,wptr,wptr
	#func global SHTestTokenMembership "SHTestTokenMembership" sptr,sptr
	#func global SHUnlockShared "SHUnlockShared" sptr
	#define global SHUpdateImage SHUpdateImageA
	#func global SHUpdateImageA "SHUpdateImageA" sptr,sptr,sptr,sptr
	#func global SHUpdateImageW "SHUpdateImageW" wptr,wptr,wptr,wptr
	#func global SHUpdateRecycleBinIcon "SHUpdateRecycleBinIcon"
	#func global SHValidateUNC "SHValidateUNC" sptr,sptr,sptr
	#define global SheChangeDir SheChangeDirA
	#func global SheChangeDirA "SheChangeDirA" sptr
	#define global SheChangeDirEx SheChangeDirExA
	#func global SheChangeDirExA "SheChangeDirExA" sptr
	#func global SheChangeDirExW "SheChangeDirExW" wptr
	#func global SheChangeDirW "SheChangeDirW" wptr
	#func global SheConvertPathW "SheConvertPathW" wptr,wptr,wptr
	#define global SheFullPath SheFullPathA
	#func global SheFullPathA "SheFullPathA" sptr,sptr,sptr
	#func global SheFullPathW "SheFullPathW" wptr,wptr,wptr
	#func global SheGetCurDrive "SheGetCurDrive"
	#define global SheGetDir SheGetDirA
	#func global SheGetDirA "SheGetDirA" sptr,sptr
	#func global SheGetDirExW "SheGetDirExW" wptr,wptr,wptr
	#func global SheGetDirW "SheGetDirW" wptr,wptr
	#func global SheGetPathOffsetW "SheGetPathOffsetW" wptr
	#define global SheRemoveQuotes SheRemoveQuotesA
	#func global SheRemoveQuotesA "SheRemoveQuotesA" sptr
	#func global SheRemoveQuotesW "SheRemoveQuotesW" wptr
	#func global SheSetCurDrive "SheSetCurDrive" sptr
	#define global SheShortenPath SheShortenPathA
	#func global SheShortenPathA "SheShortenPathA" sptr,sptr
	#func global SheShortenPathW "SheShortenPathW" wptr,wptr
	#define global ShellAbout ShellAboutA
	#func global ShellAboutA "ShellAboutA" sptr,sptr,sptr,sptr
	#func global ShellAboutW "ShellAboutW" wptr,wptr,wptr,wptr
	#define global ShellExecute ShellExecuteA
	#func global ShellExecuteA "ShellExecuteA" sptr,sptr,sptr,sptr,sptr,sptr
	#func global ShellExecuteEx "ShellExecuteEx" sptr
	#func global ShellExecuteExA "ShellExecuteExA" sptr
	#func global ShellExecuteExW "ShellExecuteExW" wptr
	#func global ShellExecuteW "ShellExecuteW" wptr,wptr,wptr,wptr,wptr,wptr
	#func global ShellHookProc "ShellHookProc" sptr,sptr,sptr
	#define global ShellMessageBox ShellMessageBoxA
	#func global ShellMessageBoxA "ShellMessageBoxA" sptr,sptr,sptr,sptr,sptr,sptr,sptr,sptr,sptr,sptr,sptr,sptr,sptr,sptr,sptr,sptr
	#func global ShellMessageBoxW "ShellMessageBoxW" wptr,wptr,wptr,wptr,wptr,wptr,wptr,wptr,wptr,wptr,wptr,wptr,wptr,wptr,wptr,wptr
	#func global Shell_GetCachedImageIndex "Shell_GetCachedImageIndex" sptr,sptr,sptr
	#func global Shell_GetImageLists "Shell_GetImageLists" sptr,sptr
	#func global Shell_MergeMenus "Shell_MergeMenus" sptr,sptr,sptr,sptr,sptr,sptr
	#func global Shell_NotifyIcon "Shell_NotifyIcon" sptr,sptr
	#func global Shell_NotifyIconA "Shell_NotifyIconA" sptr,sptr
	#func global Shell_NotifyIconW "Shell_NotifyIconW" wptr,wptr
	#func global SignalFileOpen "SignalFileOpen" sptr
	#func global WOWShellExecute "WOWShellExecute" sptr,sptr,sptr,sptr,sptr,sptr,sptr
	#func global Win32DeleteFile "Win32DeleteFile" sptr
	#func global WriteCabinetState "WriteCabinetState" sptr
#endif
#endif
