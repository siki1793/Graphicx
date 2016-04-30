all:
		gcc -g -c Source/plyfile.c -lGL -lGLU -lglut
		g++ -g Source/Main.cpp Source/Model.cpp Source/View.cpp Source/Controller.cpp Source/Scenenode.cpp Source/Matrix4.cpp Source/PlyReader.cpp Source/Texture.cpp Source/arcball.cpp plyfile.o -lglut -lGL -lGLU -o assignment4
