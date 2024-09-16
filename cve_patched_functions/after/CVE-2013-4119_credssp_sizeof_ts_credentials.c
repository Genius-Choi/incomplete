int credssp_sizeof_ts_credentials(rdpCredssp* credssp)
{
	int size = 0;

	size += ber_sizeof_integer(1);
	size += ber_sizeof_contextual_tag(ber_sizeof_integer(1));
	size += ber_sizeof_sequence_octet_string(ber_sizeof_sequence(credssp_sizeof_ts_password_creds(credssp)));

	return size;
}
