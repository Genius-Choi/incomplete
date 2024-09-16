static inline void enable_eprom_write(pegasus_t *pegasus)
{
	__u8 tmp;

	get_registers(pegasus, EthCtrl2, 1, &tmp);
	set_register(pegasus, EthCtrl2, tmp | EPROM_WR_ENABLE);
}
