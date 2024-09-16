eap_send_response(esp, id, typenum, str, lenstr)
eap_state *esp;
u_char id;
u_char typenum;
u_char *str;
int lenstr;
{
	u_char *outp;
	int msglen;

	outp = outpacket_buf;

	MAKEHEADER(outp, PPP_EAP);

	PUTCHAR(EAP_RESPONSE, outp);
	PUTCHAR(id, outp);
	esp->es_client.ea_id = id;
	msglen = EAP_HEADERLEN + sizeof (u_char) + lenstr;
	PUTSHORT(msglen, outp);
	PUTCHAR(typenum, outp);
	if (lenstr > 0) {
		BCOPY(str, outp, lenstr);
	}

	output(esp->es_unit, outpacket_buf, PPP_HDRLEN + msglen);
}
