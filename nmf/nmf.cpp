#include <iostream>
#include "Core" //Eigen Library
#include "nmf.h"

nmf::nmf(const Eigen::MatrixXd &a)
{
    this->a = a;
    this->row = a.rows();
    this->col = a.cols();
}
void nmf::init_uv(void)
{
    int row, col;
    row = this->row;
    col = this->col;

    this->u = Eigen::MatrixXd::Random(row, k).cwiseAbs();
    this->v = Eigen::MatrixXd::Random(k, col).cwiseAbs();

}
Decom nmf::fit(int k, int max_iter)
{
    int i;
    double error = 0.0;
    Eigen::MatrixXd un;
    Eigen::MatrixXd ud;
    Eigen::MatrixXd vn;
    Eigen::MatrixXd vd;
    Decom result;
    this->err = Eigen::VectorXd::Zero(max_iter);
    set_k(k);
    init_uv();

    for (i = 0; i < max_iter; i++)
    {

        error = sqerr();
        this->err(i) = error;
        if (error == 0.0){
            break;
        }
        // update rules
        vn = this->u.transpose()*this->a;
        vd = this->u.transpose()*this->u*this->v;
        this->v = this->v.cwiseProduct(vn.cwiseQuotient(vd));

        un = this->a * this->v.transpose();
        ud = this->u * this->v * this->v.transpose();
        this->u = this->u.cwiseProduct(un.cwiseQuotient(ud));

        //normalize u
        normalize();

    }
        result.u = this->u;
        result.v = this->v;
        result.err = this->err;
        result.count = i;

        return result;

}
void nmf::set_k(int k)
{
    this->k = k;
}
double nmf::sqerr(void)
{
    Eigen::MatrixXd hoge;
    Eigen::MatrixXd uv;

    uv = this->u * this->v;
    hoge = this->a - uv;
    hoge = hoge.cwiseProduct(hoge);
    return hoge.sum();
}
void nmf::normalize(void)
{
Eigen::MatrixXd sq;
Eigen::RowVectorXd norm;
Eigen::MatrixXd x = Eigen::MatrixXd::Zero(this->row,this->k);

sq = this->u.cwiseProduct(this->u);
norm = sq.colwise().sum().array().sqrt();
x.rowwise() = norm;
this->u = this->u.cwiseQuotient(x);
}
