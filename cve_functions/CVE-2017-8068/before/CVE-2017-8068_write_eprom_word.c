static int write_eprom_word(pegasus_t *pegasus, __u8 index, __u16 data)
{
	int i;
	__u8 tmp, d[4] = { 0x3f, 0, 0, EPROM_WRITE };
	int ret;
	__le16 le_data = cpu_to_le16(data);

	set_registers(pegasus, EpromOffset, 4, d);
	enable_eprom_write(pegasus);
	set_register(pegasus, EpromOffset, index);
	set_registers(pegasus, EpromData, 2, &le_data);
	set_register(pegasus, EpromCtrl, EPROM_WRITE);

	for (i = 0; i < REG_TIMEOUT; i++) {
		ret = get_registers(pegasus, EpromCtrl, 1, &tmp);
		if (ret == -ESHUTDOWN)
			goto fail;
		if (tmp & EPROM_DONE)
			break;
	}
	disable_eprom_write(pegasus);
	if (i >= REG_TIMEOUT)
		goto fail;

	return ret;

fail:
	netif_warn(pegasus, drv, pegasus->net, "%s failed\n", __func__);
	return -ETIMEDOUT;
}
