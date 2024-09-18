smb_fdata1(netdissect_options *ndo,
           const u_char *buf, const char *fmt, const u_char *maxbuf,
           int unicodestr)
{
    int reverse = 0;
    const char *attrib_fmt = "READONLY|HIDDEN|SYSTEM|VOLUME|DIR|ARCHIVE|";

    while (*fmt && buf<maxbuf) {
	switch (*fmt) {
	case 'a':
	    ND_TCHECK(buf[0]);
	    write_bits(ndo, buf[0], attrib_fmt);
	    buf++;
	    fmt++;
	    break;

	case 'A':
	    ND_TCHECK2(buf[0], 2);
	    write_bits(ndo, EXTRACT_LE_16BITS(buf), attrib_fmt);
	    buf += 2;
	    fmt++;
	    break;

	case '{':
	  {
	    char bitfmt[128];
	    char *p;
	    int l;

	    p = strchr(++fmt, '}');
	    l = PTR_DIFF(p, fmt);

	    if ((unsigned int)l > sizeof(bitfmt) - 1)
		    l = sizeof(bitfmt)-1;

	    strncpy(bitfmt, fmt, l);
	    bitfmt[l] = '\0';
	    fmt = p + 1;
	    ND_TCHECK(buf[0]);
	    write_bits(ndo, buf[0], bitfmt);
	    buf++;
	    break;
	  }

	case 'P':
	  {
	    int l = atoi(fmt + 1);
	    ND_TCHECK2(buf[0], l);
	    buf += l;
	    fmt++;
	    while (isdigit((unsigned char)*fmt))
		fmt++;
	    break;
	  }
	case 'r':
	    reverse = !reverse;
	    fmt++;
	    break;
	case 'b':
	  {
	    unsigned int x;
	    ND_TCHECK(buf[0]);
	    x = buf[0];
	    ND_PRINT((ndo, "%u (0x%x)", x, x));
	    buf += 1;
	    fmt++;
	    break;
	  }
	case 'd':
	  {
	    unsigned int x;
	    ND_TCHECK2(buf[0], 2);
	    x = reverse ? EXTRACT_16BITS(buf) :
			  EXTRACT_LE_16BITS(buf);
	    ND_PRINT((ndo, "%d (0x%x)", x, x));
	    buf += 2;
	    fmt++;
	    break;
	  }
	case 'D':
	  {
	    unsigned int x;
	    ND_TCHECK2(buf[0], 4);
	    x = reverse ? EXTRACT_32BITS(buf) :
			  EXTRACT_LE_32BITS(buf);
	    ND_PRINT((ndo, "%d (0x%x)", x, x));
	    buf += 4;
	    fmt++;
	    break;
	  }
	case 'L':
	  {
	    uint64_t x;
	    ND_TCHECK2(buf[0], 8);
	    x = reverse ? EXTRACT_64BITS(buf) :
			  EXTRACT_LE_64BITS(buf);
	    ND_PRINT((ndo, "%" PRIu64 " (0x%" PRIx64 ")", x, x));
	    buf += 8;
	    fmt++;
	    break;
	  }
	case 'M':
	  {
	    /* Weird mixed-endian length values in 64-bit locks */
	    uint32_t x1, x2;
	    uint64_t x;
	    ND_TCHECK2(buf[0], 8);
	    x1 = reverse ? EXTRACT_32BITS(buf) :
			   EXTRACT_LE_32BITS(buf);
	    x2 = reverse ? EXTRACT_32BITS(buf + 4) :
			   EXTRACT_LE_32BITS(buf + 4);
	    x = (((uint64_t)x1) << 32) | x2;
	    ND_PRINT((ndo, "%" PRIu64 " (0x%" PRIx64 ")", x, x));
	    buf += 8;
	    fmt++;
	    break;
	  }
	case 'B':
	  {
	    unsigned int x;
	    ND_TCHECK(buf[0]);
	    x = buf[0];
	    ND_PRINT((ndo, "0x%X", x));
	    buf += 1;
	    fmt++;
	    break;
	  }
	case 'w':
	  {
	    unsigned int x;
	    ND_TCHECK2(buf[0], 2);
	    x = reverse ? EXTRACT_16BITS(buf) :
			  EXTRACT_LE_16BITS(buf);
	    ND_PRINT((ndo, "0x%X", x));
	    buf += 2;
	    fmt++;
	    break;
	  }
	case 'W':
	  {
	    unsigned int x;
	    ND_TCHECK2(buf[0], 4);
	    x = reverse ? EXTRACT_32BITS(buf) :
			  EXTRACT_LE_32BITS(buf);
	    ND_PRINT((ndo, "0x%X", x));
	    buf += 4;
	    fmt++;
	    break;
	  }
	case 'l':
	  {
	    fmt++;
	    switch (*fmt) {

	    case 'b':
		ND_TCHECK(buf[0]);
		stringlen = buf[0];
		ND_PRINT((ndo, "%u", stringlen));
		buf += 1;
		break;

	    case 'd':
		ND_TCHECK2(buf[0], 2);
		stringlen = reverse ? EXTRACT_16BITS(buf) :
				      EXTRACT_LE_16BITS(buf);
		ND_PRINT((ndo, "%u", stringlen));
		buf += 2;
		break;

	    case 'D':
		ND_TCHECK2(buf[0], 4);
		stringlen = reverse ? EXTRACT_32BITS(buf) :
				      EXTRACT_LE_32BITS(buf);
		ND_PRINT((ndo, "%u", stringlen));
		buf += 4;
		break;
	    }
	    fmt++;
	    break;
	  }
	case 'S':
	case 'R':	/* like 'S', but always ASCII */
	  {
	    /*XXX unistr() */
	    const char *s;
	    uint32_t len;

	    len = 0;
	    s = unistr(ndo, buf, &len, (*fmt == 'R') ? 0 : unicodestr);
	    if (s == NULL)
		goto trunc;
	    ND_PRINT((ndo, "%s", s));
	    buf += len;
	    fmt++;
	    break;
	  }
	case 'Z':
	case 'Y':	/* like 'Z', but always ASCII */
	  {
	    const char *s;
	    uint32_t len;

	    ND_TCHECK(*buf);
	    if (*buf != 4 && *buf != 2) {
		ND_PRINT((ndo, "Error! ASCIIZ buffer of type %u", *buf));
		return maxbuf;	/* give up */
	    }
	    len = 0;
	    s = unistr(ndo, buf + 1, &len, (*fmt == 'Y') ? 0 : unicodestr);
	    if (s == NULL)
		goto trunc;
	    ND_PRINT((ndo, "%s", s));
	    buf += len + 1;
	    fmt++;
	    break;
	  }
	case 's':
	  {
	    int l = atoi(fmt + 1);
	    ND_TCHECK2(*buf, l);
	    ND_PRINT((ndo, "%-*.*s", l, l, buf));
	    buf += l;
	    fmt++;
	    while (isdigit((unsigned char)*fmt))
		fmt++;
	    break;
	  }
	case 'c':
	  {
	    ND_TCHECK2(*buf, stringlen);
	    ND_PRINT((ndo, "%-*.*s", (int)stringlen, (int)stringlen, buf));
	    buf += stringlen;
	    fmt++;
	    while (isdigit((unsigned char)*fmt))
		fmt++;
	    break;
	  }
	case 'C':
	  {
	    const char *s;
	    s = unistr(ndo, buf, &stringlen, unicodestr);
	    if (s == NULL)
		goto trunc;
	    ND_PRINT((ndo, "%s", s));
	    buf += stringlen;
	    fmt++;
	    break;
	  }
	case 'h':
	  {
	    int l = atoi(fmt + 1);
	    ND_TCHECK2(*buf, l);
	    while (l--)
		ND_PRINT((ndo, "%02x", *buf++));
	    fmt++;
	    while (isdigit((unsigned char)*fmt))
		fmt++;
	    break;
	  }
	case 'n':
	  {
	    int t = atoi(fmt+1);
	    char nbuf[255];
	    int name_type;
	    int len;

	    switch (t) {
	    case 1:
		name_type = name_extract(ndo, startbuf, PTR_DIFF(buf, startbuf),
		    maxbuf, nbuf);
		if (name_type < 0)
		    goto trunc;
		len = name_len(ndo, buf, maxbuf);
		if (len < 0)
		    goto trunc;
		buf += len;
		ND_PRINT((ndo, "%-15.15s NameType=0x%02X (%s)", nbuf, name_type,
		    name_type_str(name_type)));
		break;
	    case 2:
		ND_TCHECK(buf[15]);
		name_type = buf[15];
		ND_PRINT((ndo, "%-15.15s NameType=0x%02X (%s)", buf, name_type,
		    name_type_str(name_type)));
		buf += 16;
		break;
	    }
	    fmt++;
	    while (isdigit((unsigned char)*fmt))
		fmt++;
	    break;
	  }
	case 'T':
	  {
	    time_t t;
	    struct tm *lt;
	    const char *tstring;
	    uint32_t x;

	    switch (atoi(fmt + 1)) {
	    case 1:
		ND_TCHECK2(buf[0], 4);
		x = EXTRACT_LE_32BITS(buf);
		if (x == 0 || x == 0xFFFFFFFF)
		    t = 0;
		else
		    t = make_unix_date(buf);
		buf += 4;
		break;
	    case 2:
		ND_TCHECK2(buf[0], 4);
		x = EXTRACT_LE_32BITS(buf);
		if (x == 0 || x == 0xFFFFFFFF)
		    t = 0;
		else
		    t = make_unix_date2(buf);
		buf += 4;
		break;
	    case 3:
		ND_TCHECK2(buf[0], 8);
		t = interpret_long_date(buf);
		buf += 8;
		break;
	    default:
		t = 0;
		break;
	    }
	    if (t != 0) {
		lt = localtime(&t);
		if (lt != NULL)
		    tstring = asctime(lt);
		else
		    tstring = "(Can't convert time)\n";
	    } else
		tstring = "NULL\n";
	    ND_PRINT((ndo, "%s", tstring));
	    fmt++;
	    while (isdigit((unsigned char)*fmt))
		fmt++;
	    break;
	  }
	default:
	    ND_PRINT((ndo, "%c", *fmt));
	    fmt++;
	    break;
	}
    }

    if (buf >= maxbuf && *fmt)
	ND_PRINT((ndo, "END OF BUFFER\n"));

    return(buf);

trunc:
    ND_PRINT((ndo, "\n"));
    ND_PRINT((ndo, "WARNING: Short packet. Try increasing the snap length\n"));
    return(NULL);
}
