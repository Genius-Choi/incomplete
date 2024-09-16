static int tg3_phy_probe(struct tg3 *tp)
{
	u32 hw_phy_id_1, hw_phy_id_2;
	u32 hw_phy_id, hw_phy_id_masked;
	int err;

	/* flow control autonegotiation is default behavior */
	tg3_flag_set(tp, PAUSE_AUTONEG);
	tp->link_config.flowctrl = FLOW_CTRL_TX | FLOW_CTRL_RX;

	if (tg3_flag(tp, ENABLE_APE)) {
		switch (tp->pci_fn) {
		case 0:
			tp->phy_ape_lock = TG3_APE_LOCK_PHY0;
			break;
		case 1:
			tp->phy_ape_lock = TG3_APE_LOCK_PHY1;
			break;
		case 2:
			tp->phy_ape_lock = TG3_APE_LOCK_PHY2;
			break;
		case 3:
			tp->phy_ape_lock = TG3_APE_LOCK_PHY3;
			break;
		}
	}

	if (tg3_flag(tp, USE_PHYLIB))
		return tg3_phy_init(tp);

	/* Reading the PHY ID register can conflict with ASF
	 * firmware access to the PHY hardware.
	 */
	err = 0;
	if (tg3_flag(tp, ENABLE_ASF) || tg3_flag(tp, ENABLE_APE)) {
		hw_phy_id = hw_phy_id_masked = TG3_PHY_ID_INVALID;
	} else {
		/* Now read the physical PHY_ID from the chip and verify
		 * that it is sane.  If it doesn't look good, we fall back
		 * to either the hard-coded table based PHY_ID and failing
		 * that the value found in the eeprom area.
		 */
		err |= tg3_readphy(tp, MII_PHYSID1, &hw_phy_id_1);
		err |= tg3_readphy(tp, MII_PHYSID2, &hw_phy_id_2);

		hw_phy_id  = (hw_phy_id_1 & 0xffff) << 10;
		hw_phy_id |= (hw_phy_id_2 & 0xfc00) << 16;
		hw_phy_id |= (hw_phy_id_2 & 0x03ff) <<  0;

		hw_phy_id_masked = hw_phy_id & TG3_PHY_ID_MASK;
	}

	if (!err && TG3_KNOWN_PHY_ID(hw_phy_id_masked)) {
		tp->phy_id = hw_phy_id;
		if (hw_phy_id_masked == TG3_PHY_ID_BCM8002)
			tp->phy_flags |= TG3_PHYFLG_PHY_SERDES;
		else
			tp->phy_flags &= ~TG3_PHYFLG_PHY_SERDES;
	} else {
		if (tp->phy_id != TG3_PHY_ID_INVALID) {
			/* Do nothing, phy ID already set up in
			 * tg3_get_eeprom_hw_cfg().
			 */
		} else {
			struct subsys_tbl_ent *p;

			/* No eeprom signature?  Try the hardcoded
			 * subsys device table.
			 */
			p = tg3_lookup_by_subsys(tp);
			if (p) {
				tp->phy_id = p->phy_id;
			} else if (!tg3_flag(tp, IS_SSB_CORE)) {
				/* For now we saw the IDs 0xbc050cd0,
				 * 0xbc050f80 and 0xbc050c30 on devices
				 * connected to an BCM4785 and there are
				 * probably more. Just assume that the phy is
				 * supported when it is connected to a SSB core
				 * for now.
				 */
				return -ENODEV;
			}

			if (!tp->phy_id ||
			    tp->phy_id == TG3_PHY_ID_BCM8002)
				tp->phy_flags |= TG3_PHYFLG_PHY_SERDES;
		}
	}

	if (!(tp->phy_flags & TG3_PHYFLG_ANY_SERDES) &&
	    (tg3_asic_rev(tp) == ASIC_REV_5719 ||
	     tg3_asic_rev(tp) == ASIC_REV_5720 ||
	     tg3_asic_rev(tp) == ASIC_REV_5762 ||
	     (tg3_asic_rev(tp) == ASIC_REV_5717 &&
	      tg3_chip_rev_id(tp) != CHIPREV_ID_5717_A0) ||
	     (tg3_asic_rev(tp) == ASIC_REV_57765 &&
	      tg3_chip_rev_id(tp) != CHIPREV_ID_57765_A0)))
		tp->phy_flags |= TG3_PHYFLG_EEE_CAP;

	tg3_phy_init_link_config(tp);

	if (!(tp->phy_flags & TG3_PHYFLG_ANY_SERDES) &&
	    !tg3_flag(tp, ENABLE_APE) &&
	    !tg3_flag(tp, ENABLE_ASF)) {
		u32 bmsr, dummy;

		tg3_readphy(tp, MII_BMSR, &bmsr);
		if (!tg3_readphy(tp, MII_BMSR, &bmsr) &&
		    (bmsr & BMSR_LSTATUS))
			goto skip_phy_reset;

		err = tg3_phy_reset(tp);
		if (err)
			return err;

		tg3_phy_set_wirespeed(tp);

		if (!tg3_phy_copper_an_config_ok(tp, &dummy)) {
			tg3_phy_autoneg_cfg(tp, tp->link_config.advertising,
					    tp->link_config.flowctrl);

			tg3_writephy(tp, MII_BMCR,
				     BMCR_ANENABLE | BMCR_ANRESTART);
		}
	}

skip_phy_reset:
	if ((tp->phy_id & TG3_PHY_ID_MASK) == TG3_PHY_ID_BCM5401) {
		err = tg3_init_5401phy_dsp(tp);
		if (err)
			return err;

		err = tg3_init_5401phy_dsp(tp);
	}

	return err;
}
