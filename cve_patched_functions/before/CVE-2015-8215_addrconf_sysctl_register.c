static int addrconf_sysctl_register(struct inet6_dev *idev)
{
	int err;

	if (!sysctl_dev_name_is_allowed(idev->dev->name))
		return -EINVAL;

	err = neigh_sysctl_register(idev->dev, idev->nd_parms,
				    &ndisc_ifinfo_sysctl_change);
	if (err)
		return err;
	err = __addrconf_sysctl_register(dev_net(idev->dev), idev->dev->name,
					 idev, &idev->cnf);
	if (err)
		neigh_sysctl_unregister(idev->nd_parms);

	return err;
}
