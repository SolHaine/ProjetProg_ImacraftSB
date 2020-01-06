#pragma once

#include <glimac/common.hpp>

#include <vector>
#include <iostream>
#include <eigen3/Eigen/Dense>

#include <random>
#include <chrono>

/* RADIAL BASIS FUNCTIONS */

void genRandomControlPoints(const int nbControlPoints, std::vector<glm::vec3> &controlPoints, Eigen::VectorXd &weights, const int width);

struct RbfElts {
	int m_nbControlPoints;
	std::vector<glm::vec3> m_controlPoints;
	Eigen::VectorXd m_weights;
	Eigen::VectorXd m_coeff;

	RbfElts(const int nbControlPoints, const int width) {
		m_nbControlPoints = nbControlPoints;
		genRandomControlPoints(m_nbControlPoints, m_controlPoints, m_weights, width);
	}		
};

double phi(const double x);
void solver(RbfElts &elts);
double radialBasisFunction(const RbfElts &elts, glm::vec3 x);
