int rdma_resolve_addr(struct rdma_cm_id *id, struct sockaddr *src_addr,
		      struct sockaddr *dst_addr, int timeout_ms)
{
	struct rdma_id_private *id_priv;
	int ret;

	id_priv = container_of(id, struct rdma_id_private, id);
	if (id_priv->state == RDMA_CM_IDLE) {
		ret = cma_bind_addr(id, src_addr, dst_addr);
		if (ret)
			return ret;
	}

	if (cma_family(id_priv) != dst_addr->sa_family)
		return -EINVAL;

	if (!cma_comp_exch(id_priv, RDMA_CM_ADDR_BOUND, RDMA_CM_ADDR_QUERY))
		return -EINVAL;

	atomic_inc(&id_priv->refcount);
	memcpy(cma_dst_addr(id_priv), dst_addr, rdma_addr_size(dst_addr));
	if (cma_any_addr(dst_addr)) {
		ret = cma_resolve_loopback(id_priv);
	} else {
		if (dst_addr->sa_family == AF_IB) {
			ret = cma_resolve_ib_addr(id_priv);
		} else {
			ret = rdma_resolve_ip(&addr_client, cma_src_addr(id_priv),
					      dst_addr, &id->route.addr.dev_addr,
					      timeout_ms, addr_handler, id_priv);
		}
	}
	if (ret)
		goto err;

	return 0;
err:
	cma_comp_exch(id_priv, RDMA_CM_ADDR_QUERY, RDMA_CM_ADDR_BOUND);
	cma_deref_id(id_priv);
	return ret;
}
