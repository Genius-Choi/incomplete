smb_ofile_netinfo_fini(smb_netfileinfo_t *fi)
{
	if (fi == NULL)
		return;

	if (fi->fi_path)
		smb_mem_free(fi->fi_path);
	if (fi->fi_username)
		kmem_free(fi->fi_username, fi->fi_namelen);

	bzero(fi, sizeof (smb_netfileinfo_t));
}
