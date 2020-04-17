#include "GSLTest.h"

#if defined (NO_GLS_TEST)
void GSLTest (void){}
int polyfit(const double *x,
            const double *y,
            size_t xyLength,
            unsigned poly_n,
            std::vector<double>& out_factor,
            double& R){return 0;}
#else
#include <gsl/gsl_fit.h>
#include <gsl/gsl_multifit.h>
#include <gsl/gsl_cdf.h>

void GSLTest (void)
{
    double x[] = {0.0,0.5,1.0,1.5,2.0,2.5};
    double y[]= {0.0750234,0.256075,0.433573,0.604761,0.752816,0.872483};
    int xyLength = 6;
    double r;
    std::vector<double> out_factor;
    int ret = polyfit(y,x,xyLength,3,out_factor,r);
    printf("%d\n",ret);

    printf("%f\n",r);
    for(int i=0;i<out_factor.count();i++){
        printf("%f\n",out_factor.at(i));
    }
}


int polyfit(const double *x,const double *y,size_t xyLength
    ,unsigned poly_n
    ,QVector<double>& out_factor
    ,double& R)
{
    gsl_matrix *XX = gsl_matrix_alloc(xyLength, poly_n + 1);
    gsl_vector *c = gsl_vector_alloc(poly_n + 1);
    gsl_matrix *cov = gsl_matrix_alloc(poly_n + 1, poly_n + 1);
    gsl_vector *vY = gsl_vector_alloc(xyLength);

    for(size_t i = 0; i < xyLength; i++)
    {
        gsl_matrix_set(XX, i, 0, 1.0);
        gsl_vector_set (vY, i, y[i]);
        for(unsigned j = 1; j <= poly_n; j++)
        {
            gsl_matrix_set(XX, i, j, pow(x[i], int(j) ));
        }
    }

    double out_chisq;
    gsl_multifit_linear_workspace *workspace = gsl_multifit_linear_alloc(xyLength, poly_n + 1);
    int r = gsl_multifit_linear(XX, vY, c, cov, &out_chisq, workspace);
    if(r == 0)
        R = gsl_cdf_chisq_Q(out_chisq/2.0,(xyLength-2)/2.0);//计算拟合优度
    gsl_multifit_linear_free(workspace);
    out_factor.resize(c->size);
    for (size_t i=0;i<c->size;++i)
    {
        out_factor[i] = gsl_vector_get(c,i);
    }

    gsl_vector_free(vY);
    gsl_matrix_free(XX);
    gsl_matrix_free(cov);
    gsl_vector_free(c);

    return r;
}
#endif
