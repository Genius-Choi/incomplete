static int scsi_cd_initfn(SCSIDevice *dev)
{
    return scsi_initfn(dev, TYPE_ROM);
}
