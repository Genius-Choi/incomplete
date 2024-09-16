static int append_str(char **res, size_t *sz, const char *a, const char *b)
{
	char *str = *res;
	size_t asz = a ? strlen(a) : 0;
	size_t bsz = b ? strlen(b) : 0;
	size_t len = *sz + asz + bsz;

	if (!len)
		return -1;

	*res = str = xrealloc(str, len + 1);
	str += *sz;

	if (a) {
		memcpy(str, a, asz);
		str += asz;
	}
	if (b) {
		memcpy(str, b, bsz);
		str += bsz;
	}
	*str = '\0';
	*sz = len;
	return 0;
}
