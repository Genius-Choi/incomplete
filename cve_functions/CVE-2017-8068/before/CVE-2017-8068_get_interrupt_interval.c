static inline void get_interrupt_interval(pegasus_t *pegasus)
{
	u16 data;
	u8 interval;

	read_eprom_word(pegasus, 4, &data);
	interval = data >> 8;
	if (pegasus->usb->speed != USB_SPEED_HIGH) {
		if (interval < 0x80) {
			netif_info(pegasus, timer, pegasus->net,
				   "intr interval changed from %ums to %ums\n",
				   interval, 0x80);
			interval = 0x80;
			data = (data & 0x00FF) | ((u16)interval << 8);
#ifdef PEGASUS_WRITE_EEPROM
			write_eprom_word(pegasus, 4, data);
#endif
		}
	}
	pegasus->intr_interval = interval;
}
