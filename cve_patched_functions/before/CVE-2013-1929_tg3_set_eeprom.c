static int tg3_set_eeprom(struct net_device *dev, struct ethtool_eeprom *eeprom, u8 *data)
{
	struct tg3 *tp = netdev_priv(dev);
	int ret;
	u32 offset, len, b_offset, odd_len;
	u8 *buf;
	__be32 start, end;

	if (tp->phy_flags & TG3_PHYFLG_IS_LOW_POWER)
		return -EAGAIN;

	if (tg3_flag(tp, NO_NVRAM) ||
	    eeprom->magic != TG3_EEPROM_MAGIC)
		return -EINVAL;

	offset = eeprom->offset;
	len = eeprom->len;

	if ((b_offset = (offset & 3))) {
		/* adjustments to start on required 4 byte boundary */
		ret = tg3_nvram_read_be32(tp, offset-b_offset, &start);
		if (ret)
			return ret;
		len += b_offset;
		offset &= ~3;
		if (len < 4)
			len = 4;
	}

	odd_len = 0;
	if (len & 3) {
		/* adjustments to end on required 4 byte boundary */
		odd_len = 1;
		len = (len + 3) & ~3;
		ret = tg3_nvram_read_be32(tp, offset+len-4, &end);
		if (ret)
			return ret;
	}

	buf = data;
	if (b_offset || odd_len) {
		buf = kmalloc(len, GFP_KERNEL);
		if (!buf)
			return -ENOMEM;
		if (b_offset)
			memcpy(buf, &start, 4);
		if (odd_len)
			memcpy(buf+len-4, &end, 4);
		memcpy(buf + b_offset, data, eeprom->len);
	}

	ret = tg3_nvram_write_block(tp, offset, len, buf);

	if (buf != data)
		kfree(buf);

	return ret;
}
