void add_pending_sha1(struct rev_info *revs, const char *name,
		      const unsigned char *sha1, unsigned int flags)
{
	struct object *object = get_reference(revs, name, sha1, flags);
	add_pending_object(revs, object, name);
}
