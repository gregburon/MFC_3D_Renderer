

/*************************************************/
/*                                               */
/*    Computer Science 480                       */
/*    Programming Assignment #2                  */
/*    Created By: Greg Buron                     */
/*    November 3, 2001                           */
/*                                               */
/*                                               */
/*************************************************/


#pragma warning(disable: 4786)
using namespace std;


#include "stdafx.h"
#include <typeinfo.h>
#include <vector>
#include <string>
#include "Object3D.h"
#include "defines.h"
#include <typeinfo.h>
#include <io.h>
#include <fstream>
#include <string.h>
#include <limits.h>
#include <float.h>
#include <math.h>
#include "Material.h"

/****************************************************/
/*                                                  */
/*  Constructor/Destructor for the Material class.  */
/*                                                  */
/****************************************************/


Material::Material()
{
	this->m_Name               = "";
	this->m_KaRed              = 0.0;
	this->m_KaGreen            = 0.0;
	this->m_KaBlue             = 0.0;
	this->m_KdRed              = 0.0;
	this->m_KdGreen            = 0.0;
	this->m_KdBlue             = 0.0;
	this->m_KsRed              = 0.0;
	this->m_KsGreen            = 0.0;
	this->m_KsBlue             = 0.0;
	this->m_SpecularExponent   = 0.0;
}


Material::Material(const int& TYPE)
{
	this->SetMaterial(TYPE);
}

Material::~Material()
{

}


/****************************************************/
/*                                                  */
/*  Get Functions for the Material class.           */
/*                                                  */
/****************************************************/
string  Material::GetMaterialName()
{
	return this->m_Name;
}

double  Material::GetMaterialKaRed()
{
	return this->m_KaRed;
}

double  Material::GetMaterialKaGreen()
{
	return this->m_KaGreen;
}

double  Material::GetMaterialKaBlue()
{
	return this->m_KaBlue;
}

double  Material::GetMaterialKdRed()
{
	return this->m_KdRed;
}

double  Material::GetMaterialKdGreen()
{
	return this->m_KdGreen;
}

double  Material::GetMaterialKdBlue()
{
	return this->m_KdBlue;
}

double  Material::GetMaterialKsRed()
{
	return this->m_KsRed;
}

double  Material::GetMaterialKsGreen()
{
	return this->m_KsGreen;
}

double  Material::GetMaterialKsBlue()
{
	return this->m_KsBlue;
}

double  Material::GetMaterialSpecularExponent()
{
	return this->m_SpecularExponent;
}

string  Material::GetMaterialName() const
{
	return this->m_Name;
}

double  Material::GetMaterialKaRed() const 
{
	return this->m_KaRed;
}

double  Material::GetMaterialKaGreen() const 
{
	return this->m_KaGreen;
}

double  Material::GetMaterialKaBlue() const 
{
	return this->m_KaBlue;
}

double  Material::GetMaterialKdRed() const 
{
	return this->m_KdRed;
}

double  Material::GetMaterialKdGreen() const 
{
	return this->m_KdGreen;
}

double  Material::GetMaterialKdBlue() const 
{
	return this->m_KdBlue;
}

double  Material::GetMaterialKsRed() const 
{
	return this->m_KsRed;
}

double  Material::GetMaterialKsGreen() const 
{
	return this->m_KsGreen;
}

double  Material::GetMaterialKsBlue() const 
{
	return this->m_KsBlue;
}

double  Material::GetMaterialSpecularExponent() const 
{
	return this->m_SpecularExponent;
}


void Material::SetMaterial(const int& TYPE)
{
	switch(TYPE)
	{
	case BLUE_PLASTIC:
		this->m_Name = "Blue Plastic";
		this->m_KaRed   = 0.0;
		this->m_KaGreen = 0.0;
		this->m_KaBlue  = 0.8;

		this->m_KdRed   = 0.01;
		this->m_KdGreen = 0.01;
		this->m_KdBlue  = 0.8;

		this->m_KsRed   = 0.5;
		this->m_KsGreen = 0.5;
		this->m_KsBlue  = 0.5;

		this->m_SpecularExponent = 32.0;

		break;

	case BRASS:
		this->m_Name = "Brass";
		this->m_KaRed   = 0.329412;
		this->m_KaGreen = 0.223519;
		this->m_KaBlue  = 0.027451;

		this->m_KdRed   = 0.780392;
		this->m_KdGreen = 0.568627;
		this->m_KdBlue  = 0.113725;

		this->m_KsRed   = 0.992157;
		this->m_KsGreen = 0.941176;
		this->m_KsBlue  = 0.807843;

		this->m_SpecularExponent = 27.8974;

		break;

	case BRONZE:
		this->m_Name = "Bronze";
		this->m_KaRed   = 0.2125;
		this->m_KaGreen = 0.1275;
		this->m_KaBlue  = 0.054;

		this->m_KdRed   = 0.714;
		this->m_KdGreen = 0.4284;
		this->m_KdBlue  = 0.18144;

		this->m_KsRed   = 0.393548;
		this->m_KsGreen = 0.271906;
		this->m_KsBlue  = 0.166721;

		this->m_SpecularExponent = 25.6;

		break;

	case CHROME:
		this->m_Name = "Chrome";
		this->m_KaRed   = 0.25;
		this->m_KaGreen = 0.25;
		this->m_KaBlue  = 0.25;

		this->m_KdRed   = 0.4;
		this->m_KdGreen = 0.4;
		this->m_KdBlue  = 0.4;

		this->m_KsRed   = 0.774597;
		this->m_KsGreen = 0.774597;
		this->m_KsBlue  = 0.774597;

		this->m_SpecularExponent = 76.8;

		break;

	case COPPER:
		this->m_Name = "Copper";
		this->m_KaRed   = 0.19125;
		this->m_KaGreen = 0.0735;
		this->m_KaBlue  = 0.0225;

		this->m_KdRed   = 0.7038;
		this->m_KdGreen = 0.27048;
		this->m_KdBlue  = 0.0828;
		
		this->m_KsRed   = 0.256777;
		this->m_KsGreen = 0.137622;
		this->m_KsBlue  = 0.086014;

		this->m_SpecularExponent = 12.8;

		break;

	case GOLD:
		this->m_Name = "Gold";
		this->m_KaRed   = 0.24725;
		this->m_KaGreen = 0.1995;
		this->m_KaBlue  = 0.0745;

		this->m_KdRed   = 0.75164;
		this->m_KdGreen = 0.60648;
		this->m_KdBlue  = 0.22648;
		
		this->m_KsRed   = 0.628281;
		this->m_KsGreen = 0.555802;
		this->m_KsBlue  = 0.366065;

		this->m_SpecularExponent = 51.2;

		break;

	case PEWTER:
		this->m_Name = "Pewter";
		this->m_KaRed   = 0.10588;
		this->m_KaGreen = 0.058824;
		this->m_KaBlue  = 0.113725;

		this->m_KdRed   = 0.427451;
		this->m_KdGreen = 0.470588;
		this->m_KdBlue  = 0.541176;
		
		this->m_KsRed   = 0.333333;
		this->m_KsGreen = 0.333333;
		this->m_KsBlue  = 0.521569;

		this->m_SpecularExponent = 9.84615;

		break;

	case SILVER:
		this->m_Name = "Silver";
		this->m_KaRed   = 0.19225;
		this->m_KaGreen = 0.19225;
		this->m_KaBlue  = 0.19225;

		this->m_KdRed   = 0.50754;
		this->m_KdGreen = 0.50754;
		this->m_KdBlue  = 0.50754;
		
		this->m_KsRed   = 0.508273;
		this->m_KsGreen = 0.508273;
		this->m_KsBlue  = 0.508273;

		this->m_SpecularExponent = 51.2;

		break;

	case POLISHED_SILVER:
		this->m_Name = "Polished Silver";
		this->m_KaRed   = 0.23125;
		this->m_KaGreen = 0.23125;
		this->m_KaBlue  = 0.23125;

		this->m_KdRed   = 0.2775;
		this->m_KdGreen = 0.2775;
		this->m_KdBlue  = 0.2775;
		
		this->m_KsRed   = 0.773911;
		this->m_KsGreen = 0.773911;
		this->m_KsBlue  = 0.773911;

		this->m_SpecularExponent = 89.6;

		break;

	case LIGHT:
		this->m_Name = "Light";
		this->m_KaRed   = 0.50000;
		this->m_KaGreen = 0.50000;
		this->m_KaBlue  = 0.50000;

		this->m_KdRed   = 0.50000;
		this->m_KdGreen = 0.50000;
		this->m_KdBlue  = 0.50000;
		
		this->m_KsRed   = 0.50000;
		this->m_KsGreen = 0.50000;
		this->m_KsBlue  = 0.50000;

		this->m_SpecularExponent = 1.0;

		break;

	default:
		this->m_Name = "Custom Material";
		this->m_KaRed   = 0.50000;
		this->m_KaGreen = 0.50000;
		this->m_KaBlue  = 0.50000;

		this->m_KdRed   = 0.50000;
		this->m_KdGreen = 0.50000;
		this->m_KdBlue  = 0.50000;

		this->m_KsRed   = 0.50000;
		this->m_KsGreen = 0.50000;
		this->m_KsBlue  = 0.50000;

		this->m_SpecularExponent = 1.0;

		break;

	}// end switch
}

void Material::SetMaterial(const double& KaRed,   const double& KaGreen,
		                   const double& KaBlue,  const double& KdRed, 
				           const double& KdGreen, const double& KdBlue, 
					       const double& KsRed,   const double& KsGreen, 
					       const double& KsBlue,  const double& SpecularExponent)
{
	this->m_KaRed   = KaRed;
	this->m_KaGreen = KaGreen;
	this->m_KaBlue  = KaBlue;

	this->m_KdRed   = KdRed;
	this->m_KdGreen = KdGreen;
	this->m_KdBlue  = KdBlue;
	
	this->m_KsRed   = KsRed;
	this->m_KsBlue  = KsGreen;
	this->m_KsBlue  = KsBlue;

	this->m_SpecularExponent = SpecularExponent;
}




/****************************************************/
/*                                                  */
/*  Set Functions for the Material class.           */
/*                                                  */
/****************************************************/
void    Material::SetMaterialName(string val)
{
	this->m_Name = val;
}

void    Material::SetMaterialKaRed(double val)
{
	this->m_KaRed = val;
}

void    Material::SetMaterialKaGreen(double val)
{
	this->m_KaGreen = val;
}

void    Material::SetMaterialKaBlue(double val)
{
	this->m_KaBlue = val;
}

void    Material::SetMaterialKdRed(double val)
{
	this->m_KdRed = val;
}

void    Material::SetMaterialKdGreen(double val)
{
	this->m_KdGreen = val;
}

void    Material::SetMaterialKdBlue(double val)
{
	this->m_KdBlue = val;
}

void    Material::SetMaterialKsRed(double val)
{
	this->m_KsRed = val;
}

void    Material::SetMaterialKsGreen(double val)
{
	this->m_KsGreen = val;
}

void    Material::SetMaterialKsBlue(double val)
{
	this->m_KsBlue = val;
}

void    Material::SetMaterialSpecularExponent(double val)
{
	this->m_SpecularExponent = val;
}

  

/****************************************************/
/*                                                  */
/*  Overloaded operators for the Material class.    */
/*                                                  */
/****************************************************/
Material Material::operator =(const Material& rhs)
{
	this->m_KaRed       = rhs.m_KaRed;
	this->m_KaGreen     = rhs.m_KaGreen;
	this->m_KaBlue      = rhs.m_KaBlue;

	this->m_KdRed       = rhs.m_KdRed;
	this->m_KdGreen     = rhs.m_KdGreen;
	this->m_KdBlue      = rhs.m_KdBlue;

	this->m_KsRed       = rhs.m_KsRed;
	this->m_KsGreen     = rhs.m_KsGreen;
	this->m_KsBlue      = rhs.m_KsBlue;

	this->m_SpecularExponent   =  rhs.m_SpecularExponent;

	return *this;
}