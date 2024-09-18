dns_resolver_preparse(struct key_preparsed_payload *prep)
{
	struct user_key_payload *upayload;
	unsigned long derrno;
	int ret;
	int datalen = prep->datalen, result_len = 0;
	const char *data = prep->data, *end, *opt;

	kenter("'%*.*s',%u", datalen, datalen, data, datalen);

	if (datalen <= 1 || !data || data[datalen - 1] != '\0')
		return -EINVAL;
	datalen--;

	/* deal with any options embedded in the data */
	end = data + datalen;
	opt = memchr(data, '#', datalen);
	if (!opt) {
		/* no options: the entire data is the result */
		kdebug("no options");
		result_len = datalen;
	} else {
		const char *next_opt;

		result_len = opt - data;
		opt++;
		kdebug("options: '%s'", opt);
		do {
			const char *eq;
			int opt_len, opt_nlen, opt_vlen, tmp;

			next_opt = memchr(opt, '#', end - opt) ?: end;
			opt_len = next_opt - opt;
			if (!opt_len) {
				printk(KERN_WARNING
				       "Empty option to dns_resolver key\n");
				return -EINVAL;
			}

			eq = memchr(opt, '=', opt_len) ?: end;
			opt_nlen = eq - opt;
			eq++;
			opt_vlen = next_opt - eq; /* will be -1 if no value */

			tmp = opt_vlen >= 0 ? opt_vlen : 0;
			kdebug("option '%*.*s' val '%*.*s'",
			       opt_nlen, opt_nlen, opt, tmp, tmp, eq);

			/* see if it's an error number representing a DNS error
			 * that's to be recorded as the result in this key */
			if (opt_nlen == sizeof(DNS_ERRORNO_OPTION) - 1 &&
			    memcmp(opt, DNS_ERRORNO_OPTION, opt_nlen) == 0) {
				kdebug("dns error number option");
				if (opt_vlen <= 0)
					goto bad_option_value;

				ret = kstrtoul(eq, 10, &derrno);
				if (ret < 0)
					goto bad_option_value;

				if (derrno < 1 || derrno > 511)
					goto bad_option_value;

				kdebug("dns error no. = %lu", derrno);
				prep->type_data[0] = ERR_PTR(-derrno);
				continue;
			}

		bad_option_value:
			printk(KERN_WARNING
			       "Option '%*.*s' to dns_resolver key:"
			       " bad/missing value\n",
			       opt_nlen, opt_nlen, opt);
			return -EINVAL;
		} while (opt = next_opt + 1, opt < end);
	}

	/* don't cache the result if we're caching an error saying there's no
	 * result */
	if (prep->type_data[0]) {
		kleave(" = 0 [h_error %ld]", PTR_ERR(prep->type_data[0]));
		return 0;
	}

	kdebug("store result");
	prep->quotalen = result_len;

	upayload = kmalloc(sizeof(*upayload) + result_len + 1, GFP_KERNEL);
	if (!upayload) {
		kleave(" = -ENOMEM");
		return -ENOMEM;
	}

	upayload->datalen = result_len;
	memcpy(upayload->data, data, result_len);
	upayload->data[result_len] = '\0';

	prep->payload[0] = upayload;
	kleave(" = 0");
	return 0;
}
