#ifndef EIGENPHP_H
#define EIGENPHP_H

class EigenPhp : public Php::Base
{
private:
	bool set_matd(Eigen::MatrixXd mat);

	bool set_mati(Eigen::MatrixXi mat);

	Php::Value matd_to_zarr();

	Php::Value mati_to_zarr();

public:
	static const int MAT_DOUBLE = 0;
	static const int MAT_INTEGER = 1;

	Eigen::MatrixXd matd;
	Eigen::MatrixXi mati;

	int val_type;


	Php::Value __toString();

	Php::Value random_d(Php::Parameters &params);

	Php::Value random_i(Php::Parameters &params);

	Php::Value constant_i(Php::Parameters &params);
};

#endif
