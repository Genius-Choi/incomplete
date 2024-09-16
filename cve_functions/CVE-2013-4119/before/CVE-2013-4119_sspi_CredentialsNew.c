CREDENTIALS* sspi_CredentialsNew()
{
	CREDENTIALS* credentials;

	credentials = (CREDENTIALS*) malloc(sizeof(CREDENTIALS));
	ZeroMemory(credentials, sizeof(CREDENTIALS));

	if (credentials != NULL)
	{

	}

	return credentials;
}
