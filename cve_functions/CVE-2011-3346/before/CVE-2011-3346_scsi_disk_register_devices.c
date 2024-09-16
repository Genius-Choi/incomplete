static void scsi_disk_register_devices(void)
{
    int i;

    for (i = 0; i < ARRAY_SIZE(scsi_disk_info); i++) {
        scsi_qdev_register(&scsi_disk_info[i]);
    }
}
