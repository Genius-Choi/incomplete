static void add_objects_in_unpacked_packs(struct rev_info *revs)
{
	struct packed_git *p;
	struct in_pack in_pack;
	uint32_t i;

	memset(&in_pack, 0, sizeof(in_pack));

	for (p = packed_git; p; p = p->next) {
		const unsigned char *sha1;
		struct object *o;

		if (!p->pack_local || p->pack_keep)
			continue;
		if (open_pack_index(p))
			die("cannot open pack index");

		ALLOC_GROW(in_pack.array,
			   in_pack.nr + p->num_objects,
			   in_pack.alloc);

		for (i = 0; i < p->num_objects; i++) {
			sha1 = nth_packed_object_sha1(p, i);
			o = lookup_unknown_object(sha1);
			if (!(o->flags & OBJECT_ADDED))
				mark_in_pack_object(o, p, &in_pack);
			o->flags |= OBJECT_ADDED;
		}
	}

	if (in_pack.nr) {
		qsort(in_pack.array, in_pack.nr, sizeof(in_pack.array[0]),
		      ofscmp);
		for (i = 0; i < in_pack.nr; i++) {
			struct object *o = in_pack.array[i].object;
			add_object_entry(o->oid.hash, o->type, "", 0);
		}
	}
	free(in_pack.array);
}
