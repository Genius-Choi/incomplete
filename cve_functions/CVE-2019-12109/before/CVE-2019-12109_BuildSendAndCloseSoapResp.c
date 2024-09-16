BuildSendAndCloseSoapResp(struct upnphttp * h,
                          const char * body, int bodylen)
{
	static const char beforebody[] =
		"<?xml version=\"1.0\"?>\r\n"
		"<s:Envelope xmlns:s=\"http://schemas.xmlsoap.org/soap/envelope/\" "
		"s:encodingStyle=\"http://schemas.xmlsoap.org/soap/encoding/\">"
		"<s:Body>";

	static const char afterbody[] =
		"</s:Body>"
		"</s:Envelope>\r\n";

	int r = BuildHeader_upnphttp(h, 200, "OK",  sizeof(beforebody) - 1
	                             + sizeof(afterbody) - 1 + bodylen );

	if(r >= 0) {
		memcpy(h->res_buf + h->res_buflen, beforebody, sizeof(beforebody) - 1);
		h->res_buflen += sizeof(beforebody) - 1;

		memcpy(h->res_buf + h->res_buflen, body, bodylen);
		h->res_buflen += bodylen;

		memcpy(h->res_buf + h->res_buflen, afterbody, sizeof(afterbody) - 1);
		h->res_buflen += sizeof(afterbody) - 1;
	} else {
		BuildResp2_upnphttp(h, 500, "Internal Server Error", NULL, 0);
	}

	SendRespAndClose_upnphttp(h);
}
