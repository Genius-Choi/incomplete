static void __init pf_init_units(void)
{
	struct pf_unit *pf;
	int unit;

	pf_drive_count = 0;
	for (unit = 0, pf = units; unit < PF_UNITS; unit++, pf++) {
		struct gendisk *disk;

		disk = alloc_disk(1);
		if (!disk)
			continue;

		disk->queue = blk_mq_init_sq_queue(&pf->tag_set, &pf_mq_ops,
							1, BLK_MQ_F_SHOULD_MERGE);
		if (IS_ERR(disk->queue)) {
			put_disk(disk);
			disk->queue = NULL;
			continue;
		}

		INIT_LIST_HEAD(&pf->rq_list);
		disk->queue->queuedata = pf;
		blk_queue_max_segments(disk->queue, cluster);
		blk_queue_bounce_limit(disk->queue, BLK_BOUNCE_HIGH);
		pf->disk = disk;
		pf->pi = &pf->pia;
		pf->media_status = PF_NM;
		pf->drive = (*drives[unit])[D_SLV];
		pf->lun = (*drives[unit])[D_LUN];
		snprintf(pf->name, PF_NAMELEN, "%s%d", name, unit);
		disk->major = major;
		disk->first_minor = unit;
		strcpy(disk->disk_name, pf->name);
		disk->fops = &pf_fops;
		if (!(*drives[unit])[D_PRT])
			pf_drive_count++;
	}
}
