xfs_buf_ioapply_map(
	struct xfs_buf	*bp,
	int		map,
	int		*buf_offset,
	int		*count,
	int		rw)
{
	int		page_index;
	int		total_nr_pages = bp->b_page_count;
	int		nr_pages;
	struct bio	*bio;
	sector_t	sector =  bp->b_maps[map].bm_bn;
	int		size;
	int		offset;

	total_nr_pages = bp->b_page_count;

	/* skip the pages in the buffer before the start offset */
	page_index = 0;
	offset = *buf_offset;
	while (offset >= PAGE_SIZE) {
		page_index++;
		offset -= PAGE_SIZE;
	}

	/*
	 * Limit the IO size to the length of the current vector, and update the
	 * remaining IO count for the next time around.
	 */
	size = min_t(int, BBTOB(bp->b_maps[map].bm_len), *count);
	*count -= size;
	*buf_offset += size;

next_chunk:
	atomic_inc(&bp->b_io_remaining);
	nr_pages = BIO_MAX_SECTORS >> (PAGE_SHIFT - BBSHIFT);
	if (nr_pages > total_nr_pages)
		nr_pages = total_nr_pages;

	bio = bio_alloc(GFP_NOIO, nr_pages);
	bio->bi_bdev = bp->b_target->bt_bdev;
	bio->bi_sector = sector;
	bio->bi_end_io = xfs_buf_bio_end_io;
	bio->bi_private = bp;


	for (; size && nr_pages; nr_pages--, page_index++) {
		int	rbytes, nbytes = PAGE_SIZE - offset;

		if (nbytes > size)
			nbytes = size;

		rbytes = bio_add_page(bio, bp->b_pages[page_index], nbytes,
				      offset);
		if (rbytes < nbytes)
			break;

		offset = 0;
		sector += BTOBB(nbytes);
		size -= nbytes;
		total_nr_pages--;
	}

	if (likely(bio->bi_size)) {
		if (xfs_buf_is_vmapped(bp)) {
			flush_kernel_vmap_range(bp->b_addr,
						xfs_buf_vmap_len(bp));
		}
		submit_bio(rw, bio);
		if (size)
			goto next_chunk;
	} else {
		/*
		 * This is guaranteed not to be the last io reference count
		 * because the caller (xfs_buf_iorequest) holds a count itself.
		 */
		atomic_dec(&bp->b_io_remaining);
		xfs_buf_ioerror(bp, EIO);
		bio_put(bio);
	}

}
