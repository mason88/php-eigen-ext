#include <phpcpp.h>

#include <iostream>
#include <Eigen/Dense>

#include "EigenPhp.h"

//using namespace std;


bool EigenPhp::set_matd(Eigen::MatrixXd mat)
{
	this->matd = mat;
	this->val_type = EigenPhp::MAT_DOUBLE;

	return true;
}

bool EigenPhp::set_mati(Eigen::MatrixXi mat)
{
	this->mati = mat;
	this->val_type = EigenPhp::MAT_INTEGER;

	return true;
}

Php::Value EigenPhp::matd_to_zarr()
{
	Php::Value arr;
	int j, k;

	for(j = 0; j < this->matd.rows(); j++)
	{
		arr[j] = Php::Array();
		for(k = 0; k < this->matd.cols(); k++)
		{
			arr[j][k] = (double) this->matd(j, k);
		}
	}

	return arr;
}

Php::Value EigenPhp::mati_to_zarr()
{
	Php::Value arr;
	int j, k;

	for(j = 0; j < this->mati.rows(); j++)
	{
		arr[j] = Php::Array();
		for(k = 0; k < this->mati.cols(); k++)
		{
			arr[j][k] = (int) this->mati(j, k);
		}
	}

	return arr;
}

Php::Value EigenPhp::__toString()
{
	std::stringstream buffer;
	if (val_type == EigenPhp::MAT_DOUBLE)
		buffer << this->matd << std::endl;
	else
		buffer << this->mati << std::endl;
	return buffer.str();
}

Php::Value EigenPhp::random_d(Php::Parameters &params)
{
	int rows = (int) params[0];
	int cols = (int) params[1];

	this->set_matd(Eigen::MatrixXd::Random(rows, cols));
	return this->matd_to_zarr();
}

Php::Value EigenPhp::random_i(Php::Parameters &params)
{
	int rows = (int) params[0];
	int cols = (int) params[1];

	this->set_mati(Eigen::MatrixXi::Random(rows, cols));
	return this->mati_to_zarr();
}

Php::Value EigenPhp::constant_i(Php::Parameters &params)
{
	int rows = (int) params[0];
	int cols = (int) params[1];
	int val = (int) params[2];

	this->set_mati(Eigen::MatrixXi::Constant(rows, cols, val));
	return this->mati_to_zarr();
}


/**
 *  tell the compiler that the get_module is a pure C function
 */
extern "C" {
    
    /**
     * Function that is called by PHP right after the PHP process
     * has started, and that returns an address of an internal PHP
     * strucure with all the details and features of your extension
     *
     * @return void* a pointer to an address that is understood by PHP
     */
    PHPCPP_EXPORT void *get_module() 
    {
        // static(!) Php::Extension object that should stay in memory
        // for the entire duration of the process
        static Php::Extension extension("eigen_extension", "1.0");
        
        Php::Class<EigenPhp> eigen_php("EigenPhp");

        eigen_php.method<&EigenPhp::random_d> ("random_d", {
		Php::ByVal("a", Php::Type::Numeric),
		Php::ByVal("b", Php::Type::Numeric)
	});
        eigen_php.method<&EigenPhp::random_i> ("random_i", {
		Php::ByVal("a", Php::Type::Numeric),
		Php::ByVal("b", Php::Type::Numeric)
	});
        eigen_php.method<&EigenPhp::constant_i> ("constant_i", {
		Php::ByVal("a", Php::Type::Numeric),
		Php::ByVal("b", Php::Type::Numeric),
		Php::ByVal("c", Php::Type::Numeric)
	});

        extension.add(std::move(eigen_php));

        return(extension);
    }
}
