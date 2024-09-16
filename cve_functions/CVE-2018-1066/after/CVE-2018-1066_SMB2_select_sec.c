SMB2_select_sec(struct cifs_ses *ses, struct SMB2_sess_data *sess_data)
{
	if (ses->sectype != Kerberos && ses->sectype != RawNTLMSSP)
		ses->sectype = RawNTLMSSP;

	switch (ses->sectype) {
	case Kerberos:
		sess_data->func = SMB2_auth_kerberos;
		break;
	case RawNTLMSSP:
		sess_data->func = SMB2_sess_auth_rawntlmssp_negotiate;
		break;
	default:
		cifs_dbg(VFS, "secType %d not supported!\n", ses->sectype);
		return -EOPNOTSUPP;
	}

	return 0;
}
