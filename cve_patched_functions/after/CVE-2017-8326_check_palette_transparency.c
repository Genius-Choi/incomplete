static int check_palette_transparency(const struct iw_palette *p)
{
	int i;
	int retval = 0;

	for(i=0;i<p->num_entries;i++) {
		if(p->entry[i].a!=255) retval=1;
		if(p->entry[i].a!=255 && p->entry[i].a!=0) return 2;
	}
	return retval;
}
