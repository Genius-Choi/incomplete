static irqreturn_t __init i8042_aux_test_irq(int irq, void *dev_id)
{
	unsigned long flags;
	unsigned char str, data;
	int ret = 0;

	spin_lock_irqsave(&i8042_lock, flags);
	str = i8042_read_status();
	if (str & I8042_STR_OBF) {
		data = i8042_read_data();
		dbg("%02x <- i8042 (aux_test_irq, %s)\n",
		    data, str & I8042_STR_AUXDATA ? "aux" : "kbd");
		if (i8042_irq_being_tested &&
		    data == 0xa5 && (str & I8042_STR_AUXDATA))
			complete(&i8042_aux_irq_delivered);
		ret = 1;
	}
	spin_unlock_irqrestore(&i8042_lock, flags);

	return IRQ_RETVAL(ret);
}
