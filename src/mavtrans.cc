#include "mavtrans.h"
#include "mavlambda_params.h"

#include <algorithm>

/***********************************************************************
 * NAME : MavTrans()
 * 
 * DESCRIPTION : Constructor for the MavTrans class
 * 
 * ********************************************************************/
MavTrans::MavTrans() {
	/* all we really need to do is read in the polynomial coefficients*/
	ReadCoefficients();
}

/***********************************************************************
 * NAME : ~MavTrans()
 * 
 * DESCRIPTION : Destructor for the MavTrans class
 * 
 * ********************************************************************/
MavTrans::~MavTrans() {
	/* delete arrays*/
	
	delete[] ps_;
	delete[] pt_;
}

/***********************************************************************
 * NAME : ReadCoefficients()
 * 
 * DESCRIPTION : Read in the coefficients for the transform.
 * 
 * ********************************************************************/
void MavTrans::ReadCoefficients() {
	/* The generated header already stores coefficients in the ascending
	 * order expected by polynomial(). */
	nps_ = static_cast<int>(mavlambda.ps.size()) - 1;
	npt_ = static_cast<int>(mavlambda.pt.size()) - 1;
	ps_ = new double[nps_ + 1];
	pt_ = new double[npt_ + 1];
	std::copy(mavlambda.ps.begin(), mavlambda.ps.end(), ps_);
	std::copy(mavlambda.pt.begin(), mavlambda.pt.end(), pt_);
	
	
}

/***********************************************************************
 * NAME : PSTransform(n,r,m,mt)
 * 
 * DESCRIPTION : Transforms plasmaspheric average ion masses.
 * 
 * INPUTS : 
 * 		int 	n		Number of elements
 * 		float	*r		L-shell/radial distance from Earth in Re
 * 		float	*m		Average ion mass in amu
 * 
 * OUTPUTS : 
 * 		float 	*mt	Transformed average ion mass
 * 
 * 
 * ********************************************************************/
void MavTrans::PSTransform(int n, float *r, float *m, float *mt) {
	
	/*calculate lambda*/
	double *lambda = new double[n];
	polynomial(nps_,ps_,n,r,lambda);
	
	/*transform */
	int i;
	for (i=0;i<n;i++) {
		if (lambda[i] == 0) {
			mt[i] = (float) log((double) m[i]);
		} else {
			mt[i] = (float) ((pow((double) m[i],lambda[i]) - 1.0)/lambda[i]);
		}
	}
	delete lambda;
}	

/***********************************************************************
 * NAME : PSRevTransform(n,r,mt,m)
 * 
 * DESCRIPTION : Reverses the transform of plasmaspheric average ion 
 * 				masses.
 * 
 * INPUTS : 
 * 		int 	n		Number of elements
 * 		float	*r		L-shell/radial distance from Earth in Re
 * 		float	*mt		Transformed average ion mass
 * 
 * OUTPUTS : 
 * 		float 	*m		Average ion mass in amu
 * 
 * 
 * ********************************************************************/
void MavTrans::PSRevTransform(int n, float *r, float *mt, float *m) {
	
	/*calculate lambda*/
	double *lambda = new double[n];
	polynomial(nps_,ps_,n,r,lambda);
	
	/*transform */
	int i;
	for (i=0;i<n;i++) {
		if (lambda[i] == 0) {
			m[i] = (float) exp((double) mt[i]);
		} else {
			m[i] = (float) pow((((double) mt[i])*lambda[i] + 1.0),1.0/lambda[i]);
		}
	}
	delete lambda;
}	

/***********************************************************************
 * NAME : PTTransform(n,r,m,mt)
 * 
 * DESCRIPTION : Transforms plasmatrough average ion masses.
 * 
 * INPUTS : 
 * 		int 	n		Number of elements
 * 		float	*r		L-shell/radial distance from Earth in Re
 * 		float	*m		Average ion mass in amu
 * 
 * OUTPUTS : 
 * 		float 	*mt		Transformed average ion mass
 * 
 * 
 * ********************************************************************/
void MavTrans::PTTransform(int n, float *r, float *m, float *mt) {
	
	/*calculate lambda*/
	double *lambda = new double[n];
	polynomial(npt_,pt_,n,r,lambda);
	
	/*transform */
	int i;
	for (i=0;i<n;i++) {
		if (lambda[i] == 0) {
			mt[i] = (float) log((double) m[i]);
		} else {
			mt[i] = (float) ((pow((double) m[i],lambda[i]) - 1.0)/lambda[i]);
		}
	}
	delete lambda;
}	

/***********************************************************************
 * NAME : PTRevTransform(n,r,mt,m)
 * 
 * DESCRIPTION : Reverses the transform of plasmatrough average ion 
 * 				masses.
 * 
 * INPUTS : 
 * 		int 	n		Number of elements
 * 		float	*r		L-shell/radial distance from Earth in Re
 * 		float	*mt		Transformed average ion mass
 * 
 * OUTPUTS : 
 * 		float 	*m		Average ion mass in amu
 * 
 * 
 * ********************************************************************/
void MavTrans::PTRevTransform(int n, float *r, float *mt, float *m) {
	
	/*calculate lambda*/
	double *lambda = new double[n];
	polynomial(npt_,pt_,n,r,lambda);
	
	/*transform */
	int i;
	for (i=0;i<n;i++) {
		if (lambda[i] == 0) {
			m[i] = (float) exp((double) mt[i]);
		} else {
			m[i] = (float) pow((((double) mt[i])*lambda[i] + 1.0),1.0/lambda[i]);
		}
	}
	delete lambda;
}	

