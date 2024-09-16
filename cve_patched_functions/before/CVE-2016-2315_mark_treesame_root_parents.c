static int mark_treesame_root_parents(struct rev_info *revs, struct commit *commit)
{
	struct commit_list *p;
	int marked = 0;

	for (p = commit->parents; p; p = p->next) {
		struct commit *parent = p->item;
		if (!parent->parents && (parent->object.flags & TREESAME)) {
			parent->object.flags |= TMP_MARK;
			marked++;
		}
	}

	return marked;
}
