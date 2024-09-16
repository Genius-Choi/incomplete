static unsigned persistent_status(struct dm_exception_store *store,
				  status_type_t status, char *result,
				  unsigned maxlen)
{
	unsigned sz = 0;

	switch (status) {
	case STATUSTYPE_INFO:
		break;
	case STATUSTYPE_TABLE:
		DMEMIT(" P %llu", (unsigned long long)store->chunk_size);
	}

	return sz;
}
