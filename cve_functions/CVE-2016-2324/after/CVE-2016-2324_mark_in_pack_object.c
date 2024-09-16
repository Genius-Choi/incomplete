static void mark_in_pack_object(struct object *object, struct packed_git *p, struct in_pack *in_pack)
{
	in_pack->array[in_pack->nr].offset = find_pack_entry_one(object->oid.hash, p);
	in_pack->array[in_pack->nr].object = object;
	in_pack->nr++;
}
