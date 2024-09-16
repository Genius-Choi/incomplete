checkDownloadList(void)
{
    DownloadList *d;
    struct stat st;

    if (!FirstDL)
	return FALSE;
    for (d = FirstDL; d != NULL; d = d->next) {
	if (d->running && !lstat(d->lock, &st))
	    return TRUE;
    }
    return FALSE;
}
