int migrate_prep_local(void)
{
	lru_add_drain();

	return 0;
}
