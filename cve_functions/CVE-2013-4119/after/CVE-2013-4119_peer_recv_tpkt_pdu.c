static int peer_recv_tpkt_pdu(freerdp_peer* client, wStream* s)
{
	rdpRdp* rdp;
	UINT16 length;
	UINT16 pduType;
	UINT16 pduLength;
	UINT16 pduSource;
	UINT16 channelId;
	UINT16 securityFlags;

	rdp = client->context->rdp;

	if (!rdp_read_header(rdp, s, &length, &channelId))
	{
		fprintf(stderr, "Incorrect RDP header.\n");
		return -1;
	}

	if (rdp->settings->DisableEncryption)
	{
		if (!rdp_read_security_header(s, &securityFlags))
			return -1;

		if (securityFlags & SEC_ENCRYPT)
		{
			if (!rdp_decrypt(rdp, s, length - 4, securityFlags))
			{
				fprintf(stderr, "rdp_decrypt failed\n");
				return -1;
			}
		}
	}

	if (channelId != MCS_GLOBAL_CHANNEL_ID)
	{
		if(!freerdp_channel_peer_process(client, s, channelId))
			return -1;
	}
	else
	{
		if (!rdp_read_share_control_header(s, &pduLength, &pduType, &pduSource))
			return -1;

		client->settings->PduSource = pduSource;

		switch (pduType)
		{
			case PDU_TYPE_DATA:
				if (!peer_recv_data_pdu(client, s))
					return -1;
				break;

			default:
				fprintf(stderr, "Client sent pduType %d\n", pduType);
				return -1;
		}
	}

	return 0;
}
