#ifndef COLOR_H
#define COLOR_H
#include <string>

//only works for unix systems
namespace Color {
    #define RESET   ((const char*)"\033[0m")

    #define BLACK   ((const char*)"\033[30m")      /* Black */
    #define RED     ((const char*)"\033[31m")      /* Red */
    #define GREEN   ((const char*)"\033[32m")      /* Green */
    #define YELLOW  ((const char*)"\033[33m")      /* Yellow */
    #define BLUE    ((const char*)"\033[34m")      /* Blue */
    #define MAGENTA ((const char*)"\033[35m")      /* Magenta */
    #define CYAN    ((const char*)"\033[36m")      /* Cyan */
    #define WHITE   ((const char*)"\033[37m")      /* White */

    #define BOLDBLACK   ((const char*)"\033[1m\033[30m")      /* Bold Black */
    #define BOLDRED     ((const char*)"\033[1m\033[31m")      /* Bold Red */
    #define BOLDGREEN   ((const char*)"\033[1m\033[32m")      /* Bold Green */
    #define BOLDYELLOW  ((const char*)"\033[1m\033[33m")      /* Bold Yellow */
    #define BOLDBLUE    ((const char*)"\033[1m\033[34m")      /* Bold Blue */
    #define BOLDMAGENTA ((const char*)"\033[1m\033[35m")      /* Bold Magenta */
    #define BOLDCYAN    ((const char*)"\033[1m\033[36m")      /* Bold Cyan */
    #define BOLDWHITE   ((const char*)"\033[1m\033[37m")      /* Bold White */

    inline auto Color(int n, const std::string& s) {
        return "\33[38;5;" + std::to_string(n) + 'm' + s + "\33[m";
    }
} //namespace Color

#endif // COLOR_H
