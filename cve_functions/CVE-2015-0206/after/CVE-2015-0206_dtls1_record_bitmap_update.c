static void dtls1_record_bitmap_update(SSL *s, DTLS1_BITMAP *bitmap)
	{
	int cmp;
	unsigned int shift;
	const unsigned char *seq = s->s3->read_sequence;

	cmp = satsub64be(seq,bitmap->max_seq_num);
	if (cmp > 0)
		{
		shift = cmp;
		if (shift < sizeof(bitmap->map)*8)
			bitmap->map <<= shift, bitmap->map |= 1UL;
		else
			bitmap->map = 1UL;
		memcpy(bitmap->max_seq_num,seq,8);
		}
	else	{
		shift = -cmp;
		if (shift < sizeof(bitmap->map)*8)
			bitmap->map |= 1UL<<shift;
		}
	}
