static inline uint8_t read_u8(const unsigned char *buffer, size_t *pos)
{
	return buffer[(*pos)++];
}
