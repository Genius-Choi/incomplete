static int open_pack_bitmap_1(struct packed_git *packfile)
{
	int fd;
	struct stat st;
	char *idx_name;

	if (open_pack_index(packfile))
		return -1;

	idx_name = pack_bitmap_filename(packfile);
	fd = git_open_noatime(idx_name);
	free(idx_name);

	if (fd < 0)
		return -1;

	if (fstat(fd, &st)) {
		close(fd);
		return -1;
	}

	if (bitmap_git.pack) {
		warning("ignoring extra bitmap file: %s", packfile->pack_name);
		close(fd);
		return -1;
	}

	bitmap_git.pack = packfile;
	bitmap_git.map_size = xsize_t(st.st_size);
	bitmap_git.map = xmmap(NULL, bitmap_git.map_size, PROT_READ, MAP_PRIVATE, fd, 0);
	bitmap_git.map_pos = 0;
	close(fd);

	if (load_bitmap_header(&bitmap_git) < 0) {
		munmap(bitmap_git.map, bitmap_git.map_size);
		bitmap_git.map = NULL;
		bitmap_git.map_size = 0;
		return -1;
	}

	return 0;
}
