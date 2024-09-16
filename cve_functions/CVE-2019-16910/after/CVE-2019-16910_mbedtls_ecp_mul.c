int mbedtls_ecp_mul( mbedtls_ecp_group *grp, mbedtls_ecp_point *R,
             const mbedtls_mpi *m, const mbedtls_ecp_point *P,
             int (*f_rng)(void *, unsigned char *, size_t), void *p_rng )
{
    int ret = MBEDTLS_ERR_ECP_BAD_INPUT_DATA;
#if defined(MBEDTLS_ECP_INTERNAL_ALT)
    char is_grp_capable = 0;
#endif

    /* Common sanity checks */
    if( mbedtls_mpi_cmp_int( &P->Z, 1 ) != 0 )
        return( MBEDTLS_ERR_ECP_BAD_INPUT_DATA );

    if( ( ret = mbedtls_ecp_check_privkey( grp, m ) ) != 0 ||
        ( ret = mbedtls_ecp_check_pubkey( grp, P ) ) != 0 )
        return( ret );

#if defined(MBEDTLS_ECP_INTERNAL_ALT)
    if ( is_grp_capable = mbedtls_internal_ecp_grp_capable( grp )  )
    {
        MBEDTLS_MPI_CHK( mbedtls_internal_ecp_init( grp ) );
    }

#endif /* MBEDTLS_ECP_INTERNAL_ALT */
#if defined(ECP_MONTGOMERY)
    if( ecp_get_type( grp ) == ECP_TYPE_MONTGOMERY )
        ret = ecp_mul_mxz( grp, R, m, P, f_rng, p_rng );

#endif
#if defined(ECP_SHORTWEIERSTRASS)
    if( ecp_get_type( grp ) == ECP_TYPE_SHORT_WEIERSTRASS )
        ret = ecp_mul_comb( grp, R, m, P, f_rng, p_rng );

#endif
#if defined(MBEDTLS_ECP_INTERNAL_ALT)
cleanup:

    if ( is_grp_capable )
    {
        mbedtls_internal_ecp_free( grp );
    }

#endif /* MBEDTLS_ECP_INTERNAL_ALT */
    return( ret );
}
