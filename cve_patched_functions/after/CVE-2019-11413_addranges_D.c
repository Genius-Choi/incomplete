static void addranges_D(struct cstate *g)
{
	addrange(g, 0, '0'-1);
	addrange(g, '9'+1, 0xFFFF);
}
