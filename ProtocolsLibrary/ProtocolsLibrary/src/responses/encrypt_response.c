#include "../../include/responses/encrypt_response.h"
#include "../../include/strutils/strutils.h"

STATUS
CreateEncryptResponse(
   _Out_    PENCRYPT_RESPONSE*      response,
   _In_     LPCSTR                  encryptBuffer,
   _In_     DWORD                   encryptBufferSize
)
{
   STATUS status;
   PENCRYPT_RESPONSE tempResponse;
   DWORD i;

   i = 0;
   status = EXIT_SUCCESS_STATUS;
   tempResponse = NULL;

   if(NULL == response)
   {
      status = NULL_POINTER;
      goto CleanUp;
   }

   if (encryptBufferSize > MAX_ENCRYPT_BUFFER_LENGTH)
   {
      status = INVALID_BUFFER_SIZE;
      goto CleanUp;
   }

   tempResponse = (PENCRYPT_RESPONSE)malloc(sizeof(ENCRYPT_RESPONSE));
   if(NULL == tempResponse)
   {
      status = BAD_ALLOCATION;
      goto CleanUp;
   }

   FillWithZeroes(tempResponse->encryptBuffer, MAX_ENCRYPT_BUFFER_LENGTH);
   for (i = 0; i < encryptBufferSize; ++i)
   {
      tempResponse->encryptBuffer[i] = encryptBuffer[i];
   }
      
   tempResponse->responseType = RESPONSE_ENCRYPT;
   tempResponse->encryptBufferSize = encryptBufferSize;
   *response = tempResponse;

CleanUp:
   if(!SUCCESS(status))
   {
      DestroyEncryptResponse(&tempResponse);
   }
   return status;
}

VOID
DestroyEncryptResponse(
   _Inout_  PENCRYPT_RESPONSE*      response
)
{
   if (NULL == response)
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
GetEncryptResponseSize(
   _In_  PENCRYPT_RESPONSE          response
)
{
   DWORD res;

   res = 0;

   if (NULL == response)
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
IsEncryptResponse(
   _In_     LPVOID               lpData,
   _In_     DWORD                nDataSize
)
{
   PENCRYPT_RESPONSE response;
   response = (PENCRYPT_RESPONSE)lpData;
   
   return(GetEncryptResponseSize(response) == nDataSize && response->responseType == RESPONSE_ENCRYPT);
}

PENCRYPT_RESPONSE
ConvertToEncryptResponse(
   _In_     LPVOID               lpData
)
{
   return (PENCRYPT_RESPONSE)lpData;
}