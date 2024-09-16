static void decode_and_reconstruct_block_intra (SAMPLE *rec, int stride, int size, int qp, SAMPLE *pblock, int16_t *coeffq,
                                                int tb_split, int upright_available,int downleft_available, intra_mode_t intra_mode,int ypos,int xpos,int width,int comp, int bitdepth,
                                                qmtx_t ** iwmatrix){

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
        TEMPLATE(make_top_and_left)(left_data,top_data,&top_left,rec,stride,&rec[i*stride+j],stride,i,j,ypos,xpos,size2,upright_available,downleft_available,1,bitdepth);
        TEMPLATE(get_intra_prediction)(left_data,top_data,top_left,ypos+i,xpos+j,size2,&pblock[i*size+j],size,intra_mode,bitdepth);
        index = 2*(i/size2) + (j/size2);
        TEMPLATE(dequantize)(coeffq+index*size2*size2, rcoeff, qp, size2, iwmatrix ? iwmatrix[log2i(size2/4)] : NULL);
        inverse_transform (rcoeff, rblock2, size2, bitdepth);
        TEMPLATE(reconstruct_block)(rblock2,&pblock[i*size+j],&rec[i*stride+j],size2,size,stride,bitdepth);
      }
    }
  }
  else{
    TEMPLATE(make_top_and_left)(left_data,top_data,&top_left,rec,stride,NULL,0,0,0,ypos,xpos,size,upright_available,downleft_available,0,bitdepth);
    TEMPLATE(get_intra_prediction)(left_data,top_data,top_left,ypos,xpos,size,pblock,size,intra_mode,bitdepth);
    TEMPLATE(dequantize)(coeffq, rcoeff, qp, size, iwmatrix ? iwmatrix[log2i(size/4)] : NULL);
    inverse_transform (rcoeff, rblock, size, bitdepth);
    TEMPLATE(reconstruct_block)(rblock,pblock,rec,size,size,stride,bitdepth);
  }

  thor_free(top_data - 1);
  thor_free(left_data - 1);
  thor_free(rcoeff);
  thor_free(rblock);
  thor_free(rblock2);
}
