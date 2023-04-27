#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include <array>

using std::endl;
using std::cerr;

#include <GL/glew.h>    // include GLEW and new version of GL on Windows
#include <GLFW/glfw3.h> // GLFW helper library

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h" // for textures!

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/vec3.hpp>   // glm::vec3
#include <glm/vec4.hpp>   // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>  // glm::translate, glm::rotate, glm::scale

const int color_list[50][50] = {{1, 5, 0, 0, 5, 5, 1, 5, 0, 5, 1, 0, 5, 5, 5, 0, 1, 1, 1, 1, 0, 5, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 30, 30, 30, 1, 30, 1, 30, 30, 1},
               {0, 42, 5, 0, 0, 5, 5, 0, 0, 5, 5, 0, 0, 0, 0, 5, 5, 0, 1, 5, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 30, 0, 1, 0, 0, 0, 0, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30},
               {5, 0, 0, 5, 5, 0, 5, 0, 5, 0, 0, 5, 5, 0, 0, 5, 0, 0, 5, 0, 5, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 30, 30, 1, 30, 30, 30, 30, 30, 30},
               {42, 0, 5, 5, 0, 0, 42, 0, 5, 42, 0, 0, 5, 5, 0, 1, 1, 5, 1, 0, 5, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 1, 30, 30, 1, 30, 30, 30, 30, 30, 30},
               {1, 5, 0, 0, 42, 5, 0, 0, 0, 0, 5, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 30, 30, 1, 30, 30, 1, 30, 30, 30, 30, 30},
               {0, 5, 0, 0, 5, 0, 34, 5, 0, 0, 5, 0, 1, 0, 5, 1, 1, 1, 0, 1, 1, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 0, 30, 1, 30, 30, 1, 30, 30, 30, 30, 30, 30, 30},
               {0, 0, 0, 5, 0, 43, 34, 30, 0, 1, 0, 0, 5, 0, 0, 1, 0, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 1, 1, 30, 30, 1, 30, 1, 1, 30, 30, 30, 30, 30, 30},
               {1, 0, 0, 5, 1, 28, 10, 18, 1, 30, 0, 1, 0, 1, 0, 1, 1, 0, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 30, 1, 0, 0, 0, 1, 1, 0, 0, 30, 1, 30, 30, 1, 30, 30, 30, 30, 30, 30, 30, 30},
               {0, 5, 0, 0, 0, 36, 34, 16, 16, 22, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 38, 7, 4, 32, 38, 1, 0, 0, 1, 0, 1, 30, 30, 30, 1, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30},
               {0, 1, 1, 0, 0, 36, 36, 16, 16, 34, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 15, 15, 15, 15, 2, 19, 19, 1, 1, 1, 0, 0, 1, 1, 1, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30},
               {1, 0, 1, 5, 0, 6, 6, 22, 36, 34, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 0, 42, 2, 15, 21, 8, 31, 39, 20, 33, 33, 0, 0, 1, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 26, 30, 30, 30, 30},
               {0, 0, 0, 5, 0, 24, 35, 16, 16, 34, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 1, 18, 16, 16, 2, 2, 33, 35, 37, 33, 1, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 26, 34, 26, 26, 30, 30},
               {1, 1, 0, 0, 1, 38, 31, 3, 16, 16, 0, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 43, 18, 6, 28, 16, 16, 16, 34, 16, 16, 34, 30, 1, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 6, 34, 26, 30, 30, 30},
               {0, 1, 5, 0, 1, 42, 3, 23, 23, 16, 10, 5, 1, 0, 1, 1, 0, 0, 1, 0, 1, 9, 23, 13, 42, 34, 16, 16, 16, 28, 36, 16, 26, 30, 30, 30, 30, 30, 30, 30, 26, 18, 34, 16, 18, 34, 18, 30, 30, 30},
               {0, 0, 1, 0, 0, 1, 1, 3, 6, 3, 2, 4, 0, 1, 0, 0, 1, 0, 1, 38, 10, 28, 2, 15, 37, 16, 16, 34, 38, 24, 16, 16, 16, 26, 26, 30, 30, 30, 30, 30, 30, 3, 3, 16, 16, 16, 26, 30, 30, 30},
               {1, 0, 0, 1, 0, 1, 42, 23, 23, 2, 19, 15, 4, 1, 0, 0, 1, 38, 0, 1, 36, 22, 20, 15, 18, 34, 16, 16, 16, 37, 2, 34, 16, 26, 30, 30, 30, 30, 30, 30, 30, 30, 6, 34, 18, 16, 30, 26, 30, 30},
               {30, 1, 38, 1, 0, 1, 30, 28, 20, 31, 15, 7, 2, 14, 1, 1, 0, 1, 0, 30, 36, 22, 15, 15, 9, 16, 16, 16, 16, 2, 2, 16, 16, 26, 30, 30, 30, 30, 30, 30, 30, 30, 3, 9, 16, 16, 30, 30, 30, 30},
               {0, 1, 0, 0, 38, 1, 0, 30, 37, 15, 11, 2, 2, 33, 35, 5, 1, 0, 1, 1, 31, 6, 9, 19, 8, 19, 27, 16, 16, 15, 15, 15, 34, 30, 30, 30, 30, 30, 30, 30, 30, 43, 3, 3, 16, 16, 30, 26, 26, 30},
               {0, 0, 0, 1, 0, 42, 38, 30, 5, 15, 15, 2, 15, 33, 2, 33, 29, 1, 0, 0, 40, 41, 3, 40, 12, 12, 41, 8, 27, 16, 16, 16, 19, 0, 0, 30, 30, 30, 30, 30, 26, 32, 36, 6, 22, 30, 26, 26, 26, 26},
               {38, 38, 38, 38, 0, 1, 30, 0, 38, 38, 15, 15, 33, 33, 33, 33, 33, 2, 0, 1, 40, 40, 15, 15, 15, 15, 15, 32, 41, 19, 16, 8, 3, 0, 18, 30, 30, 30, 30, 26, 35, 11, 37, 3, 34, 26, 18, 30, 30, 30},
               {1, 0, 0, 1, 38, 0, 38, 38, 30, 38, 14, 15, 2, 2, 2, 2, 33, 15, 15, 24, 13, 32, 15, 15, 15, 15, 15, 15, 15, 40, 19, 41, 0, 18, 30, 30, 30, 38, 30, 2, 30, 21, 15, 37, 15, 3, 22, 18, 16, 32},
               {31, 19, 0, 38, 38, 42, 0, 30, 1, 38, 38, 15, 15, 15, 15, 2, 15, 15, 15, 15, 15, 23, 40, 32, 15, 15, 15, 15, 15, 15, 40, 16, 0, 0, 30, 30, 18, 34, 15, 15, 15, 31, 31, 15, 34, 3, 22, 36, 3, 32},
               {19, 10, 3, 43, 10, 26, 0, 38, 38, 1, 0, 38, 15, 15, 15, 2, 2, 15, 15, 15, 15, 15, 31, 31, 40, 40, 12, 12, 40, 23, 19, 32, 43, 42, 15, 15, 15, 2, 15, 15, 15, 17, 32, 3, 3, 6, 41, 27, 41, 20},
               {31, 19, 3, 31, 19, 32, 3, 19, 23, 23, 1, 1, 36, 2, 15, 15, 15, 15, 15, 15, 15, 15, 32, 40, 32, 32, 40, 40, 31, 32, 15, 2, 15, 2, 15, 15, 15, 15, 15, 15, 15, 15, 15, 3, 20, 3, 42, 5, 10, 37},
               {3, 21, 4, 23, 31, 22, 21, 4, 16, 3, 19, 4, 31, 27, 15, 15, 15, 15, 15, 15, 15, 15, 15, 32, 15, 15, 32, 15, 2, 33, 2, 33, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 38, 27, 18, 23, 37, 37, 20, 24},
               {10, 20, 16, 19, 31, 19, 4, 19, 21, 39, 31, 19, 19, 16, 32, 27, 15, 15, 15, 15, 15, 15, 21, 20, 15, 32, 8, 33, 33, 35, 35, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 9, 38, 35, 16, 36, 3, 23, 20, 3},
               {40, 19, 22, 37, 21, 4, 21, 21, 31, 32, 20, 19, 7, 31, 6, 8, 16, 15, 2, 15, 15, 8, 2, 12, 32, 12, 39, 31, 33, 33, 25, 33, 15, 15, 15, 15, 15, 15, 15, 15, 38, 30, 18, 35, 31, 15, 32, 32, 23, 36},
               {19, 4, 4, 19, 16, 19, 6, 22, 31, 31, 23, 19, 10, 31, 4, 4, 37, 32, 2, 2, 15, 11, 8, 21, 11, 12, 25, 20, 35, 35, 33, 15, 15, 15, 15, 15, 15, 15, 31, 31, 20, 28, 10, 37, 32, 10, 22, 31, 9, 32},
               {8, 3, 23, 20, 31, 12, 31, 19, 8, 3, 4, 20, 3, 10, 21, 4, 40, 15, 2, 15, 15, 21, 21, 7, 7, 31, 25, 20, 33, 24, 2, 2, 15, 15, 15, 15, 32, 24, 30, 4, 10, 19, 39, 34, 31, 6, 6, 4, 31, 31},
               {4, 31, 22, 16, 39, 4, 31, 21, 4, 6, 19, 31, 16, 4, 39, 21, 18, 15, 2, 15, 2, 7, 7, 32, 7, 12, 39, 33, 33, 35, 2, 2, 15, 31, 8, 24, 16, 31, 23, 36, 4, 19, 24, 31, 19, 37, 4, 31, 19, 21},
               {16, 3, 15, 6, 6, 23, 19, 7, 43, 16, 22, 20, 19, 19, 3, 23, 4, 15, 2, 15, 15, 7, 8, 7, 7, 7, 7, 33, 35, 33, 2, 2, 35, 16, 3, 15, 20, 19, 32, 19, 31, 32, 37, 31, 31, 10, 17, 4, 37, 19},
               {15, 27, 10, 39, 20, 3, 3, 27, 23, 32, 16, 19, 31, 10, 13, 19, 15, 15, 2, 2, 15, 33, 2, 25, 8, 17, 35, 33, 35, 24, 33, 2, 15, 3, 4, 40, 4, 31, 31, 6, 22, 21, 3, 20, 19, 31, 20, 4, 31},
               {32, 27, 4, 4, 8, 3, 16, 20, 32, 31, 23, 16, 0, 16, 3, 23, 15, 2, 2, 15, 2, 2, 15, 25, 17, 39, 33, 33, 33, 24, 35, 24, 2, 9, 22, 7, 31, 35, 20, 4, 21, 31, 40, 16, 17, 36, 7, 6, 21, 31},
               {25, 27, 19, 17, 27, 37, 7, 2, 2, 37, 37, 20, 37, 21, 32, 37, 15, 2, 2, 33, 33, 15, 15, 21, 33, 33, 33, 24, 33, 33, 24, 24, 2, 17, 12, 21, 32, 32, 20, 39, 12, 17, 19, 21, 4, 31, 3, 21, 8, 21},
               {7, 27, 8, 39, 19, 9, 37, 15, 15, 15, 20, 16, 32, 39, 20, 3, 15, 2, 2, 33, 2, 15, 33, 33, 33, 33, 33, 33, 24, 35, 33, 25, 24, 5, 31, 12, 20, 32, 4, 31, 31, 4, 6, 12, 16, 31, 23, 19, 40, 16},
               {31, 17, 4, 4, 4, 17, 37, 15, 15, 15, 2, 13, 37, 21, 32, 4, 39, 2, 2, 33, 15, 2, 33, 33, 33, 33, 33, 33, 24, 24, 35, 35, 24, 36, 8, 21, 8, 4, 12, 19, 31, 16, 4, 20, 10, 20, 6, 4, 37, 20},
               {8, 20, 41, 4, 32, 31, 40, 15, 15, 32, 20, 28, 23, 31, 21, 8, 4, 3, 15, 2, 2, 2, 33, 33, 33, 37, 33, 33, 33, 33, 24, 35, 35, 23, 8, 11, 7, 4, 11, 4, 27, 31, 4, 31, 8, 3, 16, 32, 21, 32},
               {4, 17, 32, 4, 20, 21, 12, 17, 15, 20, 2, 37, 8, 32, 21, 11, 39, 36, 6, 2, 33, 2, 2, 2, 2, 2, 2, 33, 33, 24, 24, 25, 35, 3, 31, 8, 7, 4, 4, 4, 19, 15, 32, 22, 19, 24, 0, 32, 17, 15},
               {2, 20, 21, 31, 32, 11, 39, 15, 15, 15, 2, 20, 4, 31, 21, 11, 36, 13, 36, 36, 36, 6, 23, 37, 37, 24, 30, 16, 16, 34, 14, 14, 34, 20, 19, 11, 39, 4, 4, 4, 3, 32, 23, 3, 3, 22, 2, 8, 21, 6},
               {2, 25, 21, 15, 22, 11, 39, 32, 15, 15, 15, 15, 31, 31, 17, 31, 36, 6, 36, 10, 10, 18, 18, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 15, 7, 11, 7, 11, 7, 4, 23, 23, 3, 3, 37, 15, 15, 17, 17, 36},
               {15, 13, 17, 39, 32, 17, 39, 32, 15, 32, 15, 15, 31, 17, 17, 7, 36, 6, 36, 36, 28, 22, 18, 34, 34, 34, 16, 34, 16, 16, 16, 34, 34, 2, 32, 11, 7, 4, 11, 4, 32, 15, 15, 20, 15, 15, 15, 31, 17, 4},
               {15, 15, 7, 7, 32, 31, 21, 2, 2, 2, 20, 15, 32, 18, 31, 7, 6, 6, 6, 6, 36, 10, 34, 18, 22, 18, 22, 22, 9, 9, 18, 16, 2, 15, 21, 11, 7, 4, 11, 17, 17, 17, 3, 3, 17, 17, 15, 39, 32, 20},
               {15, 32, 39, 32, 31, 7, 32, 15, 15, 15, 2, 15, 34, 16, 31, 32, 17, 6, 3, 3, 6, 10, 10, 22, 27, 6, 22, 16, 16, 9, 16, 16, 31, 32, 19, 32, 7, 4, 31, 17, 21, 17, 17, 17, 21, 17, 15, 4, 31, 32},
               {15, 32, 7, 31, 21, 11, 15, 32, 32, 15, 31, 36, 32, 20, 31, 19, 20, 36, 6, 3, 3, 36, 19, 6, 36, 16, 16, 16, 16, 16, 16, 16, 8, 15, 36, 32, 21, 19, 32, 17, 25, 17, 17, 35, 35, 35, 31, 31, 31, 25},
               {32, 27, 7, 31, 32, 31, 32, 20, 7, 15, 12, 11, 17, 31, 17, 17, 31, 20, 6, 6, 6, 3, 6, 18, 16, 16, 16, 16, 16, 16, 16, 18, 7, 20, 8, 7, 31, 8, 40, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17},
               {2, 41, 7, 35, 32, 32, 18, 32, 32, 15, 34, 32, 21, 11, 37, 35, 37, 17, 36, 3, 3, 3, 36, 22, 16, 16, 16, 16, 16, 34, 16, 36, 21, 16, 36, 22, 40, 12, 39, 17, 17, 31, 17, 17, 17, 17, 17, 17, 25, 17},
               {20, 32, 8, 19, 36, 22, 18, 35, 35, 3, 34, 2, 2, 32, 20, 37, 3, 15, 3, 3, 6, 3, 10, 16, 16, 16, 16, 16, 16, 16, 4, 18, 34, 19, 4, 6, 11, 21, 3, 10, 9, 22, 22, 9, 18, 22, 18, 9, 9, 9},
               {35, 35, 21, 31, 16, 34, 16, 31, 31, 3, 16, 31, 17, 9, 24, 2, 6, 6, 36, 3, 3, 3, 10, 34, 16, 16, 16, 16, 16, 13, 13, 22, 18, 20, 22, 11, 11, 39, 9, 17, 17, 17, 17, 17, 31, 17, 17, 31, 20},
               {31, 31, 6, 8, 16, 35, 31, 25, 25, 35, 17, 25, 17, 35, 9, 18, 18, 34, 18, 3, 3, 3, 27, 9, 16, 16, 16, 16, 34, 16, 18, 6, 36, 20, 31, 15, 2, 39, 20, 17, 17, 31, 17, 17, 31, 17, 17, 17, 17, 17},
               {28, 31, 31, 35, 35, 31, 25, 31, 31, 20, 22, 18, 18, 34, 18, 18, 18, 18, 3, 3, 3, 41, 41, 41, 41, 41, 16, 34, 34, 18, 18, 18, 36, 25, 17, 6, 6, 31, 36, 36, 10, 3, 36, 9, 9, 18, 18, 16, 18}};

const float color_codes[44][3] = {{0.7882, 0.7843, 0.8588}, {0.7451, 0.8235, 0.8510}, {0.0706, 0.1451, 0.0980}, {0.5686, 0.5020, 0.3843}, {1.0, 0.9333, 0.5529}, {0.6941, 0.8196, 0.8314},
                       {0.5725, 0.5255, 0.4275}, {0.8863, 0.7333, 0.2078}, {0.8196, 0.6078, 0.1098}, {0.7922, 0.7765, 0.7255}, {0.6902, 0.6314, 0.6118}, {0.7294, 0.6392, 0.0},
                       {0.6588, 0.2078, 0.0980}, {0.4510, 0.5490, 0.4863}, {0.8039, 0.8941, 0.8863}, {0.0431, 0.0510, 0.1098}, {0.9686, 0.9020, 0.8275}, {0.4588, 0.4863, 0.0980},
                       {0.8196, 0.8157, 0.8000}, {0.8196, 0.7137, 0.4784}, {0.2196, 0.1451, 0.0784}, {0.6510, 0.5373, 0.1255}, {0.7843, 0.7412, 0.6510}, {0.4275, 0.3176, 0.2863},
                       {0.2784, 0.3529, 0.3686}, {0.2510, 0.4745, 0.1412}, {0.7804, 0.8392, 0.8509}, {0.921, 0.722, 0.722}, {0.717, 0.741, 0.741}, {0.7608, 0.8471, 0.851},
                       {0.784, 0.808, 0.859}, {0.447, 0.298, 0.102}, {0.2039, 0.0941, 0.0118}, {0.0, 0.255, 0.067}, {0.882, 0.875, 0.878}, {0.2627, 0.3137, 0.2039},
                       {0.6196, 0.6157, 0.5412}, {0.25098, 0.22353, 0.2}, {0.7843, 0.8039, 0.7765}, {0.8549, 0.7882, 0.2863}, {0.447, 0.102, 0.0}, {0.8078, 0.2431, 0.0196},
                       {0.6745, 0.7529, 0.7804}, {0.7647, 0.7373, 0.7686}};

class RenderManager;

void        SetUpPuddles(int, RenderManager &);
const char *GetVertexShader();
const char *GetFragmentShader();

class Triangle
{
  public:
    glm::vec3 v0;
    glm::vec3 v1;
    glm::vec3 v2;
};

std::vector<Triangle> SplitTriangle(std::vector<Triangle> &list)
{
    std::vector<Triangle> output(4*list.size());
    output.resize(4*list.size());
    for (unsigned int i = 0 ; i < list.size() ; i++)
    {
        Triangle t = list[i];
        glm::vec3 vmid1, vmid2, vmid3;
        vmid1 = (t.v0 + t.v1) / 2.0f;
        vmid2 = (t.v1 + t.v2) / 2.0f;
        vmid3 = (t.v0 + t.v2) / 2.0f;
        output[4*i+0].v0 = t.v0;
        output[4*i+0].v1 = vmid1;
        output[4*i+0].v2 = vmid3;
        output[4*i+1].v0 = t.v1;
        output[4*i+1].v1 = vmid2;
        output[4*i+1].v2 = vmid1;
        output[4*i+2].v0 = t.v2;
        output[4*i+2].v1 = vmid3;
        output[4*i+2].v2 = vmid2;
        output[4*i+3].v0 = vmid1;
        output[4*i+3].v1 = vmid2;
        output[4*i+3].v2 = vmid3;
    }
    return output;
}

void PushVertex(std::vector<float>& coords,
                const glm::vec3& v)
{
  coords.push_back(v.x);
  coords.push_back(v.y);
  coords.push_back(v.z);
}

//
// Sets up a cylinder that is the circle x^2+y^2=1 extruded from
// Z=0 to Z=1.
//
void GetCylinderData(std::vector<float>& coords, std::vector<float>& normals)
{
  int nfacets = 30;
  for (int i = 0 ; i < nfacets ; i++)
  {
    double angle = 3.14159*2.0*i/nfacets;
    double nextAngle = (i == nfacets-1 ? 0 : 3.14159*2.0*(i+1)/nfacets);
    glm::vec3 fnormal(0.0f, 0.0f, 1.0f);
    glm::vec3 bnormal(0.0f, 0.0f, -1.0f);
    glm::vec3 fv0(0.0f, 0.0f, 1.0f);
    glm::vec3 fv1(cos(angle), sin(angle), 1);
    glm::vec3 fv2(cos(nextAngle), sin(nextAngle), 1);
    glm::vec3 bv0(0.0f, 0.0f, 0.0f);
    glm::vec3 bv1(cos(angle), sin(angle), 0);
    glm::vec3 bv2(cos(nextAngle), sin(nextAngle), 0);
    // top and bottom circle vertices
    PushVertex(coords, fv0);
    PushVertex(normals, fnormal);
    PushVertex(coords, fv1);
    PushVertex(normals, fnormal);
    PushVertex(coords, fv2);
    PushVertex(normals, fnormal);
    PushVertex(coords, bv0);
    PushVertex(normals, bnormal);
    PushVertex(coords, bv1);
    PushVertex(normals, bnormal);
    PushVertex(coords, bv2);
    PushVertex(normals, bnormal);
    // curves surface vertices
    glm::vec3 v1normal(cos(angle), sin(angle), 0);
    glm::vec3 v2normal(cos(nextAngle), sin(nextAngle), 0);
    //fv1 fv2 bv1
    PushVertex(coords, fv1);
    PushVertex(normals, v1normal);
    PushVertex(coords, fv2);
    PushVertex(normals, v2normal);
    PushVertex(coords, bv1);
    PushVertex(normals, v1normal);
    //fv2 bv1 bv2
    PushVertex(coords, fv2);
    PushVertex(normals, v2normal);
    PushVertex(coords, bv1);
    PushVertex(normals, v1normal);
    PushVertex(coords, bv2);
    PushVertex(normals, v2normal);
  }
}

void _print_shader_info_log(GLuint shader_index) {
  int max_length = 2048;
  int actual_length = 0;
  char shader_log[2048];
  glGetShaderInfoLog(shader_index, max_length, &actual_length, shader_log);
  printf("shader info log for GL index %u:\n%s\n", shader_index, shader_log);
}

class RenderManager
{
  public:
   enum ShapeType
   {
      CYLINDER
   };

                 RenderManager();
   void          SetView();
   void          SetUpGeometry();
   void          ApplyTexture(int color_code_ind);
   void          SetColor(double r, double g, double b);
   void          Render(ShapeType, glm::mat4 model);
   GLFWwindow   *GetWindow() { return window; };

  private:
   glm::vec3 color;
   GLuint cylinderVAO;
   GLuint cylinderNumPrimitives;
   GLuint mvploc;
   GLuint colorloc;
   GLuint camloc;
   GLuint ldirloc;
   glm::mat4 projection;
   glm::mat4 view;
   GLuint shaderProgram;
   GLFWwindow *window;

   void SetUpWindowAndShaders();
   void MakeModelView(glm::mat4 &);
};

RenderManager::RenderManager()
{
  SetUpWindowAndShaders();
  SetUpGeometry();
  projection = glm::perspective(
        glm::radians(45.0f), (float)1000 / (float)1000,  5.0f, 100.0f);

  // Get a handle for our MVP and color uniforms
  mvploc = glGetUniformLocation(shaderProgram, "MVP");
  colorloc = glGetUniformLocation(shaderProgram, "color");
  camloc = glGetUniformLocation(shaderProgram, "cameraloc");
  ldirloc = glGetUniformLocation(shaderProgram, "lightdir");

  glm::vec4 lightcoeff(0.3, 0.7, 2.8, 50.5); // Lighting coeff, Ka, Kd, Ks, alpha
  GLuint lcoeloc = glGetUniformLocation(shaderProgram, "lightcoeff");
  glUniform4fv(lcoeloc, 1, &lightcoeff[0]);
}

void
RenderManager::SetView()
{
   glm::vec3 camera = glm::vec3(0.0f, 0.0f, 5.0f);
   glm::vec3 origin = glm::vec3(0.0f, 0.0f, 0.0f);
   glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

   glm::mat4 v = glm::lookAt(
                       camera, // Camera in world space
                       origin, // looks at the origin
                       up      // and the head is up
                 );
   view = v;
   glUniform3fv(camloc, 1, &camera[0]);
   // Direction of light
   glm::vec3 lightdir = glm::normalize(camera - origin);
   glUniform3fv(ldirloc, 1, &lightdir[0]);
};

void
RenderManager::SetUpWindowAndShaders()
{
  // start GL context and O/S window using the GLFW helper library
  if (!glfwInit()) {
    fprintf(stderr, "ERROR: could not start GLFW3\n");
    exit(EXIT_FAILURE);
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  window = glfwCreateWindow(700, 700, "Puddles", NULL, NULL);
  if (!window) {
    fprintf(stderr, "ERROR: could not open window with GLFW3\n");
    glfwTerminate();
    exit(EXIT_FAILURE);
  }
  glfwMakeContextCurrent(window);
  // start GLEW extension handler
  glewExperimental = GL_TRUE;
  glewInit();

  // get version info
  const GLubyte *renderer = glGetString(GL_RENDERER); // get renderer string
  const GLubyte *version = glGetString(GL_VERSION);   // version as a string
  printf("Renderer: %s\n", renderer);
  printf("OpenGL version supported %s\n", version);

  // tell GL to only draw onto a pixel if the shape is closer to the viewer
  glEnable(GL_DEPTH_TEST); // enable depth-testing
  glDepthFunc(GL_LESS); // depth-testing interprets a smaller value as "closer"

  const char* vertex_shader = GetVertexShader();
  const char* fragment_shader = GetFragmentShader();

  GLuint vs = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vs, 1, &vertex_shader, NULL);
  glCompileShader(vs);
  int params = -1;
  glGetShaderiv(vs, GL_COMPILE_STATUS, &params);
  if (GL_TRUE != params) {
    fprintf(stderr, "ERROR: GL shader index %i did not compile\n", vs);
    _print_shader_info_log(vs);
    exit(EXIT_FAILURE);
  }

  GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fs, 1, &fragment_shader, NULL);
  glCompileShader(fs);
  glGetShaderiv(fs, GL_COMPILE_STATUS, &params);
  if (GL_TRUE != params) {
    fprintf(stderr, "ERROR: GL shader index %i did not compile\n", fs);
    _print_shader_info_log(fs);
    exit(EXIT_FAILURE);
  }

  shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, fs);
  glAttachShader(shaderProgram, vs);
  glLinkProgram(shaderProgram);
  glUseProgram(shaderProgram);
}

void RenderManager::SetColor(double r, double g, double b)
{
   color[0] = r;
   color[1] = g;
   color[2] = b;
}

void RenderManager::MakeModelView(glm::mat4 &model)
{
   glm::mat4 modelview = projection * view * model;
   glUniformMatrix4fv(mvploc, 1, GL_FALSE, &modelview[0][0]);
}

void RenderManager::Render(ShapeType st, glm::mat4 model)
{
   int numPrimitives = 0;
   if (st == CYLINDER)
   {
      glBindVertexArray(cylinderVAO);
      numPrimitives = cylinderNumPrimitives;
   }
   MakeModelView(model);
   glUniform3fv(colorloc, 1, &color[0]);
   glDrawElements(GL_TRIANGLES, numPrimitives, GL_UNSIGNED_INT, NULL);
}

void RenderManager::ApplyTexture(int color_code_ind) {
    unsigned char* image_data = NULL;
    int width, height, num_channels;
    // Load the texture image using stb_image
    if (color_code_ind == 41 || color_code_ind == 12){
        image_data = stbi_load("reds.png", &width, &height, &num_channels, STBI_rgb_alpha);
    } else if (color_code_ind == 17 || color_code_ind == 33 || color_code_ind == 35 || color_code_ind == 25){
        image_data = stbi_load("greens.png", &width, &height, &num_channels, STBI_rgb_alpha);
    } else if(color_code_ind == 16 || color_code_ind == 18 || color_code_ind == 34 || color_code_ind == 38 || color_code_ind == 9 || color_code_ind == 22){
        image_data = stbi_load("whites.png", &width, &height, &num_channels, STBI_rgb_alpha);
    }

    if (image_data) {
        // Modify the alpha values of the texture pixels
        for (int i = 0; i < width * height; ++i) {
            image_data[i * 4 + 3] = (unsigned char)(.3 * 255);
        }

        // Generate a texture object and bind it
        GLuint texture_id;
        glGenTextures(1, &texture_id);
        glBindTexture(GL_TEXTURE_2D, texture_id);

        // Set texture parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // Set texture data
        GLenum format = GL_RGBA;
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, image_data);

        glGenerateMipmap(GL_TEXTURE_2D);

        // Free image data and set the texture for rendering
        stbi_image_free(image_data);
        glActiveTexture(GL_TEXTURE0 + color_code_ind);
        glBindTexture(GL_TEXTURE_2D, texture_id);
    }
}


void SetUpVBOs(std::vector<float> &coords, std::vector<float> &normals,
               GLuint &points_vbo, GLuint &normals_vbo, GLuint &index_vbo)
{
  int numIndices = coords.size()/3;
  std::vector<GLuint> indices(numIndices);
  for(int i = 0; i < numIndices; i++)
    indices[i] = i;

  points_vbo = 0;
  glGenBuffers(1, &points_vbo);
  glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
  glBufferData(GL_ARRAY_BUFFER, coords.size() * sizeof(float), coords.data(), GL_STATIC_DRAW);

  normals_vbo = 0;
  glGenBuffers(1, &normals_vbo);
  glBindBuffer(GL_ARRAY_BUFFER, normals_vbo);
  glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(float), normals.data(), GL_STATIC_DRAW);

  index_vbo = 0;    // Index buffer object
  glGenBuffers(1, &index_vbo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_vbo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);
}

void RenderManager::SetUpGeometry()
{
  std::vector<float> cylCoords;
  std::vector<float> cylNormals;
  GetCylinderData(cylCoords, cylNormals);
  cylinderNumPrimitives = cylCoords.size() / 3;
  GLuint cyl_points_vbo, cyl_normals_vbo, cyl_indices_vbo;
  SetUpVBOs(cylCoords, cylNormals,
            cyl_points_vbo, cyl_normals_vbo, cyl_indices_vbo);

  GLuint vao[2];
  glGenVertexArrays(2, vao);

  glBindVertexArray(vao[CYLINDER]);
  cylinderVAO = vao[CYLINDER];
  glBindBuffer(GL_ARRAY_BUFFER, cyl_points_vbo);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
  glBindBuffer(GL_ARRAY_BUFFER, cyl_normals_vbo);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cyl_indices_vbo);
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
}

int main()
{
  RenderManager rm;
  GLFWwindow *window = rm.GetWindow();

  glm::vec3 origin(0, 0, 0);
  glm::vec3 up(0, 1, 0);

  int counter=0;
  while (!glfwWindowShouldClose(window))
  {
    double angle=counter/300.0*2*M_PI;
    counter++;

    glm::vec3 camera(10*sin(angle), 0, 10*cos(angle));
    rm.SetView();

    // wipe the drawing surface clear
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Enable blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    SetUpPuddles(counter, rm);

    // update other events like input handling
    glfwPollEvents();
    // put the stuff we've been drawing onto the display
    glfwSwapBuffers(window);
  }

  // close GL context and any other GLFW resources
  glfwTerminate();
  return 0;
}

glm::mat4 RotateMatrix(float degrees, float x, float y, float z)
{
   glm::mat4 identity(1.0f);
   glm::mat4 rotation = glm::rotate(identity,
                                    glm::radians(degrees),
                                    glm::vec3(x, y, z));
   return rotation;
}

glm::mat4 ScaleMatrix(double x, double y, double z)
{
   glm::mat4 identity(1.0f);
   glm::vec3 scale(x, y, z);
   return glm::scale(identity, scale);
}

glm::mat4 TranslateMatrix(double x, double y, double z)
{
   glm::mat4 identity(1.0f);
   glm::vec3 translate(x, y, z);
   return glm::translate(identity, translate);
}

void rows(glm::mat4 modelSoFar, RenderManager &rm, float yShift, int count)
{
   float xShift = -2.05;
   glm::mat4 yShiftT = TranslateMatrix(0, yShift, 0);
   modelSoFar = modelSoFar*yShiftT;
   for(int i = 0; i < 50; i++){
       xShift += .08;
       int ind = color_list[count][i];
       float r = color_codes[ind][0];
       float g = color_codes[ind][1];
       float b = color_codes[ind][2];
       rm.SetColor(r, g, b);
       glm::mat4 scale = ScaleMatrix(0.04, 0.04, 0.04);
       glm::mat4 translate = TranslateMatrix(xShift, 0, 0);
       rm.Render(RenderManager::CYLINDER, modelSoFar*translate*scale);
   }
}

void
SetUpPuddles(int counter, RenderManager &rm)
{
    glm::mat4 identity(1.0f);
    float yShift = 1.95;
    int count = 0;
    for (int i = 0; i < 50; i++){
       rows(identity, rm, yShift, count);
       yShift -= .08;
       count += 1;
    }
}

const char *GetVertexShader()
{
static char vertexShader[4096];
    strcpy(vertexShader,
        "#version 400\n"
        "layout (location = 0) in vec3 vertex_position;\n"
        "uniform mat4 MVP;\n"
        "void main() {\n"
        " gl_Position = MVP*vec4(vertex_position, 1.0);\n"
        "}\n"
        );
    return vertexShader;
}
const char *GetFragmentShader()
{
    static char fragmentShader[4096];
    strcpy(fragmentShader,
        "#version 400\n"
        "uniform vec3 color;\n"
        "out vec4 frag_color;\n"
        "void main() {\n"
        " frag_color = vec4(color, 1.0);\n"
        "}\n"
        );
    return fragmentShader;
}

