static void scsi_destroy(SCSIDevice *dev)
{
    SCSIDiskState *s = DO_UPCAST(SCSIDiskState, qdev, dev);

    scsi_device_purge_requests(&s->qdev, SENSE_CODE(NO_SENSE));
    blockdev_mark_auto_del(s->qdev.conf.bs);
}
