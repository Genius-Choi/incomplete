alloc_vprintf(char **out_buf,
              char *prealloc_buf,
              size_t prealloc_size,
              const char *fmt,
              va_list ap)
{
	va_list ap_copy;
	int len;

	/* Windows is not standard-compliant, and vsnprintf() returns -1 if
	 * buffer is too small. Also, older versions of msvcrt.dll do not have
	 * _vscprintf().  However, if size is 0, vsnprintf() behaves correctly.
	 * Therefore, we make two passes: on first pass, get required message
	 * length.
	 * On second pass, actually print the message. */
	va_copy(ap_copy, ap);
	len = vsnprintf_impl(NULL, 0, fmt, ap_copy);
	va_end(ap_copy);

	if (len < 0) {
		/* C runtime is not standard compliant, vsnprintf() returned -1.
		 * Switch to alternative code path that uses incremental
		 * allocations.
		*/
		va_copy(ap_copy, ap);
		len = alloc_vprintf2(out_buf, fmt, ap_copy);
		va_end(ap_copy);

	} else if ((size_t)(len) >= prealloc_size) {
		/* The pre-allocated buffer not large enough. */
		/* Allocate a new buffer. */
		*out_buf = (char *)mg_malloc((size_t)(len) + 1);
		if (!*out_buf) {
			/* Allocation failed. Return -1 as "out of memory" error. */
			return -1;
		}
		/* Buffer allocation successful. Store the string there. */
		va_copy(ap_copy, ap);
		IGNORE_UNUSED_RESULT(
		    vsnprintf_impl(*out_buf, (size_t)(len) + 1, fmt, ap_copy));
		va_end(ap_copy);

	} else {
		/* The pre-allocated buffer is large enough.
		 * Use it to store the string and return the address. */
		va_copy(ap_copy, ap);
		IGNORE_UNUSED_RESULT(
		    vsnprintf_impl(prealloc_buf, prealloc_size, fmt, ap_copy));
		va_end(ap_copy);
		*out_buf = prealloc_buf;
	}

	return len;
}
