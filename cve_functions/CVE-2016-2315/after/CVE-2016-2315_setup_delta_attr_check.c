static void setup_delta_attr_check(struct git_attr_check *check)
{
	static struct git_attr *attr_delta;

	if (!attr_delta)
		attr_delta = git_attr("delta");

	check[0].attr = attr_delta;
}
