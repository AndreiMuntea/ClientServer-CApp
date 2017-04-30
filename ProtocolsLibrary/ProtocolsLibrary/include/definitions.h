#ifndef PROTOCOLS_DEFINITIONS_H
#define PROTOCOLS_DEFINITIONS_H


typedef long STATUS;

#define MAX_PASSWORD_LENGTH               64
#define MAX_USERNAME_LENGTH               64
#define MAX_KEY_LENGTH                    64
#define MAX_ENCRYPT_BUFFER_LENGTH         512
#define MAX_PIPE_NAME_LENGTH              256
#define MAX_MESSAGE_SIZE                  1024

#define DEFAULT_WAIT_TIME_IO_OPERATION    8096

#define PIPE_PREFIX                       "\\\\.\\pipe\\"
#define PIPE_DEFAULT_NAME                 "hardcoded"

#define ERROR_BITS                        0xFFFF0000
#define WARNING_BITS                      0x0000FFFF
#define INTERNAL_ERROR_BITS               0xF0000000

#define EXIT_SUCCESS_STATUS               0x00000000
#define SUCCESS(status)                   (!((status) & ERROR_BITS))
#define INTERNAL_ERROR(status)            ((status) & INTERNAL_ERROR_BITS)

#define BAD_ALLOCATION                    0x10000000
#define NULL_POINTER                      0x20000000
#define PIPE_IO_ERROR                     0x30000000
#define TIMEOUT_ERROR                     0x40000000
#define INVALID_BUFFER_SIZE               0x50000000

#define MESSAGE_TOO_LARGE                 0x01000000
#define INVALID_ARGUMENT                  0x02000000
#define INVALID_PIPE_NAME                 0x03000000
#define IDEX_OUT_OF_BOUNDS                0x04000000
#define UNKNOWN_REQUEST                   0x05000000

#endif //PROTOCOLS_DEFINITIONS_H