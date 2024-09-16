kex_prop_free(char **proposal)
{
	u_int i;

	if (proposal == NULL)
		return;
	for (i = 0; i < PROPOSAL_MAX; i++)
		free(proposal[i]);
	free(proposal);
}
