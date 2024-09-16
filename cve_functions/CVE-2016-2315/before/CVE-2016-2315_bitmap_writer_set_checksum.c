void bitmap_writer_set_checksum(unsigned char *sha1)
{
	hashcpy(writer.pack_checksum, sha1);
}
