static struct merge_simplify_state *locate_simplify_state(struct rev_info *revs, struct commit *commit)
{
	struct merge_simplify_state *st;

	st = lookup_decoration(&revs->merge_simplification, &commit->object);
	if (!st) {
		st = xcalloc(1, sizeof(*st));
		add_decoration(&revs->merge_simplification, &commit->object, st);
	}
	return st;
}
