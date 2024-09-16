static unsigned int file_hashval(struct knfsd_fh *fh)
{
	return nfsd_fh_hashval(fh) & (FILE_HASH_SIZE - 1);
}
