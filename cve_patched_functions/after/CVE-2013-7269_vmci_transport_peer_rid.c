static u32 vmci_transport_peer_rid(u32 peer_cid)
{
	if (VMADDR_CID_HYPERVISOR == peer_cid)
		return VMCI_TRANSPORT_HYPERVISOR_PACKET_RID;

	return VMCI_TRANSPORT_PACKET_RID;
}
