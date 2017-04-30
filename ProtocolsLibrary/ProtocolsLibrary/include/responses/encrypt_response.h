#ifndef PROTOCOLS_RESPONSES_ENCRYPT_RESPONSE_H
#define PROTOCOLS_RESPONSES_ENCRYPT_RESPONSE_H

#include <Windows.h>

#include "../message_types.h"
#include "../definitions.h"

typedef struct _ENCRYPT_RESPONSE
{
   MESSAGE_TYPE  responseType;
   DWORD         encryptBufferSize;
   CHAR          encryptBuffer[MAX_ENCRYPT_BUFFER_LENGTH];

}ENCRYPT_RESPONSE, *PENCRYPT_RESPONSE;


STATUS
CreateEncryptResponse(
   _Out_    PENCRYPT_RESPONSE*      response,
   _In_     LPCSTR                  encryptBuffer,
   _In_     DWORD                   encryptBufferSize
);

VOID
DestroyEncryptResponse(
   _Inout_  PENCRYPT_RESPONSE*      response
);

DWORD
GetEncryptResponseSize(
   _In_  PENCRYPT_RESPONSE          response
);


BOOL
IsEncryptResponse(
   _In_     LPVOID               lpData,
   _In_     DWORD                nDataSize
);

PENCRYPT_RESPONSE
ConvertToEncryptResponse(
   _In_     LPVOID               lpData
);

#endif //PROTOCOLS_RESPONSES_ENCRYPT_RESPONSE_H