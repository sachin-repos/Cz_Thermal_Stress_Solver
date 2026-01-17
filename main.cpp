#include <iostream>
#include "fem_classes.h" // Import your blueprint
#include <vector> //Resizable list
#include <iomanip> //For std::setw (Make the output look like a grid)


// --- TOOL: GAUSSIAN ELIMINATION SOLVER ---
// Solves [K]{u} = {F} for {u}
// You don't need to memorize this. It's standard algebra.

std::vector<double> solve_system(std::vector<std::vector<double>> K, std::vector<double> F){
    int n = F.size();

    //1. Forward elimination

    for (int i = 0; i<n; i ++){
        double pivot = K[i][i];
        for (int j = i; j<n; j++)K[i][j]/= pivot;
        F[i] /= pivot;

        //Eliminate rows below

        for (int k = i+1; k<n; k++){
            double factor = K[k][i];
            for (int j = i; j<n; j++) K[k][j] -= factor*K[i][j];
            F[k] -= factor * F[i];
        }

        }

        //2. Backward Substitution

        std::vector<double> u(n);

        for (int i = n-1; i >=0; i--){
            double sum = 0;
            for (int k = i+1; k<n; k++) sum += K[i][k]*u[k];
            u[i] = F[i] - sum;
        }

        return u;
            
        }


//--- MAIN FEM CODE --- 


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


    //---4. APPLY LOADS (Force Vector)---
    // We want to pull node 3 to the right by 100 Newtons
    std::vector<double> F(num_nodes, 0);
    F[2] = 100;
    std::cout<<"Applied F = 100 N at Node 3"<<std::endl;

    //---5. Apply Boundary Conditions (Fix node 1)---
    // We enforce u1 = 0 using the '1-0-0' method
    std::cout<<"Fixing Node 1 (u=0)..."<<std::endl;
    int fixed_node_idx = 0; //Node 1 is at index 0

    //A. Zero out the row
    for (int j = 0; j< num_nodes; j++){
        k_global[fixed_node_idx][j] = 0;
    }

    //B. Set diagonal to 1 and Force to 0
    k_global[fixed_node_idx][fixed_node_idx] = 1;
    F[fixed_node_idx] = 0;

    //---6. Solve k_global{u} = {F}---
    std::cout<<"Solving system..."<<std::endl;
    std::vector<double> displacements = solve_system(k_global, F);

    //---7. PRINT THE RESULTS---
    std::cout<<"\n---RESULTS---"<<std::endl;
    std::cout<<"Node \t Displacement(u)"<<std::endl;
    for (int i = 0; i<num_nodes; i++){
        std::cout<<i+1<<" \t"<<displacements[i]<<" m"<<std::endl;
    }


    return 0;

}
