static void try_to_free_from_threads(size_t size)
{
	read_lock();
	release_pack_memory(size);
	read_unlock();
}
