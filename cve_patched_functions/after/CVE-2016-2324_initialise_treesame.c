static struct treesame_state *initialise_treesame(struct rev_info *revs, struct commit *commit)
{
	unsigned n = commit_list_count(commit->parents);
	struct treesame_state *st = xcalloc(1, sizeof(*st) + n);
	st->nparents = n;
	add_decoration(&revs->treesame, &commit->object, st);
	return st;
}
