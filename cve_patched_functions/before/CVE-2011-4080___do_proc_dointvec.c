static int __do_proc_dointvec(void *tbl_data, struct ctl_table *table,
		  int write, void __user *buffer,
		  size_t *lenp, loff_t *ppos,
		  int (*conv)(bool *negp, unsigned long *lvalp, int *valp,
			      int write, void *data),
		  void *data)
{
	int *i, vleft, first = 1, err = 0;
	unsigned long page = 0;
	size_t left;
	char *kbuf;
	
	if (!tbl_data || !table->maxlen || !*lenp || (*ppos && !write)) {
		*lenp = 0;
		return 0;
	}
	
	i = (int *) tbl_data;
	vleft = table->maxlen / sizeof(*i);
	left = *lenp;

	if (!conv)
		conv = do_proc_dointvec_conv;

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

	for (; left && vleft--; i++, first=0) {
		unsigned long lval;
		bool neg;

		if (write) {
			left -= proc_skip_spaces(&kbuf);

			if (!left)
				break;
			err = proc_get_long(&kbuf, &left, &lval, &neg,
					     proc_wspace_sep,
					     sizeof(proc_wspace_sep), NULL);
			if (err)
				break;
			if (conv(&neg, &lval, i, 1, data)) {
				err = -EINVAL;
				break;
			}
		} else {
			if (conv(&neg, &lval, i, 0, data)) {
				err = -EINVAL;
				break;
			}
			if (!first)
				err = proc_put_char(&buffer, &left, '\t');
			if (err)
				break;
			err = proc_put_long(&buffer, &left, lval, neg);
			if (err)
				break;
		}
	}

	if (!write && !first && left && !err)
		err = proc_put_char(&buffer, &left, '\n');
	if (write && !err && left)
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
