/******************************************************************************
 * @file main.c
 * @author David Huson
 * @brief A very basic driver program to start the parser given a filename via
 *the command line arguments
 * @date 2023-01-22
 ******************************************************************************/
#include "parse.h"
#include <stdio.h>

int main(int argc, char* argv[]) {
  startParser(argv[1]);
  return 0;
}
