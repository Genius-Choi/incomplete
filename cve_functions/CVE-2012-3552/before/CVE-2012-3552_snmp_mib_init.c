int snmp_mib_init(void __percpu *ptr[2], size_t mibsize, size_t align)
{
	BUG_ON(ptr == NULL);
	ptr[0] = __alloc_percpu(mibsize, align);
	if (!ptr[0])
		goto err0;
	ptr[1] = __alloc_percpu(mibsize, align);
	if (!ptr[1])
		goto err1;
	return 0;
err1:
	free_percpu(ptr[0]);
	ptr[0] = NULL;
err0:
	return -ENOMEM;
}
