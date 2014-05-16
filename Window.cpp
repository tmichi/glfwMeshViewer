#include "Window.hpp"

Window::Window ( const int width, const int height, char* windowName ) : oldx_( 0 ), oldy_( 0 )
{
        this->window_ =  glfwCreateWindow( width, height, windowName, NULL, NULL );
        glfwMakeContextCurrent( this->window_ );
        glfwSetFramebufferSizeCallback( this->window_, Window::resize );
}

Window::~Window( void )
{
        glfwTerminate();
        return;
}

bool
Window::operator ! ( void )
{
        return ! ( this->window_ );
}

GLFWwindow*
Window::getWindow()
{
        return this->window_;
}

void
Window::getMousePosition( double& ox, double& oy, double& nx, double& ny )
{
        ox = this->oldx_;
        oy = this->oldy_;

        double mx, my;
        int w, h;
        glfwGetCursorPos( this->window_, &mx, &my );
        glfwGetWindowSize( this->window_, &w, &h );
        const int r = w < h ? w : h;

        nx = ( 2.0 * mx - w ) / r;
        ny = ( h - 2.0 * my ) / r;

        this->oldx_ = nx;
        this->oldy_ = ny;
        return;
}

double
Window::getAspectRatio( void ) const
{
        int w, h;
        glfwGetWindowSize( this->window_, &w, &h );
        return  w * 1.0 / h ;
}

void
Window::resize ( GLFWwindow* window, int width, int height )
{
        glfwMakeContextCurrent( window );
        glViewport( 0, 0, width, height );
        return;
}

