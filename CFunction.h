#pragma once

namespace CFUNCTION
{
    BOOL GetProcessPathByPID(DWORD dwPID, LPTSTR lpPath);

    //�ļ���д����
    BOOL ReadFileToBuffer(LPCTSTR lpFilePath, CStringA& strData);
    BOOL WriteBufferToFile(LPCTSTR lpFilePath, CStringA& strData);
}
