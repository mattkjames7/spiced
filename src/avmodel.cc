#include "avmodel.h"

#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

/***********************************************************************
 * NAME : void ReadModelParams(ptr)
 * 
 * DESCRIPTION : Read the model parameters from memory.
 * 
 * INPUTS : 
 * 		unsigned char	*ptr	pointer to the area of memory where the
 * 								parameters are stored.
 * 
 * ********************************************************************/
void AvModel::ReadModelParams(const ModelParams &params) {
	ndc_ = static_cast<int>(params.dc.size());
	dc_ = new float[ndc_];
	std::copy(params.dc.begin(), params.dc.end(), dc_);

	Rshape_[0] = static_cast<int>(params.real.size());
	Rshape_[1] = Rshape_[0] == 0 ? 0 : static_cast<int>(params.real[0].size());
	R_ = new float*[Rshape_[0]];
	for (int i = 0; i < Rshape_[0]; ++i) {
		R_[i] = new float[Rshape_[1]];
		std::copy(params.real[i].begin(), params.real[i].end(), R_[i]);
	}
	
	Ishape_[0] = static_cast<int>(params.imag.size());
	Ishape_[1] = Ishape_[0] == 0 ? 0 : static_cast<int>(params.imag[0].size());
	I_ = new float*[Ishape_[0]];
	for (int i = 0; i < Ishape_[0]; ++i) {
		I_[i] = new float[Ishape_[1]];
		std::copy(params.imag[i].begin(), params.imag[i].end(), I_[i]);
	}

}


/***********************************************************************
 * NAME : void PeriodicComponents(n,mlt,R,per)
 * 
 * DESCRIPTION : Converts cartesian x and y to MLT and R
 * 
 * INPUTS : 
 * 		int 	n		Number of elements
 * 		float 	*mlt	Magnetic local time (in hours)
 * 		float 	*R		R
 * 
 * OUTPUTS : 
 * 		float 	**per	The periodic componensts of the model, shape
 * 						(nm_,n)
 * 
 * 
 * ********************************************************************/
void AvModel::PeriodicComponents(int n, float *mlt, float *R, float **per) {

	/* start by multiplying mlt by 2pi */
	float *m2pi = new float[n];
	int i, j;
	for (i=0;i<n;i++) {
		m2pi[i] = mlt[i]*2*M_PI;
	}
	
	/* work out the real and imaginary components */
	float **real = new float*[nm_];
	float **imag = new float*[nm_];
	for (i=0;i<nm_;i++) {
		/* allocate the memory for each m-number */
		real[i] = new float[n];
		imag[i] = new float[n];
		
		/*call the polynomial functions */
		polynomial(Rshape_[1]-1,R_[i],n,R,real[i]); 
		polynomial(Ishape_[1]-1,I_[i],n,R,imag[i]); 
	}

	/* work out the amplitudes and phases */
	float **A = new float*[nm_];
	float **P = new float*[nm_];
	for (i=0;i<nm_;i++) {
		A[i] = new float[n];
		P[i] = new float[n];
	}

	for (i=0;i<nm_;i++) {
		for (j=0;j<n;j++) {
			
			A[i][j] = sqrtf(powf(real[i][j],2.0) + powf(imag[i][j],2.0));
			P[i][j] = atan2f(imag[i][j],real[i][j]);
			
		}
	}

	/* now work out the periodic components */
	for (i=0;i<nm_;i++) {
		for (j=0;j<n;j++) {
			per[i][j] = A[i][j]*cosf(m2pi[j]*wl_[i] + P[i][j]);
		}
	}

	/* clean up */
	delete[] m2pi;
	for (i=0;i<nm_;i++) {
		delete[] A[i];
		delete[] P[i];
		delete[] real[i];
		delete[] imag[i];
	}
	delete[] A;
	delete[] P;
	delete[] real;
	delete[] imag;
	
}

/***********************************************************************
 * NAME : void CartMLTR(n,x,y,mlt,R)
 * 
 * DESCRIPTION : Converts cartesian x and y to MLT and R
 * 
 * INPUTS : 
 * 		int 	n		Number of elements
 * 		float	*x		x-coordinate
 * 		float	*y		y-coordinate
 * 
 * OUTPUTS : 
 * 		float 	*mlt	Magnetic local time (in hours)
 * 		float 	*R		R
 * 
 * 
 * ********************************************************************/
void AvModel::CartMLTR(int n, float *x, float *y, float *mlt, float *R) {
	
	int i;
	for (i=0;i<n;i++) {
		R[i] = sqrtf(powf(x[i],2.0) + powf(y[i],2.0));
		mlt[i] = 12.0*atan2f(-y[i],-x[i])/M_PI + 24.0;
		mlt[i] = fmodf(mlt[i],24.0);
	}
}
