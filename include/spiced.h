#ifndef __SPICED_H__
#define __SPICED_H__
#include <stdio.h>
#include <stdlib.h>
#include <ann.h>


/* these are the memory addresses for the average model parameters */
extern unsigned char _binary_mavh_bin_start;
extern unsigned char _binary_mavcps_bin_start;
extern unsigned char _binary_mavcpt_bin_start;
extern unsigned char _binary_prob_bin_start;
extern unsigned char _binary_ps_bin_start;
extern unsigned char _binary_pt_bin_start;

/* these are the memory addresses for the ANN model parameters */
extern unsigned char _binary_mavhann_bin_start;
extern unsigned char _binary_mavcpsann_bin_start;
extern unsigned char _binary_mavcptann_bin_start;
extern unsigned char _binary_probann_bin_start;
extern unsigned char _binary_psann_bin_start;
extern unsigned char _binary_ptann_bin_start;



extern "C" {
/***********************************************************************
 * NAME : 	void initModels()
 * 
 * DESCRIPTION : 
 * 		Initializes the model objects.
 * 
 * ********************************************************************/
void initModels();



/***********************************************************************
 * NAME : 	void getAvMavH(n,mlt,R,ShowDC,OnlyDC,Validate,m0,m1,out)
 * 
 * DESCRIPTION : 
 * 		Calculates the hot average ion mass model.
 * 
 * INPUTS : 
 * 		int		n			Number of points to evaluate model at.
 * 		float	*mlt		Array of local times (in hours).
 * 		float 	*R			Array of L-shells (in R_E).
 * 		bool	ShowDC		If true, DC component included in output.
 * 		bool	OnlyDC		If true, only DC component is output.
 * 		bool	Validate	If true, all points will be checked to see
 * 							that they fit within the model parameters,
 * 							anything outside will be NAN.
 * 		int		m0			First azimuthal wave number to include.
 * 		int 	m1			Last azimuthal wave number to include.
 * 
 * OUTPUTS :
 * 		float	*out		Output array.
 * 
 * ********************************************************************/
	void getAvMavH(int n, float *mlt, float *R, bool ShowDC, bool OnlyDC, 
				bool Validate, int m0, int m1, float *out);

/***********************************************************************
 * NAME : 	void getAvMavHCart(n,x,y,ShowDC,OnlyDC,Validate,m0,m1,out)
 * 
 * DESCRIPTION : 
 * 		Calculates the hot average ion mass model.
 * 
 * INPUTS : 
 * 		int		n			Number of points to evaluate model at.
 * 		float	*x			Array of x-position (SM coords, in R_E).
 * 		float 	*y			Array of y-position (SM coords, in R_E).
 * 		bool	ShowDC		If true, DC component included in output.
 * 		bool	OnlyDC		If true, only DC component is output.
 * 		bool	Validate	If true, all points will be checked to see
 * 							that they fit within the model parameters,
 * 							anything outside will be NAN.
 * 		int		m0			First azimuthal wave number to include.
 * 		int 	m1			Last azimuthal wave number to include.
 * 
 * OUTPUTS :
 * 		float	*out		Output array.
 * 
 * ********************************************************************/
	void getAvMavHCart(int n, float *x, float *y, bool ShowDC, bool OnlyDC, 
				bool Validate, int m0, int m1, float *out);
				
				
/***********************************************************************
 * NAME : 	void getScaledMavH(n,mlt,R,f107,ShowDC,OnlyDC,Validate,m0,m1,out)
 * 
 * DESCRIPTION : 
 * 		Calculates the scaled hot average ion mass model.
 * 
 * INPUTS : 
 * 		int		n			Number of points to evaluate model at.
 * 		float	*mlt		Array of local times (in hours).
 * 		float 	*R			Array of L-shells (in R_E).
 * 		float 	*f107		Array of F10.7 indices
 * 		bool	ShowDC		If true, DC component included in output.
 * 		bool	OnlyDC		If true, only DC component is output.
 * 		bool	Validate	If true, all points will be checked to see
 * 							that they fit within the model parameters,
 * 							anything outside will be NAN.
 * 		int		m0			First azimuthal wave number to include.
 * 		int 	m1			Last azimuthal wave number to include.
 * 
 * OUTPUTS :
 * 		float	*out		Output array.
 * 
 * ********************************************************************/
	void getScaledMavH(int n, float *mlt, float *R, float *f107, bool ShowDC, 
				bool OnlyDC, bool Validate, int m0, int m1, float *out);


/***********************************************************************
 * NAME : 	void getScaledMavHCart(n,x,y,f107,ShowDC,OnlyDC,Validate,m0,m1,out)
 * 
 * DESCRIPTION : 
 * 		Calculates the scaled hot average ion mass model.
 * 
 * INPUTS : 
 * 		int		n			Number of points to evaluate model at.
 * 		float	*x			Array of x-position (SM coords, in R_E).
 * 		float 	*y			Array of y-position (SM coords, in R_E).
 * 		float 	*f107		Array of F10.7 indices
 * 		bool	ShowDC		If true, DC component included in output.
 * 		bool	OnlyDC		If true, only DC component is output.
 * 		bool	Validate	If true, all points will be checked to see
 * 							that they fit within the model parameters,
 * 							anything outside will be NAN.
 * 		int		m0			First azimuthal wave number to include.
 * 		int 	m1			Last azimuthal wave number to include.
 * 
 * OUTPUTS :
 * 		float	*out		Output array.
 * 
 * ********************************************************************/
	void getScaledMavHCart(int n, float *x, float *y, float *f107, bool ShowDC,
				bool OnlyDC,bool Validate, int m0, int m1, float *out);

/***********************************************************************
 * NAME : 	void getAvMavPT(n,mlt,R,ShowDC,OnlyDC,Validate,m0,m1,RevTrans,out)
 * 
 * DESCRIPTION : 
 * 		Calculates the PT average ion mass model.
 * 
 * INPUTS : 
 * 		int		n			Number of points to evaluate model at.
 * 		float	*mlt		Array of local times (in hours).
 * 		float 	*R			Array of L-shells (in R_E).
 * 		bool	ShowDC		If true, DC component included in output.
 * 		bool	OnlyDC		If true, only DC component is output.
 * 		bool	Validate	If true, all points will be checked to see
 * 							that they fit within the model parameters,
 * 							anything outside will be NAN.
 * 		int		m0			First azimuthal wave number to include.
 * 		int 	m1			Last azimuthal wave number to include.
 * 		bool	RevTrans	Reverse transform
 * 
 * OUTPUTS :
 * 		float	*out		Output array.
 * 
 * ********************************************************************/
	void getAvMavPT(int n, float *mlt, float *R, bool ShowDC, bool OnlyDC, 
				bool Validate, int m0, int m1, bool RevTrans, float *out);

/***********************************************************************
 * NAME : 	void getAvMavPTCart(n,x,y,ShowDC,OnlyDC,Validate,m0,m1,RevTrans,out)
 * 
 * DESCRIPTION : 
 * 		Calculates the PT average ion mass model.
 * 
 * INPUTS : 
 * 		int		n			Number of points to evaluate model at.
 * 		float	*x			Array of x-position (SM coords, in R_E).
 * 		float 	*y			Array of y-position (SM coords, in R_E).
 * 		bool	ShowDC		If true, DC component included in output.
 * 		bool	OnlyDC		If true, only DC component is output.
 * 		bool	Validate	If true, all points will be checked to see
 * 							that they fit within the model parameters,
 * 							anything outside will be NAN.
 * 		int		m0			First azimuthal wave number to include.
 * 		int 	m1			Last azimuthal wave number to include.
 * 		bool	RevTrans	Reverse transform
 * 
 * OUTPUTS :
 * 		float	*out		Output array.
 * 
 * ********************************************************************/
	void getAvMavPTCart(int n, float *x, float *y, bool ShowDC, bool OnlyDC, 
				bool Validate, int m0, int m1, bool RevTrans, float *out);

/***********************************************************************
 * NAME : 	void getScaledMavPT(n,mlt,R,f107,ShowDC,OnlyDC,Validate,m0,m1,RevTrans,out)
 * 
 * DESCRIPTION : 
 * 		Calculates the scaled PT average ion mass model.
 * 
 * INPUTS : 
 * 		int		n			Number of points to evaluate model at.
 * 		float	*mlt		Array of local times (in hours).
 * 		float 	*R			Array of L-shells (in R_E).
 * 		float 	*smr		Array of SMR indices
 * 		bool	ShowDC		If true, DC component included in output.
 * 		bool	OnlyDC		If true, only DC component is output.
 * 		bool	Validate	If true, all points will be checked to see
 * 							that they fit within the model parameters,
 * 							anything outside will be NAN.
 * 		int		m0			First azimuthal wave number to include.
 * 		int 	m1			Last azimuthal wave number to include.
 * 		bool	RevTrans	Reverse transform
 * 
 * OUTPUTS :
 * 		float	*out		Output array.
 * 
 * ********************************************************************/
	void getScaledMavPT(int n, float *mlt, float *R, float *smr, bool ShowDC, 
				bool OnlyDC, bool Validate, int m0, int m1, bool RevTrans, float *out);


/***********************************************************************
 * NAME : 	void getScaledMavPTCart(n,x,y,f107,ShowDC,OnlyDC,Validate,m0,m1,RevTrans,out)
 * 
 * DESCRIPTION : 
 * 		Calculates the scaled PT average ion mass model.
 * 
 * INPUTS : 
 * 		int		n			Number of points to evaluate model at.
 * 		float	*x			Array of x-position (SM coords, in R_E).
 * 		float 	*y			Array of y-position (SM coords, in R_E).
 * 		float 	*smr		Array of SMR indices
 * 		bool	ShowDC		If true, DC component included in output.
 * 		bool	OnlyDC		If true, only DC component is output.
 * 		bool	Validate	If true, all points will be checked to see
 * 							that they fit within the model parameters,
 * 							anything outside will be NAN.
 * 		int		m0			First azimuthal wave number to include.
 * 		int 	m1			Last azimuthal wave number to include.
 * 		bool	RevTrans	Reverse transform
 * 
 * OUTPUTS :
 * 		float	*out		Output array.
 * 
 * ********************************************************************/
	void getScaledMavPTCart(int n, float *x, float *y, float *smr, bool ShowDC,
				bool OnlyDC,bool Validate, int m0, int m1, bool RevTrans, float *out);

/***********************************************************************
 * NAME : 	void getAvMavPS(n,mlt,R,ShowDC,OnlyDC,Validate,m0,m1,RevTrans,out)
 * 
 * DESCRIPTION : 
 * 		Calculates the PS average ion mass model.
 * 
 * INPUTS : 
 * 		int		n			Number of points to evaluate model at.
 * 		float	*mlt		Array of local times (in hours).
 * 		float 	*R			Array of L-shells (in R_E).
 * 		bool	ShowDC		If true, DC component included in output.
 * 		bool	OnlyDC		If true, only DC component is output.
 * 		bool	Validate	If true, all points will be checked to see
 * 							that they fit within the model parameters,
 * 							anything outside will be NAN.
 * 		int		m0			First azimuthal wave number to include.
 * 		int 	m1			Last azimuthal wave number to include.
 * 		bool	RevTrans	Reverse transform
 * 
 * OUTPUTS :
 * 		float	*out		Output array.
 * 
 * ********************************************************************/
	void getAvMavPS(int n, float *mlt, float *R, bool ShowDC, bool OnlyDC, 
				bool Validate, int m0, int m1, bool RevTrans, float *out);


/***********************************************************************
 * NAME : 	void getAvMavPSCart(n,x,y,ShowDC,OnlyDC,Validate,m0,m1,RevTrans,out)
 * 
 * DESCRIPTION : 
 * 		Calculates the PS average ion mass model.
 * 
 * INPUTS : 
 * 		int		n			Number of points to evaluate model at.
 * 		float	*x			Array of x-position (SM coords, in R_E).
 * 		float 	*y			Array of y-position (SM coords, in R_E).
 * 		bool	ShowDC		If true, DC component included in output.
 * 		bool	OnlyDC		If true, only DC component is output.
 * 		bool	Validate	If true, all points will be checked to see
 * 							that they fit within the model parameters,
 * 							anything outside will be NAN.
 * 		int		m0			First azimuthal wave number to include.
 * 		int 	m1			Last azimuthal wave number to include.
 * 		bool	RevTrans	Reverse transform
 * 
 * OUTPUTS :
 * 		float	*out		Output array.
 * 
 * ********************************************************************/
	void getAvMavPSCart(int n, float *x, float *y, bool ShowDC, bool OnlyDC, 
				bool Validate, int m0, int m1, bool RevTrans, float *out);

/***********************************************************************
 * NAME : 	void getScaledMav(n,mlt,R,f107,ShowDC,OnlyDC,Validate,m0,m1,RevTrans,out)
 * 
 * DESCRIPTION : 
 * 		Calculates the scaled PS average ion mass model.
 * 
 * INPUTS : 
 * 		int		n			Number of points to evaluate model at.
 * 		float	*mlt		Array of local times (in hours).
 * 		float 	*R			Array of L-shells (in R_E).
 * 		float 	*smr		Array of SMR indices
 * 		bool	ShowDC		If true, DC component included in output.
 * 		bool	OnlyDC		If true, only DC component is output.
 * 		bool	Validate	If true, all points will be checked to see
 * 							that they fit within the model parameters,
 * 							anything outside will be NAN.
 * 		int		m0			First azimuthal wave number to include.
 * 		int 	m1			Last azimuthal wave number to include.
 * 		bool	RevTrans	Reverse transform
 * 
 * OUTPUTS :
 * 		float	*out		Output array.
 * 
 * ********************************************************************/
	void getScaledMavPS(int n, float *mlt, float *R, float *smr, bool ShowDC, 
				bool OnlyDC, bool Validate, int m0, int m1, bool RevTrans, float *out);


/***********************************************************************
 * NAME : 	void getScaledMavPSCart(n,x,y,f107,ShowDC,OnlyDC,Validate,m0,m1,RevTrans,out)
 * 
 * DESCRIPTION : 
 * 		Calculates the scaled PS average ion mass model.
 * 
 * INPUTS : 
 * 		int		n			Number of points to evaluate model at.
 * 		float	*x			Array of x-position (SM coords, in R_E).
 * 		float 	*y			Array of y-position (SM coords, in R_E).
 * 		float 	*smr		Array of SMR indices
 * 		bool	ShowDC		If true, DC component included in output.
 * 		bool	OnlyDC		If true, only DC component is output.
 * 		bool	Validate	If true, all points will be checked to see
 * 							that they fit within the model parameters,
 * 							anything outside will be NAN.
 * 		int		m0			First azimuthal wave number to include.
 * 		int 	m1			Last azimuthal wave number to include.
 * 		bool	RevTrans	Reverse transform
 * 
 * OUTPUTS :
 * 		float	*out		Output array.
 * 
 * ********************************************************************/
	void getScaledMavPSCart(int n, float *x, float *y, float *smr, bool ShowDC,
				bool OnlyDC,bool Validate, int m0, int m1, bool RevTrans, float *out);


/***********************************************************************
 * NAME : 	void getAvProb(n,mlt,R,ShowDC,OnlyDC,Validate,m0,m1,out)
 * 
 * DESCRIPTION : 
 * 		Calculates the probability model.
 * 
 * INPUTS : 
 * 		int		n			Number of points to evaluate model at.
 * 		float	*mlt		Array of local times (in hours).
 * 		float 	*R			Array of L-shells (in R_E).
 * 		bool	ShowDC		If true, DC component included in output.
 * 		bool	OnlyDC		If true, only DC component is output.
 * 		bool	Validate	If true, all points will be checked to see
 * 							that they fit within the model parameters,
 * 							anything outside will be NAN.
 * 		int		m0			First azimuthal wave number to include.
 * 		int 	m1			Last azimuthal wave number to include.
 * 
 * OUTPUTS :
 * 		float	*out		Output array.
 * 
 * ********************************************************************/
	void getAvProb(int n, float *mlt, float *R, bool ShowDC, bool OnlyDC, 
				bool Validate, int m0, int m1, float *out);


/***********************************************************************
 * NAME : 	void getAvProbCart(n,x,y,ShowDC,OnlyDC,Validate,m0,m1,out)
 * 
 * DESCRIPTION : 
 * 		Calculates the probability model.
 * 
 * INPUTS : 
 * 		int		n			Number of points to evaluate model at.
 * 		float	*x			Array of x-position (SM coords, in R_E).
 * 		float 	*y			Array of y-position (SM coords, in R_E).
 * 		bool	ShowDC		If true, DC component included in output.
 * 		bool	OnlyDC		If true, only DC component is output.
 * 		bool	Validate	If true, all points will be checked to see
 * 							that they fit within the model parameters,
 * 							anything outside will be NAN.
 * 		int		m0			First azimuthal wave number to include.
 * 		int 	m1			Last azimuthal wave number to include.
 * 
 * OUTPUTS :
 * 		float	*out		Output array.
 * 
 * ********************************************************************/
	void getAvProbCart(int n, float *x, float *y, bool ShowDC, bool OnlyDC, 
				bool Validate, int m0, int m1, float *out);
				
/***********************************************************************
 * NAME : 	void getScaledProb(n,mlt,R,smr,ShowDC,OnlyDC,Validate,m0,m1,out)
 * 
 * DESCRIPTION : 
 * 		Calculates the scaled probability model.
 * 
 * INPUTS : 
 * 		int		n			Number of points to evaluate model at.
 * 		float	*mlt		Array of local times (in hours).
 * 		float 	*R			Array of L-shells (in R_E).
 * 		float 	*smr		Array of SMR indices.
 * 		bool	ShowDC		If true, DC component included in output.
 * 		bool	OnlyDC		If true, only DC component is output.
 * 		bool	Validate	If true, all points will be checked to see
 * 							that they fit within the model parameters,
 * 							anything outside will be NAN.
 * 		int		m0			First azimuthal wave number to include.
 * 		int 	m1			Last azimuthal wave number to include.
 * 
 * OUTPUTS :
 * 		float	*out		Output array.
 * 
 * ********************************************************************/
	void getScaledProb(int n, float *mlt, float *R, float *smr, bool ShowDC, 
				bool OnlyDC, bool Validate, int m0, int m1, float *out);

/***********************************************************************
 * NAME : 	void getScaledProbCart(n,x,y,smr,ShowDC,OnlyDC,Validate,m0,m1,out)
 * 
 * DESCRIPTION : 
 * 		Calculates the scaled probability model.
 * 
 * INPUTS : 
 * 		int		n			Number of points to evaluate model at.
 * 		float	*x			Array of x-position (SM coords, in R_E).
 * 		float 	*y			Array of y-position (SM coords, in R_E).
 * 		float 	*smr		Array of SMR indices.
 * 		bool	ShowDC		If true, DC component included in output.
 * 		bool	OnlyDC		If true, only DC component is output.
 * 		bool	Validate	If true, all points will be checked to see
 * 							that they fit within the model parameters,
 * 							anything outside will be NAN.
 * 		int		m0			First azimuthal wave number to include.
 * 		int 	m1			Last azimuthal wave number to include.
 * 
 * OUTPUTS :
 * 		float	*out		Output array.
 * 
 * ********************************************************************/
	void getScaledProbCart(int n, float *x, float *y, float *smr, bool ShowDC,
				bool OnlyDC,bool Validate, int m0, int m1, float *out);

/***********************************************************************
 * NAME : 	void getAvPS(n,mlt,R,ShowDC,OnlyDC,Validate,m0,m1,RevTrans,out)
 * 
 * DESCRIPTION : 
 * 		Calculates the plasmaspheric electron density model.
 * 
 * INPUTS : 
 * 		int		n			Number of points to evaluate model at.
 * 		float	*mlt		Array of local times (in hours).
 * 		float 	*R			Array of L-shells (in R_E).
 * 		bool	ShowDC		If true, DC component included in output.
 * 		bool	OnlyDC		If true, only DC component is output.
 * 		bool	Validate	If true, all points will be checked to see
 * 							that they fit within the model parameters,
 * 							anything outside will be NAN.
 * 		int		m0			First azimuthal wave number to include.
 * 		int 	m1			Last azimuthal wave number to include.
 * 		bool	RevTrans	If true, reverses transformed densities to 
 * 							real units.
 * 
 * OUTPUTS :
 * 		float	*out		Output array.
 * 
 * ********************************************************************/
	void getAvPS(int n, float *mlt, float *R, bool ShowDC, bool OnlyDC, 
				bool Validate, int m0, int m1, bool RevTrans, float *out);

/***********************************************************************
 * NAME : 	void getAvPSCart(n,x,y,ShowDC,OnlyDC,Validate,m0,m1,out)
 * 
 * DESCRIPTION : 
 * 		Calculates the plasmaspheric electron density model.
 * 
 * INPUTS : 
 * 		int		n			Number of points to evaluate model at.
 * 		float	*x			Array of x-position (SM coords, in R_E).
 * 		float 	*y			Array of y-position (SM coords, in R_E).
 * 		bool	ShowDC		If true, DC component included in output.
 * 		bool	OnlyDC		If true, only DC component is output.
 * 		bool	Validate	If true, all points will be checked to see
 * 							that they fit within the model parameters,
 * 							anything outside will be NAN.
 * 		int		m0			First azimuthal wave number to include.
 * 		int 	m1			Last azimuthal wave number to include.
 * 
 * OUTPUTS :
 * 		float	*out		Output array.
 * 
 * ********************************************************************/
	void getAvPSCart(int n, float *x, float *y, bool ShowDC, bool OnlyDC, 
				bool Validate, int m0, int m1, bool RevTrans, float *out);

/***********************************************************************
 * NAME : 	void getScaledPS(n,mlt,R,smr,ShowDC,OnlyDC,Validate,m0,m1,out)
 * 
 * DESCRIPTION : 
 * 		Calculates the scaled plasmaspheric electron density model.
 * 
 * INPUTS : 
 * 		int		n			Number of points to evaluate model at.
 * 		float	*mlt		Array of local times (in hours).
 * 		float 	*R			Array of L-shells (in R_E).
 * 		float 	*smr		Array of SMR indices.
 * 		bool	ShowDC		If true, DC component included in output.
 * 		bool	OnlyDC		If true, only DC component is output.
 * 		bool	Validate	If true, all points will be checked to see
 * 							that they fit within the model parameters,
 * 							anything outside will be NAN.
 * 		int		m0			First azimuthal wave number to include.
 * 		int 	m1			Last azimuthal wave number to include.
 * 
 * OUTPUTS :
 * 		float	*out		Output array.
 * 
 * ********************************************************************/
	void getScaledPS(int n, float *mlt, float *R, float *smr, bool ShowDC, 
				bool OnlyDC, bool Validate, int m0, int m1, bool RevTrans, float *out);

/***********************************************************************
 * NAME : 	void getScaledPSCart(n,x,y,smr,ShowDC,OnlyDC,Validate,m0,m1,out)
 * 
 * DESCRIPTION : 
 * 		Calculates the scaled plasmaspheric electron density model.
 * 
 * INPUTS : 
 * 		int		n			Number of points to evaluate model at.
 * 		float	*x			Array of x-position (SM coords, in R_E).
 * 		float 	*y			Array of y-position (SM coords, in R_E).
 * 		float 	*smr		Array of SMR indices.
 * 		bool	ShowDC		If true, DC component included in output.
 * 		bool	OnlyDC		If true, only DC component is output.
 * 		bool	Validate	If true, all points will be checked to see
 * 							that they fit within the model parameters,
 * 							anything outside will be NAN.
 * 		int		m0			First azimuthal wave number to include.
 * 		int 	m1			Last azimuthal wave number to include.
 * 
 * OUTPUTS :
 * 		float	*out		Output array.
 * 
 * ********************************************************************/
	void getScaledPSCart(int n, float *x, float *y, float *smr, bool ShowDC,
				bool OnlyDC,bool Validate, int m0, int m1, bool RevTrans, float *out);

/***********************************************************************
 * NAME : 	void getAvPT(n,mlt,R,ShowDC,OnlyDC,Validate,m0,m1,RevTrans,out)
 * 
 * DESCRIPTION : 
 * 		Calculates the plasma trough electron density model.
 * 
 * INPUTS : 
 * 		int		n			Number of points to evaluate model at.
 * 		float	*mlt		Array of local times (in hours).
 * 		float 	*R			Array of L-shells (in R_E).
 * 		bool	ShowDC		If true, DC component included in output.
 * 		bool	OnlyDC		If true, only DC component is output.
 * 		bool	Validate	If true, all points will be checked to see
 * 							that they fit within the model parameters,
 * 							anything outside will be NAN.
 * 		int		m0			First azimuthal wave number to include.
 * 		int 	m1			Last azimuthal wave number to include.
 * 		bool	RevTrans	If true, reverses transformed densities to 
 * 							real units.
 * 
 * OUTPUTS :
 * 		float	*out		Output array.
 * 
 * ********************************************************************/
	void getAvPT(int n, float *mlt, float *R, bool ShowDC, bool OnlyDC, 
				bool Validate, int m0, int m1, bool RevTrans, float *out);
				
/***********************************************************************
 * NAME : 	void getAvPTCart(n,x,y,ShowDC,OnlyDC,Validate,m0,m1,out)
 * 
 * DESCRIPTION : 
 * 		Calculates the plasmatrough electron density model.
 * 
 * INPUTS : 
 * 		int		n			Number of points to evaluate model at.
 * 		float	*x			Array of x-position (SM coords, in R_E).
 * 		float 	*y			Array of y-position (SM coords, in R_E).
 * 		bool	ShowDC		If true, DC component included in output.
 * 		bool	OnlyDC		If true, only DC component is output.
 * 		bool	Validate	If true, all points will be checked to see
 * 							that they fit within the model parameters,
 * 							anything outside will be NAN.
 * 		int		m0			First azimuthal wave number to include.
 * 		int 	m1			Last azimuthal wave number to include.
 * 
 * OUTPUTS :
 * 		float	*out		Output array.
 * 
 * ********************************************************************/
	void getAvPTCart(int n, float *x, float *y, bool ShowDC, bool OnlyDC, 
				bool Validate, int m0, int m1, bool RevTrans, float *out);

/***********************************************************************
 * NAME : 	void getScaledPT(n,mlt,R,smr,ShowDC,OnlyDC,Validate,m0,m1,out)
 * 
 * DESCRIPTION : 
 * 		Calculates the scaled plasmatrough electron density model.
 * 
 * INPUTS : 
 * 		int		n			Number of points to evaluate model at.
 * 		float	*mlt		Array of local times (in hours).
 * 		float 	*R			Array of L-shells (in R_E).
 * 		float 	*smr		Array of SMR indices.
 * 		bool	ShowDC		If true, DC component included in output.
 * 		bool	OnlyDC		If true, only DC component is output.
 * 		bool	Validate	If true, all points will be checked to see
 * 							that they fit within the model parameters,
 * 							anything outside will be NAN.
 * 		int		m0			First azimuthal wave number to include.
 * 		int 	m1			Last azimuthal wave number to include.
 * 
 * OUTPUTS :
 * 		float	*out		Output array.
 * 
 * ********************************************************************/
	void getScaledPT(int n, float *mlt, float *R, float *smr, bool ShowDC, 
				bool OnlyDC, bool Validate, int m0, int m1, bool RevTrans, float *out);

/***********************************************************************
 * NAME : 	void getScaledPTCart(n,x,y,smr,ShowDC,OnlyDC,Validate,m0,m1,out)
 * 
 * DESCRIPTION : 
 * 		Calculates the scaled plasmatrough electron density model.
 * 
 * INPUTS : 
 * 		int		n			Number of points to evaluate model at.
 * 		float	*x			Array of x-position (SM coords, in R_E).
 * 		float 	*y			Array of y-position (SM coords, in R_E).
 * 		float 	*smr		Array of SMR indices.
 * 		bool	ShowDC		If true, DC component included in output.
 * 		bool	OnlyDC		If true, only DC component is output.
 * 		bool	Validate	If true, all points will be checked to see
 * 							that they fit within the model parameters,
 * 							anything outside will be NAN.
 * 		int		m0			First azimuthal wave number to include.
 * 		int 	m1			Last azimuthal wave number to include.
 * 
 * OUTPUTS :
 * 		float	*out		Output array.
 * 
 * ********************************************************************/
	void getScaledPTCart(int n, float *x, float *y, float *smr, bool ShowDC,
				bool OnlyDC,bool Validate, int m0, int m1, bool RevTrans, float *out);



/***********************************************************************
 * NAME : 	void getAvMav(n,mlt,R,ShowDC,OnlyDC,Validate,m0,m1,out)
 * 
 * DESCRIPTION : 
 * 		Calculates the combined plasmasphere/plasmatrough average ion 
 * 		mass model.
 * 
 * INPUTS : 
 * 		int		n			Number of points to evaluate model at.
 * 		float	*mlt		Array of local times (in hours).
 * 		float 	*R			Array of L-shells (in R_E).
 * 		bool	ShowDC		If true, DC component included in output.
 * 		bool	OnlyDC		If true, only DC component is output.
 * 		bool	Validate	If true, all points will be checked to see
 * 							that they fit within the model parameters,
 * 							anything outside will be NAN.
 * 		int		m0			First azimuthal wave number to include.
 * 		int 	m1			Last azimuthal wave number to include.
 * 
 * OUTPUTS :
 * 		float	*out		Output array.
 * 
 * ********************************************************************/
void getAvMav(int n, float *mlt, float *R, bool ShowDC, bool OnlyDC, 
				bool Validate, int m0, int m1, float *out);

/***********************************************************************
 * NAME : 	void getAvMavCart(n,mlt,R,ShowDC,OnlyDC,Validate,m0,m1,out)
 * 
 * DESCRIPTION : 
 * 		Calculates the combined plasmasphere/plasmatrough average ion 
 * 		mass model.
 * 
 * INPUTS : 
 * 		int		n			Number of points to evaluate model at.
 * 		float	*x			Array of x-position (SM coords, in R_E).
 * 		float 	*y			Array of y-position (SM coords, in R_E).
 * 		bool	ShowDC		If true, DC component included in output.
 * 		bool	OnlyDC		If true, only DC component is output.
 * 		bool	Validate	If true, all points will be checked to see
 * 							that they fit within the model parameters,
 * 							anything outside will be NAN.
 * 		int		m0			First azimuthal wave number to include.
 * 		int 	m1			Last azimuthal wave number to include.
 * 
 * OUTPUTS :
 * 		float	*out		Output array.
 * 
 * ********************************************************************/
void getAvMavCart(int n, float *x, float *y, bool ShowDC, bool OnlyDC, 
				bool Validate, int m0, int m1, float *out);

/***********************************************************************
 * NAME : 	void getScaledMav(n,mlt,R,smr,ShowDC,OnlyDC,Validate,m0,m1,out)
 * 
 * DESCRIPTION : 
 * 		Calculates the scaled plasmasphere/plasmatrough average ion mass
 * 		model.
 * 
 * INPUTS : 
 * 		int		n			Number of points to evaluate model at.
 * 		float	*mlt		Array of local times (in hours).
 * 		float 	*R			Array of L-shells (in R_E).
 * 		float 	*smr		Array of SMR indices.
 * 		bool	ShowDC		If true, DC component included in output.
 * 		bool	OnlyDC		If true, only DC component is output.
 * 		bool	Validate	If true, all points will be checked to see
 * 							that they fit within the model parameters,
 * 							anything outside will be NAN.
 * 		int		m0			First azimuthal wave number to include.
 * 		int 	m1			Last azimuthal wave number to include.
 * 
 * OUTPUTS :
 * 		float	*out		Output array.
 * 
 * ********************************************************************/
void getScaledMav(int n, float *mlt, float *R, float *smr, bool ShowDC,  
				bool OnlyDC, bool Validate, int m0, int m1, float *out);

/***********************************************************************
 * NAME : 	void getScaledMavCart(n,x,y,R,smr,ShowDC,OnlyDC,Validate,m0,m1,out)
 * 
 * DESCRIPTION : 
 * 		Calculates the scaled plasmasphere/plasmatrough average ion mass
 * 		model.
 * 
 * INPUTS : 
 * 		int		n			Number of points to evaluate model at.
 * 		float	*x			Array of x-position (SM coords, in R_E).
 * 		float 	*y			Array of y-position (SM coords, in R_E).
 * 		float 	*smr		Array of SMR indices.
 * 		bool	ShowDC		If true, DC component included in output.
 * 		bool	OnlyDC		If true, only DC component is output.
 * 		bool	Validate	If true, all points will be checked to see
 * 							that they fit within the model parameters,
 * 							anything outside will be NAN.
 * 		int		m0			First azimuthal wave number to include.
 * 		int 	m1			Last azimuthal wave number to include.
 * 
 * OUTPUTS :
 * 		float	*out		Output array.
 * 
 * ********************************************************************/
void getScaledMavCart(int n, float *x, float *y, float *smr, bool ShowDC,  
				bool OnlyDC, bool Validate, int m0, int m1, float *out);

/***********************************************************************
 * NAME : 	void getAvDen(n,mlt,R,ShowDC,OnlyDC,Validate,m0,m1,out)
 * 
 * DESCRIPTION : 
 * 		Calculates the combined plasmasphere/plasmatrough electron 
 * 		density model.
 * 
 * INPUTS : 
 * 		int		n			Number of points to evaluate model at.
 * 		float	*mlt		Array of local times (in hours).
 * 		float 	*R			Array of L-shells (in R_E).
 * 		bool	ShowDC		If true, DC component included in output.
 * 		bool	OnlyDC		If true, only DC component is output.
 * 		bool	Validate	If true, all points will be checked to see
 * 							that they fit within the model parameters,
 * 							anything outside will be NAN.
 * 		int		m0			First azimuthal wave number to include.
 * 		int 	m1			Last azimuthal wave number to include.
 * 
 * OUTPUTS :
 * 		float	*out		Output array.
 * 
 * ********************************************************************/
	void getAvDen(int n, float *mlt, float *R, bool ShowDC, bool OnlyDC, 
				bool Validate, int m0, int m1, float *out);

/***********************************************************************
 * NAME : 	void getAvDenCart(n,mlt,R,ShowDC,OnlyDC,Validate,m0,m1,out)
 * 
 * DESCRIPTION : 
 * 		Calculates the combined plasmasphere/plasmatrough electron 
 * 		density model.
 * 
 * INPUTS : 
 * 		int		n			Number of points to evaluate model at.
 * 		float	*x			Array of x-position (SM coords, in R_E).
 * 		float 	*y			Array of y-position (SM coords, in R_E).
 * 		bool	ShowDC		If true, DC component included in output.
 * 		bool	OnlyDC		If true, only DC component is output.
 * 		bool	Validate	If true, all points will be checked to see
 * 							that they fit within the model parameters,
 * 							anything outside will be NAN.
 * 		int		m0			First azimuthal wave number to include.
 * 		int 	m1			Last azimuthal wave number to include.
 * 
 * OUTPUTS :
 * 		float	*out		Output array.
 * 
 * ********************************************************************/
	void getAvDenCart(int n, float *x, float *y, bool ShowDC, bool OnlyDC, 
				bool Validate, int m0, int m1, float *out);

/***********************************************************************
 * NAME : 	void getScaledDen(n,mlt,R,smr,ShowDC,OnlyDC,Validate,m0,m1,out)
 * 
 * DESCRIPTION : 
 * 		Calculates the scaled plasmasphere/plasmatrough electron 
 * 		density model.
 * 
 * INPUTS : 
 * 		int		n			Number of points to evaluate model at.
 * 		float	*mlt		Array of local times (in hours).
 * 		float 	*R			Array of L-shells (in R_E).
 * 		float 	*smr		Array of SMR indices.
 * 		bool	ShowDC		If true, DC component included in output.
 * 		bool	OnlyDC		If true, only DC component is output.
 * 		bool	Validate	If true, all points will be checked to see
 * 							that they fit within the model parameters,
 * 							anything outside will be NAN.
 * 		int		m0			First azimuthal wave number to include.
 * 		int 	m1			Last azimuthal wave number to include.
 * 
 * OUTPUTS :
 * 		float	*out		Output array.
 * 
 * ********************************************************************/
	void getScaledDen(int n, float *mlt, float *R, float *smr, bool ShowDC,  
				bool OnlyDC, bool Validate, int m0, int m1, float *out);

/***********************************************************************
 * NAME : 	void getScaledDenCart(n,x,y,R,smr,ShowDC,OnlyDC,Validate,m0,m1,out)
 * 
 * DESCRIPTION : 
 * 		Calculates the scaled plasmasphere/plasmatrough electron 
 * 		density model.
 * 
 * INPUTS : 
 * 		int		n			Number of points to evaluate model at.
 * 		float	*x			Array of x-position (SM coords, in R_E).
 * 		float 	*y			Array of y-position (SM coords, in R_E).
 * 		float 	*smr		Array of SMR indices.
 * 		bool	ShowDC		If true, DC component included in output.
 * 		bool	OnlyDC		If true, only DC component is output.
 * 		bool	Validate	If true, all points will be checked to see
 * 							that they fit within the model parameters,
 * 							anything outside will be NAN.
 * 		int		m0			First azimuthal wave number to include.
 * 		int 	m1			Last azimuthal wave number to include.
 * 
 * OUTPUTS :
 * 		float	*out		Output array.
 * 
 * ********************************************************************/
	void getScaledDenCart(int n, float *x, float *y, float *smr, bool ShowDC,  
				bool OnlyDC, bool Validate, int m0, int m1, float *out);

/***********************************************************************
 * NAME : 	void getAvPMD(n,mlt,R,ShowDC,OnlyDC,Validate,m0,m1,out)
 * 
 * DESCRIPTION : 
 * 		Calculates the combined plasmasphere/plasmatrough plasma mass
 * 		density model.
 * 
 * INPUTS : 
 * 		int		n			Number of points to evaluate model at.
 * 		float	*mlt		Array of local times (in hours).
 * 		float 	*R			Array of L-shells (in R_E).
 * 		bool	ShowDC		If true, DC component included in output.
 * 		bool	OnlyDC		If true, only DC component is output.
 * 		bool	Validate	If true, all points will be checked to see
 * 							that they fit within the model parameters,
 * 							anything outside will be NAN.
 * 		int		m0			First azimuthal wave number to include.
 * 		int 	m1			Last azimuthal wave number to include.
 * 
 * OUTPUTS :
 * 		float	*out		Output array.
 * 
 * ********************************************************************/
	void getAvPMD(int n, float *mlt, float *R, bool ShowDC, bool OnlyDC, 
				bool Validate, int m0, int m1, float *out);

/***********************************************************************
 * NAME : 	void getAvPMDCart(n,mlt,R,ShowDC,OnlyDC,Validate,m0,m1,out)
 * 
 * DESCRIPTION : 
 * 		Calculates the combined plasmasphere/plasmatrough plasma mass
 * 		density model.
 * 
 * INPUTS : 
 * 		int		n			Number of points to evaluate model at.
 * 		float	*x			Array of x-position (SM coords, in R_E).
 * 		float 	*y			Array of y-position (SM coords, in R_E).
 * 		bool	ShowDC		If true, DC component included in output.
 * 		bool	OnlyDC		If true, only DC component is output.
 * 		bool	Validate	If true, all points will be checked to see
 * 							that they fit within the model parameters,
 * 							anything outside will be NAN.
 * 		int		m0			First azimuthal wave number to include.
 * 		int 	m1			Last azimuthal wave number to include.
 * 
 * OUTPUTS :
 * 		float	*out		Output array.
 * 
 * ********************************************************************/
	void getAvPMDCart(int n, float *x, float *y, bool ShowDC, bool OnlyDC, 
				bool Validate, int m0, int m1, float *out) ;

/***********************************************************************
 * NAME : 	void getScaledPMD(n,mlt,R,f107,smr,ShowDC,OnlyDC,Validate,m0,m1,out)
 * 
 * DESCRIPTION : 
 * 		Calculates the scaled combined plasmasphere/plasmatrough plasma 
 * 		mass density model.
 * 
 * INPUTS : 
 * 		int		n			Number of points to evaluate model at.
 * 		float	*mlt		Array of local times (in hours).
 * 		float 	*R			Array of L-shells (in R_E).
 * 		float 	*smr		Array of SMR indices.
 * 		bool	ShowDC		If true, DC component included in output.
 * 		bool	OnlyDC		If true, only DC component is output.
 * 		bool	Validate	If true, all points will be checked to see
 * 							that they fit within the model parameters,
 * 							anything outside will be NAN.
 * 		int		m0			First azimuthal wave number to include.
 * 		int 	m1			Last azimuthal wave number to include.
 * 
 * OUTPUTS :
 * 		float	*out		Output array.
 * 
 * ********************************************************************/
	void getScaledPMD(int n, float *mlt, float *R, float *smr, bool ShowDC,  
				bool OnlyDC, bool Validate, int m0, int m1, float *out);

/***********************************************************************
 * NAME : 	void getScaledPMDCart(n,x,y,f107,smr,ShowDC,OnlyDC,Validate,m0,m1,out)
 * 
 * DESCRIPTION : 
 * 		Calculates the scaled combined plasmasphere/plasmatrough plasma 
 * 		mass density model.
 * 
 * INPUTS : 
 * 		int		n			Number of points to evaluate model at.
 * 		float	*x			Array of x-position (SM coords, in R_E).
 * 		float 	*y			Array of y-position (SM coords, in R_E).
 * 		float 	*smr		Array of SMR indices.
 * 		bool	ShowDC		If true, DC component included in output.
 * 		bool	OnlyDC		If true, only DC component is output.
 * 		bool	Validate	If true, all points will be checked to see
 * 							that they fit within the model parameters,
 * 							anything outside will be NAN.
 * 		int		m0			First azimuthal wave number to include.
 * 		int 	m1			Last azimuthal wave number to include.
 * 
 * OUTPUTS :
 * 		float	*out		Output array.
 * 
 * ********************************************************************/
	void getScaledPMDCart(int n, float *x, float *y, float *smr, bool ShowDC,  
				bool OnlyDC, bool Validate, int m0, int m1, float *out);
}


/***********************************************************************
 * NAME : 	class MavTrans
 * 
 * DESCRIPTION : This object will handle the transformation of average
 * 			ion masses. We use a Box-Cox transform where lambda is a 
 * 			non-linear function of R.
 * 
 * 
 * ********************************************************************/

class MavTrans {
	public:
		MavTrans();
		~MavTrans();
		void PSTransform(int,float*,float*,float*);
		void PTTransform(int,float*,float*,float*);
		void PSRevTransform(int,float*,float*,float*);
		void PTRevTransform(int,float*,float*,float*);
	private:
		void ReadCoefficients();
	
		/*These are the number of degrees in the polynomials*/
		int nps_,npt_;
		
		/* polynomial coefficients */
		double *ps_, *pt_;
};



/***********************************************************************
 * NAME : float rescaleSMR(smr)
 * 
 * DESCRIPTION : Rescales the SMR index so it is suitable as an input to
 * 				the ANN.
 * 
 * INPUTS : 
 * 		float	smr		The SMR index.
 * 
 * RETURNS : 
 * 		float	smrt 	The rescaled SMR index.
 * 
 * ********************************************************************/
float rescaleSMR(float smr);

/***********************************************************************
 * NAME : float rescaleF107(f107)
 * 
 * DESCRIPTION : Rescales the F10.7 index so it is suitable as an input to
 * 				the ANN.
 * 
 * INPUTS : 
 * 		float	f107	The F10.7 index.
 * 
 * RETURNS : 
 * 		float	f107t 	The rescaled F10.7 index.
 * 
 * ********************************************************************/
float rescaleF107(float f107);

/***********************************************************************
 * NAME : float rescaleR(R)
 * 
 * DESCRIPTION : Rescales the L-shell so it is suitable as an input to
 * 				the ANN.
 * 
 * INPUTS : 
 * 		float	R		The L-shell.
 * 
 * RETURNS : 
 * 		float	Rt 		The rescaled L-shell.
 * 
 * ********************************************************************/
float rescaleR(float R);

/***********************************************************************
 * NAME : float unscaleDensity(dt)
 * 
 * DESCRIPTION : Reverses the Box-Cox transform of the density output
 * 				from the ANN.
 * 
 * INPUTS : 
 * 		float	dt		The transformed density output from the ANN.
 * 
 * RETURNS : 
 * 		float	d		Density in real units.
 * 
 * ********************************************************************/
float unscaleDensity(float dt);


/***********************************************************************
 * NAME : 	void polynomial(nd,coef,n,x,y)
 * 
 * DESCRIPTION : This function will calculate the result of a polynomial
 * 
 * INPUTS : 
 * 		int		nd		The degree of the polynomial
 * 		double	*coef	Coefficients, length = nd + 1
 * 		int		n		Number of points to evaluate
 * 		float 	*x		Array of points at which to calculate the 
 * 						polynomial
 * 
 * OUTPUTS : 
 * 		double	*y		Result 
 * ********************************************************************/
void polynomial(int nd, double *coef, int n, float *x, double *y);

/***********************************************************************
 * NAME : 	void polynomial(nd,coef,n,x,y)
 * 
 * DESCRIPTION : This function will calculate the result of a polynomial
 * 
 * INPUTS : 
 * 		int		nd		The degree of the polynomial
 * 		float	*coef	Coefficients, length = nd + 1
 * 		int		n		Number of points to evaluate
 * 		float 	*x		Array of points at which to calculate the 
 * 						polynomial
 * 
 * OUTPUTS : 
 * 		float	*y		Result 
 * ********************************************************************/
void polynomial(int nd, float *coef, int n, float *x, float *y);

/***********************************************************************
 * NAME	: 	void reverseArray(n,x)
 * 
 * DESCRIPTION : 	Reverses the elements of an array.
 * 
 * INPUTS : 
 * 		int		n		The number of elements
 * 		float 	*x		The array to be reversed
 * 
 * ********************************************************************/
void reverseArray(int n, float *x);

/***********************************************************************
 * NAME	: 	void reverseArray(n,x)
 * 
 * DESCRIPTION : 	Reverses the elements of an array.
 * 
 * INPUTS : 
 * 		int		n		The number of elements
 * 		double 	*x		The array to be reversed
 * 
 * ********************************************************************/
void reverseArray(int n, double *x);


/***********************************************************************
 * NAME : 	class ANNModel
 * 
 * DESCRIPTION : This is the basic model class object for storing the 
 * 				ANN object and obtaining the model parameters. This 
 * 				class should not be used directly, it should be 
 * 				inherited by one of the other model classes.
 * 
 * 
 * ********************************************************************/
class ANNModel {
	public:
		/* This ann will provide the components of the model */
		NetworkFunc *ann_;
		
		/* Load the neural network */
		void LoadANN(unsigned char *);
		
		/* calculate the model components */
		/* Calculate the model components */
		void ModelComponents(int,float*,float*,float*,float*,float**);
		void ModelComponentsCart(int,float*,float*,float*,float*,float**);

		/* Cartesian to MLT and R */
		void CartMLTR(int,float*,float*,float*,float*);
		
		/* we need to know the number of m-numbers */
		int nm_, *m_;
		
		/* frequencies */
		float *wl_;
};

/***********************************************************************
 * NAME : 	class ANNMavHModel
 * 
 * DESCRIPTION : This class object is based upon the ANNModel object and
 * 				will store the average ion mass neural network. Its 
 * 				member functions can be used to access the model.
 * 
 * 				NOTE - this is for hot ions!!!
 * 
 * ********************************************************************/
class ANNMavHModel: public ANNModel {
	public:
		/* constructor for the model object */
		ANNMavHModel(unsigned char *);
		
		/* destructor for the model object */
		~ANNMavHModel();
		
		/* the full model - this ought to be used by default */
		void Model(int,float*,float*,float*,bool,bool,bool,int,int,float*);
		void ModelCart(int,float*,float*,float*,bool,bool,bool,int,int,float*);	
};

/***********************************************************************
 * NAME : 	class ANNMavPSModel
 * 
 * DESCRIPTION : This class object is based upon the ANNModel object and
 * 				will store the average ion mass neural network. Its 
 * 				member functions can be used to access the model.
 * 
 * 				This is the cold ion plasmsphere model!
 * 
 * ********************************************************************/
class ANNMavPSModel: public ANNModel {
	public:
		/* constructor for the model object */
		ANNMavPSModel(unsigned char *);
		
		/* destructor for the model object */
		~ANNMavPSModel();
		
		/* the full model - this ought to be used by default */
		void Model(int,float*,float*,float*,bool,bool,bool,int,int,bool,float*);
		void ModelCart(int,float*,float*,float*,bool,bool,bool,int,int,bool,float*);	

	private:
		MavTrans *MT_;
};


/***********************************************************************
 * NAME : 	class ANNMavPTModel
 * 
 * DESCRIPTION : This class object is based upon the ANNModel object and
 * 				will store the average ion mass neural network. Its 
 * 				member functions can be used to access the model.
 * 
 * 				This is the cold ion plasmsphere model!
 * 
 * ********************************************************************/
class ANNMavPTModel: public ANNModel {
	public:
		/* constructor for the model object */
		ANNMavPTModel(unsigned char *);
		
		/* destructor for the model object */
		~ANNMavPTModel();
		
		/* the full model - this ought to be used by default */
		void Model(int,float*,float*,float*,bool,bool,bool,int,int,bool,float*);
		void ModelCart(int,float*,float*,float*,bool,bool,bool,int,int,bool,float*);	

	private:
		MavTrans *MT_;
};

/***********************************************************************
 * NAME : 	class ANNProbModel
 * 
 * DESCRIPTION : This class object is based upon the ANNModel object and
 * 				will store the probability model neural network. Its 
 * 				member functions can be used to access the model.
 * 
 * ********************************************************************/
class ANNProbModel: public ANNModel {
	public:
		/* constructor for the model object */
		ANNProbModel(unsigned char *);
		
		/* destructor for the model object */
		~ANNProbModel();
		
		/* the full model - this ought to be used by default */
		void Model(int,float*,float*,float*,bool,bool,bool,int,int,float*);
		void ModelCart(int,float*,float*,float*,bool,bool,bool,int,int,float*);	
};

/***********************************************************************
 * NAME : 	class ANNPSModel
 * 
 * DESCRIPTION : This class object is based upon the ANNModel object and
 * 				will store the plasmasphere model neural network. Its 
 * 				member functions can be used to access the model.
 * 
 * ********************************************************************/
class ANNPSModel: public ANNModel {
	public:
		/* constructor for the model object */
		ANNPSModel(unsigned char *);
		
		/* destructor for the model object */
		~ANNPSModel();
		
		/* the full model - this ought to be used by default */
		void Model(int,float*,float*,float*,bool,bool,bool,int,int,bool,float*);
		void ModelCart(int,float*,float*,float*,bool,bool,bool,int,int,bool,float*);	
};

/***********************************************************************
 * NAME : 	class ANNPTModel
 * 
 * DESCRIPTION : This class object is based upon the ANNModel object and
 * 				will store the plasma trough model neural network. Its 
 * 				member functions can be used to access the model.
 * 
 * ********************************************************************/
class ANNPTModel: public ANNModel {
	public:
		/* constructor for the model object */
		ANNPTModel(unsigned char *);
		
		/* destructor for the model object */
		~ANNPTModel();
		
		/* the full model - this ought to be used by default */
		void Model(int,float*,float*,float*,bool,bool,bool,int,int,bool,float*);
		void ModelCart(int,float*,float*,float*,bool,bool,bool,int,int,bool,float*);	
};




/***********************************************************************
 * NAME : 	class AvModel
 * 
 * DESCRIPTION : This is hte basic model class object for storing the
 * 				average model parameters. This class should not be used
 * 				directly, it should be inherited by one of the other 
 * 				model classes.
 * 
 * 
 * ********************************************************************/
class AvModel {
	public:
		/* these pointers will be used to store the model variables */
		int ndc_, Rshape_[2], Ishape_[2];
		float *dc_, **R_, **I_;
		
		/* this is for storing the number of m-numbers */
		int nm_;
		int *m_;
		float *wl_;
		
		/* read in the model variables */
		void ReadModelParams(unsigned char *);
		
		/* calculate the model components */
		void PeriodicComponents(int,float*,float*,float**);
		
		/* Cartesian to MLT and R */
		void CartMLTR(int,float*,float*,float*,float*);
};




/***********************************************************************
 * NAME : 	class AvMavHModel
 * 
 * DESCRIPTION : This class object is based upon the AvModel object and
 * 				will store the average ion mass model parameters. Its 
 * 				member functions can be used to access the model.
 * 
 * 				NOTE - this is the hot average ion mass model - it bares
 * 				little resemblance to the cold composition.
 * 
 * ********************************************************************/
class AvMavHModel: public AvModel {
	public:
		/* model constructor */
		AvMavHModel(unsigned char *);
		
		/* model destructor */
		~AvMavHModel();
		
		/* DC function */
		void DC(int,float*,float*);
		
		/* Calculate the model separate components */
		void ModelComponents(int,float*,float*,float*,float**);
		void ModelComponentsCart(int,float*,float*,float*,float**);
		
		/* The full model - use this by default */
		void Model(int,float*,float*,bool,bool,bool,int,int,float*);
		void ModelCart(int,float*,float*,bool,bool,bool,int,int,float*);
};


/***********************************************************************
 * NAME : 	class AvMavPSModel
 * 
 * DESCRIPTION : This class object is based upon the AvModel object and
 * 				will store the average ion mass model parameters. Its 
 * 				member functions can be used to access the model.
 * 
 * 				NOTE - this is the cold ion model.
 * 
 * ********************************************************************/
class AvMavPSModel: public AvModel {
	public:
		/* model constructor */
		AvMavPSModel(unsigned char *);
		
		/* model destructor */
		~AvMavPSModel();
		
		/* DC function */
		void DC(int,float*,float*);
		
		/* Calculate the model separate components */
		void ModelComponents(int,float*,float*,float*,float**);
		void ModelComponentsCart(int,float*,float*,float*,float**);
		
		/* The full model - use this by default */
		void Model(int,float*,float*,bool,bool,bool,int,int,bool,float*);
		void ModelCart(int,float*,float*,bool,bool,bool,int,int,bool,float*);
	private:
		MavTrans *MT_;
};

/***********************************************************************
 * NAME : 	class AvMavPTModel
 * 
 * DESCRIPTION : This class object is based upon the AvModel object and
 * 				will store the average ion mass model parameters. Its 
 * 				member functions can be used to access the model.
 * 
 * 				NOTE - this is the cold ion model.
 * 
 * ********************************************************************/
class AvMavPTModel: public AvModel {
	public:
		/* model constructor */
		AvMavPTModel(unsigned char *);
		
		/* model destructor */
		~AvMavPTModel();
		
		/* DC function */
		void DC(int,float*,float*);
		
		/* Calculate the model separate components */
		void ModelComponents(int,float*,float*,float*,float**);
		void ModelComponentsCart(int,float*,float*,float*,float**);
		
		/* The full model - use this by default */
		void Model(int,float*,float*,bool,bool,bool,int,int,bool,float*);
		void ModelCart(int,float*,float*,bool,bool,bool,int,int,bool,float*);
	private:
		MavTrans *MT_;
};


/***********************************************************************
 * NAME : 	class AvProbModel
 * 
 * DESCRIPTION : This class object is based upon the AvModel object and
 * 				will store the average probability model parameters. Its 
 * 				member functions can be used to access the model.
 * 
 * ********************************************************************/
class AvProbModel: public AvModel {
	public:
		/* model constructor */
		AvProbModel(unsigned char *);
		
		/* model destructor */
		~AvProbModel();
		
		/* DC function */
		void DC(int,float*,float*);
		
		/* Calculate the model separate components */
		void ModelComponents(int,float*,float*,float*,float**);
		void ModelComponentsCart(int,float*,float*,float*,float**);
		
		/* The full model - use this by default */
		void Model(int,float*,float*,bool,bool,bool,int,int,float*);
		void ModelCart(int,float*,float*,bool,bool,bool,int,int,float*);
};

/***********************************************************************
 * NAME : 	class AvPSModel
 * 
 * DESCRIPTION : This class object is based upon the AvModel object and
 * 				will store the plasmasphere density model parameters. 
 * 				Its member functions can be used to access the model.
 * 
 * ********************************************************************/
class AvPSModel: public AvModel {
	public:
		/* model constructor */
		AvPSModel(unsigned char *);
		
		/* model destructor */
		~AvPSModel();
		
		/* DC function */
		void DC(int,float*,float*);
		
		/* Calculate the model separate components */
		void ModelComponents(int,float*,float*,float*,float**);
		void ModelComponentsCart(int,float*,float*,float*,float**);
		
		/* The full model - use this by default */
		void Model(int,float*,float*,bool,bool,bool,int,int,bool,float*);
		void ModelCart(int,float*,float*,bool,bool,bool,int,int,bool,float*);
};

/***********************************************************************
 * NAME : 	class AvPTModel
 * 
 * DESCRIPTION : This class object is based upon the AvModel object and
 * 				will store the plasma trough density model parameters. 
 * 				Its member functions can be used to access the model.
 * 
 * ********************************************************************/
class AvPTModel: public AvModel {
	public:
		/* model constructor */
		AvPTModel(unsigned char *);
		
		/* model destructor */
		~AvPTModel();
		
		/* DC function */
		void DC(int,float*,float*);
		
		/* Calculate the model separate components */
		void ModelComponents(int,float*,float*,float*,float**);
		void ModelComponentsCart(int,float*,float*,float*,float**);
		
		/* The full model - use this by default */
		void Model(int,float*,float*,bool,bool,bool,int,int,bool,float*);
		void ModelCart(int,float*,float*,bool,bool,bool,int,int,bool,float*);
};

#endif
