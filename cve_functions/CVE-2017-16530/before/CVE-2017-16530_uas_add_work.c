static void uas_add_work(struct uas_cmd_info *cmdinfo)
{
	struct scsi_pointer *scp = (void *)cmdinfo;
	struct scsi_cmnd *cmnd = container_of(scp, struct scsi_cmnd, SCp);
	struct uas_dev_info *devinfo = cmnd->device->hostdata;

	lockdep_assert_held(&devinfo->lock);
	cmdinfo->state |= IS_IN_WORK_LIST;
	schedule_work(&devinfo->work);
}
