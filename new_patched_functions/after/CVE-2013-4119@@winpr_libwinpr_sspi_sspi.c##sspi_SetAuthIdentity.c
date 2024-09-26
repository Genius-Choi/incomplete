void sspi_SetAuthIdentity(SEC_WINNT_AUTH_IDENTITY* identity, char* user, char* domain, char* password)
{
	identity->Flags = SEC_WINNT_AUTH_IDENTITY_UNICODE;

	if (user)
	{
		identity->UserLength = ConvertToUnicode(CP_UTF8, 0, user, -1, &identity->User, 0) - 1;
	}
	else
	{
		identity->User = (UINT16*) NULL;
		identity->UserLength = 0;
	}

	if (domain)
	{
		identity->DomainLength = ConvertToUnicode(CP_UTF8, 0, domain, -1, &identity->Domain, 0) - 1;
	}
	else
	{
		identity->Domain = (UINT16*) NULL;
		identity->DomainLength = 0;
	}

	if (password != NULL)
	{
		identity->PasswordLength = ConvertToUnicode(CP_UTF8, 0, password, -1, &identity->Password, 0) - 1;
	}
	else
	{
		identity->Password = NULL;
		identity->PasswordLength = 0;
	}
}
