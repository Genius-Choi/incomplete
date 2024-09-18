static int hash_get_nents(struct scatterlist *sg, int size, bool *aligned)
{
	int nents = 0;
	bool aligned_data = true;

	while (size > 0 && sg) {
		nents++;
		size -= sg->length;

		/* hash_set_dma_transfer will align last nent */
		if ((aligned && !IS_ALIGNED(sg->offset, HASH_DMA_ALIGN_SIZE)) ||
		    (!IS_ALIGNED(sg->length, HASH_DMA_ALIGN_SIZE) && size > 0))
			aligned_data = false;

		sg = sg_next(sg);
	}

	if (aligned)
		*aligned = aligned_data;

	if (size != 0)
		return -EFAULT;

	return nents;
}
