static void br_multicast_query_received(struct net_bridge *br,
					struct net_bridge_port *port,
					int saddr)
{
	if (saddr)
		mod_timer(&br->multicast_querier_timer,
			  jiffies + br->multicast_querier_interval);
	else if (timer_pending(&br->multicast_querier_timer))
		return;

	br_multicast_mark_router(br, port);
}
