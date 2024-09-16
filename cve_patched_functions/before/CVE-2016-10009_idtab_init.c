idtab_init(void)
{
	int i;

	for (i = 0; i <=2; i++) {
		TAILQ_INIT(&idtable[i].idlist);
		idtable[i].nentries = 0;
	}
}
