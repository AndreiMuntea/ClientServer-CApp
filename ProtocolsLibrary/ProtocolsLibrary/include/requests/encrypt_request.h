#ifndef PROTOCOLS_REQUESTS_ENCRYPT_REQUEST_H
#define PROTOCOLS_REQUESTS_ENCRYPT_REQUEST_H

#include <Windows.h>


#include "../definitions.h"
#include "../message_types.h"


typedef struct _ENCRYPT_REQUEST
{
   MESSAGE_TYPE requestType;
   DWORD        encryptBufferLength;
   CHAR         encryptBuffer[MAX_ENCRYPT_BUFFER_LENGTH];

}ENCRYPT_REQUEST, *PENCRYPT_REQUEST;


STATUS
CreateEncryptRequest(
   _Out_    PENCRYPT_REQUEST*    request,
   _In_     DWORD                encryptBufferSize,
   _In_     LPCSTR               encryptBuffer
);

VOID
DestroyEncryptRequest(
   _Inout_  PENCRYPT_REQUEST*    request
);

DWORD
GetEncryptRequestSize(
   _In_     PENCRYPT_REQUEST     request
);

BOOL
IsEncryptRequest(
   _In_     LPVOID               lpData,
   _In_     DWORD                nDataSize
);

PENCRYPT_REQUEST
ConvertToEncryptRequest(
   _In_     LPVOID               lpData
);

#endif //PROTOCOLS_REQUESTS_ENCRYPT_REQUEST_H