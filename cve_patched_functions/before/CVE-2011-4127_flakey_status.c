static int flakey_status(struct dm_target *ti, status_type_t type,
			 char *result, unsigned int maxlen)
{
	unsigned sz = 0;
	struct flakey_c *fc = ti->private;
	unsigned drop_writes;

	switch (type) {
	case STATUSTYPE_INFO:
		result[0] = '\0';
		break;

	case STATUSTYPE_TABLE:
		DMEMIT("%s %llu %u %u ", fc->dev->name,
		       (unsigned long long)fc->start, fc->up_interval,
		       fc->down_interval);

		drop_writes = test_bit(DROP_WRITES, &fc->flags);
		DMEMIT("%u ", drop_writes + (fc->corrupt_bio_byte > 0) * 5);

		if (drop_writes)
			DMEMIT("drop_writes ");

		if (fc->corrupt_bio_byte)
			DMEMIT("corrupt_bio_byte %u %c %u %u ",
			       fc->corrupt_bio_byte,
			       (fc->corrupt_bio_rw == WRITE) ? 'w' : 'r',
			       fc->corrupt_bio_value, fc->corrupt_bio_flags);

		break;
	}
	return 0;
}
