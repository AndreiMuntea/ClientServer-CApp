#ifndef PROTOCOLS_RESPONSES_OK_RESPONSE_H
#define PROTOCOLS_RESPONSES_OK_RESPONSE_H

#include <Windows.h>

#include "../message_types.h"
#include "../definitions.h"


typedef struct _OK_RESPONSE
{
   MESSAGE_TYPE  responseType;
   STATUS        status;
}OK_RESPONSE, *POK_RESPONSE;

STATUS
CreateOkResponse(
   _Out_    POK_RESPONSE*  response,
   _In_     STATUS         responseStatus
);

VOID
DestroyOkResponse(
   _Inout_  POK_RESPONSE*  response
);

DWORD
GetOkResponseSize(
   _In_     POK_RESPONSE   response
);

BOOL
IsOkResponse(
   _In_     LPVOID               lpData,
   _In_     DWORD                nDataSize
);

POK_RESPONSE
ConvertToOkResponse(
   _In_     LPVOID               lpData
);

#endif //PROTOCOLS_RESPONSES_OK_RESPONSE_H