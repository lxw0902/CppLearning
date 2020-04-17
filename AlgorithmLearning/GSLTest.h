#ifndef GSLTEST_H
#define GSLTEST_H

#include <vector>
#include <stdio.h>
int polyfit(const double *x,//x轴
            const double *y,//y轴
            size_t xyLength,//数据个数
            unsigned poly_n,//拟合阶数
            std::vector<double>& out_factor,//输出结果
            double& R);//拟合曲线

void GSLTest(void);


#endif
