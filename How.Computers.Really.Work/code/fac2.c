#include <stdio.h>

// Calculate the factorial of n.
int factorial(int n)
{
  int result = n;

  while(--n > 0)
  {
    result = result * n;
  }

  return result;
}

int main()
{
  int answer = factorial(4);
  printf("%d\n", answer);
}
