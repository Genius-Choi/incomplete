do_chdir(struct bsdtar *bsdtar)
{
	if (bsdtar->pending_chdir == NULL)
		return;

	if (chdir(bsdtar->pending_chdir) != 0) {
		lafe_errc(1, 0, "could not chdir to '%s'\n",
		    bsdtar->pending_chdir);
	}
	free(bsdtar->pending_chdir);
	bsdtar->pending_chdir = NULL;
}
