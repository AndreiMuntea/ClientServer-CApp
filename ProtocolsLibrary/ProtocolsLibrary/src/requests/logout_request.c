#include "../../include/requests/logout_request.h"
#include "../../include/strutils/strutils.h"


STATUS
CreateLogoutRequest(
   _Out_    PLOGOUT_REQUEST*     request,
   _In_     LPCSTR               userName
)
{
   STATUS status;
   size_t userNameLength;
   PLOGOUT_REQUEST tempRequest;

   userNameLength = 0;
   status = EXIT_SUCCESS_STATUS;
   tempRequest = NULL;

   if(NULL == request)
   {
      status = NULL_POINTER;
      goto CleanUp;
   }

   tempRequest = (PLOGOUT_REQUEST)malloc(sizeof(LOGOUT_REQUEST));
   if(NULL == tempRequest)
   {
      status = BAD_ALLOCATION;
      goto CleanUp;
   }

   FillWithZeroes(tempRequest->userName, MAX_USERNAME_LENGTH);

   status = CopyBufferWithoutAlloc(userName, MAX_USERNAME_LENGTH, tempRequest->userName, &userNameLength);
   if (!SUCCESS(status))
   {
      goto CleanUp;
   }

   tempRequest->requestType = REQUEST_LOGOUT;
   tempRequest->nUserNameLength = userNameLength;
   
   *request = tempRequest;


CleanUp:
   if(!SUCCESS(status))
   {
      DestroyLogoutRequest(&tempRequest);
   }
   return status;
}

VOID
DestroyLogoutRequest(
   _Inout_  PLOGOUT_REQUEST*     request
)
{
   if(NULL == request)
   {
      goto Out;
   }

   if(NULL == *request)
   {
      goto Out;
   }

   free(*request);
   *request = NULL;
   
Out:;
}

DWORD
GetLogoutRequestSize(
   _In_     PLOGOUT_REQUEST     request
)
{
   DWORD res;

   res = 0;

   if (NULL == request)
   {
      goto Out;
   }

   res = sizeof(MESSAGE_TYPE) +
      sizeof(DWORD) +
      MAX_USERNAME_LENGTH * sizeof(CHAR);

Out:
   return res;
}

BOOL
IsLogoutRequest(
   _In_     LPVOID               lpData,
   _In_     DWORD                nDataSize
)
{
   PLOGOUT_REQUEST request;
   request = (PLOGOUT_REQUEST)lpData;

   return(GetLogoutRequestSize(request) == nDataSize && request->requestType == REQUEST_LOGOUT);
}

PLOGOUT_REQUEST
ConvertToLogoutRequest(
   _In_     LPVOID               lpData
)
{
   return (PLOGOUT_REQUEST)lpData;
}