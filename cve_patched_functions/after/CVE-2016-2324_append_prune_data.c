static void append_prune_data(struct cmdline_pathspec *prune, const char **av)
{
	while (*av) {
		ALLOC_GROW(prune->path, prune->nr + 1, prune->alloc);
		prune->path[prune->nr++] = *(av++);
	}
}
