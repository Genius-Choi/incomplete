static int __do_proc_doulongvec_minmax(void *data, struct ctl_table *table, int write,
				     void __user *buffer,
				     size_t *lenp, loff_t *ppos,
				     unsigned long convmul,
				     unsigned long convdiv)
{
	unsigned long *i, *min, *max;
	int vleft, first = 1, err = 0;
	unsigned long page = 0;
	size_t left;
	char *kbuf;

	if (!data || !table->maxlen || !*lenp || (*ppos && !write)) {
		*lenp = 0;
		return 0;
	}

	i = (unsigned long *) data;
	min = (unsigned long *) table->extra1;
	max = (unsigned long *) table->extra2;
	vleft = table->maxlen / sizeof(unsigned long);
	left = *lenp;

	if (write) {
		if (left > PAGE_SIZE - 1)
			left = PAGE_SIZE - 1;
		page = __get_free_page(GFP_TEMPORARY);
		kbuf = (char *) page;
		if (!kbuf)
			return -ENOMEM;
		if (copy_from_user(kbuf, buffer, left)) {
			err = -EFAULT;
			goto free;
		}
		kbuf[left] = 0;
	}

	for (; left && vleft--; i++, first = 0) {
		unsigned long val;

		if (write) {
			bool neg;

			left -= proc_skip_spaces(&kbuf);

			err = proc_get_long(&kbuf, &left, &val, &neg,
					     proc_wspace_sep,
					     sizeof(proc_wspace_sep), NULL);
			if (err)
				break;
			if (neg)
				continue;
			if ((min && val < *min) || (max && val > *max))
				continue;
			*i = val;
		} else {
			val = convdiv * (*i) / convmul;
			if (!first)
				err = proc_put_char(&buffer, &left, '\t');
			err = proc_put_long(&buffer, &left, val, false);
			if (err)
				break;
		}
	}

	if (!write && !first && left && !err)
		err = proc_put_char(&buffer, &left, '\n');
	if (write && !err)
		left -= proc_skip_spaces(&kbuf);
free:
	if (write) {
		free_page(page);
		if (first)
			return err ? : -EINVAL;
	}
	*lenp -= left;
	*ppos += *lenp;
	return err;
}
