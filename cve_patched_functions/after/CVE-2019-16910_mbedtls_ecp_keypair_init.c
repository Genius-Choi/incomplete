void mbedtls_ecp_keypair_init( mbedtls_ecp_keypair *key )
{
    if( key == NULL )
        return;

    mbedtls_ecp_group_init( &key->grp );
    mbedtls_mpi_init( &key->d );
    mbedtls_ecp_point_init( &key->Q );
}
