static bool tg3_phy_copper_an_config_ok(struct tg3 *tp, u32 *lcladv)
{
	u32 advmsk, tgtadv, advertising;

	advertising = tp->link_config.advertising;
	tgtadv = ethtool_adv_to_mii_adv_t(advertising) & ADVERTISE_ALL;

	advmsk = ADVERTISE_ALL;
	if (tp->link_config.active_duplex == DUPLEX_FULL) {
		tgtadv |= mii_advertise_flowctrl(tp->link_config.flowctrl);
		advmsk |= ADVERTISE_PAUSE_CAP | ADVERTISE_PAUSE_ASYM;
	}

	if (tg3_readphy(tp, MII_ADVERTISE, lcladv))
		return false;

	if ((*lcladv & advmsk) != tgtadv)
		return false;

	if (!(tp->phy_flags & TG3_PHYFLG_10_100_ONLY)) {
		u32 tg3_ctrl;

		tgtadv = ethtool_adv_to_mii_ctrl1000_t(advertising);

		if (tg3_readphy(tp, MII_CTRL1000, &tg3_ctrl))
			return false;

		if (tgtadv &&
		    (tg3_chip_rev_id(tp) == CHIPREV_ID_5701_A0 ||
		     tg3_chip_rev_id(tp) == CHIPREV_ID_5701_B0)) {
			tgtadv |= CTL1000_AS_MASTER | CTL1000_ENABLE_MASTER;
			tg3_ctrl &= (ADVERTISE_1000HALF | ADVERTISE_1000FULL |
				     CTL1000_AS_MASTER | CTL1000_ENABLE_MASTER);
		} else {
			tg3_ctrl &= (ADVERTISE_1000HALF | ADVERTISE_1000FULL);
		}

		if (tg3_ctrl != tgtadv)
			return false;
	}

	return true;
}
