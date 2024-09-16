static int __svc_register(struct net *net, const char *progname,
			  const u32 program, const u32 version,
			  const int family,
			  const unsigned short protocol,
			  const unsigned short port)
{
	int error = -EAFNOSUPPORT;

	switch (family) {
	case PF_INET:
		error = __svc_rpcb_register4(net, program, version,
						protocol, port);
		break;
#if IS_ENABLED(CONFIG_IPV6)
	case PF_INET6:
		error = __svc_rpcb_register6(net, program, version,
						protocol, port);
#endif
	}

	return error;
}
