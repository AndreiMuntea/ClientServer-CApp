#include <strutils/strutils.h>

#include "../include/user.h"


STATUS
CreateUser(
   _Out_    PUSER*   user,
   _In_     LPCSTR   userName,
   _In_     LPCSTR   password
)
{
   STATUS status;
   PUSER tempUser;
   size_t size;

   size = 0;
   status = EXIT_SUCCESS_STATUS;
   tempUser = NULL;

   if(NULL == user || 
      NULL == userName || 
      NULL == password)
   {
      status = NULL_POINTER;
      goto CleanUp;
   }

   tempUser = (PUSER)malloc(sizeof(USER));
   if(NULL == tempUser)
   {
      status = BAD_ALLOCATION;
      goto CleanUp;
   }

   tempUser->userName = NULL;
   tempUser->password = NULL;

   status = CopyBufferWithAlloc(userName, &tempUser->userName, &size);
   if(!SUCCESS(status))
   {
      goto CleanUp;
   }

   status = CopyBufferWithAlloc(password, &tempUser->password, &size);
   if(!SUCCESS(status))
   {
      goto CleanUp;
   }

   *user = tempUser;


CleanUp:
   if(!SUCCESS(status))
   {
      DestroyUser(&tempUser);
   }
   return status;
}

VOID
DestroyUser(
   _Inout_  PUSER*   user
)
{
   if(NULL == user)
   {
      goto Out;
   }

   if(NULL == *user)
   {
      goto Out;
   }

   free((*user)->userName);
   free((*user)->password);
   free(*user);
   *user = NULL;

Out:;
}

BOOL
EqualsUsers(
   _In_     PUSER    firstUser,
   _In_     PUSER    secondUser
)
{
   return 
      (strcmp(firstUser->userName, secondUser->userName) == 0) &&
      (strcmp(firstUser->password, secondUser->password) == 0);
}