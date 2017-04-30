#ifndef PROTOCOLS_RESPONSES_FAILURE_RESPONSE_H
#define PROTOCOLS_RESPONSES_FAILURE_RESPONSE_H

#include <Windows.h>

#include "../message_types.h"
#include "../definitions.h"


typedef struct _FAILURE_RESPONSE
{
   MESSAGE_TYPE  responseType;
   STATUS        status;
}FAILURE_RESPONSE, *PFAILURE_RESPONSE;

STATUS
CreateFailureResponse(
   _Out_    PFAILURE_RESPONSE*   response,
   _In_     STATUS               responseStatus
);

VOID
DestroyFailureResponse(
   _Inout_  PFAILURE_RESPONSE*   response
);

DWORD
GetFailureResponseSize(
   _In_     PFAILURE_RESPONSE    response
);

BOOL
IsFailureResponse(
   _In_     LPVOID               lpData,
   _In_     DWORD                nDataSize
);

PFAILURE_RESPONSE
ConvertToFailureResponse(
   _In_     LPVOID               lpData
);

#endif //PROTOCOLS_RESPONSES_FAILURE_RESPONSE_H