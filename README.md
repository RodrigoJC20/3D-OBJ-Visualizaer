# OBJ Reader

## Stage 1: Load .obj Files

The first stage of the project focused on implementing the file loading functionality. The program was designed to open .obj files and parse the vertex and face data to display the object. The object is stored in a class that contains a vector of vertices and edges. To display the object, the program utilizes OpenGL, specifically the glBegin() and glEnd() functions to create triangles based on the face data. At this stage, the program only displays the object with a solid color.

![Model loaded screenshot](https://github.com/RodrigoJC20/OBJ-Reader/blob/main/OBJ_Reader/img/dragon_preview.png)

## Stage 2: Implementing basic animations

The second stage of the project focused on implementing basic animations. To do this, I implemented functions for matrix multiplication and obtain the model matrix for each object. With these functions in place, I was able to simulate animations, like rotation or translation. Additionally, the Bezier equation was used to create a curve, and a ping-pong table was used as a test object.

![Rotation animation](https://github.com/RodrigoJC20/OBJ-Reader/blob/main/OBJ_Reader/img/pingpong.gif)

## Future Improvements

In the future, I plan to add more features. Specifically, the program will be updated to provide shadow support, which will improve the overall visual quality of the object. Additionally, keyboard controls will be implemented to allow users to interact with the object in real-time. Stay tuned for updates!
