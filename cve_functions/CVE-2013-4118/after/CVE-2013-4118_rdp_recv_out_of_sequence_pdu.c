BOOL rdp_recv_out_of_sequence_pdu(rdpRdp* rdp, STREAM* s)
{
	UINT16 type;
	UINT16 length;
	UINT16 channelId;

	if (!rdp_read_share_control_header(s, &length, &type, &channelId))
		return FALSE;

	if (type == PDU_TYPE_DATA)
	{
		return (rdp_recv_data_pdu(rdp, s) < 0) ? FALSE : TRUE;
	}
	else if (type == PDU_TYPE_SERVER_REDIRECTION)
	{
		return rdp_recv_enhanced_security_redirection_packet(rdp, s);
	}
	else
	{
		return FALSE;
	}
}
