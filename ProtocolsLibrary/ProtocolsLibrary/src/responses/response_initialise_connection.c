#include "../../include/responses/response_initialise_connection.h"
#include "../../include/strutils/strutils.h"

STATUS
CreateInitialiseConnectionResponse(
   _Out_       PINITIALISE_CONNECTION_RESPONSE*       response,
   _In_        LPCSTR                                 serverInputPipeFileName,
   _In_        LPCSTR                                 serverOutputPipeFileName
)
{
   STATUS status;
   size_t serverInputFileNameSize;
   size_t serverOutputFileNameSize;
   PINITIALISE_CONNECTION_RESPONSE tempResponse;

   serverInputFileNameSize = 0;
   serverOutputFileNameSize = 0;
   status = EXIT_SUCCESS_STATUS;
   tempResponse = NULL;

   if(NULL == response)
   {
      status = NULL_POINTER;
      goto CleanUp;
   }

   tempResponse = (PINITIALISE_CONNECTION_RESPONSE)malloc(sizeof(INITIALISE_CONNECTION_RESPONSE));
   if(NULL == tempResponse)
   {
      status = BAD_ALLOCATION;
      goto CleanUp;
   }

   FillWithZeroes(tempResponse->serverInputPipeFileName, MAX_PIPE_NAME_LENGTH);
   FillWithZeroes(tempResponse->serverOutputPipeFileName, MAX_PIPE_NAME_LENGTH);

   status = CopyBufferWithoutAlloc(
      serverInputPipeFileName, 
      MAX_PIPE_NAME_LENGTH, 
      tempResponse->serverInputPipeFileName, 
      &serverInputFileNameSize
   );
   if(!SUCCESS(status))
   {
      goto CleanUp;
   }

   status = CopyBufferWithoutAlloc(
      serverOutputPipeFileName, 
      MAX_PIPE_NAME_LENGTH, 
      tempResponse->serverOutputPipeFileName, 
      &serverOutputFileNameSize
   );
   if (!SUCCESS(status))
   {
      goto CleanUp;
   }

   tempResponse->serverInputPipeFileNameSize = serverInputFileNameSize;
   tempResponse->serverOutputPipeFileNameSize = serverOutputFileNameSize;
   tempResponse->responseType = RESPONSE_INITIALISE_CONNECTION;
   *response = tempResponse;

CleanUp:
   if(!SUCCESS(status))
   {
      DestroyInitialiseConnectionResponse(&tempResponse);
   }
   return status;
}

VOID
DestroyInitialiseConnectionResponse(
   _Inout_     PINITIALISE_CONNECTION_RESPONSE*       response
)
{
   if(NULL == response)
   {
      goto Out;
   }

   if(NULL == *response)
   {
      goto Out;
   }

   free(*response);
   *response = NULL;

Out:;
}

DWORD
GetInitialiseConnectionResponseSize(
   _In_        PINITIALISE_CONNECTION_RESPONSE        response
)
{
   DWORD res;

   res = 0;

   if (NULL == response)
   {
      goto Out;
   }

   res = sizeof(MESSAGE_TYPE) +
      2 * sizeof(DWORD) +
      2 * MAX_PIPE_NAME_LENGTH * sizeof(CHAR);

Out:
   return res;
}

BOOL
IsGetInitialiseConnectionResponse(
   _In_     LPVOID               lpData,
   _In_     DWORD                nDataSize
)
{
   PINITIALISE_CONNECTION_RESPONSE response;
   response = (PINITIALISE_CONNECTION_RESPONSE)lpData;

   return(nDataSize == GetInitialiseConnectionResponseSize(response) && response->responseType == RESPONSE_INITIALISE_CONNECTION);
}

PINITIALISE_CONNECTION_RESPONSE
ConvertToInitialiseConnectionResponse(
   _In_     LPVOID               lpData
)
{
   return (PINITIALISE_CONNECTION_RESPONSE)lpData;
}