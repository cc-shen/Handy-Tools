"""
  Short program to do vector-matrix multiplication.
"""

import numpy as np

cost_basis = np.array([300, 200, 0])
print("c_B:", cost_basis)
A_basis_inverse = np.array([[-.025, 0.375, 0], [0.5, -0.25, 0], [-0.25, -0.125, 1]])
print("A_B^-1:", A_basis_inverse)

y = np.dot(cost_basis, A_basis_inverse)
print("y^T:", y)

cost = np.array([1, 1, 1])

print("cost:", np.dot(y, cost))
