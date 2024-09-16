std::string thread_task_slice_segment::name() const {
  char buf[100];
  sprintf(buf,"slice-segment-%d;%d",debug_startCtbX,debug_startCtbY);
  return buf;
}
