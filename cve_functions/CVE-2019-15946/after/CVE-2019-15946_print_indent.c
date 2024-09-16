static void print_indent(size_t depth)
{
	for (; depth > 0; depth--) {
		putchar(' ');
	}
}
