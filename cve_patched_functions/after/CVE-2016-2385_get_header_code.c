char get_header_code(struct hdr_field *hf)
{
   switch(hf->type){
      case HDR_CALLID_T:
	 return 'i';
      case HDR_CONTACT_T:
	 return 'm';
      case HDR_CONTENTLENGTH_T:
	 return 'l';
      case HDR_CONTENTTYPE_T:
	 return 'c';
      case HDR_FROM_T:
	 return 'f';
      case HDR_SUBJECT_T:
	 return 's';
      case HDR_SUPPORTED_T:
	 return 'k';
      case HDR_TO_T:
	 return 't';
      case HDR_VIA_T:
	 return 'v';
      case HDR_ROUTE_T:
	 return 'r';
      case HDR_RECORDROUTE_T:
	 return 'R';
      case HDR_ALLOW_T:
	 return 'a';
      case HDR_ACCEPT_T:
	 return 'A';
      case HDR_CSEQ_T:
	 return 'S';
      case HDR_REFER_TO_T:
	 return 'o';
      case HDR_RPID_T:
	 return 'p';
      case HDR_EXPIRES_T:
	 return 'P';
      case HDR_AUTHORIZATION_T:
	 return 'H';
      case HDR_PROXYAUTH_T:
	 return 'z';
      default:
	 return 'x';
   }
   return 'x';
}
