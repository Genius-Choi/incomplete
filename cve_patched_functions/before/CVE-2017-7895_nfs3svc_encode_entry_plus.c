nfs3svc_encode_entry_plus(void *cd, const char *name,
			  int namlen, loff_t offset, u64 ino,
			  unsigned int d_type)
{
	return encode_entry(cd, name, namlen, offset, ino, d_type, 1);
}
