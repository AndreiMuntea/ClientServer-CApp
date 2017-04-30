#ifndef PROTOCOLS_RESPONSES_INITIALISE_CONNECTION_H
#define PROTOCOLS_RESPONSES_INITIALISE_CONNECTION_H

#include <Windows.h>

#include "../message_types.h"
#include "../definitions.h"

typedef struct _INITIALISE_CONNECTION_RESPONSE
{
   MESSAGE_TYPE  responseType;
   DWORD         serverInputPipeFileNameSize;
   CHAR          serverInputPipeFileName[MAX_PIPE_NAME_LENGTH];
   DWORD         serverOutputPipeFileNameSize;
   CHAR          serverOutputPipeFileName[MAX_PIPE_NAME_LENGTH];
}INITIALISE_CONNECTION_RESPONSE,*PINITIALISE_CONNECTION_RESPONSE;

STATUS
CreateInitialiseConnectionResponse(
   _Out_       PINITIALISE_CONNECTION_RESPONSE*       response,
   _In_        LPCSTR                                 serverInputPipeFileName,
   _In_        LPCSTR                                 serverOutputPipeFileName
);

VOID
DestroyInitialiseConnectionResponse(
   _Inout_     PINITIALISE_CONNECTION_RESPONSE*       response
);

DWORD
GetInitialiseConnectionResponseSize(
   _In_        PINITIALISE_CONNECTION_RESPONSE        response
);

BOOL
IsGetInitialiseConnectionResponse(
   _In_     LPVOID               lpData,
   _In_     DWORD                nDataSize
);

PINITIALISE_CONNECTION_RESPONSE
ConvertToInitialiseConnectionResponse(
   _In_     LPVOID               lpData
);

#endif //PROTOCOLS_RESPONSES_INITIALISE_CONNECTION_H