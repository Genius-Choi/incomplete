static int tg3_init_5401phy_dsp(struct tg3 *tp)
{
	int err;

	/* Turn off tap power management. */
	/* Set Extended packet length bit */
	err = tg3_phy_auxctl_write(tp, MII_TG3_AUXCTL_SHDWSEL_AUXCTL, 0x4c20);

	err |= tg3_phydsp_write(tp, 0x0012, 0x1804);
	err |= tg3_phydsp_write(tp, 0x0013, 0x1204);
	err |= tg3_phydsp_write(tp, 0x8006, 0x0132);
	err |= tg3_phydsp_write(tp, 0x8006, 0x0232);
	err |= tg3_phydsp_write(tp, 0x201f, 0x0a20);

	udelay(40);

	return err;
}
