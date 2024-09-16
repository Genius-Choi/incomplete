static int rtl8150_get_settings(struct net_device *netdev, struct ethtool_cmd *ecmd)
{
	rtl8150_t *dev = netdev_priv(netdev);
	short lpa, bmcr;

	ecmd->supported = (SUPPORTED_10baseT_Half |
			  SUPPORTED_10baseT_Full |
			  SUPPORTED_100baseT_Half |
			  SUPPORTED_100baseT_Full |
			  SUPPORTED_Autoneg |
			  SUPPORTED_TP | SUPPORTED_MII);
	ecmd->port = PORT_TP;
	ecmd->transceiver = XCVR_INTERNAL;
	ecmd->phy_address = dev->phy;
	get_registers(dev, BMCR, 2, &bmcr);
	get_registers(dev, ANLP, 2, &lpa);
	if (bmcr & BMCR_ANENABLE) {
		u32 speed = ((lpa & (LPA_100HALF | LPA_100FULL)) ?
			     SPEED_100 : SPEED_10);
		ethtool_cmd_speed_set(ecmd, speed);
		ecmd->autoneg = AUTONEG_ENABLE;
		if (speed == SPEED_100)
			ecmd->duplex = (lpa & LPA_100FULL) ?
			    DUPLEX_FULL : DUPLEX_HALF;
		else
			ecmd->duplex = (lpa & LPA_10FULL) ?
			    DUPLEX_FULL : DUPLEX_HALF;
	} else {
		ecmd->autoneg = AUTONEG_DISABLE;
		ethtool_cmd_speed_set(ecmd, ((bmcr & BMCR_SPEED100) ?
					     SPEED_100 : SPEED_10));
		ecmd->duplex = (bmcr & BMCR_FULLDPLX) ?
		    DUPLEX_FULL : DUPLEX_HALF;
	}
	return 0;
}
