static void loosen_unused_packed_objects(struct rev_info *revs)
{
	struct packed_git *p;
	uint32_t i;
	const unsigned char *sha1;

	for (p = packed_git; p; p = p->next) {
		if (!p->pack_local || p->pack_keep)
			continue;

		if (open_pack_index(p))
			die("cannot open pack index");

		for (i = 0; i < p->num_objects; i++) {
			sha1 = nth_packed_object_sha1(p, i);
			if (!packlist_find(&to_pack, sha1, NULL) &&
			    !has_sha1_pack_kept_or_nonlocal(sha1) &&
			    !loosened_object_can_be_discarded(sha1, p->mtime))
				if (force_object_loose(sha1, p->mtime))
					die("unable to force loose object");
		}
	}
}
