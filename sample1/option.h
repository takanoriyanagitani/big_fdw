#pragma once

#include <foreign/foreign.h>
#include <commands/defrem.h>

typedef struct S1Option {
  const char* root_dirname;
} S1Option;

static void s1_get_option(Oid id, S1Option* o){
  ForeignTable* t = GetForeignTable(id);
  ListCell* i = NULL;

  foreach(i, t->options){
    DefElem* d = lfirst(i);
    const char* name = NULL == d ? NULL : d->defname;
    const char c = NULL == name ? '\0' : name[0];
    switch(c){
      case 'r':
        o->root_dirname = defGetString(d);
        return;
      default: continue;
    }
  }
}
