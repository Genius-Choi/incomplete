static inline int __strnlen(const char *str, int len) {
	int l = 0;
	while (IS_PRINTABLE (*str) && --len) {
		if (((ut8)*str) == 0xff) {
			break;
		}
		str++;
		l++;
	}
	return l + 1;
}
