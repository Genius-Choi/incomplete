static void addranges_w(struct cstate *g)
{
	addrange(g, '0', '9');
	addrange(g, 'A', 'Z');
	addrange(g, '_', '_');
	addrange(g, 'a', 'z');
}
