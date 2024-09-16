static enum rewrite_result rewrite_one(struct rev_info *revs, struct commit **pp)
{
	struct commit_list *cache = NULL;

	for (;;) {
		struct commit *p = *pp;
		if (!revs->limited)
			if (add_parents_to_list(revs, p, &revs->commits, &cache) < 0)
				return rewrite_one_error;
		if (p->object.flags & UNINTERESTING)
			return rewrite_one_ok;
		if (!(p->object.flags & TREESAME))
			return rewrite_one_ok;
		if (!p->parents)
			return rewrite_one_noparents;
		if ((p = one_relevant_parent(revs, p->parents)) == NULL)
			return rewrite_one_ok;
		*pp = p;
	}
}
