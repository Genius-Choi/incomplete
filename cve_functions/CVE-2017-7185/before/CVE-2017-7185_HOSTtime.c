time_t HOSTtime() {
  struct timeval tp;
  gettimeofday(&tp, NULL);
  return tp.tv_sec;
}
