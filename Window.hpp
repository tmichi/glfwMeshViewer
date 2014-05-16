/**
 * @file Window.hpp
 * @author Takashi Michikawa <michikawa@acm.org>
 */
#ifndef WINDOW_HPP
#define WINDOW_HPP 1
#include <GLFW/glfw3.h>

class Window
{
private:
        GLFWwindow* window_;
        double oldx_;
        double oldy_;
private:

public:
        explicit Window ( const int width, const int height, char* windowName = "Hello World" );
        virtual ~Window( void );
        bool operator ! ( void );
        GLFWwindow* getWindow();
        void getMousePosition( double& ox, double& oy, double& nx, double& ny );

        double getAspectRatio( void ) const;
        static void resize ( GLFWwindow* window, int width, int height );
};
#endif // WINDOW_HPP


