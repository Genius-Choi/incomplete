static void print_ls(int mode, const unsigned char *sha1, const char *path)
{
	static struct strbuf line = STRBUF_INIT;

	/* See show_tree(). */
	const char *type =
		S_ISGITLINK(mode) ? commit_type :
		S_ISDIR(mode) ? tree_type :
		blob_type;

	if (!mode) {
		/* missing SP path LF */
		strbuf_reset(&line);
		strbuf_addstr(&line, "missing ");
		quote_c_style(path, &line, NULL, 0);
		strbuf_addch(&line, '\n');
	} else {
		/* mode SP type SP object_name TAB path LF */
		strbuf_reset(&line);
		strbuf_addf(&line, "%06o %s %s\t",
				mode & ~NO_DELTA, type, sha1_to_hex(sha1));
		quote_c_style(path, &line, NULL, 0);
		strbuf_addch(&line, '\n');
	}
	cat_blob_write(line.buf, line.len);
}
