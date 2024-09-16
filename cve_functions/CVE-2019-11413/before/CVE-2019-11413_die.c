static void die(struct cstate *g, const char *message)
{
	g->error = message;
	longjmp(g->kaboom, 1);
}
