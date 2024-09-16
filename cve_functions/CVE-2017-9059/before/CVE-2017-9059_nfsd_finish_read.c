nfsd_finish_read(struct file *file, unsigned long *count, int host_err)
{
	if (host_err >= 0) {
		nfsdstats.io_read += host_err;
		*count = host_err;
		fsnotify_access(file);
		return 0;
	} else 
		return nfserrno(host_err);
}
