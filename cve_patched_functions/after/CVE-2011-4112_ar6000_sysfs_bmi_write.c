ar6000_sysfs_bmi_write(struct file *fp, struct kobject *kobj,
                       struct bin_attribute *bin_attr,
                       char *buf, loff_t pos, size_t count)
{
    int index;
    struct ar6_softc *ar;
    struct hif_device_os_device_info   *osDevInfo;

    AR_DEBUG_PRINTF(ATH_DEBUG_INFO,("BMI: Write %d bytes\n", (u32)count));
    for (index=0; index < MAX_AR6000; index++) {
        ar = (struct ar6_softc *)ar6k_priv(ar6000_devices[index]);
        osDevInfo = &ar->osDevInfo;
        if (kobj == (&(((struct device *)osDevInfo->pOSDevice)->kobj))) {
            break;
        }
    }

    if (index == MAX_AR6000) return 0;

    if ((BMIRawWrite(ar->arHifDevice, (u8*)buf, count)) != 0) {
        return 0;
    }

    return count;
}
