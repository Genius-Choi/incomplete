static unsigned int clientid_hashval(u32 id)
{
	return id & CLIENT_HASH_MASK;
}
