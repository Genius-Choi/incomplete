static int bitmap_position(const unsigned char *sha1)
{
	int pos = bitmap_position_packfile(sha1);
	return (pos >= 0) ? pos : bitmap_position_extended(sha1);
}
