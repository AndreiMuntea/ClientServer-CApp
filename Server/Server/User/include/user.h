#ifndef SERVER_USER_H 
#define SERVER_USER_H

#include <Windows.h>
#include <definitions.h>

typedef struct _USER
{
   LPSTR userName;
   LPSTR password;
}USER, *PUSER;


STATUS
CreateUser(
   _Out_    PUSER*   user,
   _In_     LPCSTR   userName,
   _In_     LPCSTR   password
);

VOID
DestroyUser(
   _Inout_  PUSER*   user
);

BOOL
EqualsUsers(
   _In_     PUSER    firstUser,
   _In_     PUSER    secondUser
);

#endif //SERVER_USER_H