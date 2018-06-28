#include "Mesh.h"

#include <gl_core_4_4.h>

Mesh::Mesh()
	: triCount(0)
	, vao(0)
	, vbo(0)
	, ibo(0)
{

}


Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ibo);
}

void Mesh::initialiseQuad()
{
	// check that the mesh is not initialised already
	assert(vao == 0);

	glGenBuffers(1, &vbo);
	glGenVertexArrays(1, &vao);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	// Two triangles with no shared vertices. 
	Vertex vertices[6];
	vertices[0].m_position = { -1, 0, 1, 1 };
	vertices[1].m_position = { 1, 0, 1, 1 };
	vertices[2].m_position = { -1, 0, -1, 1 };

	vertices[3].m_position = { -1, 0, -1, 1 };
	vertices[4].m_position = { 1, 0, 1, 1 };
	vertices[5].m_position = { 1, 0, -1, 1 };

	vertices[0].m_texCoord = { 0, 1 }; //bottom left
	vertices[1].m_texCoord = { 1, 1 }; //bottom right
	vertices[2].m_texCoord = { 0, 0 }; //top left

	vertices[3].m_texCoord = { 0, 0 }; //top left
	vertices[4].m_texCoord = { 1, 1 }; //bottom right
	vertices[5].m_texCoord = { 1, 0 }; //top right

	vertices[0].m_normal = { 0, 1, 0, 0 };
	vertices[1].m_normal = { 0, 1, 0, 0 };
	vertices[2].m_normal = { 0, 1, 0, 0 };
	vertices[3].m_normal = { 0, 1, 0, 0 };
	vertices[4].m_normal = { 0, 1, 0, 0 };
	vertices[5].m_normal = { 0, 1, 0, 0 };

	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(Vertex), vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_TRUE, sizeof(Vertex), (void*)16);

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)32);

	//Unbinds the buffers
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//quad has 2 triangles
	triCount = 2;
}

void Mesh::initialise(unsigned int a_vertexCount, const Vertex * a_vertices, unsigned int a_indexCount, unsigned int * a_indices)
{
	assert(vao == 0);
	// generate buffers
	glGenBuffers(1, &vbo);
	glGenVertexArrays(1, &vao);

	// bind vertex array aka a mesh wrapper
	glBindVertexArray(vao);

	// bind vertex buffer
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	// fill vertex buffer
	glBufferData(GL_ARRAY_BUFFER, a_vertexCount * sizeof(Vertex), a_vertices, GL_STATIC_DRAW);

	// enable first element as position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_TRUE, sizeof(Vertex), (void*)16);

	//Enables the second 3 position for the texture
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)32);

	// bind indices if there are any
	if (a_indexCount != 0)
	{
		glGenBuffers(1, &ibo);
		// bind vertex buffer
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
		// fill vertex buffer
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, a_indexCount * sizeof(unsigned int), a_indices, GL_STATIC_DRAW);
		triCount = a_indexCount / 3;
	}
	else
	{
		triCount = a_vertexCount / 3;
	}
	// unbind buffers
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Mesh::render()
{
	glBindVertexArray(vao);

	if (ibo != 0)
	{
		glDrawElements(GL_TRIANGLES, 3 * triCount, GL_UNSIGNED_INT, 0);
	}
	else
	{
		glDrawArrays(GL_TRIANGLES, 0, 3 * triCount);
	}
}