static u32 tg3_ape_read32(struct tg3 *tp, u32 off)
{
	return readl(tp->aperegs + off);
}
