#ifndef PROTOCOLS_REQUESTS_LOGIN_REQUEST_H
#define PROTOCOLS_REQUESTS_LOGIN_REQUEST_H

#include <Windows.h>

#include "../definitions.h"
#include "../message_types.h"


typedef struct _LOGIN_REQUEST
{
   MESSAGE_TYPE requestType;
   DWORD        nUserNameLength;
   CHAR         userName[MAX_USERNAME_LENGTH];
   DWORD        nPasswordLength;
   CHAR         password[MAX_PASSWORD_LENGTH];
   DWORD        nKeyLength;
   CHAR         key[MAX_KEY_LENGTH];
}LOGIN_REQUEST, *PLOGIN_REQUEST;


STATUS
CreateLoginRequest(
   _Out_       PLOGIN_REQUEST*   request,
   _In_        LPCSTR            userName,
   _In_        LPCSTR            password,
   _In_        LPCSTR            key
);

VOID
DestroyLoginRequest(
   _Inout_     PLOGIN_REQUEST*   request
);


DWORD
GetLoginRequestSize(
   _In_        PLOGIN_REQUEST    request
);

BOOL
IsLoginRequest(
   _In_     LPVOID               lpData,
   _In_     DWORD                nDataSize
);

PLOGIN_REQUEST
ConvertToLoginRequest(
   _In_     LPVOID               lpData
);

#endif //PROTOCOLS_REQUESTS_LOGIN_REQUEST_H