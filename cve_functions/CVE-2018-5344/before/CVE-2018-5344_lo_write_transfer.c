static int lo_write_transfer(struct loop_device *lo, struct request *rq,
		loff_t pos)
{
	struct bio_vec bvec, b;
	struct req_iterator iter;
	struct page *page;
	int ret = 0;

	page = alloc_page(GFP_NOIO);
	if (unlikely(!page))
		return -ENOMEM;

	rq_for_each_segment(bvec, rq, iter) {
		ret = lo_do_transfer(lo, WRITE, page, 0, bvec.bv_page,
			bvec.bv_offset, bvec.bv_len, pos >> 9);
		if (unlikely(ret))
			break;

		b.bv_page = page;
		b.bv_offset = 0;
		b.bv_len = bvec.bv_len;
		ret = lo_write_bvec(lo->lo_backing_file, &b, &pos);
		if (ret < 0)
			break;
	}

	__free_page(page);
	return ret;
}
