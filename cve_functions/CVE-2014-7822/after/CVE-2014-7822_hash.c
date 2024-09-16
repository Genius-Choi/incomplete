static inline unsigned long hash(dev_t dev)
{
	return MAJOR(dev)+MINOR(dev);
}
