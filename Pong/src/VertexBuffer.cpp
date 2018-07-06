#include "VertexBuffer.h"
#include "Renderer.h"


VertexBuffer::VertexBuffer(){}

VertexBuffer::VertexBuffer(std::vector<float> &data, unsigned int size){

	GLCall(glGenBuffers(1, &m_RendererID));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
	//Size of vector * size of float.  
	GLCall(glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), &data.front(), GL_STATIC_DRAW));

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
