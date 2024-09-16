static int nl80211_netlink_notify(struct notifier_block * nb,
				  unsigned long state,
				  void *_notify)
{
	struct netlink_notify *notify = _notify;
	struct cfg80211_registered_device *rdev;
	struct wireless_dev *wdev;

	if (state != NETLINK_URELEASE)
		return NOTIFY_DONE;

	rcu_read_lock();

	list_for_each_entry_rcu(rdev, &cfg80211_rdev_list, list)
		list_for_each_entry_rcu(wdev, &rdev->netdev_list, list)
			cfg80211_mlme_unregister_socket(wdev, notify->pid);

	rcu_read_unlock();

	return NOTIFY_DONE;
}
