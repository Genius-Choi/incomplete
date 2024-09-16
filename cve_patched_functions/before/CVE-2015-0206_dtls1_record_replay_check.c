static int dtls1_record_replay_check(SSL *s, DTLS1_BITMAP *bitmap)
	{
	int cmp;
	unsigned int shift;
	const unsigned char *seq = s->s3->read_sequence;

	cmp = satsub64be(seq,bitmap->max_seq_num);
	if (cmp > 0)
		{
		memcpy (s->s3->rrec.seq_num,seq,8);
		return 1; /* this record in new */
		}
	shift = -cmp;
	if (shift >= sizeof(bitmap->map)*8)
		return 0; /* stale, outside the window */
	else if (bitmap->map & (1UL<<shift))
		return 0; /* record previously received */

	memcpy (s->s3->rrec.seq_num,seq,8);
	return 1;
	}
