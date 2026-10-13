#ifndef __strdup_compat_h
#define __strdup_compat_h

/**
 * @file
 * @brief Do not use, json-c internal, may be changed or removed at any time.
 */

#ifdef SGX_ENCLAVE
#include <stdlib.h>
#include <string.h>

/*
 * SGX Enclave modification:
 * Intel SGX trusted libc does not provide strdup() on all SDK versions.
 * Keep the replacement private to json-c and allocate from enclave heap.
 */
static char *json_c_sgx_strdup(const char *s)
{
    size_t len;
    char *copy;

    if (s == NULL)
        return NULL;

    len = strlen(s) + 1;
    copy = (char *)malloc(len);
    if (copy == NULL)
        return NULL;

    memcpy(copy, s, len);
    return copy;
}
#define strdup json_c_sgx_strdup

#elif !defined(HAVE_STRDUP) && defined(_MSC_VER)
/* MSC has the version as _strdup */
#define strdup _strdup
#elif !defined(HAVE_STRDUP)
#error You do not have strdup on your system.
#endif /* SGX_ENCLAVE / HAVE_STRDUP */

#endif
