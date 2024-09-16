static int i8042_flush(void)
{
	unsigned long flags;
	unsigned char data, str;
	int count = 0;
	int retval = 0;

	spin_lock_irqsave(&i8042_lock, flags);

	while ((str = i8042_read_status()) & I8042_STR_OBF) {
		if (count++ < I8042_BUFFER_SIZE) {
			udelay(50);
			data = i8042_read_data();
			dbg("%02x <- i8042 (flush, %s)\n",
			    data, str & I8042_STR_AUXDATA ? "aux" : "kbd");
		} else {
			retval = -EIO;
			break;
		}
	}

	spin_unlock_irqrestore(&i8042_lock, flags);

	return retval;
}
