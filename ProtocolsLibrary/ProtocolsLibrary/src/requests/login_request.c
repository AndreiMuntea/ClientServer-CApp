#include "../../include/requests/login_request.h"
#include "../../include/strutils/strutils.h"


STATUS
CreateLoginRequest(
   _Out_       PLOGIN_REQUEST*   request,
   _In_        LPCSTR            userName,
   _In_        LPCSTR            password,
   _In_        LPCSTR            key
)
{
   STATUS status;
   size_t userNameLength;
   size_t passwordLength;
   size_t keyLength;
   PLOGIN_REQUEST tempRequest;


   userNameLength = 0;
   passwordLength = 0;
   keyLength = 0;
   status = EXIT_SUCCESS_STATUS;
   tempRequest = NULL;

   if(NULL == request)
   {
      status = NULL_POINTER;
      goto CleanUp;
   }


   tempRequest = (PLOGIN_REQUEST)malloc(sizeof(LOGIN_REQUEST));
   if(NULL == tempRequest)
   {
      status = BAD_ALLOCATION;
      goto CleanUp;
   }
   
   FillWithZeroes(tempRequest->userName, MAX_USERNAME_LENGTH);
   FillWithZeroes(tempRequest->key, MAX_KEY_LENGTH);
   FillWithZeroes(tempRequest->password, MAX_PASSWORD_LENGTH);

   status = CopyBufferWithoutAlloc(userName, MAX_USERNAME_LENGTH, tempRequest->userName, &userNameLength);
   if(!SUCCESS(status))
   {
      goto CleanUp;
   }

   status = CopyBufferWithoutAlloc(key, MAX_KEY_LENGTH, tempRequest->key, &keyLength);
   if (!SUCCESS(status))
   {
      goto CleanUp;
   }

   status = CopyBufferWithoutAlloc(password, MAX_PASSWORD_LENGTH, tempRequest->password, &passwordLength);
   if (!SUCCESS(status))
   {
      goto CleanUp;
   }

   tempRequest->requestType = REQUEST_LOGIN;
   tempRequest->nUserNameLength = userNameLength;
   tempRequest->nKeyLength = keyLength;
   tempRequest->nPasswordLength = passwordLength;

   *request = tempRequest;

CleanUp:
   if(!SUCCESS(status))
   {
      DestroyLoginRequest(&tempRequest);
   }
   return status;
}

VOID
DestroyLoginRequest(
   _Inout_     PLOGIN_REQUEST*   request
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
GetLoginRequestSize(
   _In_        PLOGIN_REQUEST    request
)
{
   DWORD res;

   res = 0;

   if(NULL == request)
   {
      goto Out;
   }

   res = sizeof(MESSAGE_TYPE) +
      3 * sizeof(DWORD) +
      MAX_PASSWORD_LENGTH * sizeof(CHAR) +
      MAX_KEY_LENGTH * sizeof(CHAR) +
      MAX_USERNAME_LENGTH * sizeof(CHAR);

Out:
   return res;
}

BOOL
IsLoginRequest(
   _In_     LPVOID               lpData,
   _In_     DWORD                nDataSize
)
{
   PLOGIN_REQUEST request;
   request = (PLOGIN_REQUEST)lpData;

   return(GetLoginRequestSize(request) == nDataSize && request->requestType == REQUEST_LOGIN);
}

PLOGIN_REQUEST
ConvertToLoginRequest(
   _In_     LPVOID               lpData
)
{
   return (PLOGIN_REQUEST)lpData;
}