struct commit_list *get_saved_parents(struct rev_info *revs, const struct commit *commit)
{
	struct commit_list *parents;

	if (!revs->saved_parents_slab)
		return commit->parents;

	parents = *saved_parents_at(revs->saved_parents_slab, commit);
	if (parents == EMPTY_PARENT_LIST)
		return NULL;
	return parents;
}
