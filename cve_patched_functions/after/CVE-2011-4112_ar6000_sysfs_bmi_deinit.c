ar6000_sysfs_bmi_deinit(struct ar6_softc *ar)
{
    AR_DEBUG_PRINTF(ATH_DEBUG_INFO,("BMI: Deleting sysfs entry\n"));

    sysfs_remove_bin_file(&(((struct device *)ar->osDevInfo.pOSDevice)->kobj), &bmi_attr);
}
