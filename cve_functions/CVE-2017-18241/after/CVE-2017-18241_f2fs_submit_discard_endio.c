static void f2fs_submit_discard_endio(struct bio *bio)
{
	struct discard_cmd *dc = (struct discard_cmd *)bio->bi_private;

	dc->error = bio->bi_error;
	dc->state = D_DONE;
	complete_all(&dc->wait);
	bio_put(bio);
}
