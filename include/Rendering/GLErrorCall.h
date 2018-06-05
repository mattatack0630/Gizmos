//
// Created by mathew on 5/30/18.
//

#pragma once

//#define BREAK(x) if(!(x))
#include <glad/glad.h>
#include <iostream>
#include <debug_break.h>

#define GLCall(x) clearError();x;logError(#x, __LINE__, __FILE__);

static void clearError(){
	while(glGetError() != GL_NO_ERROR);
}

static void logError(const char* function, int line, const char* file){
	while(GLenum error = glGetError()){
		std::cout<<"OpenGL ERROR code "<<error<<" in function "<<function<<" on line "<<line<<" of "<< file<<std::endl<<std::endl;
		debug_break();
	}

}

