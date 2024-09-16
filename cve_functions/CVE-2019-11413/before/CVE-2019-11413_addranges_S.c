static void addranges_S(struct cstate *g)
{
	addrange(g, 0, 0x9-1);
	addrange(g, 0xD+1, 0x20-1);
	addrange(g, 0x20+1, 0xA0-1);
	addrange(g, 0xA0+1, 0x2028-1);
	addrange(g, 0x2029+1, 0xFEFF-1);
	addrange(g, 0xFEFF+1, 0xFFFF);
}
