#include "Scenenode.h"

unsigned int counter=0;

SceneNode::SceneNode(PlyReader *ply,int id,char* name)
{
	worldTransform = Matrix4::Identity();
	localTransform = Matrix4::Identity();
	modelScale = Vec3i(1,1,1);
	parent=NULL;
	node=ply;
	nodeId=id;
	nodeName=name;

}
SceneNode::SceneNode(const SceneNode &n)
{
	worldTransform = n.worldTransform;
	localTransform = n.localTransform;
	// modelScale = Vec3i(1,1,1);
	children=n.children;
	parent=n.parent;
	node=n.node;
	nodeId=n.nodeId;
	nodeName=n.nodeName;

}
SceneNode::~SceneNode(void)    {
    for(unsigned  int i = 0; i < children.size (); ++i) {
	    children.erase(children.begin()+i);
    }
}

void SceneNode::addChild(SceneNode *n)
{
	// if(children)
	children.push_back(n);

	printf("inside add children\n");

	n->parent=this;
}

Matrix4 SceneNode::getWorldTransform()
{
	SceneNode * temp = parent;
	Matrix4 matrix = Matrix4::Identity()*localTransform;

	while(parent)
	{
		matrix = matrix * parent->getLocalTransform();
		parent=parent->getParent();
	}

	return matrix;
}

void SceneNode::deleteChild(SceneNode *n)
{
	// SceneNode *temp = (n);
	if(n!=NULL)
	for(std::vector<SceneNode *>::iterator iter= children.begin(); iter != children.end(); ++iter)
	{
		// if(n!=NULL)
		if((*iter)->getNodeId()==n->getNodeId())
		{
			// auto pos = std::distance(children.begin(), *iter);
			int pos=(iter-children.begin());
			std::cout<<"found at position iter "<<(iter-children.begin())<<" and int pos value "<<pos<<std::endl;

			children.erase(children.begin()+pos);

			std::cout<<"  after   erase  "<<std::endl;
			return;
			// return n;
		}
	}
	// children.erase(remove(children.begin(),children.end(),n),children.end());
}

SceneNode * SceneNode::getParent()
{
	return this->parent;
}

// void SceneNode::remove()
// {
// 	parent->deleteChild(this);
// 	parent=NULL;
// }

SceneNode * SceneNode::getSceneNode(int index)
{
	SceneNode *temp=NULL;
	if(index==nodeId)
	{
		return this;
	}
	int p=0;
	for( std::vector<SceneNode *>::iterator iter = children.begin(); iter != children.end(); ++iter ){
		temp = (*iter)->getSceneNode(index);
		printf("%d child name %s\n",p,temp->getNodeName() );
		if(temp!=NULL){
			return temp;
			}
			p++;
	}
	return NULL;
}

void SceneNode::drawSceneNode()
{
	glPushMatrix();
		// std::cout<<"before the multmatrix"<<std::endl;
		// localTransform.printMatrix();
		glMultMatrixf(localTransform._Entries[0]);
		// std::cout<<"after the multmatrix"<<std::endl;
		// localTransform.printMatrix();

		// std::cout<<"inside Scenenode at "<<counter<<std::endl;

		counter++;

		node->drawScene(2,getNodeId());
		int p=0;
		for(std::vector <SceneNode *>::iterator i = children.begin ();
                                i !=  children.end (); ++i) {
			printf("%d child name %s\n",p,(*i)->getNodeName() );
			if((*i)->nodeId==1)
			{
				// glTranslatef(-0.2, 0.0, 0.0);
				// glRotatef(-90.0, 1.0, 0.0, 0.0);
			}
            (*i)->drawSceneNode();
            p++;
        }
	glPopMatrix();
}