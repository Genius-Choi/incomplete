static void set_class_tag(struct rtable *rt, u32 tag)
{
	if (!(rt->dst.tclassid & 0xFFFF))
		rt->dst.tclassid |= tag & 0xFFFF;
	if (!(rt->dst.tclassid & 0xFFFF0000))
		rt->dst.tclassid |= tag & 0xFFFF0000;
}
