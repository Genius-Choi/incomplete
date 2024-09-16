static int has_sha1_pack_kept_or_nonlocal(const unsigned char *sha1)
{
	static struct packed_git *last_found = (void *)1;
	struct packed_git *p;

	p = (last_found != (void *)1) ? last_found : packed_git;

	while (p) {
		if ((!p->pack_local || p->pack_keep) &&
			find_pack_entry_one(sha1, p)) {
			last_found = p;
			return 1;
		}
		if (p == last_found)
			p = packed_git;
		else
			p = p->next;
		if (p == last_found)
			p = p->next;
	}
	return 0;
}
