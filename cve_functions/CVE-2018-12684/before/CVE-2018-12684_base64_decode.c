base64_decode(const unsigned char *src, int src_len, char *dst, size_t *dst_len)
{
	int i;
	unsigned char a, b, c, d;

	*dst_len = 0;

	for (i = 0; i < src_len; i += 4) {
		a = b64reverse(src[i]);
		if (a >= 254) {
			return i;
		}

		b = b64reverse(((i + 1) >= src_len) ? 0 : src[i + 1]);
		if (b >= 254) {
			return i + 1;
		}

		c = b64reverse(((i + 2) >= src_len) ? 0 : src[i + 2]);
		if (c == 254) {
			return i + 2;
		}

		d = b64reverse(((i + 3) >= src_len) ? 0 : src[i + 3]);
		if (d == 254) {
			return i + 3;
		}

		dst[(*dst_len)++] = (a << 2) + (b >> 4);
		if (c != 255) {
			dst[(*dst_len)++] = (b << 4) + (c >> 2);
			if (d != 255) {
				dst[(*dst_len)++] = (c << 6) + d;
			}
		}
	}
	return -1;
}
