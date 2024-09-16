sk_deep_copy(void *sk_void, void *copy_func_void, void *free_func_void)
{
	_STACK *sk = sk_void;
	void *(*copy_func)(void *) = copy_func_void;
	void (*free_func)(void *) = free_func_void;
	_STACK *ret = sk_dup(sk);
	size_t i;

	if (ret == NULL)
		return NULL;

	for (i = 0; i < ret->num; i++) {
		if (ret->data[i] == NULL)
			continue;
		ret->data[i] = copy_func(ret->data[i]);
		if (ret->data[i] == NULL) {
			size_t j;
			for (j = 0; j < i; j++) {
				if (ret->data[j] != NULL)
					free_func(ret->data[j]);
			}
			sk_free(ret);
			return NULL;
		}
	}

	return ret;
}
