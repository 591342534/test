#include "StdAfx.h"
#include "CFunction.h"

#pragma comment(lib, "Psapi.lib")

namespace CFUNCTION
{
    BOOL GetProcessPathByPID( DWORD dwPID, LPTSTR lpPath )
    {
        if (!lpPath)
        {
            return FALSE;
        }

        BOOL bRet = FALSE;
        HANDLE hProcess = ::OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, dwPID);
        if (!hProcess)
        {
            goto Exit0;
        }

        if (!::GetModuleFileNameEx(hProcess, NULL, lpPath, MAX_PATH))
        {
            goto Exit0;
        }

        bRet = TRUE;
    Exit0:
        if (hProcess)
        {
            ::CloseHandle(hProcess);
        }
        return bRet;
    }

    BOOL ReadFileToBuffer( LPCTSTR lpFilePath, CStringA& strData )
    {
        if (!lpFilePath || !*lpFilePath)
        {
            return FALSE;
        }

        BOOL bRet = FALSE;
        DWORD dwFileSize = 0;
        LPSTR lpBuffer = NULL;
        HANDLE hFile = ::CreateFile(lpFilePath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
        if (INVALID_HANDLE_VALUE == hFile)
        {
            goto Exit0;
        }
 
        dwFileSize = ::GetFileSize(hFile, NULL);
        if (INVALID_FILE_SIZE == dwFileSize)
        {
            goto Exit0;
        }

        lpBuffer = new char[dwFileSize + 1];
        if (!lpBuffer)
        {
            goto Exit0;
        }

        if (!::ReadFile(hFile, lpBuffer, dwFileSize, &dwFileSize, NULL))
        {
            goto Exit0;
        }

        lpBuffer[dwFileSize] = '\0';
        strData = lpBuffer;
        bRet = TRUE;

    Exit0:
        if (lpBuffer)
        {
            delete[] lpBuffer;
            lpBuffer = NULL;
        }

        if (INVALID_HANDLE_VALUE != hFile)
        {
            ::CloseHandle(hFile);
            hFile = INVALID_HANDLE_VALUE;
        }

        return bRet;
    }

    BOOL WriteBufferToFile( LPCTSTR lpFilePath, CStringA& strData )
    {
        BOOL bRet = FALSE;
        HANDLE hFile = ::CreateFile(lpFilePath, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        if (hFile == INVALID_HANDLE_VALUE)
        {
            goto Exit0;
        }

        DWORD dwSizeWrite = 0;
        DWORD dwSizeToWrite = strData.GetLength();
        BOOL bRetCode = ::WriteFile(hFile, strData.GetBuffer(), dwSizeToWrite, &dwSizeWrite, NULL);

        strData.ReleaseBuffer();
        if (!bRetCode || dwSizeWrite != dwSizeToWrite) 
        {
            goto Exit0;
        }

        bRet = TRUE;
    Exit0:
        if (hFile != INVALID_HANDLE_VALUE) 
        {
            ::CloseHandle(hFile);
            hFile = INVALID_HANDLE_VALUE;
        }

        return bRet;
    }
}