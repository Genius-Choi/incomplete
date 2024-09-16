static inline void dump_bitmap(struct sha1file *f, struct ewah_bitmap *bitmap)
{
	if (ewah_serialize_to(bitmap, sha1write_ewah_helper, f) < 0)
		die("Failed to write bitmap index");
}
