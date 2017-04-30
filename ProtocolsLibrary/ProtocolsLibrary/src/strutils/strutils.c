#include "../../include/strutils/strutils.h"

#include <strsafe.h>


STATUS
CreatePipeName(
   _Out_    LPSTR*      destination,
   _In_     LPCSTR      source
)
{
   STATUS status;
   size_t sourceSize;
   size_t prefixSize;
   size_t finalSize;
   LPSTR tempPipeName;
   HRESULT res;

   res = S_OK;
   finalSize = 0;
   sourceSize = 0;
   prefixSize = 0;
   status = EXIT_SUCCESS_STATUS;
   tempPipeName = NULL;

   if(NULL == destination || 
      NULL == source)
   {
      status = NULL_POINTER;
      goto CleanUp;
   }

   res = StringCchLengthA(source, STRSAFE_MAX_CCH, &sourceSize);
   if(S_OK != res)
   {
      status = res;
      goto CleanUp;
   }

   res = StringCchLengthA(PIPE_PREFIX, STRSAFE_MAX_CCH, &prefixSize);
   if(S_OK != res)
   {
      status = res;
      goto CleanUp;
   }

   finalSize = sourceSize + prefixSize + 1;

   if(finalSize > MAX_PIPE_NAME_LENGTH)
   {
      status = INVALID_PIPE_NAME;
      goto CleanUp;
   }

   tempPipeName = (LPSTR)malloc(finalSize * sizeof(CHAR));
   if(NULL == tempPipeName)
   {
      status = BAD_ALLOCATION;
      goto CleanUp;
   }

   res = StringCchCopyA(tempPipeName, finalSize, PIPE_PREFIX);
   if(S_OK != res)
   {
      status = res;
      goto CleanUp;
   }

   res = StringCchCatA(tempPipeName, finalSize, source);
   if (S_OK != res)
   {
      status = res;
      goto CleanUp;
   }

   *destination = tempPipeName;

CleanUp:
   if(!SUCCESS(status))
   {
      free(tempPipeName);
      tempPipeName = NULL;
   }
   return status;
}

STATUS
CopyBufferWithAlloc(
   _In_     LPCSTR      source,
   _Out_    LPSTR*      destination,
   _Out_    size_t*     destinationSize
)
{
   STATUS status;
   size_t srcSize;
   HRESULT result;
   LPSTR tempBuff;

   tempBuff = NULL;
   result = S_OK;
   srcSize = 0;
   status = EXIT_SUCCESS_STATUS;

   if(NULL == destination ||
      NULL == destinationSize)
   {
      status = NULL_POINTER;
      goto CleanUp;
   }

   result = StringCchLengthA(
      source,
      STRSAFE_MAX_CCH,
      &srcSize
   );

   if(S_OK != result)
   {
      status = result;
      goto CleanUp;
   }

   tempBuff = (LPSTR)malloc((srcSize + 1) * sizeof(CHAR));
   if(NULL == tempBuff)
   {
      status = BAD_ALLOCATION;
      goto CleanUp;
   }

   result = StringCchCopyA(
      tempBuff,
      srcSize + 1,
      source
   );

   if(S_OK != result)
   {
      status = BAD_ALLOCATION;
      goto CleanUp;
   }

   *destination = tempBuff;
   *destinationSize = srcSize;

CleanUp:
   if(!SUCCESS(status))
   {
      free(tempBuff);
      tempBuff = NULL;
   }
   return status;
}

STATUS
CopyBufferWithoutAlloc(
   _In_     LPCSTR      source,
   _In_     size_t      maxCharacters,
   _Out_    LPSTR       destination,
   _Out_    size_t*     destinationSize
)
{
   STATUS status;
   size_t srcSize;
   HRESULT result;
   size_t i;

   i = 0;
   result = S_OK;
   srcSize = 0;
   status = EXIT_SUCCESS_STATUS;

   if (NULL == destination ||
       NULL == destinationSize)
   {
      status = NULL_POINTER;
      goto CleanUp;
   }

   result = StringCchLengthA(
      source,
      STRSAFE_MAX_CCH,
      &srcSize
   );
   srcSize++; // '\0'

   if (S_OK != result)
   {
      status = result;
      goto CleanUp;
   }

   if(srcSize > maxCharacters)
   {
      status = INVALID_BUFFER_SIZE;
      goto CleanUp;
   }
   
   for(i = 0; i < srcSize; ++i)
   {
      destination[i] = source[i];
   }

   *destinationSize = srcSize;

CleanUp:
   return status;
}

VOID
FillWithZeroes(
   _Out_    LPSTR      str,
   _In_     size_t     strSize
)
{
   size_t i;

   for(i = 0; i < strSize; ++i)
   {
      str[i] = '\0';
   }
}