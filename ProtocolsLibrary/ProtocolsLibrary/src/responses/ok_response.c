#include "../../include/responses/ok_response.h"

STATUS
CreateOkResponse(
   _Out_    POK_RESPONSE*  response,
   _In_     STATUS         responseStatus
)
{
   STATUS status;
   POK_RESPONSE tempResponse;

   status = EXIT_SUCCESS_STATUS;
   tempResponse = NULL;

   if(NULL == response)
   {
      status = NULL_POINTER;
      goto CleanUp;
   }

   tempResponse = (POK_RESPONSE)malloc(sizeof(OK_RESPONSE));
   if(NULL == tempResponse)
   {
      status = BAD_ALLOCATION;
      goto CleanUp;
   }

   tempResponse->responseType = RESPONSE_OK;
   tempResponse->status = responseStatus;
   *response = tempResponse;

CleanUp:
   if(!SUCCESS(status))
   {
      DestroyOkResponse(&tempResponse);
   }
   return status;
}

VOID
DestroyOkResponse(
   _Inout_  POK_RESPONSE*  response
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
GetOkResponseSize(
   _In_     POK_RESPONSE   response
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
IsOkResponse(
   _In_     LPVOID               lpData,
   _In_     DWORD                nDataSize
)
{
   POK_RESPONSE response;
   response = (POK_RESPONSE)lpData;
   
   return(nDataSize == GetOkResponseSize(response) && response->responseType == RESPONSE_OK);
}

POK_RESPONSE
ConvertToOkResponse(
   _In_     LPVOID               lpData
)
{
   return (POK_RESPONSE)lpData;
}
