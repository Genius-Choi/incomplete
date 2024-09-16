static void scsi_cd_change_media_cb(void *opaque, bool load)
{
    ((SCSIDiskState *)opaque)->tray_open = !load;
}
