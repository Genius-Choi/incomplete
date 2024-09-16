destroyAssociationKey(PRIVATE_ASSOCIATIONKEY ** key)
{
    if (*key && (*key)->connection) delete (*key)->connection;
    free(*key);
    *key = NULL;
}
