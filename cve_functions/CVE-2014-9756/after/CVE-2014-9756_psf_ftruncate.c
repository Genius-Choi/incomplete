psf_ftruncate (SF_PRIVATE *psf, sf_count_t len)
{	int retval ;

	/* Returns 0 on success, non-zero on failure. */
	if (len < 0)
		return 1 ;

	/* The global village idiots at micorsoft decided to implement
	** nearly all the required 64 bit file offset functions except
	** for one, truncate. The fscking morons!
	**
	** This is not 64 bit file offset clean. Somone needs to clean
	** this up.
	*/
	if (len > 0x7FFFFFFF)
		return -1 ;

	retval = chsize (psf->file.filedes, len) ;

	if (retval == -1)
		psf_log_syserr (psf, errno) ;

	return retval ;
} /* psf_ftruncate */
