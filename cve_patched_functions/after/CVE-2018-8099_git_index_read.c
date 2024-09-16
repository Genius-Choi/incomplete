int git_index_read(git_index *index, int force)
{
	int error = 0, updated;
	git_buf buffer = GIT_BUF_INIT;
	git_futils_filestamp stamp = index->stamp;

	if (!index->index_file_path)
		return create_index_error(-1,
			"failed to read index: The index is in-memory only");

	index->on_disk = git_path_exists(index->index_file_path);

	if (!index->on_disk) {
		if (force)
			return git_index_clear(index);
		return 0;
	}

	if ((updated = git_futils_filestamp_check(&stamp, index->index_file_path) < 0) ||
	    ((updated = compare_checksum(index)) < 0)) {
		giterr_set(
			GITERR_INDEX,
			"failed to read index: '%s' no longer exists",
			index->index_file_path);
		return updated;
	}
	if (!updated && !force)
		return 0;

	error = git_futils_readbuffer(&buffer, index->index_file_path);
	if (error < 0)
		return error;

	index->tree = NULL;
	git_pool_clear(&index->tree_pool);

	error = git_index_clear(index);

	if (!error)
		error = parse_index(index, buffer.ptr, buffer.size);

	if (!error)
		git_futils_filestamp_set(&index->stamp, &stamp);

	git_buf_free(&buffer);
	return error;
}
