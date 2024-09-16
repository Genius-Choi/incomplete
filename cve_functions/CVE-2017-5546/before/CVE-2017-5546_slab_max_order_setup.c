static int __init slab_max_order_setup(char *str)
{
	get_option(&str, &slab_max_order);
	slab_max_order = slab_max_order < 0 ? 0 :
				min(slab_max_order, MAX_ORDER - 1);
	slab_max_order_set = true;

	return 1;
}
