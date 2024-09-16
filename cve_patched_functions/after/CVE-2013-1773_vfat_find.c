static int vfat_find(struct inode *dir, struct qstr *qname,
		     struct fat_slot_info *sinfo)
{
	unsigned int len = vfat_striptail_len(qname);
	if (len == 0)
		return -ENOENT;
	return fat_search_long(dir, qname->name, len, sinfo);
}
