static int list_drivers(void)
{
	int i;

	if (ctx->card_drivers[0] == NULL) {
		printf("No card drivers installed!\n");
		return 0;
	}
	printf("Configured card drivers:\n");
	for (i = 0; ctx->card_drivers[i] != NULL; i++) {
		printf("  %-16s %s\n", ctx->card_drivers[i]->short_name,
		      ctx->card_drivers[i]->name);
	}
	return 0;
}
