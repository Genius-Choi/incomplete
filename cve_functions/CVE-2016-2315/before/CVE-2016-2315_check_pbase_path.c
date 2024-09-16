static int check_pbase_path(unsigned hash)
{
	int pos = (!done_pbase_paths) ? -1 : done_pbase_path_pos(hash);
	if (0 <= pos)
		return 1;
	pos = -pos - 1;
	ALLOC_GROW(done_pbase_paths,
		   done_pbase_paths_num + 1,
		   done_pbase_paths_alloc);
	done_pbase_paths_num++;
	if (pos < done_pbase_paths_num)
		memmove(done_pbase_paths + pos + 1,
			done_pbase_paths + pos,
			(done_pbase_paths_num - pos - 1) * sizeof(unsigned));
	done_pbase_paths[pos] = hash;
	return 0;
}
