static int cma_acquire_dev(struct rdma_id_private *id_priv,
			   struct rdma_id_private *listen_id_priv)
{
	struct rdma_dev_addr *dev_addr = &id_priv->id.route.addr.dev_addr;
	struct cma_device *cma_dev;
	union ib_gid gid, iboe_gid;
	int ret = -ENODEV;
	u8 port, found_port;
	enum rdma_link_layer dev_ll = dev_addr->dev_type == ARPHRD_INFINIBAND ?
		IB_LINK_LAYER_INFINIBAND : IB_LINK_LAYER_ETHERNET;

	if (dev_ll != IB_LINK_LAYER_INFINIBAND &&
	    id_priv->id.ps == RDMA_PS_IPOIB)
		return -EINVAL;

	mutex_lock(&lock);
	rdma_ip2gid((struct sockaddr *)&id_priv->id.route.addr.src_addr,
		    &iboe_gid);

	memcpy(&gid, dev_addr->src_dev_addr +
	       rdma_addr_gid_offset(dev_addr), sizeof gid);
	if (listen_id_priv &&
	    rdma_port_get_link_layer(listen_id_priv->id.device,
				     listen_id_priv->id.port_num) == dev_ll) {
		cma_dev = listen_id_priv->cma_dev;
		port = listen_id_priv->id.port_num;
		if (rdma_node_get_transport(cma_dev->device->node_type) == RDMA_TRANSPORT_IB &&
		    rdma_port_get_link_layer(cma_dev->device, port) == IB_LINK_LAYER_ETHERNET)
			ret = ib_find_cached_gid(cma_dev->device, &iboe_gid,
						 &found_port, NULL);
		else
			ret = ib_find_cached_gid(cma_dev->device, &gid,
						 &found_port, NULL);

		if (!ret && (port  == found_port)) {
			id_priv->id.port_num = found_port;
			goto out;
		}
	}
	list_for_each_entry(cma_dev, &dev_list, list) {
		for (port = 1; port <= cma_dev->device->phys_port_cnt; ++port) {
			if (listen_id_priv &&
			    listen_id_priv->cma_dev == cma_dev &&
			    listen_id_priv->id.port_num == port)
				continue;
			if (rdma_port_get_link_layer(cma_dev->device, port) == dev_ll) {
				if (rdma_node_get_transport(cma_dev->device->node_type) == RDMA_TRANSPORT_IB &&
				    rdma_port_get_link_layer(cma_dev->device, port) == IB_LINK_LAYER_ETHERNET)
					ret = ib_find_cached_gid(cma_dev->device, &iboe_gid, &found_port, NULL);
				else
					ret = ib_find_cached_gid(cma_dev->device, &gid, &found_port, NULL);

				if (!ret && (port == found_port)) {
					id_priv->id.port_num = found_port;
					goto out;
				}
			}
		}
	}

out:
	if (!ret)
		cma_attach_to_dev(id_priv, cma_dev);

	mutex_unlock(&lock);
	return ret;
}
