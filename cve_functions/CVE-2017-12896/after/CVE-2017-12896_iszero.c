iszero(const u_char *p, size_t l)
{
	while (l--) {
		if (*p++)
			return 0;
	}
	return 1;
}
