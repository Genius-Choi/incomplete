void netdev_lower_state_changed(struct net_device *lower_dev,
				void *lower_state_info)
{
	struct netdev_notifier_changelowerstate_info changelowerstate_info;

	ASSERT_RTNL();
	changelowerstate_info.lower_state_info = lower_state_info;
	call_netdevice_notifiers_info(NETDEV_CHANGELOWERSTATE, lower_dev,
				      &changelowerstate_info.info);
}
