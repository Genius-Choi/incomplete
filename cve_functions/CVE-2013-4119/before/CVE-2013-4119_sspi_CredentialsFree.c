void sspi_CredentialsFree(CREDENTIALS* credentials)
{
	if (!credentials)
		return;

	free(credentials);
}
