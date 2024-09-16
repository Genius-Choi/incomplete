static int cma_resolve_ib_dev(struct rdma_id_private *id_priv)
{
	struct cma_device *cma_dev, *cur_dev;
	struct sockaddr_ib *addr;
	union ib_gid gid, sgid, *dgid;
	u16 pkey, index;
	u8 p;
	int i;

	cma_dev = NULL;
	addr = (struct sockaddr_ib *) cma_dst_addr(id_priv);
	dgid = (union ib_gid *) &addr->sib_addr;
	pkey = ntohs(addr->sib_pkey);

	list_for_each_entry(cur_dev, &dev_list, list) {
		if (rdma_node_get_transport(cur_dev->device->node_type) != RDMA_TRANSPORT_IB)
			continue;

		for (p = 1; p <= cur_dev->device->phys_port_cnt; ++p) {
			if (ib_find_cached_pkey(cur_dev->device, p, pkey, &index))
				continue;

			for (i = 0; !ib_get_cached_gid(cur_dev->device, p, i, &gid); i++) {
				if (!memcmp(&gid, dgid, sizeof(gid))) {
					cma_dev = cur_dev;
					sgid = gid;
					id_priv->id.port_num = p;
					goto found;
				}

				if (!cma_dev && (gid.global.subnet_prefix ==
						 dgid->global.subnet_prefix)) {
					cma_dev = cur_dev;
					sgid = gid;
					id_priv->id.port_num = p;
				}
			}
		}
	}

	if (!cma_dev)
		return -ENODEV;

found:
	cma_attach_to_dev(id_priv, cma_dev);
	addr = (struct sockaddr_ib *) cma_src_addr(id_priv);
	memcpy(&addr->sib_addr, &sgid, sizeof sgid);
	cma_translate_ib(addr, &id_priv->id.route.addr.dev_addr);
	return 0;
}
