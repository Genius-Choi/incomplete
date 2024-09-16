gluster_compare_hosts(gluster_hostdef *src_server, gluster_hostdef *dst_server)
{
	if (src_server->type != dst_server->type)
		return false;

	switch (src_server->type) {
		case GLUSTER_TRANSPORT_UNIX:
			if (!strcmp(src_server->u.uds.socket, dst_server->u.uds.socket))
				return true;
			break;
		case GLUSTER_TRANSPORT_TCP:
		case GLUSTER_TRANSPORT_RDMA:
			if (!strcmp(src_server->u.inet.addr, dst_server->u.inet.addr)
					&&
				!strcmp(src_server->u.inet.port, dst_server->u.inet.port))
				return true;
			break;
		case GLUSTER_TRANSPORT__MAX:
			break;
	}

    return false;
}
