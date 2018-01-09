#ifndef VEAMY_H1NORMCALCULATOR_H
#define VEAMY_H1NORMCALCULATOR_H

#include <veamy/postprocess/NormCalculator.h>
#include <veamy/postprocess/analytic/StrainValue.h>
#include <veamy/postprocess/analytic/StressValue.h>
#include <feamy/postprocess/integrator/FeamyIntegrator.h>
#include <veamy/postprocess/computables/StrainStressDifferenceComputable.h>
#include <veamy/postprocess/computables/StrainStressComputable.h>
#include <veamy/postprocess/analytic/DisplacementValue.h>
#include <veamy/postprocess/integrator/IdentityIntegrator.h>
#include <veamy/postprocess/computables/StrainComputable.h>
#include <feamy/postprocess/calculators/FeamyStrainCalculator.h>
#include <veamy/physics/conditions/LinearElasticityConditions.h>
#include <veamy/postprocess/computables/StrainDifferenceComputable.h>
#include <veamy/postprocess/calculators/VeamyStrainCalculator.h>

/*
 * Computes the H1 norm
 */
template <typename T>
class ElasticityH1NormCalculator : public NormCalculator<T> {
private:
    /*
     * Analytical stress, strain and displacement values
     */
    StressValue* stressValue;
    StrainValue* strainValue;
    DisplacementValue* value;

    /*
     * Material matrix
     */
    Eigen::MatrixXd D;

    /*
     *
     */
    H1Computable<T>* numComputable;
    H1Computable<T>* denComputable;
public:
    /*
     * Constructor
     */
    ElasticityH1NormCalculator(StrainValue *strain, StressValue *stress, DisplacementValue* value, Eigen::VectorXd u, DOFS d);

    /*
    * Constructor
    */
    ElasticityH1NormCalculator(StrainValue *strain, DisplacementValue* value, Eigen::VectorXd u, DOFS d);

    /* Sets the calculators for this norm
     * @param integrator Calculator to use
     * @param info additional required information
     */
    void setCalculator(FeamyIntegrator<T>* integrator, FeamyAdditionalInfo info);

    /* Sets the calculators for this norm
     * @param integrator Calculator to use
     */
    void setCalculator(VeamyIntegrator<T> *integrator, std::vector<Point> &point);

    /* Sets all extra information from the problem conditions that is used for norm computation
     * @param conditions problem conditions
     */
    void setExtraInformation(Conditions* conditions);
};

#endif