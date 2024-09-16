static inline void sign_extend(unsigned int count, unsigned char *dst)
{
#ifdef __LITTLE_ENDIAN__
	if ((count == 1) && dst[0] & 0x80) {
		dst[1] = 0xff;
		dst[2] = 0xff;
		dst[3] = 0xff;
	}
	if ((count == 2) && dst[1] & 0x80) {
		dst[2] = 0xff;
		dst[3] = 0xff;
	}
#else
	if ((count == 1) && dst[3] & 0x80) {
		dst[2] = 0xff;
		dst[1] = 0xff;
		dst[0] = 0xff;
	}
	if ((count == 2) && dst[2] & 0x80) {
		dst[1] = 0xff;
		dst[0] = 0xff;
	}
#endif
}
