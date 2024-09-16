static void update_progress(struct connectivity_progress *cp)
{
	cp->count++;
	if ((cp->count & 1023) == 0)
		display_progress(cp->progress, cp->count);
}
