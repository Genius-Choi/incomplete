static int __mii_op(pegasus_t *p, __u8 phy, __u8 indx, __u16 *regd, __u8 cmd)
{
	int i;
	__u8 data[4] = { phy, 0, 0, indx };
	__le16 regdi;
	int ret = -ETIMEDOUT;

	if (cmd & PHY_WRITE) {
		__le16 *t = (__le16 *) & data[1];
		*t = cpu_to_le16(*regd);
	}
	set_register(p, PhyCtrl, 0);
	set_registers(p, PhyAddr, sizeof(data), data);
	set_register(p, PhyCtrl, (indx | cmd));
	for (i = 0; i < REG_TIMEOUT; i++) {
		ret = get_registers(p, PhyCtrl, 1, data);
		if (ret < 0)
			goto fail;
		if (data[0] & PHY_DONE)
			break;
	}
	if (i >= REG_TIMEOUT)
		goto fail;
	if (cmd & PHY_READ) {
		ret = get_registers(p, PhyData, 2, &regdi);
		*regd = le16_to_cpu(regdi);
		return ret;
	}
	return 0;
fail:
	netif_dbg(p, drv, p->net, "%s failed\n", __func__);
	return ret;
}
