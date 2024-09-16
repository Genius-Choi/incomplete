static void bi_complete(struct bio *bio, int error)
{
	complete((struct completion *)bio->bi_private);
}
