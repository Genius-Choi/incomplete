should_include(struct commit *commit, void *_data)
{
	struct bitmap *base = _data;

	if (!add_to_include_set(base, commit)) {
		struct commit_list *parent = commit->parents;

		mark_as_seen((struct object *)commit);

		while (parent) {
			parent->item->object.flags |= SEEN;
			mark_as_seen((struct object *)parent->item);
			parent = parent->next;
		}

		return 0;
	}

	return 1;
}
