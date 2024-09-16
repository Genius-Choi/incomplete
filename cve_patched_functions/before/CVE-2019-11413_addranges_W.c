static void addranges_W(struct cstate *g)
{
	addrange(g, 0, '0'-1);
	addrange(g, '9'+1, 'A'-1);
	addrange(g, 'Z'+1, '_'-1);
	addrange(g, '_'+1, 'a'-1);
	addrange(g, 'z'+1, 0xFFFF);
}
