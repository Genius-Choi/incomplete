static int vp8_decode_block_coeffs_internal(VP56RangeCoder *r,
                                            int16_t block[16],
                                            uint8_t probs[16][3][NUM_DCT_TOKENS - 1],
                                            int i, uint8_t *token_prob,
                                            int16_t qmul[2])
{
    return decode_block_coeffs_internal(r, block, probs, i,
                                        token_prob, qmul, ff_zigzag_scan, IS_VP8);
}
