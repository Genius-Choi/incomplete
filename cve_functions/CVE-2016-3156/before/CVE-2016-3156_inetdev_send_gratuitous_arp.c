static void inetdev_send_gratuitous_arp(struct net_device *dev,
					struct in_device *in_dev)

{
	struct in_ifaddr *ifa;

	for (ifa = in_dev->ifa_list; ifa;
	     ifa = ifa->ifa_next) {
		arp_send(ARPOP_REQUEST, ETH_P_ARP,
			 ifa->ifa_local, dev,
			 ifa->ifa_local, NULL,
			 dev->dev_addr, NULL);
	}
}
