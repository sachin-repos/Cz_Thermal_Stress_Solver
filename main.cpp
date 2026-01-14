#include <iostream>
#include "fem_classes.h" // Import your blueprint

int main() {
    std::cout << "--- FEM SOLVER V1.0 ---" << std::endl;

    // 1. MANUFACTURE THE PARTS (Objects)
    // Create Node 1 at x=0
    Node n1(1, 0.0);
    
    // Create Node 2 at x=1.0
    Node n2(2, 1.0);

    Node n3(3,3.0);

    // 2. CONNECT THEM (Pointers)
    // Create an Element connecting Node 1 and Node 2
    // E=200 GPa, Area=0.1
    Element e1(1, &n1, &n2, 200e9, 0.1);
    Element e2(2, &n2, &n3, 200e9, 0.1);

    // 3. VERIFY THE CONNECTION
    std::cout << "Element " << e1.id << " created." << std::endl;
    std::cout << "Connecting Node " << e1.node1->id << " to Node " << e1.node2->id << std::endl;
    std::cout << "Calculated Length: " << e1.L << " m" << std::endl;

    std::cout << "Element " << e2.id << " created." << std::endl;
    std::cout << "Connecting Node " << e2.node1->id << " to Node " << e2.node2->id << std::endl;
    std::cout << "Calculated Length: " << e2.L << " m" << std::endl;

    return 0;
}