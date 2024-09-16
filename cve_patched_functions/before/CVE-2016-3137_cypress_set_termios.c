static void cypress_set_termios(struct tty_struct *tty,
	struct usb_serial_port *port, struct ktermios *old_termios)
{
	struct cypress_private *priv = usb_get_serial_port_data(port);
	struct device *dev = &port->dev;
	int data_bits, stop_bits, parity_type, parity_enable;
	unsigned cflag, iflag;
	unsigned long flags;
	__u8 oldlines;
	int linechange = 0;

	spin_lock_irqsave(&priv->lock, flags);
	/* We can't clean this one up as we don't know the device type
	   early enough */
	if (!priv->termios_initialized) {
		if (priv->chiptype == CT_EARTHMATE) {
			tty->termios = tty_std_termios;
			tty->termios.c_cflag = B4800 | CS8 | CREAD | HUPCL |
				CLOCAL;
			tty->termios.c_ispeed = 4800;
			tty->termios.c_ospeed = 4800;
		} else if (priv->chiptype == CT_CYPHIDCOM) {
			tty->termios = tty_std_termios;
			tty->termios.c_cflag = B9600 | CS8 | CREAD | HUPCL |
				CLOCAL;
			tty->termios.c_ispeed = 9600;
			tty->termios.c_ospeed = 9600;
		} else if (priv->chiptype == CT_CA42V2) {
			tty->termios = tty_std_termios;
			tty->termios.c_cflag = B9600 | CS8 | CREAD | HUPCL |
				CLOCAL;
			tty->termios.c_ispeed = 9600;
			tty->termios.c_ospeed = 9600;
		}
		priv->termios_initialized = 1;
	}
	spin_unlock_irqrestore(&priv->lock, flags);

	/* Unsupported features need clearing */
	tty->termios.c_cflag &= ~(CMSPAR|CRTSCTS);

	cflag = tty->termios.c_cflag;
	iflag = tty->termios.c_iflag;

	/* check if there are new settings */
	if (old_termios) {
		spin_lock_irqsave(&priv->lock, flags);
		priv->tmp_termios = tty->termios;
		spin_unlock_irqrestore(&priv->lock, flags);
	}

	/* set number of data bits, parity, stop bits */
	/* when parity is disabled the parity type bit is ignored */

	/* 1 means 2 stop bits, 0 means 1 stop bit */
	stop_bits = cflag & CSTOPB ? 1 : 0;

	if (cflag & PARENB) {
		parity_enable = 1;
		/* 1 means odd parity, 0 means even parity */
		parity_type = cflag & PARODD ? 1 : 0;
	} else
		parity_enable = parity_type = 0;

	switch (cflag & CSIZE) {
	case CS5:
		data_bits = 0;
		break;
	case CS6:
		data_bits = 1;
		break;
	case CS7:
		data_bits = 2;
		break;
	case CS8:
		data_bits = 3;
		break;
	default:
		dev_err(dev, "%s - CSIZE was set, but not CS5-CS8\n", __func__);
		data_bits = 3;
	}
	spin_lock_irqsave(&priv->lock, flags);
	oldlines = priv->line_control;
	if ((cflag & CBAUD) == B0) {
		/* drop dtr and rts */
		dev_dbg(dev, "%s - dropping the lines, baud rate 0bps\n", __func__);
		priv->line_control &= ~(CONTROL_DTR | CONTROL_RTS);
	} else
		priv->line_control = (CONTROL_DTR | CONTROL_RTS);
	spin_unlock_irqrestore(&priv->lock, flags);

	dev_dbg(dev, "%s - sending %d stop_bits, %d parity_enable, %d parity_type, %d data_bits (+5)\n",
		__func__, stop_bits, parity_enable, parity_type, data_bits);

	cypress_serial_control(tty, port, tty_get_baud_rate(tty),
			data_bits, stop_bits,
			parity_enable, parity_type,
			0, CYPRESS_SET_CONFIG);

	/* we perform a CYPRESS_GET_CONFIG so that the current settings are
	 * filled into the private structure this should confirm that all is
	 * working if it returns what we just set */
	cypress_serial_control(tty, port, 0, 0, 0, 0, 0, 0, CYPRESS_GET_CONFIG);

	/* Here we can define custom tty settings for devices; the main tty
	 * termios flag base comes from empeg.c */

	spin_lock_irqsave(&priv->lock, flags);
	if (priv->chiptype == CT_EARTHMATE && priv->baud_rate == 4800) {
		dev_dbg(dev, "Using custom termios settings for a baud rate of 4800bps.\n");
		/* define custom termios settings for NMEA protocol */

		tty->termios.c_iflag /* input modes - */
			&= ~(IGNBRK  /* disable ignore break */
			| BRKINT     /* disable break causes interrupt */
			| PARMRK     /* disable mark parity errors */
			| ISTRIP     /* disable clear high bit of input char */
			| INLCR      /* disable translate NL to CR */
			| IGNCR      /* disable ignore CR */
			| ICRNL      /* disable translate CR to NL */
			| IXON);     /* disable enable XON/XOFF flow control */

		tty->termios.c_oflag /* output modes */
			&= ~OPOST;    /* disable postprocess output char */

		tty->termios.c_lflag /* line discipline modes */
			&= ~(ECHO     /* disable echo input characters */
			| ECHONL      /* disable echo new line */
			| ICANON      /* disable erase, kill, werase, and rprnt
					 special characters */
			| ISIG        /* disable interrupt, quit, and suspend
					 special characters */
			| IEXTEN);    /* disable non-POSIX special characters */
	} /* CT_CYPHIDCOM: Application should handle this for device */

	linechange = (priv->line_control != oldlines);
	spin_unlock_irqrestore(&priv->lock, flags);

	/* if necessary, set lines */
	if (linechange) {
		priv->cmd_ctrl = 1;
		cypress_write(tty, port, NULL, 0);
	}
} /* cypress_set_termios */
