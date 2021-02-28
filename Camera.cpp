


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
#include "defines.h"
#include "Vector.h"
#include "Camera.h"


Camera::Camera()
{
	// Set the camera to its initial 
	// point and pointing toward the origin.
	m_COP._u =  0.0;
	m_COP._v =  0.0;
	m_COP._n = -100.0;
	m_COP._h =  1.0;

	m_VRP._x = 0.0;
	m_VRP._y = 0.0;
	m_VRP._z = 50.0;
	m_VRP._h = 1.0;

	m_VUP.SetVector(0.0, 1.0, 0.0);

	m_VPN.SetVector(0.0, 0.0, -1.0);

}

Camera::~Camera()
{

}



/***********************************************************/
/*                                                         */
/*  Camera Get Parameter functions                         */
/*                                                         */
/***********************************************************/

// Get the camera's Center of projection functions.
double Camera::GetCameraCOP_U()
{
	return this->m_COP._u;
}

double Camera::GetCameraCOP_V()
{
	return this->m_COP._v;
}

double Camera::GetCameraCOP_N()
{
	return this->m_COP._n;
}


double Camera::GetCameraCOP_U() const
{
	return this->m_COP._u;
}

double Camera::GetCameraCOP_V() const
{
	return this->m_COP._v;
}

double Camera::GetCameraCOP_N() const
{
	return this->m_COP._n;
}


Vector Camera::GetCameraCOP_Vector()
{
	Vector temp;

	temp.SetVectorX(this->m_COP._u);
	temp.SetVectorY(this->m_COP._v);
	temp.SetVectorZ(this->m_COP._n);
	temp.SetVectorH(1.0);

	return temp;
}

Vector Camera::GetCameraCOP_Vector() const
{
	Vector temp;

	temp.SetVectorX(this->m_COP._u);
	temp.SetVectorY(this->m_COP._v);
	temp.SetVectorZ(this->m_COP._n);
	temp.SetVectorH(1.0);

	return temp;
}

// Get the camera's View reference point functions
double Camera::GetCameraVRP_X()
{
	return this->m_VRP._x;
}

double Camera::GetCameraVRP_Y()
{
	return this->m_VRP._y;
}

double Camera::GetCameraVRP_Z()
{
	return this->m_VRP._z;
}

Vector Camera::GetCameraVRP_Vector()
{
	Vector temp;

	temp.SetVectorX(this->m_VRP._x);
	temp.SetVectorY(this->m_VRP._y);
	temp.SetVectorZ(this->m_VRP._z);
	temp.SetVectorH(1.0);

	return temp;
}

Vector Camera::GetCameraVRP_Vector() const
{
	Vector temp;

	temp.SetVectorX(this->m_VRP._x);
	temp.SetVectorY(this->m_VRP._y);
	temp.SetVectorZ(this->m_VRP._z);
	temp.SetVectorH(1.0);

	return temp;
}


// Get the camera's View Up vector functions
double Camera::GetCameraVUP_X()
{
	return this->m_VUP.GetVectorX();
}

double Camera::GetCameraVUP_Y()
{
	return this->m_VUP.GetVectorY();
}

double Camera::GetCameraVUP_Z()
{
	return this->m_VUP.GetVectorZ();
}

Vector Camera::GetCameraVUP_Vector()
{
	return this->m_VUP;
}

Vector Camera::GetCameraVUP_Vector() const
{
	return this->m_VUP;
}



// Get the camera's View Plane Normal functions
double Camera::GetCameraVPN_X()
{
	return this->m_VPN.GetVectorX();
}

double Camera::GetCameraVPN_Y()
{
	return this->m_VPN.GetVectorY();
}

double Camera::GetCameraVPN_Z()
{
	return this->m_VPN.GetVectorZ();
}

Vector Camera::GetCameraVPN_Vector()
{
	return this->m_VPN;
}

Vector Camera::GetCameraVPN_Vector() const
{
	return this->m_VPN;
}


// Get the camera's View Plane Normal functions, constant
double Camera::GetCameraVPN_X() const
{
	return this->m_VPN.GetVectorX();
}

double Camera::GetCameraVPN_Y() const
{
	return this->m_VPN.GetVectorY();
}

double Camera::GetCameraVPN_Z() const
{
	return this->m_VPN.GetVectorZ();
}




/***********************************************************/
/*                                                         */
/*  Camera Set Parameter functions                         */
/*                                                         */
/***********************************************************/

// Set the camera's Center of projection functions.
void Camera::SetCameraCOP_U(double val)
{
	this->m_COP._u = val;
}

void Camera::SetCameraCOP_V(double val)
{
	this->m_COP._v = val;
}

void Camera::SetCameraCOP_N(double val)
{
	this->m_COP._n = val;
}


// Set the camera's View reference point functions
void Camera::SetCameraVRP_X(double val)
{
	this->m_VRP._x = val;
}

void Camera::SetCameraVRP_Y(double val)
{
	this->m_VRP._y = val;
}

void Camera::SetCameraVRP_Z(double val)
{
	this->m_VRP._z = val;
}


// Set the camera's View Up vector functions
void Camera::SetCameraVUP_X(double val)
{
	this->m_VUP.SetVectorX(val);
}

void Camera::SetCameraVUP_Y(double val)
{
	this->m_VUP.SetVectorY(val);
}

void Camera::SetCameraVUP_Z(double val)
{
	this->m_VUP.SetVectorZ(val);
}


// Set the camera's View Plane Normal functions
void Camera::SetCameraVPN_X(double val)
{
	this->m_VPN.SetVectorX(val);
}

void Camera::SetCameraVPN_Y(double val)
{
	this->m_VPN.SetVectorY(val);
}

void Camera::SetCameraVPN_Z(double val)
{
	this->m_VPN.SetVectorZ(val);
}






