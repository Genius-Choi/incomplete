void credssp_free(rdpCredssp* credssp)
{
	if (credssp != NULL)
	{
		if (credssp->table)
			credssp->table->DeleteSecurityContext(&credssp->context);

		sspi_SecBufferFree(&credssp->PublicKey);
		sspi_SecBufferFree(&credssp->ts_credentials);

		free(credssp->ServicePrincipalName);

		free(credssp->identity.User);
		free(credssp->identity.Domain);
		free(credssp->identity.Password);
		free(credssp);
	}
}
