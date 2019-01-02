/**
 * Better Programming Practices
 *
 * Compilation of bad code from various sources
 *
 * This file will not compile, but it is indented properly! ;-)
 *
 * Index
 *
 * TODO -- NEED to PRIORITIZE by SEVERITY
 * TODO -- add from http://faculty.washington.edu/pisan/cpp/snippets.html
 *
 * ERR: Cleanup your code
 * ERR: 80 Characters
 * ERR: Meaningful comments
 * ERR: Destructor Destroys
 * ERR: if (found == true)
 * ERR: Return the bool
 * ERR: cin skips
 * ERR: const reference when possible
 * ERR: Meaningful variable names
 * ERR: Initialize in header OR in constructor
 * ERR: Use initialization lists
 * ERR: Trust the Compiler
 * ERR: Empty Destructor
 * ERR: Assert to Check
 * ERR: return const reference
 * ERR: if outside of for
 * ERR: stringstream if lots of string appends
 * ERR: TODO
 * ERR: nullptr is false
 * ERR: conditional operator
 */


/**
 * ERR: Cleanup your code
 * If it is unused, take it out
 * Also you need a SPACE after //
 */

class Edge {
  friend class Vertex;
  friend class Graph;

 public:

  //Unused Getters and Setters
  /*
  int getWeight() const;
  Vertex* getVertexTo() const;
  Vertex* getVertexFrom() const;
  */
 private:
  //Initialize an edge with 2 vertex pointers and a edge weight
  Edge(Vertex *vertexFrom, Vertex *vertexTo, int edgeWeight);
};

/**
 * ERR: 80 Characters
 * Is there a reson to go over 80 characters in this case?/
 */
Edge::Edge(Vertex *v1, Vertex *v2, int edgeWeight) : vFrom(v1), vTo(v2), weight(edgeWeight) {}


/**
 * ERR: Meaningful comments
 *
 * If your code is so close to English or any rasonable C++ speaker
 * can see what you are doing, do not document it
 * Refactor/rename variables instead
 * Below "delete e" could be "delete edge"
 * Look we got self documenting code
 * Each function needs a comment, but inline comments only when something
 * tricky is going on, not for what can be read in English
 */
/** destructor, delete all vertices and edges */
Graph::~Graph() {
  //Iterate through all vertices and all edges in the vertices
  for (auto const &v : vertices) {
    for (auto const &e : v.second->allOutgoingEdges) {
      //Delete the edge
      delete e;
    }
    //Delete the vertex
    delete v.second;
  }
}

/**
 * ERR: Destructor Destroys
 *
 * Does std::map.clear() destroy anything?
 * Does setting an integer to 0 destroy anything?
 * Assuming myEdgesPtr is private and nobody can access it after the destructor
 * is called, what is the point of setting it?
 */
Graph::~Graph() {
  //Clear the map
  vertices.clear();
  edges = 0;
  myEdgesPtr = nullptr;
}

/**
 * ERR: if (found == true)
 *
 * Do we have to check if a bool is true as a condition?
 * bool is already a true/false value
 * Use if (found) or maybe
 * use if(!found)
 * Doesn't that read better?
 */
bool Graph::Connect(const string &fromLabel,
                    const string &toLabel, int edgeWeight = 0) {
  //If vertices don't exist, add them
  if (HasVertex(fromLabel) == false) {
    AddVertex(fromLabel);
  }
}

/**
 * ERR: Return the bool
 *
 * If a function is already returning a bool, you can return that value
 * No need to use if(funcReturnsTrue) return true else resturn false
 * return funcReturnsTrue;
 * It also works to return the opposite truth value
 * return !findEdge(otherVertex);
 */
bool Vertex::addEdge(Vertex &otherVertex, int weight) {
  // code deleted
  if (findEdge(otherVertex))
    return true;
  return false;
}

bool Vertex::removeEdge(Vertex &otherVertex) {
  // code deleted
  if (!(findEdge(otherVertex)))
    return true;
  return false;
}

/**
 * ERR: cin skips
 *
 * The format of the data file is an integer for number-of-edges
 * followed by that many "string string int" lines
 * Instead of reading the first integer and then using a for loop,
 * the code below discards the number-of-edges
 * Each iteration of the loop calls getline,
 * which has nothing to read but a newline
 *
 * cin and ifstream will read the correct data types,
 * so would have already skipped over newline and extra spaces
 * No need for getline
 * Plus, if we put additional comments below the graph info
 * now the graph function will error out
 */
bool Graph::ReadFile(const string &filename) {
  int edgeWeight;
  string line, vertexFrom, vertexTo;
  ifstream file(filename);
  if (file.is_open()) {
    while (getline(file, line)) {
      file >> vertexFrom >> vertexTo >> edgeWeight;
      // Connect(vertexFrom, vertexTo, edgeWeight);
    }
  }
}

/**
 * ERR: const reference when possible
 *
 * If it is not a builtin data type (bool, char, int, double, float),
 * do not copy unless you really really need to
 */
Vertex::Vertex(string l) : label(l), visited(false) {}

/**
 * ERR: Meaningful variable names
 *
 * label instead of l
 * l is especially bad since it looks like the number "1" for certain fonts
 */
Vertex::Vertex(string l) : label(l), visited(false) {}

/**
 * ERR: Initialize in header OR in constructor
 *
 * Decide where you want to initialize your variables and srtick to it
 * It is OK to initialize some in header and some in constructor, but
 * you should not have both.
 * Leads to confusion when defaults change.
 */
Vertex::Vertex(string l) : label(l), visited(false) {}
// in .h file
// bool visited = false;
// string label = "";


/**
 * ERR: Use initialization lists
 *
 * When possible use initialization lists rather than initializing
 * variables in the body of the constructor
 */
Vertex::Vertex() {
  vertexLabel = "";
  visited = false;
}

/**
 * ERR: Trust the Compiler
 *
 * Make the compiler generate the default empty constructor
 * You can use
 * Vertex() = default;
 * in .h file and set default values in .h file
 */
Vertex::Vertex() {
  vertexLabel = "";
  visited = false;
}

/**
 * ERR: Empty Destructor
 *
 * Unless you have a virtual function, do not write an empty destructor
 * Eat-my-words: I previously suggested writing empty destructuctor
 * even when it is empty as a good habit. Proabbly a good idea when starting
 * programmers, but concise code is better for more advanced programmers
 */
Vertex::~Vertex() {
}

/**
 * ERR: Assert to Check
 *
 * Use assert to check that functions are working correctly
 * Assuming removeEdgeHelper is working correctly, this function should
 * always return true if the edge is deleted, so check it with
 * assert(!findEdge(otherVertex))
 * assert statements can be excluded from release code, so your code will
 * run faster in release version, but still be fully testable as you work
 */
bool Vertex::removeEdge(Vertex &otherVertex) {
  if (!findEdge(otherVertex))
    return false;
  Edge *toBeDeleted = removeEdgeHelper(otherVertex);
  delete toBeDeleted;
  // confirm disconnected
  return !findEdge(otherVertex);
}

/**
 * ERR: return const reference
 *
 * Better to return const reference to provide a reference to the object
 * without letting the caller modify it
 * const string& string Vertex::getLabel() const;
 * Returning a reference means, the caller can either use
 * const string &label = v.getLabel()
 * OR
 * string label = v.getLabel()
 * if they want their own copy. Their choice!
 */
string Vertex::getLabel() const {
  return vertexLabel;
}

/**
 * ERR: if outside of for
 *
 * The code below is trying to print edges with commas between them
 * something like "A-B 5, A-F 3, A-H 2" without having a comma at the end
 * Having an if statement inside the loop means, it checks the condition
 * for each iteration. If there are million edges, it checks it million
 * times when we only need to check it once using
 * string Vertex::print() const {
 *      string vertexString = "";
 *      if (edges.size() > 0)
 *          vertexString += edges[0]->print();
 *      for (size_t i = 1; i < edges.size(); i++) {
 *           vertexString += ",";
 *           vertexString += edges[i]->print();
 *      }
 *      return vertexString;
 * }
 */
string Vertex::print() const {
  string vertexString = "";
  for (size_t i = 0; i < edges.size(); i++) {
    vertexString += edges[i]->print();
    if (i < edges.size() - 1)
      vertexString += ",";
  }
  return vertexString;
}

/**
 * ERR: stringstream if lots of string appends
 *
 * If you are putting lots of things into a string, use a stringstream
 * rather than using + or append
 * #include <sstream>
 * string Vertex::print() const {
 *      stringstream ss;
 *      if (edges.size() > 0)
 *          ss << edges[0]->print();
 *      for (size_t i = 1; i < edges.size(); i++)
 *          ss << "," << edges[i]->print();
 *      return ss.str();
 * }
 */
string Vertex::print() const {
  string vertexString = "";
  for (size_t i = 0; i < edges.size(); i++) {
    vertexString += edges[i]->print();
    if (i < edges.size() - 1)
      vertexString += ",";
  }
  return vertexString;
}

/**
 * ERR: TODO
 *
 * Add TODO for function stubs that you will implement later
 * AND, implement them before submitting
 * You can search for TODO in the whole project before final submission
 */
// destructor, delete all vertices and edges
Graph::~Graph() {
}

/**
 * ERR: nullptr is false
 *
 * nullptr will be cast to the boolean false, much cleaner to write
 * if (v) ... else ...;
 * This works because there is an implicit conversion from pointer to bool
 * (i.e. a constructor for bool that is not marked explicit and takes a pointer)
 */
int Graph::NumberOfEdges(const string &label) const {
  Vertex *v = findVertex(label);
  if (v != nullptr)
    return v->numberOfEdges();
  // if Vertex was not found - nullptr - then return -1
  return -1;
}

/**
 * ERR: conditional operator
 *
 * Do not abuse the "?" conditional operator, but use it to simplify code
 * Vertex *v = findVertex(label);
 * return v ? v->numberOfEdges() : -1;
 */
int Graph::NumberOfEdges(const string &label) const {
  Vertex *v = findVertex(label);
  if (v != nullptr)
    return v->numberOfEdges();
  // if Vertex was not found - nullptr - then return -1
  return -1;
}

* ERR:
cin skips

/**
 * ERR: compact cin
 *
 * cin and ifstream will extract multiple variables per line
 * file >> vFrom >> vTo >> weight;
 */
bool Graph::ReadFile(const string &filename) {
  // code deleted
  // read rest of lines (numberOfEdges times)
  for (int i = 0; i < numberOfEdges; i++) {
    file >> vFrom;
    file >> vTo;
    file >> weight;
    Connect(vFrom, vTo, weight);
  }
}

/**
 * ERR: similar names, similar functions
 *
 * if getEdges returns a string and Vertex::print returns a string
 * why do they have such different names?
 * For that matter, GetEdges should really return edges, i.e edge objects
 * If we want a string, we should have GetEdgesAsString
 */
string Graph::GetEdges(const string &label) const {
  return findVertex(label)->print();
}
string Vertex::print() const {
  string vertexString = "";
  // code deleted
  return vertexString;
}

/**
 * ERR: explicit constructors
 *
 * if a constructor takes a single parameter,
 * make it explicit otherwise it cannot be explicit
 */

class Vertex {
  friend class Graph;
 private:
  //  Declaration of Vertex class' one-parameter constructor
  //  Initializes Vertex with string vertexLabel
  Vertex(const string &vertexLabel);
  explicit Vertex(const string &vertexLabel, bool visited);
};

/**
 * ERR: static functions
 *
 * if a class function does not need to access the object,
 * make it static
 */
class Vertex {
 private:
  bool compareEdge(Edge *firstEdge, Edge *secondEdge);
};

/**
 * ERR: range-based-for
 *
 * Use range based for over index based for or over iterators
 * for (auto& edge : edgesGoingOut)
 *      delete edge
 */
Vertex::~Vertex() {
  for (std::vector<Edge *>::iterator it = edgesGoingOut.begin();
       it != edgesGoingOut.end(); ++it)
    delete *it;
  edgesGoingOut.clear();
}

/**
 * ERR: const getters
 *
 * getter should be const functions
 * other functions should also be const whenever possible
 * Sometimes it is necessary to write two versions of the same function
 * one as const, and the other non-const. This is standard practice.
 */
class Vertex {
 public:
  Vertex();
  string getLabel() { return label; }
};

/**
 * ERR: simplify conditions
 *
 * combne if statements if the body is the same
 * if ((edge->getVertex1Pointer() == vertex) ||
 *     (edge->getVertex2Pointer() == vertex))
 *     return true;
 */
bool Vertex::isConnectedTo(Vertex *vertex) {
  for (Edge *edge: edges) {
    if (edge->getVertex1Pointer() == vertex)
      return true;
    if (edge->getVertex2Pointer() == vertex)
      return true;
  }
  return false;
}

/**
 * ERR: extra vectors
 *
 * beware of making extra copies of vector objects,
 * return by const reference if possible,
 *          const vector<Edge *>& Vertex::getEdges()
 * return by reference if not
 *          vector<Edge *>& Vertex::getEdges()
 * This case is relatively harmless since it is a vector of pointers,
 * which are just integers, but still....
 */
vector<Edge *> Vertex::getEdges() {
  return edges;
}

/**
 * ERR: map key exists
 *
 * use container.count(key) == 1 to check if the key exists in the map
 * if you use container[key] then you are forcing the map to create that key
 * with the default values, increasing the size of the map unnecessarily
 * and possibly creating a new object using the default constructor
 * Testcase:
 * class Foo {};
 * map<int, Foo*> mp;
 * cout << "size: " << mp.size() << endl;
 * if (mp[3] == nullptr);
 * cout << "size: " << mp.size() << endl;
 */
Vertex *Graph::createVertex(const std::string &vertexLabel) {
  if (vertices[vertexLabel] == nullptr) {
    // ...
  }
}