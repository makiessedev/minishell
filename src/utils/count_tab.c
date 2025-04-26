#include "minishell.h"

int count_tab(char **tab) {
  int i;

  i = 0;
  while (tab && tab[i])
    i++;
  return (i);
}
