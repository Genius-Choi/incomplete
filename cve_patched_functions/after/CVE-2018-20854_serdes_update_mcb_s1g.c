static int serdes_update_mcb_s1g(struct regmap *regmap, u8 macro)
{
	return __serdes_write_mcb_s1g(regmap, macro,
		HSIO_MCB_S1G_ADDR_CFG_SERDES1G_RD_ONE_SHOT);
}
