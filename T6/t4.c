#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#include "integral.h"

double integral_par(Funcion f, void *ptr, double xi, double xf, int n, int p)
{
  double step = (xf - xi) / p;
  double final = 0;

  double intgs[p]; // dde se recolectarán
  pid_t pids[p];

  for (int i = 0; i < p; i++)
  {
    int fd[2];
    pipe(fd);
    pids[i] = fork();

    if (pids[i] == 0) //hijo
    {
      close(fd[0]);
      double intg = integral(f, ptr, xi + i * step, xi + (i + 1) * step, n);
      write(fd[1], (char *)&intg, sizeof(intg));
      exit(0);
    }

    else // padre
    {
      close(fd[1]);
      intgs[i] = fd[0];
    }
  }

  for (int i = 0; i < p; i++)
  {
    double intg;
    read(intgs[i], &intg, sizeof(intg));
    final += intg;
    close(intgs[i]);
    waitpid(pids[i], NULL, 0);
  }

  return final;
}
