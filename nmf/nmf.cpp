#include <iostream>
#include <random>
#include "Core" //Eigen Library
#include "nmf.h"

nmf::nmf(const Eigen::MatrixXd &a)
{
    this->a = a;
    this->row = a.rows();
    this->col = a.cols();
}
void nmf::test(void)
{
    std::cout << this->row << std::endl;
    std::cout << this->col << std::endl;
    std::cout << this->a << std::endl;
    std::cout << this->u << std::endl;
    std::cout << this->v << std::endl;
}
void nmf::init_uv(void)
{
    int row, col;
    row = this->row;
    col = this->col;

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(0.0, 1.0);

    this->u = Eigen::MatrixXd::Zero(row, k);
    this->v = Eigen::MatrixXd::Zero(k, col);

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < k; j++)
        {
            this->u(i, j) = dist(mt);
        }
    }
    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < col; j++)
        {
            this->v(i, j) = dist(mt);
        }
    }
}
void nmf::fit(int k, int max_iter)
{
    int i;
    double error = 0.0;
    Eigen::MatrixXd un;
    Eigen::MatrixXd ud;
    Eigen::MatrixXd vn;
    Eigen::MatrixXd vd;
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
        this->processed_iter = i;
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
Eigen::MatrixXd nmf::get_uv(void)
{
 return (this->u*this->v);
}
Eigen::MatrixXd nmf::get_u(void)
{
 return this->u;
}
Eigen::MatrixXd nmf::get_v(void)
{
 return this->v;
}
Eigen::VectorXd nmf::get_err(void)
{
    return this->err;
}
int nmf::get_iterend(void)
{
    return this->processed_iter;
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
