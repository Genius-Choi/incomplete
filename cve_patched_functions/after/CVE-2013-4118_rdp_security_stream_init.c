static int rdp_security_stream_init(rdpRdp* rdp, STREAM* s)
{
	if (rdp->do_crypt)
	{
		stream_seek(s, 12);

		if (rdp->settings->EncryptionMethods == ENCRYPTION_METHOD_FIPS)
			stream_seek(s, 4);

		rdp->sec_flags |= SEC_ENCRYPT;

		if (rdp->do_secure_checksum)
			rdp->sec_flags |= SEC_SECURE_CHECKSUM;
	}
	else if (rdp->sec_flags != 0)
	{
		stream_seek(s, 4);
	}

	return 0;
}
