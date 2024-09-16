int snd_usb_create_mixer(struct snd_usb_audio *chip, int ctrlif,
			 int ignore_error)
{
	static struct snd_device_ops dev_ops = {
		.dev_free = snd_usb_mixer_dev_free
	};
	struct usb_mixer_interface *mixer;
	struct snd_info_entry *entry;
	int err;

	strcpy(chip->card->mixername, "USB Mixer");

	mixer = kzalloc(sizeof(*mixer), GFP_KERNEL);
	if (!mixer)
		return -ENOMEM;
	mixer->chip = chip;
	mixer->ignore_ctl_error = ignore_error;
	mixer->id_elems = kcalloc(MAX_ID_ELEMS, sizeof(*mixer->id_elems),
				  GFP_KERNEL);
	if (!mixer->id_elems) {
		kfree(mixer);
		return -ENOMEM;
	}

	mixer->hostif = &usb_ifnum_to_if(chip->dev, ctrlif)->altsetting[0];
	switch (get_iface_desc(mixer->hostif)->bInterfaceProtocol) {
	case UAC_VERSION_1:
	default:
		mixer->protocol = UAC_VERSION_1;
		break;
	case UAC_VERSION_2:
		mixer->protocol = UAC_VERSION_2;
		break;
	}

	if ((err = snd_usb_mixer_controls(mixer)) < 0 ||
	    (err = snd_usb_mixer_status_create(mixer)) < 0)
		goto _error;

	snd_usb_mixer_apply_create_quirk(mixer);

	err = snd_device_new(chip->card, SNDRV_DEV_CODEC, mixer, &dev_ops);
	if (err < 0)
		goto _error;

	if (list_empty(&chip->mixer_list) &&
	    !snd_card_proc_new(chip->card, "usbmixer", &entry))
		snd_info_set_text_ops(entry, chip, snd_usb_mixer_proc_read);

	list_add(&mixer->list, &chip->mixer_list);
	return 0;

_error:
	snd_usb_mixer_free(mixer);
	return err;
}
