# L1 and L2 Regularization

Regularization is a set of techniques used to prevent models from **Overfitting** by penalizing complexity. It works by adding a penalty term to the base Loss Function (e.g., Mean Squared Error or Cross-Entropy). 

`Total Loss = Base Loss + Penalty`

When minimizing the total loss, the optimizer must not only minimize prediction errors but also keep the model weights as small as possible.

---

## 1. L1 Regularization (Lasso)
### Principle
L1 Regularization adds the **Absolute Value of Magnitude** of the weights as the penalty term to the loss function.

`L1 Penalty = λ * Σ |w_i|` (where `λ` is the regularization hyperparameter determining the penalty strength).

### Key Characteristics
*   **Sparsity & Feature Selection:** Because it uses absolute values, L1 optimization naturally pushes the weights of less important features to **exactly zero**. 
*   **Use Case:** Excellent for high-dimensional datasets where you suspect many features might be irrelevant. It acts as an automatic feature selection mechanism, yielding a simpler, more interpretable model.

---

## 2. L2 Regularization (Ridge)
### Principle
L2 Regularization adds the **Squared Magnitude** of the weights as the penalty term to the loss function.

`L2 Penalty = λ * Σ (w_i)^2`

### Key Characteristics
*   **Weight Shrinkage (No Sparsity):** Because it squares the weights, the penalty grows exponentially for large weights. It strongly penalizes highly influential parameters, forcing the model to distribute weight more evenly across all features. It shrinks weights very close to zero, but **rarely exactly zero**.
*   **Use Case:** Excellent for preventing specific features from dominating the model. It handles multicollinearity well and generally yields better overall predictive accuracy than L1 when most features are useful.

---

## Summary Comparison
| Feature | L1 Regularization (Lasso) | L2 Regularization (Ridge) |
| :--- | :--- | :--- |
| **Penalty Term** | Sum of absolute weights | Sum of squared weights |
| **Resulting Weights**| Sparse (many zero weights) | Small, distributed (close to zero) |
| **Model Complexity**| Results in simpler, readable models | Retains all features |
| **Main Utility** | Feature Selection | General Overfitting Prevention |

*(Note: **Elastic Net** is a technique that combines both L1 and L2 penalties to get the benefits of both sparsity and stable weight shrinkage).*
