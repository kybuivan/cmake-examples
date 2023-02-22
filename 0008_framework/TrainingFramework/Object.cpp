#include "stdafx.h"
#include "Object.h"

void Object::Init()
{
	Matrix Pos, Rot, Scale;
	Pos.SetTranslation(m_objectInfo.objectPos);
	if (m_objectInfo.objectRot.x > 0)
	{
		Rot.SetRotationX(m_objectInfo.objectRot.x);
	}
	else if (m_objectInfo.objectRot.y > 0)
	{
		Rot.SetRotationY(m_objectInfo.objectRot.y);
	}
	else
		Rot.SetRotationZ(m_objectInfo.objectRot.z);
	Scale.SetScale(m_objectInfo.objectSca);
	world = Scale.operator*(Rot).operator*(Pos);
}

void Object::Draw(ESContext *esContext)
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glUseProgram(m_shader->program);
	if (m_objectInfo.numCubeTex != 0)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, m_cubeTex->GetCubeTextureID());
	}
	else{    //printf("Error couldn't load textureID!\n"); 
	}
		
	glBindBuffer(GL_ARRAY_BUFFER, m_model->GetVboModel());
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_model->GetIboModel());

	if (m_shader->positionAttribute != -1)
	{
		glEnableVertexAttribArray(m_shader->positionAttribute);
		glVertexAttribPointer(m_shader->positionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	}

	if (m_shader->normAttribute != -1)
	{
		glEnableVertexAttribArray(m_shader->normAttribute);
		glVertexAttribPointer(m_shader->normAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)sizeof(Vector3));
	}

	if (m_shader->bitangentAttribute != -1)
	{
		glEnableVertexAttribArray(m_shader->bitangentAttribute);
		glVertexAttribPointer(m_shader->bitangentAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(0 + sizeof(Vector3) * 2));
	}

	if (m_shader->tangentAttribute != -1)
	{
		glEnableVertexAttribArray(m_shader->tangentAttribute);
		glVertexAttribPointer(m_shader->tangentAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(0 + sizeof(Vector3) * 3));
	}

	if (m_shader->uvAttribute != -1)
	{
		glEnableVertexAttribArray(m_shader->uvAttribute);
		glVertexAttribPointer(m_shader->uvAttribute, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(0 + sizeof(Vector3) * 4));
	}

	if (m_shader->runTime != -1)
	{
		glUniform1f(m_shader->runTime, m_runtime);
	}

	if (m_objectInfo.numCubeTex > 0)
	{
		if(m_shader->iCubeTexLoc != -1)
			glUniform1i(m_shader->iCubeTexLoc, 0);
	}

	if (m_objectInfo.numLight > 0)
	{
		for (int i = 0; i < m_objectInfo.numLight; i++)
		{
			switch (i)
			{
			case 0:
				if (m_shader->lightPos1 != -1)
					glUniform3f(m_shader->lightPos1, m_light[i].m_pos.x, m_light[i].m_pos.y, m_light[i].m_pos.z);
				if (m_shader->lightColor1 != -1)
					glUniform3f(m_shader->lightColor1, m_light[i].m_color.x, m_light[i].m_color.y, m_light[i].m_color.z);
				break;
			case 1:
				break;
			default:
				break;
			}
		}
	}

	if(m_objectInfo.numTexture > 0)
	{
		for (int i = 0; i < m_objectInfo.numTexture; i++)
		{
			glActiveTexture(GL_TEXTURE0+i);
			glBindTexture(GL_TEXTURE_2D, m_texture[i].GetTextureID());
			switch (i)
			{
				case 0:
					if (m_shader->iTextureLoc != -1)
						glUniform1i(m_shader->iTextureLoc, i);
					break;
				case 1:
					if (m_shader->iTextureLoc1 != -1)
						glUniform1i(m_shader->iTextureLoc1, i);
					break;
				case 2:
					if (m_shader->iTextureLoc2 != -1)
						glUniform1i(m_shader->iTextureLoc2, i);
					break;
				case 3:
					if (m_shader->iTextureLoc3 != -1)
						glUniform1i(m_shader->iTextureLoc3, i);
					break;
				default:
					break;
			}
		}
	}

	if (m_shader->wvpLoc != -1)
	{
		glUniformMatrix4fv(m_shader->wvpLoc, 1, GL_FALSE, &MVPMatrix.m[0][0]);
	}

	if (m_shader->worldLoc != -1)
	{
		glUniformMatrix4fv(m_shader->worldLoc, 1, GL_FALSE, &world.m[0][0]);
	}

	if (m_shader->cameraPos != -1)
	{
		glUniform3f(m_shader->cameraPos, m_camerapos.x, m_camerapos.y, m_camerapos.z);
	}
	
	glDrawElements(GL_TRIANGLES, m_model->NrIndices, GL_UNSIGNED_INT, 0);
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glDisable(GL_BLEND);
	if (m_objectInfo.numTexture != 0)
		glBindTexture(GL_TEXTURE_2D, 0);
	else if (m_objectInfo.numCubeTex !=0)
		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}
Object::~Object()
{
	//printf("Object::~Object()");
	if (m_objectInfo.numTexture > 0)
	{
		delete[] m_objectInfo.textureID;
	}
	if (m_objectInfo.numCubeTex > 0)
	{
		delete[] m_objectInfo.CubeTexID;
	}
	if (m_objectInfo.numLight > 0)
	{
		delete[] m_objectInfo.lightID;
	}
}