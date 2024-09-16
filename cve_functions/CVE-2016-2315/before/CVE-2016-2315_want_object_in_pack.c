static int want_object_in_pack(const unsigned char *sha1,
			       int exclude,
			       struct packed_git **found_pack,
			       off_t *found_offset)
{
	struct packed_git *p;

	if (!exclude && local && has_loose_object_nonlocal(sha1))
		return 0;

	*found_pack = NULL;
	*found_offset = 0;

	for (p = packed_git; p; p = p->next) {
		off_t offset = find_pack_entry_one(sha1, p);
		if (offset) {
			if (!*found_pack) {
				if (!is_pack_valid(p))
					continue;
				*found_offset = offset;
				*found_pack = p;
			}
			if (exclude)
				return 1;
			if (incremental)
				return 0;
			if (local && !p->pack_local)
				return 0;
			if (ignore_packed_keep && p->pack_local && p->pack_keep)
				return 0;
		}
	}

	return 1;
}
