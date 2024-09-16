int dcbnl_ieee_notify(struct net_device *dev, int event, int cmd,
		      u32 seq, u32 portid)
{
	return dcbnl_notify(dev, event, cmd, seq, portid, DCB_CAP_DCBX_VER_IEEE);
}
