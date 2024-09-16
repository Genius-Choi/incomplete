static int accept(struct cstate *g, int t)
{
	if (g->lookahead == t) {
		next(g);
		return 1;
	}
	return 0;
}
