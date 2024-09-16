static int open_pack_bitmap(void)
{
	struct packed_git *p;
	int ret = -1;

	assert(!bitmap_git.map && !bitmap_git.loaded);

	prepare_packed_git();
	for (p = packed_git; p; p = p->next) {
		if (open_pack_bitmap_1(p) == 0)
			ret = 0;
	}

	return ret;
}
