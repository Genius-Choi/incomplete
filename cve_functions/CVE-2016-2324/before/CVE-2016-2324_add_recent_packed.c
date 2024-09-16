static int add_recent_packed(const unsigned char *sha1,
			     struct packed_git *p, uint32_t pos,
			     void *data)
{
	struct object *obj = lookup_object(sha1);

	if (obj && obj->flags & SEEN)
		return 0;
	add_recent_object(sha1, p->mtime, data);
	return 0;
}
