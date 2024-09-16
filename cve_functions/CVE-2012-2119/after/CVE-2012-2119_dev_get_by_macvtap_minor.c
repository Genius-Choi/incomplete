static struct net_device *dev_get_by_macvtap_minor(int minor)
{
	struct net_device *dev = NULL;
	struct macvlan_dev *vlan;

	mutex_lock(&minor_lock);
	vlan = idr_find(&minor_idr, minor);
	if (vlan) {
		dev = vlan->dev;
		dev_hold(dev);
	}
	mutex_unlock(&minor_lock);
	return dev;
}
