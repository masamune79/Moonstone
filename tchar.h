#ifndef TCHAR_H
#define TCHAR_H
#endif

#include <wchar.h>
#include <string.h>

// CHAR or UNICODE
#define UNICODE

#ifdef CHAR
typedef char TCHAR;
#define _t(chr) chr
#define _tcslen strlen
#define _tprint printf
#define STR "%s"
#endif

#ifdef UNICODE
typedef wchar_t TCHAR;
#define _t(chr) L##chr
#define _tcslen wcslen
#define _tprint wprintf
#define STR "%ls"
#endif
