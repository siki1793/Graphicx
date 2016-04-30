#ifndef SCENENODE_H
#define SCENENODE_H

#include <vector>
#include <string>
#include <map>//hash map kind
#include <algorithm>
#include <iostream>
#include <stdlib.h>

#include "PlyReader.h"
#include "Vector.h"
#include "Model.h"
#include "Matrix4.h"

class SceneNode{

private:



public:
	PlyReader *node;
	SceneNode *parent;
	int nodeId;
	char *nodeName;
	Matrix4 localTransform;
	Matrix4 worldTransform;
	Vec3i modelScale;
	std::vector<SceneNode *> children;
	SceneNode(PlyReader*,int,char*);
	SceneNode(const SceneNode &n);
	~SceneNode();

	void addChild(SceneNode*);
	void deleteChild(SceneNode*);

	SceneNode* getParent();
	// void remove();

	SceneNode * getSceneNode(int);

	void drawSceneNode();

	void setLocalTransform(const Matrix4 &matrix){
		localTransform = matrix;
	}

	Matrix4 getLocalTransform(){
		return localTransform ;
	}
	Matrix4 getWorldTransform();
	void setModelScale(Vec3i s){
		modelScale = s;
	}
	char* getNodeName(){
		return nodeName;
	}
	int getNodeId(){
		return nodeId;
	}


};




#endif