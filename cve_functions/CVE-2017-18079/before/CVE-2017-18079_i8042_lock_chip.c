void i8042_lock_chip(void)
{
	mutex_lock(&i8042_mutex);
}
