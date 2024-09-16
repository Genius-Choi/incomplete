static void rtl8150_get_drvinfo(struct net_device *netdev, struct ethtool_drvinfo *info)
{
	rtl8150_t *dev = netdev_priv(netdev);

	strlcpy(info->driver, driver_name, sizeof(info->driver));
	strlcpy(info->version, DRIVER_VERSION, sizeof(info->version));
	usb_make_path(dev->udev, info->bus_info, sizeof(info->bus_info));
}
