lookup_gname(struct cpio *cpio, gid_t gid)
{
	return (lookup_name(cpio, &cpio->gname_cache,
		    &lookup_gname_helper, (id_t)gid));
}
