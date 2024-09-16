static void shadow_walk_next(struct kvm_shadow_walk_iterator *iterator)
{
	return __shadow_walk_next(iterator, *iterator->sptep);
}
