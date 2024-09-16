int hostap_set_antsel(local_info_t *local)
{
	u16 val;
	int ret = 0;

	if (local->antsel_tx != HOSTAP_ANTSEL_DO_NOT_TOUCH &&
	    local->func->cmd(local->dev, HFA384X_CMDCODE_READMIF,
			     HFA386X_CR_TX_CONFIGURE,
			     NULL, &val) == 0) {
		val &= ~(BIT(2) | BIT(1));
		switch (local->antsel_tx) {
		case HOSTAP_ANTSEL_DIVERSITY:
			val |= BIT(1);
			break;
		case HOSTAP_ANTSEL_LOW:
			break;
		case HOSTAP_ANTSEL_HIGH:
			val |= BIT(2);
			break;
		}

		if (local->func->cmd(local->dev, HFA384X_CMDCODE_WRITEMIF,
				     HFA386X_CR_TX_CONFIGURE, &val, NULL)) {
			printk(KERN_INFO "%s: setting TX AntSel failed\n",
			       local->dev->name);
			ret = -1;
		}
	}

	if (local->antsel_rx != HOSTAP_ANTSEL_DO_NOT_TOUCH &&
	    local->func->cmd(local->dev, HFA384X_CMDCODE_READMIF,
			     HFA386X_CR_RX_CONFIGURE,
			     NULL, &val) == 0) {
		val &= ~(BIT(1) | BIT(0));
		switch (local->antsel_rx) {
		case HOSTAP_ANTSEL_DIVERSITY:
			break;
		case HOSTAP_ANTSEL_LOW:
			val |= BIT(0);
			break;
		case HOSTAP_ANTSEL_HIGH:
			val |= BIT(0) | BIT(1);
			break;
		}

		if (local->func->cmd(local->dev, HFA384X_CMDCODE_WRITEMIF,
				     HFA386X_CR_RX_CONFIGURE, &val, NULL)) {
			printk(KERN_INFO "%s: setting RX AntSel failed\n",
			       local->dev->name);
			ret = -1;
		}
	}

	return ret;
}
