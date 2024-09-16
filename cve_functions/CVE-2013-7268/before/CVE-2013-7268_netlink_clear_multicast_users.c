void netlink_clear_multicast_users(struct sock *ksk, unsigned int group)
{
	netlink_table_grab();
	__netlink_clear_multicast_users(ksk, group);
	netlink_table_ungrab();
}
