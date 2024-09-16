set_default_mcast_group(data_t * data)
{
	inet_stosockaddr(INADDR_VRRP_GROUP, 0, (struct sockaddr_storage *)&data->vrrp_mcast_group4);
	inet_stosockaddr(INADDR6_VRRP_GROUP, 0, (struct sockaddr_storage *)&data->vrrp_mcast_group6);
}
