static size_t read_extension(git_index *index, const char *buffer, size_t buffer_size)
{
	struct index_extension dest;
	size_t total_size;

	/* buffer is not guaranteed to be aligned */
	memcpy(&dest, buffer, sizeof(struct index_extension));
	dest.extension_size = ntohl(dest.extension_size);

	total_size = dest.extension_size + sizeof(struct index_extension);

	if (dest.extension_size > total_size ||
		buffer_size < total_size ||
		buffer_size - total_size < INDEX_FOOTER_SIZE)
		return 0;

	/* optional extension */
	if (dest.signature[0] >= 'A' && dest.signature[0] <= 'Z') {
		/* tree cache */
		if (memcmp(dest.signature, INDEX_EXT_TREECACHE_SIG, 4) == 0) {
			if (git_tree_cache_read(&index->tree, buffer + 8, dest.extension_size, &index->tree_pool) < 0)
				return 0;
		} else if (memcmp(dest.signature, INDEX_EXT_UNMERGED_SIG, 4) == 0) {
			if (read_reuc(index, buffer + 8, dest.extension_size) < 0)
				return 0;
		} else if (memcmp(dest.signature, INDEX_EXT_CONFLICT_NAME_SIG, 4) == 0) {
			if (read_conflict_names(index, buffer + 8, dest.extension_size) < 0)
				return 0;
		}
		/* else, unsupported extension. We cannot parse this, but we can skip
		 * it by returning `total_size */
	} else {
		/* we cannot handle non-ignorable extensions;
		 * in fact they aren't even defined in the standard */
		return 0;
	}

	return total_size;
}
