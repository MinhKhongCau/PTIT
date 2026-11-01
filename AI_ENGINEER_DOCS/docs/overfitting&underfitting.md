# Overfitting & Underfitting

Understanding Overfitting and Underfitting is crucial for building robust Machine Learning models. Both relate directly to the **Bias-Variance Tradeoff**.

## 1. Underfitting (High Bias)

### Definition

Underfitting occurs when a **machine learning model** is **too simple** to capture the underlying patterns and **complexities of the data**. The model performs poorly on both the training data and the unseen test/validation data.

### Principle & Causes

- **High Bias:** The model makes strong, broad assumptions (heuristics) about the data that are incorrect.
- **Causes:**
  - The chosen algorithm is not powerful enough (e.g., using a linear model for highly non-linear data).
  - The model hasn't been trained for enough epochs.
  - Too much regularization was applied.

### How to Fix

- Increase model complexity (add more layers, use a non-linear algorithm like Decision Trees or Neural Networks).
- Add more relevant features (Feature Engineering).
- Train longer or reduce regularization penalties.

---

## 2. Overfitting (High Variance)

### Definition

Overfitting occurs when a model learns the training data _too well_, memorizing not just the underlying patterns but also the random noise and outliers. While it performs exceptionally well on the training data, it fails to generalize, performing poorly on unseen validation/test data.

### Principle & Causes

- **High Variance:** The model is highly sensitive to the specific fluctuations in the training set.
- **Causes:**
  - The model is too complex (too many parameters/layers relative to the dataset size).
  - The dataset is too small or contains too much noise.
  - The model was trained for too many epochs without early stopping.

### How to Fix

- **Get more data:** The more data, the harder it is for the model to memorize noise.
- **Data Augmentation:** Artificially expand the training set.
- **Reduce model complexity:** Prune trees, use fewer layers/parameters.
- **Apply Regularization:** Use techniques like **L1/L2 Regularization** or **Dropout** to penalize complexity.
- **Cross-Validation & Early Stopping:** Monitor validation loss and stop training when it begins to diverge from training loss.
