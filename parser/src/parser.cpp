#include "parser.h"

#include <string>
#include <fstream>
#include <sstream>
#include <streambuf>

namespace
{

void readVector(size_t size, std::vector<Coord>& v, std::istringstream& ss)
{
    v.resize(size);
    for (size_t i = 0; i < size; ++i)
        ss >> v[i];
}

MathFunc readFunc(std::istringstream& ss)
{
    std::string type;
    ss >> type;
    if (type == "const")
    {
        float val;
        ss >> val;
        return [val](Coord x, Coord y){
            return val;
        };
    }
    else if (type == "linear")
    {
        float a, b, c;
        ss >> a >> b >> c;
        return [a, b, c](Coord x, Coord y){ return a*x + b*y + c; };
    }
    else if (type == "quad")
    {
        float a, b, c;
        ss >> a >> b >> c;
        return [a, b, c](Coord x, Coord y){
            return a*x*x + b*y*y + c;
        };
    }
    else if (type == "x")
    {
        return [](Coord x, Coord y){ return x; };
    }
    else if (type == "y")
    {
        return [](Coord x, Coord y){ return y; };
    }
    else
    {
        return [](Coord x, Coord y){ return 0; };
    }
}

std::string& ltrim(std::string& str, const std::string& chars = "\t\n\v\f\r ")
{
    str.erase(0, str.find_first_not_of(chars));
    return str;
}

std::string& rtrim(std::string& str, const std::string& chars = "\t\n\v\f\r ")
{
    str.erase(str.find_last_not_of(chars) + 1);
    return str;
}

std::string& trim(std::string& str, const std::string& chars = "\t\n\v\f\r ")
{
    return ltrim(rtrim(str, chars), chars);
}

}

InputData parseInput(const std::string& str)
{
    std::string input = str;
    trim(input);

    /**
     * Nx, Ny - количество точек разбиения по направлению x,y
     * hx[0 .. Nx-1], hy[0 .. Ny-1] - и массивы шагов по x,y.
     * XO, YO -- координата левого нижнего угла прямоугольной области
     * k_x(x,y), k_y(x,y), f(x,y) -- коэффициенты уравнения
     * phi(x,y) -- функция, задающая граничное условие.
     *
     * cond1 -- граничное условие первого рода
     */

    size_t Nx, Ny;
    InputData inputData;
    std::istringstream ss(input);
    ss >> Nx >> Ny;

    readVector(Nx, inputData.hx, ss);
    readVector(Ny, inputData.hy, ss);

    ss >> inputData.x0 >> inputData.y0;

    inputData.k_x = readFunc(ss);
    inputData.k_y = readFunc(ss);
    inputData.f = readFunc(ss);
    inputData.phi = readFunc(ss);

    size_t condSize;
    ss >> condSize;
    for (int i = 0; i < condSize; ++i)
    {
        int pos;
        float val;
        ss >> pos >> val;
        inputData.cond1[pos] = val;
    }

    return inputData;
}

InputData parseFile(const std::string& file)
{
    std::ifstream f(file);
    std::string input((std::istreambuf_iterator<char>(f)),
            std::istreambuf_iterator<char>()
    );
    return parseInput(input);
}
