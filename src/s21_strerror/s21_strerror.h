#ifndef S21_STRERROR_H
#define S21_STRERROR_H

#ifdef __APPLE__
#define ERRORS ((char const *[]){ \  \\ Я не знаю, где взять коды ошибок на МАК
})
#define ERR_SIZE 133                 \\ Я не знаю количество ошибок на МАК
#elif __linux__
#define ERRORS ((char const *[]){ \
  "Unknown error nnn", \
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
  "Resource temporarily unavailable", \
  "Cannot allocate memory", \
  "Permission denied", \
  "Bad address", \
  "Block device required", \
  "Device or resource busy", \
  "File exists", \
  "Invalid cross-device link", \
  "No such device", \
  "Not a directory", \
  "Is a directory", \
  "Invalid argument", \
  "Too many open files in system", \
  "Too many open files", \
  "Inappropriate ioctl for device", \
  "Text file busy", \
  "File too large", \
  "No space left on device", \
  "Illegal seek", \
  "Read-only file system", \
  "Too many links", \
  "Broken pipe", \
  "Numerical argument out of domain", \
  "Numerical result out of range", \
  "Resource deadlock avoided", \
  "File name too long", \
  "No locks available", \
  "Function not implemented", \
  "Directory not empty", \
  "Too many levels of symbolic links", \
  "Resource temporarily unavailable", \
  "No message of desired type", \
  "Identifier removed", \
  "Channel number out of range", \
  "Level 2 not synchronized", \
  "Level 3 halted", \
  "Level 3 reset", \
  "Link number out of range", \
  "Protocol driver not attached", \
  "No CSI structure available", \
  "Level 2 halted", \
  "Invalid exchange", \
  "Invalid request descriptor", \
  "Exchange full", \
  "No anode", \
  "Invalid request code", \
  "Invalid slot", \
  "Resource deadlock avoided", \
  "Bad font file format", \
  "Device not a stream", \
  "No data available", \
  "Timer expired", \
  "Out of streams resources", \
  "Machine is not on the network", \
  "Package not installed", \
  "Object is remote", \
  "Link has been severed", \
  "Advertise error", \
  "Srmount error", \
  "Communication error on send", \
  "Protocol error", \
  "Multihop attempted", \
  "RFS specific error", \
  "Bad message", \
  "Value too large for defined data type", \
  "Name not unique on network", \
  "File descriptor in bad state", \
  "Remote address changed", \
  "Can not access a needed shared library", \
  "Accessing a corrupted shared library", \
  ".lib section in a.out corrupted", \
  "Attempting to link in too many shared libraries", \
  "Cannot exec a shared library directly", \
  "Invalid or incomplete multibyte or wide character", \
  "Interrupted system call should be restarted", \
  "Streams pipe error", \
  "Too many users", \
  "Socket operation on non-socket", \
  "Destination address required", \
  "Message too long", \
  "Protocol wrong type for socket", \
  "Protocol not available", \
  "Protocol not supported", \
  "Socket type not supported", \
  "Operation not supported", \
  "Protocol family not supported", \
  "Address family not supported by protocol", \
  "Address already in use", \
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
#define ERR_SIZE 133
#endif

#include "../common/basetypes.h"

char *s21_strerror(int);

#endif