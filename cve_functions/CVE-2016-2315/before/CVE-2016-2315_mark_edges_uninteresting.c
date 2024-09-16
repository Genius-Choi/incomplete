void mark_edges_uninteresting(struct rev_info *revs, show_edge_fn show_edge)
{
	struct commit_list *list;
	int i;

	for (list = revs->commits; list; list = list->next) {
		struct commit *commit = list->item;

		if (commit->object.flags & UNINTERESTING) {
			mark_tree_uninteresting(commit->tree);
			if (revs->edge_hint_aggressive && !(commit->object.flags & SHOWN)) {
				commit->object.flags |= SHOWN;
				show_edge(commit);
			}
			continue;
		}
		mark_edge_parents_uninteresting(commit, revs, show_edge);
	}
	if (revs->edge_hint_aggressive) {
		for (i = 0; i < revs->cmdline.nr; i++) {
			struct object *obj = revs->cmdline.rev[i].item;
			struct commit *commit = (struct commit *)obj;
			if (obj->type != OBJ_COMMIT || !(obj->flags & UNINTERESTING))
				continue;
			mark_tree_uninteresting(commit->tree);
			if (!(obj->flags & SHOWN)) {
				obj->flags |= SHOWN;
				show_edge(commit);
			}
		}
	}
}
