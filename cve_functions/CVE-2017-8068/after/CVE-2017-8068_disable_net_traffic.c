static inline void disable_net_traffic(pegasus_t *pegasus)
{
	__le16 tmp = cpu_to_le16(0);

	set_registers(pegasus, EthCtrl0, sizeof(tmp), &tmp);
}
