#ifndef PROTOCOLS_MESSAGE_H 
#define PROTOCOLS_MESSAGE_H

#include <Windows.h>

#include "definitions.h"

STATUS
WriteMessage(
   _In_     HANDLE         pHandle,
   _Inout_  LPOVERLAPPED   lpOverlapped,
   _In_     DWORD          nMessageSize,
   _In_     LPVOID         lpMessageData
);

STATUS
ReadMessage(
   _In_     HANDLE         pHandle,
   _Inout_  LPOVERLAPPED   lpOverlapped,
   _Out_    LPDWORD        lpNumberOfBytesRead,
   _Out_    LPVOID         lpMessageData
);

#endif //PROTOCOLS_MESSAGE_H