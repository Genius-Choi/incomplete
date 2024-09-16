int mbedtls_ecp_is_zero( mbedtls_ecp_point *pt )
{
    return( mbedtls_mpi_cmp_int( &pt->Z, 0 ) == 0 );
}
