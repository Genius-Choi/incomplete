static int __videobuf_mmap_free(struct videobuf_queue *q)
{
	unsigned int i;

	for (i = 0; i < VIDEO_MAX_FRAME; i++) {
		if (q->bufs[i]) {
			if (q->bufs[i]->map)
				return -EBUSY;
		}
	}

	return 0;
}
