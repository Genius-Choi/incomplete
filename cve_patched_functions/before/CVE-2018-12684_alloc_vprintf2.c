alloc_vprintf2(char **buf, const char *fmt, va_list ap)
{
	va_list ap_copy;
	size_t size = MG_BUF_LEN / 4;
	int len = -1;

	*buf = NULL;
	while (len < 0) {
		if (*buf) {
			mg_free(*buf);
		}

		size *= 4;
		*buf = (char *)mg_malloc(size);
		if (!*buf) {
			break;
		}

		va_copy(ap_copy, ap);
		len = vsnprintf_impl(*buf, size - 1, fmt, ap_copy);
		va_end(ap_copy);
		(*buf)[size - 1] = 0;
	}

	return len;
}
