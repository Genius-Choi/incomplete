static uint16_t strto16(const char *str)
{
	unsigned long val = strtoul(str, NULL, 16);
	if (val > UINT16_MAX)
		exit(1);
	return (uint16_t)val;
}
