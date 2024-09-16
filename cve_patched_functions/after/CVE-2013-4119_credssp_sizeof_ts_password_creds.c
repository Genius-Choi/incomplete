int credssp_sizeof_ts_password_creds(rdpCredssp* credssp)
{
	int length = 0;

	length += ber_sizeof_sequence_octet_string(credssp->identity.DomainLength * 2);
	length += ber_sizeof_sequence_octet_string(credssp->identity.UserLength * 2);
	length += ber_sizeof_sequence_octet_string(credssp->identity.PasswordLength * 2);

	return length;
}
