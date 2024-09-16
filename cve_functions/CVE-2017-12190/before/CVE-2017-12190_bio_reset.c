void bio_reset(struct bio *bio)
{
	unsigned long flags = bio->bi_flags & (~0UL << BIO_RESET_BITS);

	bio_uninit(bio);

	memset(bio, 0, BIO_RESET_BYTES);
	bio->bi_flags = flags;
	atomic_set(&bio->__bi_remaining, 1);
}
