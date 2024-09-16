static inline uint32_t __nlm_alloc_pid(struct nlm_host *host)
{
	uint32_t res;
	do {
		res = host->h_pidcount++;
	} while (nlm_pidbusy(host, res) < 0);
	return res;
}
