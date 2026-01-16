#ifndef FEM_CLASSES_H
#define FEM_CLASSES_H

#include <iostream>
#include <cmath> //required for std::abs
#include <vector> //may use later

//--THE BLUEPRINTS--//

//1. Node - A point in space

class Node{

    public:
    int id;
    double x; //coordinate (1D for now)
    double u; //Displacement (The unknown we solve for)
    double f; //External force applied 

    //Constructor: How to "manufacture" a node; what would be given in the code to make a node
    Node(int node_id, double x_coord){
        id = node_id;
        x = x_coord;
        u = 0; //always start with zero displacement
        f = 0; //always start with zero force
    }

};

//2. Element - A spring connecting two nodes

class Element {
    public:
    int id;

    //Critical Part: Pointers (*)
    //We do not hold the node. We hold the address of the node.
    Node* node1;
    Node* node2;
    double E; //Young's modulus (Stiffness)
    double A; //Area
    double L; //Length (Calculated, not given)
    double k[2][2]; //Stiffness matrix

    //Constructor: "How to manufacture an Element"
    //Notice we accept node pointers (Node* n1, Node* n2)
    Element (int elem_id, Node* n1, Node* n2, double E_val, double A_val){
        id = elem_id;
        node1 = n1;
        node2 = n2;
        E = E_val;
        A = A_val;
        //calculate the length automatically: |x2 - x1|
        //we use arrow (->) because node1 is a pointer
        L = std::abs(node2->x - node1->x);
        //calculate stiffness immediately
        calculate_stiffness();
    }
    void calculate_stiffness(){
        double k_value = A*E/L;
        k[0][0] = k_value;
        k[0][1] = -k_value;
        k[1][0] = -k_value;
        k[1][1] = k_value;

    }
    void print_matrix(){
        std::cout<<"Stiffness matrix for Element "<<id<<":"<<std::endl;
        std::cout<<"[ "<<k[0][0]<<" "<<k[0][1]<<" ]"<<std::endl;
        std::cout<<"[ "<<k[1][0]<<" "<<k[1][1]<<" ]"<<std::endl;
    }
};

#endif