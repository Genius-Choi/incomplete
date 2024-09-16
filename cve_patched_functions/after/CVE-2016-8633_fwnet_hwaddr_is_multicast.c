static bool fwnet_hwaddr_is_multicast(u8 *ha)
{
	return !!(*ha & 1);
}
