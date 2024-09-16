static int atusb_ed(struct ieee802154_hw *hw, u8 *level)
{
	BUG_ON(!level);
	*level = 0xbe;
	return 0;
}
