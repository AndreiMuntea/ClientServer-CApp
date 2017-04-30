#include "../../include/requests/encrypt_request.h"
#include "../../include/strutils/strutils.h"

STATUS
CreateEncryptRequest(
   _Out_    PENCRYPT_REQUEST*    request,
   _In_     DWORD                encryptBufferSize,
   _In_     LPCSTR               encryptBuffer
)
{
   STATUS status;
   DWORD i;
   PENCRYPT_REQUEST tempRequest;

   i = 0;
   status = EXIT_SUCCESS_STATUS;
   tempRequest = NULL;

   if(NULL == request)
   {
      status = NULL_POINTER;
      goto CleanUp;
   }

   if (encryptBufferSize > MAX_ENCRYPT_BUFFER_LENGTH)
   {
      status = INVALID_BUFFER_SIZE;
      goto CleanUp;
   }

   tempRequest = (PENCRYPT_REQUEST)malloc(sizeof(ENCRYPT_REQUEST));
   if(NULL == tempRequest)
   {
      status = BAD_ALLOCATION;
      goto CleanUp;
   }
   
   FillWithZeroes(tempRequest->encryptBuffer, MAX_ENCRYPT_BUFFER_LENGTH);
   for(i = 0; i < encryptBufferSize; ++i)
   {
      tempRequest->encryptBuffer[i] = encryptBuffer[i];
   }

   tempRequest->encryptBufferLength = encryptBufferSize;
   tempRequest->requestType = REQUEST_ENCRYPT;
   *request = tempRequest;



CleanUp:
   if(!SUCCESS(status))
   {
      DestroyEncryptRequest(&tempRequest);
   }
   return status;
}

VOID
DestroyEncryptRequest(
   _Inout_  PENCRYPT_REQUEST*    request
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
GetEncryptRequestSize(
   _In_     PENCRYPT_REQUEST     request
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
      MAX_ENCRYPT_BUFFER_LENGTH * sizeof(CHAR);

Out:
   return res;
}


BOOL
IsEncryptRequest(
   _In_     LPVOID               lpData,
   _In_     DWORD                nDataSize
)
{
   PENCRYPT_REQUEST request;
   request = (PENCRYPT_REQUEST)lpData;

   return(GetEncryptRequestSize(request) == nDataSize && request->requestType == REQUEST_ENCRYPT);
}

PENCRYPT_REQUEST
ConvertToEncryptRequest(
   _In_     LPVOID               lpData
)
{
   return (PENCRYPT_REQUEST)lpData;
}
