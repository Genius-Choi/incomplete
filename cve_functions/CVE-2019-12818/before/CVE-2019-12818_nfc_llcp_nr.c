static u8 nfc_llcp_nr(struct sk_buff *pdu)
{
	return pdu->data[2] & 0xf;
}
