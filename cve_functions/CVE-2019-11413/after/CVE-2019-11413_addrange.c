static void addrange(struct cstate *g, Rune a, Rune b)
{
	if (a > b)
		die(g, "invalid character class range");
	if (g->yycc->end + 2 == g->yycc->spans + nelem(g->yycc->spans))
		die(g, "too many character class ranges");
	*g->yycc->end++ = a;
	*g->yycc->end++ = b;
}
