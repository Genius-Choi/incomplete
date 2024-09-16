static int _find_waiter(struct waiter *w, uint32_t *jp)
{
	return (w->jobid == *jp);
}
