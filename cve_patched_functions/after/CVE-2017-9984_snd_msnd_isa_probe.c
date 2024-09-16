static int snd_msnd_isa_probe(struct device *pdev, unsigned int idx)
{
	int err;
	struct snd_card *card;
	struct snd_msnd *chip;

	if (has_isapnp(idx)
#ifndef MSND_CLASSIC
	    || cfg[idx] == SNDRV_AUTO_PORT
#endif
	    ) {
		printk(KERN_INFO LOGNAME ": Assuming PnP mode\n");
		return -ENODEV;
	}

	err = snd_card_new(pdev, index[idx], id[idx], THIS_MODULE,
			   sizeof(struct snd_msnd), &card);
	if (err < 0)
		return err;

	chip = card->private_data;
	chip->card = card;

#ifdef MSND_CLASSIC
	switch (irq[idx]) {
	case 5:
		chip->irqid = HPIRQ_5; break;
	case 7:
		chip->irqid = HPIRQ_7; break;
	case 9:
		chip->irqid = HPIRQ_9; break;
	case 10:
		chip->irqid = HPIRQ_10; break;
	case 11:
		chip->irqid = HPIRQ_11; break;
	case 12:
		chip->irqid = HPIRQ_12; break;
	}

	switch (mem[idx]) {
	case 0xb0000:
		chip->memid = HPMEM_B000; break;
	case 0xc8000:
		chip->memid = HPMEM_C800; break;
	case 0xd0000:
		chip->memid = HPMEM_D000; break;
	case 0xd8000:
		chip->memid = HPMEM_D800; break;
	case 0xe0000:
		chip->memid = HPMEM_E000; break;
	case 0xe8000:
		chip->memid = HPMEM_E800; break;
	}
#else
	printk(KERN_INFO LOGNAME ": Non-PnP mode: configuring at port 0x%lx\n",
			cfg[idx]);

	if (!request_region(cfg[idx], 2, "Pinnacle/Fiji Config")) {
		printk(KERN_ERR LOGNAME ": Config port 0x%lx conflict\n",
			   cfg[idx]);
		snd_card_free(card);
		return -EIO;
	}
	if (reset[idx])
		if (snd_msnd_pinnacle_cfg_reset(cfg[idx])) {
			err = -EIO;
			goto cfg_error;
		}

	/* DSP */
	err = snd_msnd_write_cfg_logical(cfg[idx], 0,
					 io[idx], 0,
					 irq[idx], mem[idx]);

	if (err)
		goto cfg_error;

	/* The following are Pinnacle specific */

	/* MPU */
	if (mpu_io[idx] != SNDRV_AUTO_PORT
	    && mpu_irq[idx] != SNDRV_AUTO_IRQ) {
		printk(KERN_INFO LOGNAME
		       ": Configuring MPU to I/O 0x%lx IRQ %d\n",
		       mpu_io[idx], mpu_irq[idx]);
		err = snd_msnd_write_cfg_logical(cfg[idx], 1,
						 mpu_io[idx], 0,
						 mpu_irq[idx], 0);

		if (err)
			goto cfg_error;
	}

	/* IDE */
	if (ide_io0[idx] != SNDRV_AUTO_PORT
	    && ide_io1[idx] != SNDRV_AUTO_PORT
	    && ide_irq[idx] != SNDRV_AUTO_IRQ) {
		printk(KERN_INFO LOGNAME
		       ": Configuring IDE to I/O 0x%lx, 0x%lx IRQ %d\n",
		       ide_io0[idx], ide_io1[idx], ide_irq[idx]);
		err = snd_msnd_write_cfg_logical(cfg[idx], 2,
						 ide_io0[idx], ide_io1[idx],
						 ide_irq[idx], 0);

		if (err)
			goto cfg_error;
	}

	/* Joystick */
	if (joystick_io[idx] != SNDRV_AUTO_PORT) {
		printk(KERN_INFO LOGNAME
		       ": Configuring joystick to I/O 0x%lx\n",
		       joystick_io[idx]);
		err = snd_msnd_write_cfg_logical(cfg[idx], 3,
						 joystick_io[idx], 0,
						 0, 0);

		if (err)
			goto cfg_error;
	}
	release_region(cfg[idx], 2);

#endif /* MSND_CLASSIC */

	set_default_audio_parameters(chip);
#ifdef MSND_CLASSIC
	chip->type = msndClassic;
#else
	chip->type = msndPinnacle;
#endif
	chip->io = io[idx];
	chip->irq = irq[idx];
	chip->base = mem[idx];

	chip->calibrate_signal = calibrate_signal ? 1 : 0;
	chip->recsrc = 0;
	chip->dspq_data_buff = DSPQ_DATA_BUFF;
	chip->dspq_buff_size = DSPQ_BUFF_SIZE;
	if (write_ndelay[idx])
		clear_bit(F_DISABLE_WRITE_NDELAY, &chip->flags);
	else
		set_bit(F_DISABLE_WRITE_NDELAY, &chip->flags);
#ifndef MSND_CLASSIC
	if (digital[idx])
		set_bit(F_HAVEDIGITAL, &chip->flags);
#endif
	spin_lock_init(&chip->lock);
	err = snd_msnd_probe(card);
	if (err < 0) {
		printk(KERN_ERR LOGNAME ": Probe failed\n");
		snd_card_free(card);
		return err;
	}

	err = snd_msnd_attach(card);
	if (err < 0) {
		printk(KERN_ERR LOGNAME ": Attach failed\n");
		snd_card_free(card);
		return err;
	}
	dev_set_drvdata(pdev, card);

	return 0;

#ifndef MSND_CLASSIC
cfg_error:
	release_region(cfg[idx], 2);
	snd_card_free(card);
	return err;
#endif
}
