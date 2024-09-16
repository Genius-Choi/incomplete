lookup_uname(struct cpio *cpio, uid_t uid)
{
	return (lookup_name(cpio, &cpio->uname_cache,
		    &lookup_uname_helper, (id_t)uid));
}
