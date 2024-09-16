static size_t parse_mb_utf8(unsigned *wc, const char *ptr, const char *end)
{
	unsigned wchar;
	size_t consumed = utf8towc(&wchar, (const unsigned char *) ptr, end - ptr);

	if (!consumed || consumed == (size_t) -1) {
		return 0;
	}

	if (wc) {
		*wc = wchar;
	}
	return consumed;
}
