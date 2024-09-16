static inline void set_ethernet_addr(rtl8150_t * dev)
{
	u8 node_id[6];

	get_registers(dev, IDR, sizeof(node_id), node_id);
	memcpy(dev->netdev->dev_addr, node_id, sizeof(node_id));
}
