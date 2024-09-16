cifs_writedata_release(struct kref *refcount)
{
	struct cifs_writedata *wdata = container_of(refcount,
					struct cifs_writedata, refcount);

	if (wdata->cfile)
		cifsFileInfo_put(wdata->cfile);

	kfree(wdata);
}
