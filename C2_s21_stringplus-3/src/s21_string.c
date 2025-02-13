#include "s21_string.h"

#if defined(__linux__)
#define MAX_ERRLIST 134
#define MIN_ERRLIST -1
#define ERROR "Unknown error"
static const char *s21_errorArray[] = {
    "Success",
    "Operation not permitted",
    "No such file or directory",
    "No such process",
    "Interrupted system call",
    "Input/output error",
    "No such device or address",
    "Argument list too long",
    "Exec format error",
    "Bad file descriptor",
    "No child processes",
    "Resource temporarily unavailable",
    "Cannot allocate memory",
    "Permission denied",
    "Bad address",
    "Block device required",
    "Device or resource busy",
    "File exists",
    "Invalid cross-device link",
    "No such device",
    "Not a directory",
    "Is a directory",
    "Invalid argument",
    "Too many open files in system",
    "Too many open files",
    "Inappropriate ioctl for device",
    "Text file busy",
    "File too large",
    "No space left on device",
    "Illegal seek",
    "Read-only file system",
    "Too many links",
    "Broken pipe",
    "Numerical argument out of domain",
    "Numerical result out of range",
    "Resource deadlock avoided",
    "File name too long",
    "No locks available",
    "Function not implemented",
    "Directory not empty",
    "Too many levels of symbolic links",
    "Unknown error 41",
    "No message of desired type",
    "Identifier removed",
    "Channel number out of range",
    "Level 2 not synchronized",
    "Level 3 halted",
    "Level 3 reset",
    "Link number out of range",
    "Protocol driver not attached",
    "No CSI structure available",
    "Level 2 halted",
    "Invalid exchange",
    "Invalid request descriptor",
    "Exchange full",
    "No anode",
    "Invalid request code",
    "Invalid slot",
    "Unknown error 58",
    "Bad font file format",
    "Device not a stream",
    "No data available",
    "Timer expired",
    "Out of streams resources",
    "Machine is not on the network",
    "Package not installed",
    "Object is remote",
    "Link has been severed",
    "Advertise error",
    "Srmount error",
    "Communication error on send",
    "Protocol error",
    "Multihop attempted",
    "RFS specific error",
    "Bad message",
    "Value too large for defined data type",
    "Name not unique on network",
    "File descriptor in bad state",
    "Remote address changed",
    "Can not access a needed shared library",
    "Accessing a corrupted shared library",
    ".lib section in a.out corrupted",
    "Attempting to link in too many shared libraries",
    "Cannot exec a shared library directly",
    "Invalid or incomplete multibyte or wide character",
    "Interrupted system call should be restarted",
    "Streams pipe error",
    "Too many users",
    "Socket operation on non-socket",
    "Destination address required",
    "Message too long",
    "Protocol wrong type for socket",
    "Protocol not available",
    "Protocol not supported",
    "Socket type not supported",
    "Operation not supported",
    "Protocol family not supported",
    "Address family not supported by protocol",
    "Address already in use",
    "Cannot assign requested address",
    "Network is down",
    "Network is unreachable",
    "Network dropped connection on reset",
    "Software caused connection abort",
    "Connection reset by peer",
    "No buffer space available",
    "Transport endpoint is already connected",
    "Transport endpoint is not connected",
    "Cannot send after transport endpoint shutdown",
    "Too many references: cannot splice",
    "Connection timed out",
    "Connection refused",
    "Host is down",
    "No route to host",
    "Operation already in progress",
    "Operation now in progress",
    "Stale file handle",
    "Structure needs cleaning",
    "Not a XENIX named type file",
    "No XENIX semaphores available",
    "Is a named type file",
    "Remote I/O error",
    "Disk quota exceeded",
    "No medium found",
    "Wrong medium type",
    "Operation canceled",
    "Required key not available",
    "Key has expired",
    "Key has been revoked",
    "Key was rejected by service",
    "Owner died",
    "State not recoverable",
    "Operation not possible due to RF-kill",
    "Memory page has hardware error"};

#elif defined(__APPLE__)
#define MAX_ERRLIST 107
#define MIN_ERRLIST -1
#define ERROR "Unknown error: "

static const char *s21_errorArray[] = {
    "Undefined error: 0",
    "Operation not permitted",
    "No such file or directory",
    "No such process",
    "Interrupted system call",
    "Input/output error",
    "Device not configured",
    "Argument list too long",
    "Exec format error",
    "Bad file descriptor",
    "No child processes",
    "Resource deadlock avoided",
    "Cannot allocate memory",
    "Permission denied",
    "Bad address",
    "Block device required",
    "Resource busy",
    "File exists",
    "Cross-device link",
    "Operation not supported by device",
    "Not a directory",
    "Is a directory",
    "Invalid argument",
    "Too many open files in system",
    "Too many open files",
    "Inappropriate ioctl for device",
    "Text file busy",
    "File too large",
    "No space left on device",
    "Illegal seek",
    "Read-only file system",
    "Too many links",
    "Broken pipe",
    "Numerical argument out of domain",
    "Result too large",
    "Resource temporarily unavailable",
    "Operation now in progress",
    "Operation already in progress",
    "Socket operation on non-socket",
    "Destination address required",
    "Message too long",
    "Protocol wrong type for socket",
    "Protocol not available",
    "Protocol not supported",
    "Socket type not supported",
    "Operation not supported",
    "Protocol family not supported",
    "Address family not supported by protocol family",
    "Address already in use",
    "Can't assign requested address",
    "Network is down",
    "Network is unreachable",
    "Network dropped connection on reset",
    "Software caused connection abort",
    "Connection reset by peer",
    "No buffer space available",
    "Socket is already connected",
    "Socket is not connected",
    "Can't send after socket shutdown",
    "Too many references: can't splice",
    "Operation timed out",
    "Connection refused",
    "Too many levels of symbolic links",
    "File name too long",
    "Host is down",
    "No route to host",
    "Directory not empty",
    "Too many processes",
    "Too many users",
    "Disc quota exceeded",
    "Stale NFS file handle",
    "Too many levels of remote in path",
    "RPC struct is bad",
    "RPC version wrong",
    "RPC prog. not avail",
    "Program version wrong",
    "Bad procedure for program",
    "No locks available",
    "Function not implemented",
    "Inappropriate file type or format",
    "Authentication error",
    "Need authenticator",
    "Device power is off",
    "Device error",
    "Value too large to be stored in data type",
    "Bad executable (or shared library)",
    "Bad CPU type in executable",
    "Shared library version mismatch",
    "Malformed Mach-o file",
    "Operation canceled",
    "Identifier removed",
    "No message of desired type",
    "Illegal byte sequence",
    "Attribute not found",
    "Bad message",
    "EMULTIHOP (Reserved)",
    "No message available on STREAM",
    "ENOLINK (Reserved)",
    "No STREAM resources",
    "Not a STREAM",
    "Protocol error",
    "STREAM ioctl timeout",
    "Operation not supported on socket",
    "Policy not found",
    "State not recoverable",
    "Previous owner died",
    "Interface output queue is full"};
#endif

void *s21_memchr(const void *str, int c, s21_size_t n) {
  const unsigned char *res = (const unsigned char *)str;
  unsigned char uc = (unsigned char)c;
  for (s21_size_t i = 0; i < n; i++) {
    if (res[i] == uc) {
      return (void *)(res + i);
    }
  }
  return s21_NULL;
}

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  const unsigned char *res1 = str1;
  const unsigned char *res2 = str2;
  for (s21_size_t i = 0; i < n; i++) {
    if (res1[i] != res2[i]) {
      return res1[i] - res2[i];
    }
  }
  return 0;
}

void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  char *resultDest = (char *)dest;
  const char *resultStr = (const char *)src;
  for (s21_size_t i = 0; i < n; i++) {
    resultDest[i] = resultStr[i];
  }
  return dest;
}

void *s21_memset(void *str, int c, s21_size_t n) {
  unsigned char *res = (unsigned char *)str;

  for (s21_size_t i = 0; i < n; i++) {
    res[i] = (unsigned char)c;
  }
  return str;
}

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  s21_size_t dest_length = s21_strlen(dest);
  s21_size_t i;
  for (i = 0; i < n && src[i] != '\0'; i++) {
    dest[dest_length + i] = src[i];
  }
  dest[dest_length + i] = '\0';
  return dest;
}

char *s21_strchr(const char *str, int c) {
  if (c == '\0') {
    return (char *)(str + s21_strlen(str));
  }
  while (*str != '\0') {
    if (*str == c) {
      return (char *)str;
    }
    str++;
  }
  return s21_NULL;
}

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  for (s21_size_t i = 0; i < n; i++) {
    if (str1[i] == '\0' || str2[i] == '\0') {
      return (unsigned char)str1[i] - (unsigned char)str2[i];
    }
    if (str1[i] < str2[i]) {
      return -1;
    }
    if (str1[i] > str2[i]) {
      return 1;
    }
  }
  return 0;
}

void s21_strcpy(char *dest, const char *src) {
  while (*src != '\0') {
    *dest = *src;
    dest++;
    src++;
  }
  *dest = '\0';
}

char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  s21_size_t i;
  for (i = 0; i < n && src[i] != '\0'; i++) {
    dest[i] = src[i];
  }
  dest[i] = '\0';
  return dest;
}

s21_size_t s21_strcspn(const char *str1, const char *str2) {
  const char *first;
  const char *second;
  for (first = str1; *first != '\0'; ++first) {
    for (second = str2; *second != '\0'; ++second) {
      if (*first == *second) {
        return first - str1;
      }
    }
  }
  return first - str1;
}

s21_size_t s21_strspn(const char *str1, const char *str2) {
  const char *first;
  const char *second;
  s21_size_t count = 0;

  for (first = str1; *first != '\0'; ++first) {
    for (second = str2; *second != '\0'; ++second) {
      if (*first == *second) {
        break;
      }
    }
    if (*second == '\0') {
      return count;
    }
    ++count;
  }
  return count;
}

char *s21_strerror(int errnum) {
  static char result[200];
  if (errnum <= MIN_ERRLIST || errnum >= MAX_ERRLIST ||
      s21_errorArray[errnum] == NULL) {
    s21_sprintf(result, "Unknown error %d", errnum);
  } else {
    s21_sprintf(result, "%s", s21_errorArray[errnum]);
  }
  return result;
}

s21_size_t s21_strlen(const char *c) {
  s21_size_t length = 0;
  while (c[length] != '\0') {
    length++;
  }
  return length;
}

char *s21_strpbrk(const char *str1, const char *str2) {
  while (*str1) {
    const char *ptr = str2;
    while (*ptr) {
      if (*ptr == *str1) {
        return (char *)str1;
      }
      ptr++;
    }
    str1++;
  }
  return s21_NULL;
}

char *s21_strrchr(const char *str, int c) {
  if (str == s21_NULL) {
    return s21_NULL;
  }
  int length = s21_strlen(str);
  for (int i = length - 1; i >= 0; i--) {
    if (str[i] == c) {
      return (char *)&str[i];
    }
  }
  if (c == '\0') {
    return (char *)(str + length);
  }
  return s21_NULL;
}

char *s21_strstr(const char *haystack, const char *needle) {
  int i = 0;
  while (haystack[i] != '\0') {
    int j = 0;
    while (needle[j] != '\0' && haystack[i + j] == needle[j]) {
      j++;
    }
    if (needle[j] == '\0') {
      return (char *)&haystack[i];
    }
    i++;
  }
  return s21_NULL;
}

char *s21_strtok(char *str, const char *delim) {
  static char *last = s21_NULL;
  char *start = s21_NULL;
  char *end = s21_NULL;
  if (str != s21_NULL) {
    start = str;
  } else {
    if (last == s21_NULL) {
      return s21_NULL;
    }
    start = last;
  }
  start += s21_strspn(start, delim);
  if (*start == '\0') {
    return s21_NULL;
  }
  end = start + s21_strcspn(start, delim);
  last = end;
  if (*last != '\0') {
    *last = '\0';
    last++;
  }
  return start;
}

void *s21_to_upper(const char *str) {
  char *res = s21_NULL;
  if (str != s21_NULL) {
    s21_size_t length = s21_strlen(str);
    res = (char *)malloc(sizeof(char) * (length + 1));
    if (res) {
      for (s21_size_t i = 0; i <= length; i++) {
        if (str[i] >= 97 && str[i] <= 122) {
          res[i] = str[i] - 32;
        } else {
          res[i] = str[i];
        }
      }
      res[length] = '\0';
    }
  }
  return res;
}

void *s21_to_lower(const char *str) {
  char *res = s21_NULL;
  if (str != s21_NULL) {
    s21_size_t length = s21_strlen(str);
    res = (char *)malloc(sizeof(char) * (length + 1));
    if (res) {
      for (s21_size_t i = 0; i < length; i++) {
        if (str[i] >= 'A' && str[i] <= 'Z') {
          res[i] = str[i] + 32;
        } else {
          res[i] = str[i];
        }
      }
      res[length] = '\0';
    }
  }
  return res;
}

void *s21_insert(const char *src, const char *str, size_t start_index) {
  char *res = s21_NULL;
  s21_size_t src_length = 0, str_length = 0, res_length = 0;
  if (src == s21_NULL || str == s21_NULL) {
    return s21_NULL;
  }
  src_length = s21_strlen(src);
  str_length = s21_strlen(str);
  res_length = src_length + str_length;
  if (start_index > src_length) {
    return s21_NULL;
  }
  res = (char *)calloc(res_length + 1, sizeof(char));
  if (res == s21_NULL) {
    return s21_NULL;
  }
  for (s21_size_t i = 0; i < start_index; i++) {
    res[i] = src[i];
  }
  for (s21_size_t i = 0; i < str_length; i++) {
    res[start_index + i] = str[i];
  }
  for (s21_size_t i = start_index; i < src_length; i++) {
    res[i + str_length] = src[i];
  }
  res[res_length] = '\0';
  return res;
}

void *s21_trim(const char *src, const char *trim_chars) {
  char *res = s21_NULL;
  if (src) {
    if (trim_chars && trim_chars[0]) {
      size_t length = s21_strlen(src);
      size_t start = 0, end = length;
      while (start < length && s21_strchr(trim_chars, src[start])) {
        start++;
      }
      if (start != length) {
        while (end > start && s21_strchr(trim_chars, src[end - 1])) {
          end--;
        }
        res = (char *)calloc(end - start + 1, sizeof(char));
        s21_memcpy(res, src + start, end - start);
        res[end - start] = '\0';
      } else {
        res = (char *)calloc(1, sizeof(char));
        res[0] = '\0';
      }
    } else {
      res = s21_trim(src, "\t\n ");
    }
  }
  return res;
}

void *s21_memmove(void *dest, const void *src, size_t n) {
  unsigned char *d = dest;
  const unsigned char *s = src;

  if (d > s && d < s + n) {
    for (size_t i = n; i > 0; --i) {
      d[i - 1] = s[i - 1];
    }
  } else {
    for (size_t i = 0; i < n; ++i) {
      d[i] = s[i];
    }
  }
  return dest;
}

int s21_strcmp(const char *s1, const char *s2) {
  while (*s1 && *s2 && *s1 == *s2) {
    s1++;
    s2++;
  }
  return *(const unsigned char *)s1 - *(const unsigned char *)s2;
}
