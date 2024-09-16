static int tg3_power_up(struct tg3 *tp)
{
	int err;

	tg3_enable_register_access(tp);

	err = pci_set_power_state(tp->pdev, PCI_D0);
	if (!err) {
		/* Switch out of Vaux if it is a NIC */
		tg3_pwrsrc_switch_to_vmain(tp);
	} else {
		netdev_err(tp->dev, "Transition to D0 failed\n");
	}

	return err;
}
