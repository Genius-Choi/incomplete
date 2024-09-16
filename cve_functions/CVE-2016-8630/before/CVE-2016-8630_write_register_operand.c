static void write_register_operand(struct operand *op)
{
	return assign_register(op->addr.reg, op->val, op->bytes);
}
