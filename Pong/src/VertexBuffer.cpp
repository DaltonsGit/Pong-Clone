#include "VertexBuffer.h"
#include "Renderer.h"
#include <iostream>


VertexBuffer::VertexBuffer(){
	
	glGenBuffers(1, &m_RendererID);

}

VertexBuffer::VertexBuffer(std::vector<float> &data, unsigned int size){

	glGenBuffers(1, &m_RendererID);
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	//Size of vector * size of float.  
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), &data.front(), GL_STATIC_DRAW);

}

void VertexBuffer::subData(std::vector<float> data)
{
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	glBufferSubData(GL_ARRAY_BUFFER, 0, data.size() * sizeof(float), &data.front());
}

VertexBuffer::~VertexBuffer(){

	glDeleteBuffers(1, &m_RendererID);

}

void VertexBuffer::Bind() const{

	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
}

void VertexBuffer::Unbind() const{

	glBindBuffer(GL_ARRAY_BUFFER, 0);

}
