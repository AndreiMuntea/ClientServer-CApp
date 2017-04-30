#ifndef PROTOCOLS_STRUTILS_H
#define PROTOCOLS_STRUTILS_H

#include <Windows.h>

#include "../definitions.h"

STATUS
CreatePipeName(
   _Out_    LPSTR*      destination,
   _In_     LPCSTR      source
);

STATUS
CopyBufferWithAlloc(
   _In_     LPCSTR      source,
   _Out_    LPSTR*      destination,
   _Out_    size_t*     destinationSize
);

STATUS
CopyBufferWithoutAlloc(
   _In_     LPCSTR      source,
   _In_     size_t      maxCharacters,
   _Out_    LPSTR       destination,
   _Out_    size_t*     destinationSize
);

VOID
FillWithZeroes(
   _Out_    LPSTR      str,
   _In_     size_t     strSize
);

#endif //PROTOCOLS_STRUTILS_H