static int scsi_hd_initfn(SCSIDevice *dev)
{
    return scsi_initfn(dev, TYPE_DISK);
}
