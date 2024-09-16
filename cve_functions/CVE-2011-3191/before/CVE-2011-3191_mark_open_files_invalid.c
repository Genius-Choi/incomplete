static void mark_open_files_invalid(struct cifs_tcon *pTcon)
{
	struct cifsFileInfo *open_file = NULL;
	struct list_head *tmp;
	struct list_head *tmp1;

/* list all files open on tree connection and mark them invalid */
	spin_lock(&cifs_file_list_lock);
	list_for_each_safe(tmp, tmp1, &pTcon->openFileList) {
		open_file = list_entry(tmp, struct cifsFileInfo, tlist);
		open_file->invalidHandle = true;
		open_file->oplock_break_cancelled = true;
	}
	spin_unlock(&cifs_file_list_lock);
	/* BB Add call to invalidate_inodes(sb) for all superblocks mounted
	   to this tcon */
}
