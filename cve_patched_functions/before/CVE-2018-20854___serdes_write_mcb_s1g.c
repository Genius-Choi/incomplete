static int __serdes_write_mcb_s1g(struct regmap *regmap, u8 macro, u32 op)
{
	unsigned int regval;

	regmap_write(regmap, HSIO_MCB_S1G_ADDR_CFG, op |
		     HSIO_MCB_S1G_ADDR_CFG_SERDES1G_ADDR(BIT(macro)));

	return regmap_read_poll_timeout(regmap, HSIO_MCB_S1G_ADDR_CFG, regval,
					(regval & op) != op, 100,
					MCB_S1G_CFG_TIMEOUT * 1000);
}
