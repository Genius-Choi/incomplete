static void ims_pcu_destroy_bootloader_mode(struct ims_pcu *pcu)
{
	/* Make sure our initial firmware request has completed */
	wait_for_completion(&pcu->async_firmware_done);
}
