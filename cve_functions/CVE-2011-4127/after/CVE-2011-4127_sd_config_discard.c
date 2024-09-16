static void sd_config_discard(struct scsi_disk *sdkp, unsigned int mode)
{
	struct request_queue *q = sdkp->disk->queue;
	unsigned int logical_block_size = sdkp->device->sector_size;
	unsigned int max_blocks = 0;

	q->limits.discard_zeroes_data = sdkp->lbprz;
	q->limits.discard_alignment = sdkp->unmap_alignment *
		logical_block_size;
	q->limits.discard_granularity =
		max(sdkp->physical_block_size,
		    sdkp->unmap_granularity * logical_block_size);

	switch (mode) {

	case SD_LBP_DISABLE:
		q->limits.max_discard_sectors = 0;
		queue_flag_clear_unlocked(QUEUE_FLAG_DISCARD, q);
		return;

	case SD_LBP_UNMAP:
		max_blocks = min_not_zero(sdkp->max_unmap_blocks, 0xffffffff);
		break;

	case SD_LBP_WS16:
		max_blocks = min_not_zero(sdkp->max_ws_blocks, 0xffffffff);
		break;

	case SD_LBP_WS10:
		max_blocks = min_not_zero(sdkp->max_ws_blocks, (u32)0xffff);
		break;

	case SD_LBP_ZERO:
		max_blocks = min_not_zero(sdkp->max_ws_blocks, (u32)0xffff);
		q->limits.discard_zeroes_data = 1;
		break;
	}

	q->limits.max_discard_sectors = max_blocks * (logical_block_size >> 9);
	queue_flag_set_unlocked(QUEUE_FLAG_DISCARD, q);

	sdkp->provisioning_mode = mode;
}
