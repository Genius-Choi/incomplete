static void tx3g_dump_rgb16(FILE * trace, char *name, char col[6])
{
	fprintf(trace, "%s=\"%x %x %x\"", name, *((u16*)col), *((u16*)(col+1)), *((u16*)(col+2)));
}
