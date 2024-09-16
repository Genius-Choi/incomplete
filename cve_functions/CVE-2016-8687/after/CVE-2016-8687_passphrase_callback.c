passphrase_callback(struct archive *a, void *_client_data)
{
	struct bsdtar *bsdtar = (struct bsdtar *)_client_data;
	(void)a; /* UNUSED */

	if (bsdtar->ppbuff == NULL) {
		bsdtar->ppbuff = malloc(PPBUFF_SIZE);
		if (bsdtar->ppbuff == NULL)
			lafe_errc(1, errno, "Out of memory");
	}
	return lafe_readpassphrase("Enter passphrase:",
		bsdtar->ppbuff, PPBUFF_SIZE);
}
