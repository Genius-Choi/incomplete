int cdrom_ioctl(struct cdrom_device_info *cdi, struct block_device *bdev,
		fmode_t mode, unsigned int cmd, unsigned long arg)
{
	void __user *argp = (void __user *)arg;
	int ret;

	/*
	 * Try the generic SCSI command ioctl's first.
	 */
	ret = scsi_cmd_blk_ioctl(bdev, mode, cmd, argp);
	if (ret != -ENOTTY)
		return ret;

	switch (cmd) {
	case CDROMMULTISESSION:
		return cdrom_ioctl_multisession(cdi, argp);
	case CDROMEJECT:
		return cdrom_ioctl_eject(cdi);
	case CDROMCLOSETRAY:
		return cdrom_ioctl_closetray(cdi);
	case CDROMEJECT_SW:
		return cdrom_ioctl_eject_sw(cdi, arg);
	case CDROM_MEDIA_CHANGED:
		return cdrom_ioctl_media_changed(cdi, arg);
	case CDROM_SET_OPTIONS:
		return cdrom_ioctl_set_options(cdi, arg);
	case CDROM_CLEAR_OPTIONS:
		return cdrom_ioctl_clear_options(cdi, arg);
	case CDROM_SELECT_SPEED:
		return cdrom_ioctl_select_speed(cdi, arg);
	case CDROM_SELECT_DISC:
		return cdrom_ioctl_select_disc(cdi, arg);
	case CDROMRESET:
		return cdrom_ioctl_reset(cdi, bdev);
	case CDROM_LOCKDOOR:
		return cdrom_ioctl_lock_door(cdi, arg);
	case CDROM_DEBUG:
		return cdrom_ioctl_debug(cdi, arg);
	case CDROM_GET_CAPABILITY:
		return cdrom_ioctl_get_capability(cdi);
	case CDROM_GET_MCN:
		return cdrom_ioctl_get_mcn(cdi, argp);
	case CDROM_DRIVE_STATUS:
		return cdrom_ioctl_drive_status(cdi, arg);
	case CDROM_DISC_STATUS:
		return cdrom_ioctl_disc_status(cdi);
	case CDROM_CHANGER_NSLOTS:
		return cdrom_ioctl_changer_nslots(cdi);
	}

	/*
	 * Use the ioctls that are implemented through the generic_packet()
	 * interface. this may look at bit funny, but if -ENOTTY is
	 * returned that particular ioctl is not implemented and we
	 * let it go through the device specific ones.
	 */
	if (CDROM_CAN(CDC_GENERIC_PACKET)) {
		ret = mmc_ioctl(cdi, cmd, arg);
		if (ret != -ENOTTY)
			return ret;
	}

	/*
	 * Note: most of the cd_dbg() calls are commented out here,
	 * because they fill up the sys log when CD players poll
	 * the drive.
	 */
	switch (cmd) {
	case CDROMSUBCHNL:
		return cdrom_ioctl_get_subchnl(cdi, argp);
	case CDROMREADTOCHDR:
		return cdrom_ioctl_read_tochdr(cdi, argp);
	case CDROMREADTOCENTRY:
		return cdrom_ioctl_read_tocentry(cdi, argp);
	case CDROMPLAYMSF:
		return cdrom_ioctl_play_msf(cdi, argp);
	case CDROMPLAYTRKIND:
		return cdrom_ioctl_play_trkind(cdi, argp);
	case CDROMVOLCTRL:
		return cdrom_ioctl_volctrl(cdi, argp);
	case CDROMVOLREAD:
		return cdrom_ioctl_volread(cdi, argp);
	case CDROMSTART:
	case CDROMSTOP:
	case CDROMPAUSE:
	case CDROMRESUME:
		return cdrom_ioctl_audioctl(cdi, cmd);
	}

	return -ENOSYS;
}
