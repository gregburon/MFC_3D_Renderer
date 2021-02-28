



/*************************************************/
/*                                               */
/*    Computer Science 480                       */
/*    Programming Assignment #2                  */
/*    Created By: Greg Buron                     */
/*    November 3, 2001                           */
/*                                               */
/*                                               */
/*************************************************/

#ifndef MATERIAL_H
#define MATERIAL_H

#pragma warning(disable: 4786)
using namespace std;


#include "stdafx.h"
#include <typeinfo.h>
#include <vector>
#include <string>
#include "defines.h"


class Material
{
public:

	Material();
	Material(const int& TYPE);
	~Material();

	void    SetMaterial(const int& TYPE);
	void    SetMaterial(const double& KaRed,   const double& KaGreen,
		                const double& KaBlue,  const double& KdRed, 
						const double& KdGreen, const double& KdBlue, 
						const double& KsRed,   const double& KsGreen, 
						const double& KsBlue,  const double& SpecularExponent);

	string  GetMaterialName();
	double  GetMaterialKaRed();
	double  GetMaterialKaGreen();
	double  GetMaterialKaBlue();
	double  GetMaterialKdRed();
	double  GetMaterialKdGreen();
	double  GetMaterialKdBlue();
	double  GetMaterialKsRed();
	double  GetMaterialKsGreen();
	double  GetMaterialKsBlue();
	double  GetMaterialSpecularExponent();

	string  GetMaterialName() const;
	double  GetMaterialKaRed() const;
	double  GetMaterialKaGreen() const;
	double  GetMaterialKaBlue() const;
	double  GetMaterialKdRed() const;
	double  GetMaterialKdGreen() const;
	double  GetMaterialKdBlue() const;
	double  GetMaterialKsRed() const;
	double  GetMaterialKsGreen() const;
	double  GetMaterialKsBlue() const;
	double  GetMaterialSpecularExponent() const;

	void    SetMaterialName(string name);
	void    SetMaterialKaRed(double val);
	void    SetMaterialKaGreen(double val);
	void    SetMaterialKaBlue(double val);
	void    SetMaterialKdRed(double val);
	void    SetMaterialKdGreen(double val);
	void    SetMaterialKdBlue(double val);
	void    SetMaterialKsRed(double val);
	void    SetMaterialKsGreen(double val);
	void    SetMaterialKsBlue(double val);
	void    SetMaterialSpecularExponent(double val);

	Material operator =(const Material& rhs);

private:
	
	string  m_Name;

	double  m_KaRed;
	double  m_KaGreen;
	double  m_KaBlue;

	double  m_KdRed;
	double  m_KdGreen;
	double  m_KdBlue;

	double  m_KsRed;
	double  m_KsGreen;
	double  m_KsBlue;

	double  m_SpecularExponent;
};


#endif