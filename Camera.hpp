/**
* @file Camera.h
* @author Takashi Michikawa <michikawa@acm.org>
*/
#pragma once
#ifndef CAMERA_H
#define CAMERA_H 1
#include <Eigen/Dense>

class Camera
{
private:
        Eigen::Quaterniond rotation_;	// ��]
        Eigen::Vector3d center_;	// ���S�_
        double	 dist_;			// ���_-���S�_�̋���
        double   radius_;		// �o�E���f�B���O���̔��a
        double   fov_;			// ��p
private:
        Camera ( const Camera& that );
        void operator = ( const Camera& that );
public:
        explicit Camera ( const double fov = 40 );
        void init( const Eigen::Vector3d& bmin, const Eigen::Vector3d& bmax );
        void clone ( const Camera& that );
        void getLookAt( Eigen::Vector3d& eye, Eigen::Vector3d& center, Eigen::Vector3d& up );
        void getPerspective( double& fov, double& zNear, double& zFar );
        void rotate( const double  oldx, const double oldy, const double newx, const double newy );
private:
        void project_to_sphere( const double& radius, Eigen::Vector3d& p ) const;
};
#endif//CAMERA_H