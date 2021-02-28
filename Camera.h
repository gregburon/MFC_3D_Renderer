

/*************************************************/
/*                                               */
/*    Computer Science 480                       */
/*    Programming Assignment #2                  */
/*    Created By: Greg Buron                     */
/*    November 3, 2001                           */
/*                                               */
/*                                               */
/*************************************************/

#ifndef CAMERA_H
#define CAMERA_H

#pragma warning(disable: 4786)
using namespace std;


#include "stdafx.h"
#include <typeinfo.h>
#include <vector>
#include <string>
#include "defines.h"
#include "Vector.h"


class Camera
{
public:
	Camera();
	~Camera();

	// Get the camera's Center of projection functions.
	double GetCameraCOP_U();
	double GetCameraCOP_V();
	double GetCameraCOP_N();
	double GetCameraCOP_U() const;
	double GetCameraCOP_V() const;
	double GetCameraCOP_N() const;
	Vector GetCameraCOP_Vector();
	Vector GetCameraCOP_Vector() const;

	// Get the camera's View reference point functions
	double GetCameraVRP_X();
	double GetCameraVRP_Y();
	double GetCameraVRP_Z();
	Vector GetCameraVRP_Vector();
	Vector GetCameraVRP_Vector() const;

	// Get the camera's View Up vector functions
	double GetCameraVUP_X();
	double GetCameraVUP_Y();
	double GetCameraVUP_Z();

	Vector GetCameraVUP_Vector();
	Vector GetCameraVUP_Vector() const;

	// Get the camera's View Plane Normal functions
	double GetCameraVPN_X();
	double GetCameraVPN_Y();
	double GetCameraVPN_Z();
	double GetCameraVPN_X() const;
	double GetCameraVPN_Y() const;
	double GetCameraVPN_Z() const;
	Vector GetCameraVPN_Vector();
	Vector GetCameraVPN_Vector() const;

	// Set the camera's Center of projection functions.
	void SetCameraCOP_U(double val);
	void SetCameraCOP_V(double val);
	void SetCameraCOP_N(double val);

	// Set the camera's View reference point functions
	void SetCameraVRP_X(double val);
	void SetCameraVRP_Y(double val);
	void SetCameraVRP_Z(double val);

	// Set the camera's View Up vector functions
	void SetCameraVUP_X(double val);
	void SetCameraVUP_Y(double val);
	void SetCameraVUP_Z(double val);

	// Set the camera's View Plane Normal functions
	void SetCameraVPN_X(double val);
	void SetCameraVPN_Y(double val);
	void SetCameraVPN_Z(double val);

private:

	point_uvn   m_COP;
	point       m_VRP;
	Vector		m_VUP;
	Vector      m_VPN;
};


#endif