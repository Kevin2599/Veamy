#ifndef VEAMY_CALCULATOR2D_H
#define VEAMY_CALCULATOR2D_H

#include <utilities/UniqueList.h>
#include <veamy/physics/conditions/Conditions.h>
#include <veamy/models/dof/DOFS.h>
#include <veamy/problems/ProblemDiscretization.h>

/*
 * Abstract class that encapsulates all common behaviour for linear elasticity calculations, no matter the method
 * used
 */
template <typename T>
class Calculator2D {
protected:
    /*
     * Elements of the system
     */
    std::vector<Element*> elements;

    /*
     * Problem to solve
     */
    ProblemDiscretization* problem;

    /*
     * Mesh points
     */
    UniqueList<Point> points;
public:
    /*
     * Degrees of freedom of the system
     */
    DOFS* DOFs;

    /* Gets the degrees of freedom indexes related to a point
     * @param point_index point to lookup
     * @return pair of dofs (x and y) related to the given point
     */
    Pair<int> pointToDOFS(int point_index);

    /*
     * @return mesh points
     */
    UniqueList<Point> getPoints() const;

    /*
     * @return mesh points
     */
    UniqueList<Point> getPoints();

    /* Assembles the global stiffness matrix and load vector
     * @param Kglobal global stiffness matrix
     * @param fGlobal global load vector
     */
    virtual void assemble(Eigen::MatrixXd &Kglobal, Eigen::VectorXd &fGlobal) = 0;

    /* Creates the global stiffness matrix and load vector, imposes the essential boundary conditions on the system and
     * solves the problem
     * @param mesh domain of the problem
     * @return computed displacements
     */
    Eigen::VectorXd simulate(Mesh<T> &mesh);

    /* Writes the computed nodal displacements to a text file
     * @param fileName name of the file to write the displacements to
     * @param u computed displacements
     */
    void writeDisplacements(std::string fileName, Eigen::VectorXd u);
};

#endif