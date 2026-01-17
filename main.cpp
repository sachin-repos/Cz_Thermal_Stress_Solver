#include <iostream>
#include "fem_classes.h" // Import your blueprint
#include <vector> //Resizable list
#include <iomanip> //For std::setw (Make the output look like a grid)


int main() {
    std::cout << "\n--- FEM SOLVER V1.2 GLOBAL ASSEMBLY---" << std::endl;

    //1. SETUP -use simple numbers so we can verify the math easily

    double E = 1000;
    double A = 1;

    // MANUFACTURE THE PARTS (Objects) - Create 3 nodes (The Geometry)
    // Create Node 1 at x=0
    Node n1(1, 0.0);
    Node n2(2, 1.0);
    Node n3(3,3.0);

    //put them in a list so we can count them

    std::vector<Node*> nodes = {&n1, &n2, &n3};
    int num_nodes = nodes.size();

    // CONNECT THEM (Pointers) - Create 2 elements (The Physics)
    // Create an Element connecting Node 1 and Node 2
    // E=200 GPa, Area=0.1
    Element e1(1, &n1, &n2, E, A); //k = 1000
    Element e2(2, &n2, &n3, E, A); //k = 500

    std::vector<Element*> elements = {&e1, &e2};

    //---2. CREATE THE EMPTY GLOBAL MATRIX ---

    std::vector<std::vector<double>> k_global(num_nodes, std::vector<double>(num_nodes, 0));
    //create a vector of vectors (containing double type entries) called kglobal
    //what comes after k_global in the () is a constructor
    // it says there should be num_nodes number of rows
    //Each row should contain a vector of double type with num_nodes size each initialized to 0

    std::cout <<"Initialized "<< num_nodes << " x "<< num_nodes<< " Global Matrix" << std::endl;


    // ---3. THE ASSEMBLY LOOP (The Core Logic)---

    std::cout<<"Starting Assembly ..."<<std::endl;

    for (Element* elem: elements){
        int idx1 = elem->node1->id - 1;
        int idx2 = elem->node2->id - 1;

        k_global[idx1][idx1] += elem->k[0][0];
        k_global[idx1][idx2] += elem->k[0][1];
        k_global[idx2][idx1] += elem->k[1][0];
        k_global[idx2][idx2] += elem->k[1][1];
    }


    //---4. PRINT THE RESULTS ---
    std::cout<<"\n--- FINAL GLOBAL STIFFNESS MATRIX ---"<<std::endl;

    for(int i=0; i < num_nodes; i++){
        std::cout<<"[";
        for (int j = 0; j<num_nodes; j++){
            std::cout<<std::setw(6)<<k_global[i][j]<<" ";
        }
        std::cout<<"]"<<std::endl;
    }

    return 0;

}
