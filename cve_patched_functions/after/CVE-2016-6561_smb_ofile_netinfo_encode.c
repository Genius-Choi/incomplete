smb_ofile_netinfo_encode(smb_ofile_t *of, uint8_t *buf, size_t buflen,
    uint32_t *nbytes)
{
	smb_netfileinfo_t	fi;
	int			rc;

	rc = smb_ofile_netinfo_init(of, &fi);
	if (rc == 0) {
		rc = smb_netfileinfo_encode(&fi, buf, buflen, nbytes);
		smb_ofile_netinfo_fini(&fi);
	}

	return (rc);
}
