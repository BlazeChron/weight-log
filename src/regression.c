#include <stdio.h>

// b0 is intercept and b1 is gradient
// input are values with x and y, n is length,
// output is through pointers b0 and b1
void calculate_simple_linear_regression(
  double values[][2], int n,
  double *b0, double *b1)
{
  double xx_sum = 0;
  double x_sum = 0;
  double y_sum = 0;
  double xy_sum = 0;
  double x_ave = 0;
  double y_ave = 0;
  // calculating b1
  for (int i = 0; i < n; i++)
  {
    double x = values[i][0];
    double y = values[i][1];
    printf("x: %f, y: %f\n", x, y);
    xx_sum += x * x;
    y_sum += y;
    x_sum += x;
    xy_sum += x * y;
  }
  x_ave = x_sum / n;
  y_ave = y_sum / n;

  *b1 = (xy_sum - y_sum * x_sum / n) / (xx_sum - x_sum * x_sum / n);
  *b0 = y_ave - *b1 * x_ave;
}
