magic_entry_free(struct magic_entry *me, uint32_t nme)
{
	uint32_t i;
	if (me == NULL)
		return;
	for (i = 0; i < nme; i++)
		free(me[i].mp);
	free(me);
}
