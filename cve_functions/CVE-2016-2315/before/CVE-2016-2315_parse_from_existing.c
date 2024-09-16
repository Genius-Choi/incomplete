static void parse_from_existing(struct branch *b)
{
	if (is_null_sha1(b->sha1)) {
		hashclr(b->branch_tree.versions[0].sha1);
		hashclr(b->branch_tree.versions[1].sha1);
	} else {
		unsigned long size;
		char *buf;

		buf = read_object_with_reference(b->sha1,
			commit_type, &size, b->sha1);
		parse_from_commit(b, buf, size);
		free(buf);
	}
}
