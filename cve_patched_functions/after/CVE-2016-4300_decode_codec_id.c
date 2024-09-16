decode_codec_id(const unsigned char *codecId, size_t id_size)
{
	unsigned i;
	unsigned long id = 0;

	for (i = 0; i < id_size; i++) {
		id <<= 8;
		id += codecId[i];
	}
	return (id);
}
