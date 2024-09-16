static struct ewah_bitmap *read_bitmap_1(struct bitmap_index *index)
{
	struct ewah_bitmap *b = ewah_pool_new();

	int bitmap_size = ewah_read_mmap(b,
		index->map + index->map_pos,
		index->map_size - index->map_pos);

	if (bitmap_size < 0) {
		error("Failed to load bitmap index (corrupted?)");
		ewah_pool_free(b);
		return NULL;
	}

	index->map_pos += bitmap_size;
	return b;
}
