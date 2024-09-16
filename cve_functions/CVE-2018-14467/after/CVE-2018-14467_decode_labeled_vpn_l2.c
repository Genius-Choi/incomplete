decode_labeled_vpn_l2(netdissect_options *ndo,
                      const u_char *pptr, char *buf, u_int buflen)
{
        int plen,tlen,stringlen,tlv_type,tlv_len,ttlv_len;

	ND_TCHECK2(pptr[0], 2);
        plen=EXTRACT_16BITS(pptr);
        tlen=plen;
        pptr+=2;
	/* Old and new L2VPN NLRI share AFI/SAFI
         *   -> Assume a 12 Byte-length NLRI is auto-discovery-only
         *      and > 17 as old format. Complain for the middle case
         */
        if (plen==12) {
	    /* assume AD-only with RD, BGPNH */
	    ND_TCHECK2(pptr[0],12);
	    buf[0]='\0';
	    stringlen=snprintf(buf, buflen, "RD: %s, BGPNH: %s",
			       bgp_vpn_rd_print(ndo, pptr),
			       ipaddr_string(ndo, pptr+8)
			       );
	    UPDATE_BUF_BUFLEN(buf, buflen, stringlen);
	    pptr+=12;
	    tlen-=12;
	    return plen;
        } else if (plen>17) {
	    /* assume old format */
	    /* RD, ID, LBLKOFF, LBLBASE */

	    ND_TCHECK2(pptr[0],15);
	    buf[0]='\0';
	    stringlen=snprintf(buf, buflen, "RD: %s, CE-ID: %u, Label-Block Offset: %u, Label Base %u",
			       bgp_vpn_rd_print(ndo, pptr),
			       EXTRACT_16BITS(pptr+8),
			       EXTRACT_16BITS(pptr+10),
			       EXTRACT_24BITS(pptr+12)>>4); /* the label is offsetted by 4 bits so lets shift it right */
	    UPDATE_BUF_BUFLEN(buf, buflen, stringlen);
	    pptr+=15;
	    tlen-=15;

	    /* ok now the variable part - lets read out TLVs*/
	    while (tlen>0) {
		if (tlen < 3)
		    return -1;
		ND_TCHECK2(pptr[0], 3);
		tlv_type=*pptr++;
		tlv_len=EXTRACT_16BITS(pptr);
		ttlv_len=tlv_len;
		pptr+=2;

		switch(tlv_type) {
		case 1:
		    if (buflen!=0) {
			stringlen=snprintf(buf,buflen, "\n\t\tcircuit status vector (%u) length: %u: 0x",
					   tlv_type,
					   tlv_len);
			UPDATE_BUF_BUFLEN(buf, buflen, stringlen);
		    }
		    ttlv_len=ttlv_len/8+1; /* how many bytes do we need to read ? */
		    while (ttlv_len>0) {
			ND_TCHECK(pptr[0]);
			if (buflen!=0) {
			    stringlen=snprintf(buf,buflen, "%02x",*pptr++);
			    UPDATE_BUF_BUFLEN(buf, buflen, stringlen);
			}
			ttlv_len--;
		    }
		    break;
		default:
		    if (buflen!=0) {
			stringlen=snprintf(buf,buflen, "\n\t\tunknown TLV #%u, length: %u",
					   tlv_type,
					   tlv_len);
			UPDATE_BUF_BUFLEN(buf, buflen, stringlen);
		    }
		    break;
		}
		tlen-=(tlv_len<<3); /* the tlv-length is expressed in bits so lets shift it right */
	    }
	    return plen+2;

        } else {
	    /* complain bitterly ? */
	    /* fall through */
            goto trunc;
        }

trunc:
        return -2;
}
