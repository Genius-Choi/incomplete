static int upload_dsp_code(struct snd_card *card)
{
	struct snd_msnd *chip = card->private_data;
	const struct firmware *init_fw = NULL, *perm_fw = NULL;
	int err;

	outb(HPBLKSEL_0, chip->io + HP_BLKS);

	err = request_firmware(&init_fw, INITCODEFILE, card->dev);
	if (err < 0) {
		printk(KERN_ERR LOGNAME ": Error loading " INITCODEFILE);
		goto cleanup1;
	}
	err = request_firmware(&perm_fw, PERMCODEFILE, card->dev);
	if (err < 0) {
		printk(KERN_ERR LOGNAME ": Error loading " PERMCODEFILE);
		goto cleanup;
	}

	memcpy_toio(chip->mappedbase, perm_fw->data, perm_fw->size);
	if (snd_msnd_upload_host(chip, init_fw->data, init_fw->size) < 0) {
		printk(KERN_WARNING LOGNAME ": Error uploading to DSP\n");
		err = -ENODEV;
		goto cleanup;
	}
	printk(KERN_INFO LOGNAME ": DSP firmware uploaded\n");
	err = 0;

cleanup:
	release_firmware(perm_fw);
cleanup1:
	release_firmware(init_fw);
	return err;
}
