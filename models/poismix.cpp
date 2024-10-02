#include <TMB.hpp>

template<class Type>
Type objective_function<Type>::operator() ()
{
  DATA_VECTOR(Y);            // Objective variable
  DATA_VECTOR(X);            // Explanatory variable
  DATA_IVECTOR(G);           // Group index
  PARAMETER(alpha);          // Intercept
  PARAMETER(beta);           // Slope
  PARAMETER_VECTOR(epsilon); // Random effect
  PARAMETER(log_sigma);      // log SD of random effect
  Type nll = 0;              // negative log likelihood

  nll += -sum(dnorm(epsilon, Type(0.0), exp(log_sigma), true));
  for (int i = 0; i < Y.size(); i++) {
    Type lambda = exp(alpha + beta * X(i) + epsilon(G(i)));
    nll += -dpois(Y(i), lambda, true);
  }
  return nll;
}
