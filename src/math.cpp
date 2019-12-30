#include "../include/math.hpp"

// RADIAL BASIS FUNCTIONS

double phi(const double x) {
	// most simple, used for now (maybe phi could be inline)
	return x;
}

void solver(RbfElts &elts) {
	// Construction on the matrix
	Eigen::MatrixXd matrix = Eigen::MatrixXd::Zero(elts.m_nbControlPoints, elts.m_nbControlPoints);
	for(int i=0; i<elts.m_nbControlPoints; i++) {
		for(int j=0; j<elts.m_nbControlPoints; j++) {
			double value = phi(double(glm::distance(elts.m_controlPoints[i], elts.m_controlPoints[j])));
			matrix(i, j) = value;
		}
	}
	elts.m_coeff = matrix.inverse()*elts.m_weights;
}

double radialBasisFunction(const RbfElts &elts, glm::vec3 x) {
	double weight = 0;
	for(int i=0; i<elts.m_nbControlPoints; i++) {
		weight += elts.m_coeff(i)*phi(glm::distance(x, elts.m_controlPoints[i]));
	}
	return weight;
}

void genRandomControlPoints(const int nbControlPoints, std::vector<glm::vec3> &controlPoints, Eigen::VectorXd &weights) {
	// select seed from time
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

	// select a random generator engine
	std::default_random_engine generator(seed);

	// control points
	// uniform int distribution
	std::uniform_int_distribution<int> uniformIntDistribution(-15, 15);
	for(int i=0; i<nbControlPoints; i++) {
	   	int x = uniformIntDistribution(generator);
	   	int y = uniformIntDistribution(generator);
	   	controlPoints.push_back(glm::vec3(x, 0, y));
	}

	// control points weights
	// uniform int distribution
	std::uniform_int_distribution<int> uniformIntDistributionWeights(-5, 5);
	Eigen::VectorXd randWeights = Eigen::VectorXd::Zero(nbControlPoints);
	for(int i=0; i<nbControlPoints; i++) {
		int weight = uniformIntDistributionWeights(generator);
		randWeights(i) = double(weight);
	}
	weights = randWeights;
}