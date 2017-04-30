#ifndef PROTOCOLS_REQUESTS_LOGOUT_REQUEST_H
#define PROTOCOLS_REQUEST_LOGOUT_REQUEST_H

#include <Windows.h>

#include "../definitions.h"
#include "../message_types.h"


typedef struct _LOGOUT_REQUEST
{
   MESSAGE_TYPE requestType;
   DWORD        nUserNameLength;
   CHAR         userName[MAX_USERNAME_LENGTH];

}LOGOUT_REQUEST, *PLOGOUT_REQUEST;

STATUS
CreateLogoutRequest(
   _Out_    PLOGOUT_REQUEST*     request,
   _In_     LPCSTR               userName
);

VOID
DestroyLogoutRequest(
   _Inout_  PLOGOUT_REQUEST*     request
);

DWORD
GetLogoutRequestSize(
   _In_     PLOGOUT_REQUEST     request
);


BOOL
IsLogoutRequest(
   _In_     LPVOID               lpData,
   _In_     DWORD                nDataSize
);

PLOGOUT_REQUEST
ConvertToLogoutRequest(
   _In_     LPVOID               lpData
);

#endif //PROTOCOLS_REQUEST_LOGOUT_REQUEST_H