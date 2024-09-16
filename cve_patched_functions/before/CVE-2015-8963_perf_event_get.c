struct perf_event *perf_event_get(unsigned int fd)
{
	int err;
	struct fd f;
	struct perf_event *event;

	err = perf_fget_light(fd, &f);
	if (err)
		return ERR_PTR(err);

	event = f.file->private_data;
	atomic_long_inc(&event->refcount);
	fdput(f);

	return event;
}
