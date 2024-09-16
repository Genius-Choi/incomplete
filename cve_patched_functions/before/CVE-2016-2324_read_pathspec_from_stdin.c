static void read_pathspec_from_stdin(struct rev_info *revs, struct strbuf *sb,
				     struct cmdline_pathspec *prune)
{
	while (strbuf_getline(sb, stdin) != EOF) {
		ALLOC_GROW(prune->path, prune->nr + 1, prune->alloc);
		prune->path[prune->nr++] = xstrdup(sb->buf);
	}
}
