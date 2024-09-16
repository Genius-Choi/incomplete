static u8 nfc_llcp_ssap(struct sk_buff *pdu)
{
	return pdu->data[1] & 0x3f;
}
