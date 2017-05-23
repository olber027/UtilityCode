search algorithm design:
    SearchAlgorithm:
    This is a virtual base class for all the search algorithms. Each
    Algorithm will contain a way to load an environment, and it will
    provide a way to navigate that same environment. The environment
    is assumed to be in a cartesian system (although this may be
    extended to other coordinate systems in the future), and that
    all terrain not explicitly specified as impassable, will be
    passable. The impassable terrain will be given to the algorithm
    as a list of Obstacles, which is expanded on below, and will also
    consist of a boundary area which will also be defined as an obstacle

    Obstacle:
    This is simply a list of Vertices, defining a 2 or 3 dimensional
    impassable object. The vertices will be given in clockwise order,
    and in the case of 3D, they will also be sorted by ascending Z
    values. e.g. a cube could be given by passing the vertices:
    {(0,0,0), (0,1,0), (1,1,0), (1,0,0), (0,0,1), (0,1,1), (1,1,1)
    (1,0,1)}

    Vertex:
    This is just a list of 2 or 3 coordinates defining a point.
    e.g. (1,2,3) or (4,5)

data structure design:
    LinkedList:
    This is a templated linked list. supports all basic linked list
    operations.