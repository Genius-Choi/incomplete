static void read_pcm_samples(thread_context* tctx, int x0, int y0, int log2CbSize)
{
  bitreader br;
  br.data            = tctx->cabac_decoder.bitstream_curr;
  br.bytes_remaining = tctx->cabac_decoder.bitstream_end - tctx->cabac_decoder.bitstream_curr;
  br.nextbits = 0;
  br.nextbits_cnt = 0;


  if (tctx->img->high_bit_depth(0)) {
    read_pcm_samples_internal<uint16_t>(tctx,x0,y0,log2CbSize,0,br);
  } else {
    read_pcm_samples_internal<uint8_t>(tctx,x0,y0,log2CbSize,0,br);
  }

  if (tctx->img->get_sps().ChromaArrayType != CHROMA_MONO) {
    if (tctx->img->high_bit_depth(1)) {
      read_pcm_samples_internal<uint16_t>(tctx,x0,y0,log2CbSize,1,br);
      read_pcm_samples_internal<uint16_t>(tctx,x0,y0,log2CbSize,2,br);
    } else {
      read_pcm_samples_internal<uint8_t>(tctx,x0,y0,log2CbSize,1,br);
      read_pcm_samples_internal<uint8_t>(tctx,x0,y0,log2CbSize,2,br);
    }
  }

  prepare_for_CABAC(&br);
  tctx->cabac_decoder.bitstream_curr = br.data;
  init_CABAC_decoder_2(&tctx->cabac_decoder);
}
