void sspi_CopyAuthIdentity(SEC_WINNT_AUTH_IDENTITY* identity, SEC_WINNT_AUTH_IDENTITY* srcIdentity)
{
	if (identity->Flags == SEC_WINNT_AUTH_IDENTITY_ANSI)
	{
		sspi_SetAuthIdentity(identity, (char*) srcIdentity->User,
				(char*) srcIdentity->Domain, (char*) srcIdentity->Password);

		identity->Flags = SEC_WINNT_AUTH_IDENTITY_UNICODE;

		return;
	}

	identity->Flags = SEC_WINNT_AUTH_IDENTITY_UNICODE;

	identity->User = identity->Domain = identity->Password = NULL;

	identity->UserLength = srcIdentity->UserLength;

	if (identity->UserLength > 0)
	{
		identity->User = (UINT16*) malloc((identity->UserLength + 1) * sizeof(WCHAR));
		CopyMemory(identity->User, srcIdentity->User, identity->UserLength * sizeof(WCHAR));
		identity->User[identity->UserLength] = 0;
	}

	identity->DomainLength = srcIdentity->DomainLength;

	if (identity->DomainLength > 0)
	{
		identity->Domain = (UINT16*) malloc((identity->DomainLength + 1) * sizeof(WCHAR));
		CopyMemory(identity->Domain, srcIdentity->Domain, identity->DomainLength * sizeof(WCHAR));
		identity->Domain[identity->DomainLength] = 0;
	}

	identity->PasswordLength = srcIdentity->PasswordLength;

	if (identity->PasswordLength > 0)
	{
		identity->Password = (UINT16*) malloc((identity->PasswordLength + 1) * sizeof(WCHAR));
		CopyMemory(identity->Password, srcIdentity->Password, identity->PasswordLength * sizeof(WCHAR));
		identity->Password[identity->PasswordLength] = 0;
	}
}
