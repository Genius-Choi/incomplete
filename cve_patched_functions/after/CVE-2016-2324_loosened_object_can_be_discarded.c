static int loosened_object_can_be_discarded(const unsigned char *sha1,
					    unsigned long mtime)
{
	if (!unpack_unreachable_expiration)
		return 0;
	if (mtime > unpack_unreachable_expiration)
		return 0;
	if (sha1_array_lookup(&recent_objects, sha1) >= 0)
		return 0;
	return 1;
}
