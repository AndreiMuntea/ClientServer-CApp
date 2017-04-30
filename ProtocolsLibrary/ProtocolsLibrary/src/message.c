#include "../include/message.h"

STATUS
WriteMessage(
   _In_     HANDLE         pHandle,
   _Inout_  LPOVERLAPPED   lpOverlapped,
   _In_     DWORD          nMessageSize,
   _In_     LPVOID         lpMessageData
)
{

   STATUS status;
   BOOL   bSuccess;
   DWORD  nNumberOfBytesWritten;
   DWORD  waitResult;

   waitResult = 0;
   bSuccess = FALSE;
   status   = EXIT_SUCCESS_STATUS;
   nNumberOfBytesWritten = 0;

   if (NULL == lpOverlapped ||
       NULL == lpMessageData || 
       NULL == pHandle
      )
   {
      status = NULL_POINTER;
      goto CleanUp;
   }


   bSuccess = WriteFile(
      pHandle,
      lpMessageData,
      nMessageSize,
      &nNumberOfBytesWritten,
      lpOverlapped
   );

   // Success operation
   if(bSuccess)
   {
      goto CleanUp;
   }

   if(ERROR_IO_PENDING == GetLastError())
   {
      waitResult = WaitForSingleObject(
         lpOverlapped->hEvent, 
         DEFAULT_WAIT_TIME_IO_OPERATION
      );

      if(WAIT_OBJECT_0 != waitResult)
      {
         status = TIMEOUT_ERROR;
         CancelIoEx(pHandle, lpOverlapped);
         goto CleanUp;
      }

      bSuccess = GetOverlappedResult(
         pHandle,
         lpOverlapped,
         &nNumberOfBytesWritten,
         FALSE                      // don't wait
      );
   }

   // Another error occured
   if(!bSuccess)
   {
      status = GetLastError();
      goto CleanUp;
   }

   if(nNumberOfBytesWritten != nMessageSize)
   {
      status = PIPE_IO_ERROR;
      goto CleanUp;
   }

CleanUp:
   return status;
}


STATUS
ReadMessage(
   _In_     HANDLE         pHandle,
   _Inout_  LPOVERLAPPED   lpOverlapped,
   _Out_    LPDWORD        lpNumberOfBytesRead,
   _Out_    LPVOID         lpMessageData
)
{
   STATUS status;
   BOOL   bSuccess;
   DWORD  waitResult;

   waitResult = 0;
   bSuccess = FALSE;
   status = EXIT_SUCCESS_STATUS;
   
   if(NULL == lpNumberOfBytesRead ||
      NULL == lpOverlapped || 
      NULL == lpMessageData || 
      NULL == pHandle
      )
   {
      status = NULL_POINTER;
      goto CleanUp;
   }

   bSuccess = ReadFile(
      pHandle,
      lpMessageData,
      MAX_MESSAGE_SIZE,
      lpNumberOfBytesRead,
      lpOverlapped
   );

   // Success operation
   if (bSuccess)
   {
      goto CleanUp;
   }

   if (ERROR_IO_PENDING == GetLastError())
   {
      waitResult = WaitForSingleObject(
         lpOverlapped->hEvent,
         DEFAULT_WAIT_TIME_IO_OPERATION
      );

      if (WAIT_OBJECT_0 != waitResult)
      {
         status = TIMEOUT_ERROR;
         CancelIoEx(pHandle, lpOverlapped);
         goto CleanUp;
      }

      bSuccess = GetOverlappedResult(
         pHandle,
         lpOverlapped,
         lpNumberOfBytesRead,
         FALSE                      // don't wait
      );
   }

   // Another error occured
   if (!bSuccess)
   {
      status = GetLastError();
      goto CleanUp;
   }


CleanUp:
   return status;
}