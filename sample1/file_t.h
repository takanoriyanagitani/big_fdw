#pragma once

void file_close(FILE* f){
  for(; NULL != f;){
    FreeFile(f);
    break;
  }
}
