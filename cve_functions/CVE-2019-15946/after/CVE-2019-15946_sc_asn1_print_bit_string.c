static void sc_asn1_print_bit_string(const u8 * buf, size_t buflen, size_t depth)
{
#ifndef _WIN32
	long long a = 0;
#else
	__int64 a = 0;
#endif
	int r, i;

	if (buflen > sizeof(a) + 1) {
		print_hex(buf, buflen, depth);
	} else {
		r = sc_asn1_decode_bit_string(buf, buflen, &a, sizeof(a));
		if (r < 0) {
			printf("decode error");
			return;
		}
		for (i = r - 1; i >= 0; i--) {
			printf("%c", ((a >> i) & 1) ? '1' : '0');
		}
	}
}
