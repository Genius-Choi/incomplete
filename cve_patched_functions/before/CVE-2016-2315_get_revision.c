struct commit *get_revision(struct rev_info *revs)
{
	struct commit *c;
	struct commit_list *reversed;

	if (revs->reverse) {
		reversed = NULL;
		while ((c = get_revision_internal(revs)))
			commit_list_insert(c, &reversed);
		revs->commits = reversed;
		revs->reverse = 0;
		revs->reverse_output_stage = 1;
	}

	if (revs->reverse_output_stage) {
		c = pop_commit(&revs->commits);
		if (revs->track_linear)
			revs->linear = !!(c && c->object.flags & TRACK_LINEAR);
		return c;
	}

	c = get_revision_internal(revs);
	if (c && revs->graph)
		graph_update(revs->graph, c);
	if (!c) {
		free_saved_parents(revs);
		if (revs->previous_parents) {
			free_commit_list(revs->previous_parents);
			revs->previous_parents = NULL;
		}
	}
	return c;
}
