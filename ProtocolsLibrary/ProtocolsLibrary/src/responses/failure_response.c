#include "../../include/responses/failure_response.h"


STATUS
CreateFailureResponse(
   _Out_    PFAILURE_RESPONSE*   response,
   _In_     STATUS               responseStatus
)
{
   STATUS status;
   PFAILURE_RESPONSE tempResponse;

   status = EXIT_SUCCESS_STATUS;
   tempResponse = NULL;

   if (NULL == response)
   {
      status = NULL_POINTER;
      goto CleanUp;
   }

   tempResponse = (PFAILURE_RESPONSE)malloc(sizeof(FAILURE_RESPONSE));
   if (NULL == tempResponse)
   {
      status = BAD_ALLOCATION;
      goto CleanUp;
   }

   tempResponse->responseType = RESPONSE_FAILURE;
   tempResponse->status = responseStatus;
   *response = tempResponse;

CleanUp:
   if (!SUCCESS(status))
   {
      DestroyFailureResponse(&tempResponse);
   }
   return status;
}

VOID
DestroyFailureResponse(
   _Inout_  PFAILURE_RESPONSE*   response
)
{
   if (NULL == response)
   {
      goto Out;
   }

   if (NULL == *response)
   {
      goto Out;
   }

   free(*response);
   *response = NULL;

Out:;
}

DWORD
GetFailureResponseSize(
   _In_     PFAILURE_RESPONSE    response
)
{
   DWORD res;

   res = 0;

   if (NULL == response)
   {
      goto Out;
   }

   res = sizeof(MESSAGE_TYPE) + sizeof(STATUS);

Out:
   return res;
}


BOOL
IsFailureResponse(
   _In_     LPVOID               lpData,
   _In_     DWORD                nDataSize
)
{
   PFAILURE_RESPONSE response;
   response = (PFAILURE_RESPONSE)lpData;
   
   return(nDataSize == GetFailureResponseSize(response) && response->responseType == RESPONSE_FAILURE);
}

PFAILURE_RESPONSE
ConvertToFailureResponse(
   _In_     LPVOID               lpData
)
{
   return (PFAILURE_RESPONSE)lpData;
}