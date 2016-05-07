#pragma once

namespace CFUNCTION
{
    BOOL GetProcessPathByPID(DWORD dwPID, LPTSTR lpPath);

    //ÎÄ¼þ¶ÁÐ´²Ù×÷
    BOOL ReadFileToBuffer(LPCTSTR lpFilePath, CStringA& strData);
    BOOL WriteBufferToFile(LPCTSTR lpFilePath, CStringA& strData);
}
