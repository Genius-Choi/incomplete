static void set_track(struct kmem_cache *s, void *object,
				enum track_item alloc, void *addr)
{
	struct track *p;

	if (s->offset)
		p = object + s->offset + sizeof(void *);
	else
		p = object + s->inuse;

	p += alloc;
	if (addr) {
		p->addr = addr;
		p->cpu = smp_processor_id();
		p->pid = current ? current->pid : -1;
		p->when = jiffies;
	} else
		memset(p, 0, sizeof(struct track));
}
