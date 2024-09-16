void i8042_unlock_chip(void)
{
	mutex_unlock(&i8042_mutex);
}
