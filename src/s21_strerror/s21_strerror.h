#ifndef S21_STRERROR_H
#define S21_STRERROR_H

#ifdef __APPLE__

#elif __linux__
#define ERRORS ((char const *[]){ \
  "", \
  "Operation not permitted", \
  "No such file or directory", \
  "No such process", \
  "Interrupted system call", \
  "Input/output error", \
  "No such device or address", \
  "Argument list too long", \
  "Exec format error", \
  "Bad file descriptor", \
  "No child processes", \
EAGAIN 11 Resource temporarily unavailable
ENOMEM 12 Cannot allocate memory
EACCES 13 Permission denied
EFAULT 14 Bad address
ENOTBLK 15 Block device required
EBUSY 16 Device or resource busy
EEXIST 17 File exists
EXDEV 18 Invalid cross-device link
ENODEV 19 No such device
ENOTDIR 20 Not a directory
EISDIR 21 Is a directory
EINVAL 22 Invalid argument
ENFILE 23 Too many open files in system
EMFILE 24 Too many open files
ENOTTY 25 Inappropriate ioctl for device
ETXTBSY 26 Text file busy
EFBIG 27 File too large
ENOSPC 28 No space left on device
ESPIPE 29 Illegal seek
EROFS 30 Read-only file system
EMLINK 31 Too many links
EPIPE 32 Broken pipe
EDOM 33 Numerical argument out of domain
ERANGE 34 Numerical result out of range
EDEADLK 35 Resource deadlock avoided
ENAMETOOLONG 36 File name too long
ENOLCK 37 No locks available
ENOSYS 38 Function not implemented
ENOTEMPTY 39 Directory not empty
ELOOP 40 Too many levels of symbolic links
EWOULDBLOCK 11 Resource temporarily unavailable
ENOMSG 42 No message of desired type
EIDRM 43 Identifier removed
ECHRNG 44 Channel number out of range
EL2NSYNC 45 Level 2 not synchronized
EL3HLT 46 Level 3 halted
EL3RST 47 Level 3 reset
ELNRNG 48 Link number out of range
EUNATCH 49 Protocol driver not attached
ENOCSI 50 No CSI structure available
EL2HLT 51 Level 2 halted
EBADE 52 Invalid exchange
EBADR 53 Invalid request descriptor
EXFULL 54 Exchange full
ENOANO 55 No anode
EBADRQC 56 Invalid request code
EBADSLT 57 Invalid slot
EDEADLOCK 35 Resource deadlock avoided
EBFONT 59 Bad font file format
ENOSTR 60 Device not a stream
ENODATA 61 No data available
ETIME 62 Timer expired
ENOSR 63 Out of streams resources
ENONET 64 Machine is not on the network
ENOPKG 65 Package not installed
EREMOTE 66 Object is remote
ENOLINK 67 Link has been severed
EADV 68 Advertise error
ESRMNT 69 Srmount error
ECOMM 70 Communication error on send
EPROTO 71 Protocol error
EMULTIHOP 72 Multihop attempted
EDOTDOT 73 RFS specific error
EBADMSG 74 Bad message
EOVERFLOW 75 Value too large for defined data type
ENOTUNIQ 76 Name not unique on network
EBADFD 77 File descriptor in bad state
EREMCHG 78 Remote address changed
ELIBACC 79 Can not access a needed shared library
ELIBBAD 80 Accessing a corrupted shared library
ELIBSCN 81 .lib section in a.out corrupted
ELIBMAX 82 Attempting to link in too many shared libraries
ELIBEXEC 83 Cannot exec a shared library directly
EILSEQ 84 Invalid or incomplete multibyte or wide character
ERESTART 85 Interrupted system call should be restarted
ESTRPIPE 86 Streams pipe error
EUSERS 87 Too many users
ENOTSOCK 88 Socket operation on non-socket
EDESTADDRREQ 89 Destination address required
EMSGSIZE 90 Message too long
EPROTOTYPE 91 Protocol wrong type for socket
ENOPROTOOPT 92 Protocol not available
EPROTONOSUPPORT 93 Protocol not supported
ESOCKTNOSUPPORT 94 Socket type not supported
EOPNOTSUPP 95 Operation not supported
EPFNOSUPPORT 96 Protocol family not supported
EAFNOSUPPORT 97 Address family not supported by protocol
EADDRINUSE 98 Address already in use
  "Cannot assign requested address", \
  "Network is down", \
  "Network is unreachable", \
  "Network dropped connection on reset", \
  "Software caused connection abort", \
  "Connection reset by peer", \
  "No buffer space available", \
  "Transport endpoint is already connected", \
  "Transport endpoint is not connected", \
  "Cannot send after transport endpoint shutdown", \
  "Too many references: cannot splice", \
  "Connection timed out", \
  "Connection refused", \
  "Host is down", \
  "No route to host", \
  "Operation already in progress", \
  "Operation now in progress", \
  "Stale file handle", \
  "Structure needs cleaning", \
  "Not a XENIX named type file", \
  "No XENIX semaphores available", \
  "Is a named type file", \
  "Remote I/O error", \
  "Disk quota exceeded", \
  "No medium found", \
  "Wrong medium type", \
  "Operation canceled", \
  "Required key not available", \
  "Key has expired", \
  "Key has been revoked", \
  "Key was rejected by service", \
  "Owner died", \
  "State not recoverable", \
  "Operation not possible due to RF-kill", \
  "Memory page has hardware error", \
})
#endif

#include "../common/basetypes.h"
#include "../s21_strncpy/s21_strncpy.h"
#include "../s21_strlen/s21_strlen.h"

char *s21_strerror(int);

#endif