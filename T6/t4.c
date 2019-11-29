#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#include "integral.h"

double integral_par(Funcion f, void *ptr, double xi, double xf, int n, int p)
{
  double step = (xf - xi) / p;
  double final = 0;

  double infds[p]; // dde se recolectarán
  double intg;
  pid_t pids[p];

  for (int i = 0; i < p; i++)
  {
    int fds[2];
    pipe(fds);
    pids[i] = fork();

    if (pids[i] == 0) //hijo
    {
      close(fds[0]);
      intg = integral(f, ptr, xi + i * step, xi + (i + 1) * step, n / p);
      write(fds[1], (char *)&intg, sizeof(intg));
      exit(0);
    }

    else // padre
    {
      close(fds[1]);
      infds[i] = fds[0];
    }
  }

  for (int i = 0; i < p; i++)
  {
    read(infds[i], &intg, sizeof(intg));
    waitpid(pids[i], NULL, 0);
    close(infds[i]);

    final += intg;
  }

  return final;
}
