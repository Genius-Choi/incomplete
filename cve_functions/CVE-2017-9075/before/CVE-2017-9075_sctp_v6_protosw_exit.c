void sctp_v6_protosw_exit(void)
{
	inet6_unregister_protosw(&sctpv6_seqpacket_protosw);
	inet6_unregister_protosw(&sctpv6_stream_protosw);
	proto_unregister(&sctpv6_prot);
}
