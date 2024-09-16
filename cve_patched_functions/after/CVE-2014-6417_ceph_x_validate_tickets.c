static void ceph_x_validate_tickets(struct ceph_auth_client *ac, int *pneed)
{
	int want = ac->want_keys;
	struct ceph_x_info *xi = ac->private;
	int service;

	*pneed = ac->want_keys & ~(xi->have_keys);

	for (service = 1; service <= want; service <<= 1) {
		struct ceph_x_ticket_handler *th;

		if (!(ac->want_keys & service))
			continue;

		if (*pneed & service)
			continue;

		th = get_ticket_handler(ac, service);

		if (IS_ERR(th)) {
			*pneed |= service;
			continue;
		}

		if (get_seconds() >= th->renew_after)
			*pneed |= service;
		if (get_seconds() >= th->expires)
			xi->have_keys &= ~service;
	}
}
