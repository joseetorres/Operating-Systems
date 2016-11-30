#include "assembler.h"
#include "virtualMachine.h"

int main(int argc, char *argv[]){

  Assembler a;
  a.assemble();

  VirtualMachine v;
  v.iFetch();
}
