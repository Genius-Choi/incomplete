static void tg3_phy_toggle_apd(struct tg3 *tp, bool enable)
{
	u32 reg;

	if (!tg3_flag(tp, 5705_PLUS) ||
	    (tg3_flag(tp, 5717_PLUS) &&
	     (tp->phy_flags & TG3_PHYFLG_MII_SERDES)))
		return;

	if (tp->phy_flags & TG3_PHYFLG_IS_FET) {
		tg3_phy_fet_toggle_apd(tp, enable);
		return;
	}

	reg = MII_TG3_MISC_SHDW_WREN |
	      MII_TG3_MISC_SHDW_SCR5_SEL |
	      MII_TG3_MISC_SHDW_SCR5_LPED |
	      MII_TG3_MISC_SHDW_SCR5_DLPTLM |
	      MII_TG3_MISC_SHDW_SCR5_SDTL |
	      MII_TG3_MISC_SHDW_SCR5_C125OE;
	if (tg3_asic_rev(tp) != ASIC_REV_5784 || !enable)
		reg |= MII_TG3_MISC_SHDW_SCR5_DLLAPD;

	tg3_writephy(tp, MII_TG3_MISC_SHDW, reg);


	reg = MII_TG3_MISC_SHDW_WREN |
	      MII_TG3_MISC_SHDW_APD_SEL |
	      MII_TG3_MISC_SHDW_APD_WKTM_84MS;
	if (enable)
		reg |= MII_TG3_MISC_SHDW_APD_ENABLE;

	tg3_writephy(tp, MII_TG3_MISC_SHDW, reg);
}
