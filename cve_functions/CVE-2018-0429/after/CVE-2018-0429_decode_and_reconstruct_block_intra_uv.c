static void decode_and_reconstruct_block_intra_uv (SAMPLE *rec_u, SAMPLE *rec_v, int stride, int size, int qp, SAMPLE *pblock_u, SAMPLE *pblock_v, int16_t *coeffq_u, int16_t *coeffq_v,
                                                   int tb_split, int upright_available,int downleft_available, intra_mode_t intra_mode,int ypos,int xpos,int width,int comp, int bitdepth,
                                                   qmtx_t ** iwmatrix, SAMPLE *pblock_y, SAMPLE *rec_y, int rec_stride, int sub){

  int16_t *rcoeff = thor_alloc(2*MAX_TR_SIZE*MAX_TR_SIZE, 32);
  int16_t *rblock = thor_alloc(2*MAX_TR_SIZE*MAX_TR_SIZE, 32);
  int16_t *rblock2 = thor_alloc(2*MAX_TR_SIZE*MAX_TR_SIZE, 32);

  SAMPLE* left_data = (SAMPLE*)thor_alloc((2*MAX_TR_SIZE+2)*sizeof(SAMPLE),32)+1;
  SAMPLE* top_data = (SAMPLE*)thor_alloc((2*MAX_TR_SIZE+2)*sizeof(SAMPLE),32)+1;
  SAMPLE top_left;

  if (tb_split){
    int size2 = size/2;
    int i,j,index;
    for (i=0;i<size;i+=size2){
      for (j=0;j<size;j+=size2){
        TEMPLATE(make_top_and_left)(left_data,top_data,&top_left,rec_u,stride,&rec_u[i*stride+j],stride,i,j,ypos,xpos,size2,upright_available,downleft_available,1,bitdepth);
        TEMPLATE(get_intra_prediction)(left_data,top_data,top_left,ypos+i,xpos+j,size2,&pblock_u[i*size+j],size,intra_mode,bitdepth);
        TEMPLATE(make_top_and_left)(left_data,top_data,&top_left,rec_v,stride,&rec_v[i*stride+j],stride,i,j,ypos,xpos,size2,upright_available,downleft_available,1,bitdepth);
        TEMPLATE(get_intra_prediction)(left_data,top_data,top_left,ypos+i,xpos+j,size2,&pblock_v[i*size+j],size,intra_mode,bitdepth);
	if (pblock_y)
	  TEMPLATE(improve_uv_prediction)(&pblock_y[i*size+j], &pblock_u[i*size+j], &pblock_v[i*size+j], &rec_y[(i<<sub)*rec_stride+(j<<sub)], size2 << sub, size << sub, rec_stride, sub, bitdepth);
        index = 2*(i/size2) + (j/size2);
        TEMPLATE(dequantize)(coeffq_u+index*size2*size2, rcoeff, qp, size2, iwmatrix ? iwmatrix[log2i(size2/4)] : NULL);
        inverse_transform (rcoeff, rblock2, size2, bitdepth);
        TEMPLATE(reconstruct_block)(rblock2,&pblock_u[i*size+j],&rec_u[i*stride+j],size2,size,stride,bitdepth);
        TEMPLATE(dequantize)(coeffq_v+index*size2*size2, rcoeff, qp, size2, iwmatrix ? iwmatrix[log2i(size2/4)] : NULL);
        inverse_transform (rcoeff, rblock2, size2, bitdepth);
        TEMPLATE(reconstruct_block)(rblock2,&pblock_v[i*size+j],&rec_v[i*stride+j],size2,size,stride,bitdepth);
      }
    }
  }
  else{
    TEMPLATE(make_top_and_left)(left_data,top_data,&top_left,rec_u,stride,NULL,0,0,0,ypos,xpos,size,upright_available,downleft_available,0,bitdepth);
    TEMPLATE(get_intra_prediction)(left_data,top_data,top_left,ypos,xpos,size,pblock_u,size,intra_mode,bitdepth);
    TEMPLATE(make_top_and_left)(left_data,top_data,&top_left,rec_v,stride,NULL,0,0,0,ypos,xpos,size,upright_available,downleft_available,0,bitdepth);
    TEMPLATE(get_intra_prediction)(left_data,top_data,top_left,ypos,xpos,size,pblock_v,size,intra_mode,bitdepth);
    if (pblock_y)
      TEMPLATE(improve_uv_prediction)(pblock_y, pblock_u, pblock_v, rec_y, size << sub, size << sub, rec_stride, sub, bitdepth);
    TEMPLATE(dequantize)(coeffq_u, rcoeff, qp, size, iwmatrix ? iwmatrix[log2i(size/4)] : NULL);
    inverse_transform (rcoeff, rblock, size, bitdepth);
    TEMPLATE(reconstruct_block)(rblock,pblock_u,rec_u,size,size,stride,bitdepth);
    TEMPLATE(dequantize)(coeffq_v, rcoeff, qp, size, iwmatrix ? iwmatrix[log2i(size/4)] : NULL);
    inverse_transform (rcoeff, rblock, size, bitdepth);
    TEMPLATE(reconstruct_block)(rblock,pblock_v,rec_v,size,size,stride,bitdepth);
  }

  thor_free(top_data - 1);
  thor_free(left_data - 1);
  thor_free(rcoeff);
  thor_free(rblock);
  thor_free(rblock2);
}
