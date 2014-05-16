#include "Camera.hpp"
#include <iostream>

Camera::Camera ( const double fov ): rotation_ ( Eigen::Quaterniond( 1,0,0,0 ) ), center_( Eigen::Vector3d() ), dist_( 0 ), radius_( 100 ), fov_( fov )
{
        Eigen::Vector3d b( 1,1,1 );
        b.normalize();
        b*= 100;
        this->init( -b, b );
        return;
}


void
Camera::init( const Eigen::Vector3d& bmin, const Eigen::Vector3d& bmax )
{
        this->center_ = ( bmin + bmax ) * 0.5;
        this->radius_ = ( bmin - bmax ).norm()* 0.5;
        this->dist_ = this->radius_  / std::sin ( this->fov_ / 360.0 * 3.1415926 );

        return;
}
void
Camera::clone ( const Camera& that )
{
        this->rotation_ = that.rotation_;
        this->center_ = that.center_;
        this->dist_   = that.dist_;
        this->radius_ = that.radius_;
        this->fov_    = that.fov_;
        return;
}


void
Camera::getLookAt( Eigen::Vector3d& eye, Eigen::Vector3d& center, Eigen::Vector3d& up )
{
        Eigen::Matrix3d r; // rotation matrix
        r.setIdentity();
        r = this->rotation_.toRotationMatrix();
        Eigen::Vector3d eye0( 0, 0, this->dist_ );
        Eigen::Vector3d up0( 0, 1, 0 );
        center = this->center_;

        eye = r * eye0 + this->center_;
        up  = r * up0;
        return;
}

void
Camera::getPerspective( double& fov, double& zNear, double& zFar )
{
        fov = this->fov_;
        zNear = this->dist_ - this->radius_;
        zFar  = this->dist_ + this->radius_;
        if( zNear < 0 ) zNear = 0.01;

        return;
}
void
Camera::rotate( const double  oldx, const double oldy, const double newx, const double newy )
{
        Eigen::Vector3d oldp( oldx, oldy, 0 );
        Eigen::Vector3d newp( newx, newy, 0 );

        if ( oldp.isApprox( newp, 1.0e-16 ) ) return;

        double radius_virtual_sphere = 0.9;
        this->project_to_sphere( radius_virtual_sphere, oldp );
        this->project_to_sphere( radius_virtual_sphere, newp );
        Eigen::Quaterniond dr;
        dr.setFromTwoVectors( newp, oldp );
        this->rotation_ *= dr;
        return;
}
void
Camera::project_to_sphere( const double& radius, Eigen::Vector3d& p ) const
{
        p.z() = 0;
        const double d = p.x()* p.x()+ p.y() * p.y();
        const double r = radius * radius;
        if ( d < r )	p.z() = std::sqrt( r - d );
        else		p *= radius / p.norm();
        return;
}
